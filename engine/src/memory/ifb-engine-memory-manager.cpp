#pragma once

#include "ifb-engine-memory.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb_engine {

    IFBEngineMemoryManager* memory_manager_allocate              (IFBMEMStack global_stack_handle);
    IFBMEMReservation       memory_manager_reserve_system_memory (IFBMEMStack global_stack_handle);
    IFBVoid                 memory_manager_init_stack            (IFBEngineMemoryManager* memory_manager);
    IFBVoid                 memory_manager_init_arenas           (IFBEngineMemoryManager* memory_manager);
};

/**********************************************************************************/
/* MEMORY MANAGER                                                                 */
/**********************************************************************************/

ifb_internal IFBEngineMemoryManager* 
ifb_engine::memory_manager_create(
    IFBMEMStack global_stack_handle) {

    //allocate manager and reserve system memory
    IFBEngineMemoryManager* memory_manager     = ifb_engine::memory_manager_allocate              (global_stack_handle);
    IFBMEMReservation       system_reservation = ifb_engine::memory_manager_reserve_system_memory (global_stack_handle);

    //set handles
    IFBEngineMemoryHandles* handles = memory_manager->handles; 
    handles->global_stack       = global_stack_handle;
    handles->system_reservation = system_reservation;

    //initialize the manager stack and arenas
    ifb_engine::memory_manager_init_stack  (memory_manager);
    ifb_engine::memory_manager_init_arenas (memory_manager);

    //we're done
    return(memory_manager);
}    

ifb_internal IFBVoid
ifb_engine::memory_manager_allocate_core_systems(
    const IFBEngineMemoryManager* memory_manager) {

    //arenas
    IFBEngineMemoryArenas* engine_arenas = memory_manager->arenas;

    //get the core stack memory
    IFBEngineCore engine_core;
    ifb_engine::memory_stack_get_core(
        memory_manager->stack,
        engine_core);

    //memory struct for tracking allocations
    IFBMemory memory;

    //graphics memory
    IFBEngineGraphicsManager* graphics_manager = engine_core.graphics;
    IFBMEMArena               graphics_arena   = engine_arenas->array[IFBEngineMemoryArena_Core_ManagerGraphics]; 
    const IFBU32  graphics_data_size  = ifb_engine::_memory_graphics_sizes.graphics_manager_total; 
    const IFBAddr graphics_data_start = ifb_memory::arena_push_bytes_absolute_address(graphics_arena,graphics_data_size);

    //graphics window
    memory.start                    = graphics_data_start;
    memory.size                     = ifb_graphics::window_memory_size(ifb_engine::_memory_graphics_sizes.window_title_length); 
    graphics_manager->window_handle = ifb_graphics::window_memory_initialize(memory);
}


/**********************************************************************************/
/* INTERNAL                                                                        */
/**********************************************************************************/

inline IFBEngineMemoryManager* 
ifb_engine::memory_manager_allocate(
    IFBMEMStack global_stack_handle) {

    //push the manager on the stack
    const IFBAddr addr_memory_manager = ifb_memory::stack_push_bytes_absolute_address(
        global_stack_handle,
        ifb_engine::_memory_manager_sizes.total_manager);
    ifb_macro_assert(addr_memory_manager);

    //calculate addresses
    const IFBAddr addr_handles      = addr_memory_manager + ifb_engine::_memory_manager_sizes.struct_manager;
    const IFBAddr addr_stack_struct = addr_handles        + ifb_engine::_memory_manager_sizes.struct_handles;
    const IFBAddr addr_stack_start  = addr_stack_struct   + ifb_engine::_memory_manager_sizes.struct_stack;
    const IFBAddr addr_arenas       = addr_stack_start    + ifb_engine::_memory_manager_sizes.stack;

    //set the pointers
    IFBEngineMemoryManager* memory_manager = (IFBEngineMemoryManager*)addr_memory_manager; 
    memory_manager->handles = (IFBEngineMemoryHandles*)addr_handles;
    memory_manager->stack   =   (IFBEngineMemoryStack*)addr_stack_struct;
    memory_manager->arenas  =  (IFBEngineMemoryArenas*)addr_arenas;

    //we're done
    return(memory_manager);
}

inline IFBMEMReservation
ifb_engine::memory_manager_reserve_system_memory(
    IFBMEMStack global_stack_handle) {

    //reserve the memory
    IFBMEMReservation system_reservation_handle = ifb_memory::reserve_system_memory(
        global_stack_handle,
        ifb_engine::_memory_manager_sizes.total_reservation,
        ifb_engine::_memory_manager_sizes.total_arena);

    //sanity check
    ifb_macro_assert(system_reservation_handle);

    //we're done
    return(system_reservation_handle);
}

inline IFBVoid
ifb_engine::memory_manager_init_stack(
    IFBEngineMemoryManager* memory_manager) {

    //get the stack
    IFBEngineMemoryStack* stack = memory_manager->stack;

    //calculate the start
    stack->start = ((IFBAddr)stack) + ifb_engine::_memory_manager_sizes.struct_stack;
}

inline IFBVoid
ifb_engine::memory_manager_init_arenas(
    IFBEngineMemoryManager* memory_manager) {

    //get the arenas and reservation handle
    IFBEngineMemoryArenas* arenas      = memory_manager->arenas;
    IFBMEMReservation      reservation = memory_manager->handles->system_reservation;

    //get the arena array info
    const IFBU32 arena_count = IFBEngineMemoryArena_Count;
    IFBMEMArena* arena_array = arenas->array;

    //initialize the arenas
    for (
        IFBU32 index = 0;
               index < arena_count;
             ++index) {

        arena_array[index] = ifb_memory::arena_commit(reservation);
    }
}
