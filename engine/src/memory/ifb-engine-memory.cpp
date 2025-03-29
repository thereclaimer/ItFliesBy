#pragma once

#include "ifb-engine-memory.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb_engine {

    IFBEngineMemory*  memory_allocate_struct       (IFBMEMStack global_stack_handle);
    IFBMEMReservation memory_reserve_system_memory (IFBMEMStack global_stack_handle);
    IFBVoid           memory_init_stack            (IFBEngineMemory* memory);
    IFBVoid           memory_init_arenas           (IFBEngineMemory* memory);
    IFBVoid           memory_allocate_core         (const IFBEngineMemory* memory);

};

/**********************************************************************************/
/* ENGINE MEMORY                                                                 */
/**********************************************************************************/

ifb_internal IFBEngineMemory* 
ifb_engine::memory_allocate(
    IFBMEMStack global_stack_handle) {

    //allocate manager and reserve system memory
    IFBEngineMemory*  memory             = ifb_engine::memory_allocate_struct       (global_stack_handle);
    IFBMEMReservation system_reservation = ifb_engine::memory_reserve_system_memory (global_stack_handle);

    //set handles
    IFBEngineMemoryHandles* handles = memory->handles; 
    handles->global_stack       = global_stack_handle;
    handles->system_reservation = system_reservation;

    //initialize the manager stack and arenas
    ifb_engine::memory_init_stack  (memory);
    ifb_engine::memory_init_arenas (memory);

    //allocate the engine systems
    ifb_engine::memory_allocate_core(memory);

    //we're done
    return(memory);
}    

inline IFBVoid
ifb_engine::memory_allocate_core(
    const IFBEngineMemory* engine_memory) {

    //arenas
    IFBEngineMemoryArenas* engine_arenas = engine_memory->arenas;

    //get the core stack memory
    IFBEngineCore engine_core;
    ifb_engine::memory_stack_get_core(engine_memory->stack, &engine_core);

    //memory struct for tracking allocations
    IFBMemory memory;

    //graphics memory
    IFBEngineGraphicsManager* graphics_manager = engine_core.graphics;
    IFBMEMArena               graphics_arena   = engine_arenas->array[IFBEngineMemoryArena_Core_ManagerGraphics]; 
    
    const IFBU32  graphics_size_window = ifb_graphics::window_memory_size(ifb_engine::_memory_graphics_sizes.window_title_length); 
    const IFBU32  graphics_data_size  = graphics_size_window; //NOTE(SAM): for now 
    const IFBAddr graphics_data_start = ifb_memory::arena_push_bytes_absolute_address(graphics_arena,graphics_data_size);

    //graphics window
    memory.start                    = graphics_data_start;
    memory.size                     = graphics_size_window; 
    graphics_manager->window_handle = ifb_graphics::window_memory_initialize(memory);
}

/**********************************************************************************/
/* INTERNAL                                                                        */
/**********************************************************************************/

inline IFBEngineMemory* 
ifb_engine::memory_allocate_struct(
    IFBMEMStack global_stack_handle) {

    //push the manager on the stack
    const IFBAddr addr_memory = ifb_memory::stack_push_bytes_absolute_address(
        global_stack_handle,
        ifb_engine::_memory_sizes.total_manager);
    ifb_macro_assert(addr_memory);

    //calculate addresses
    const IFBAddr addr_handles      = addr_memory       + ifb_engine::_memory_sizes.struct_manager;
    const IFBAddr addr_stack_struct = addr_handles      + ifb_engine::_memory_sizes.struct_handles;
    const IFBAddr addr_stack_start  = addr_stack_struct + ifb_engine::_memory_sizes.struct_stack;
    const IFBAddr addr_arenas       = addr_stack_start  + ifb_engine::_memory_sizes.stack;

    //set the pointers
    IFBEngineMemory* memory = (IFBEngineMemory*)addr_memory; 
    memory->handles =  (IFBEngineMemoryHandles*)addr_handles;
    memory->stack   =    (IFBEngineMemoryStack*)addr_stack_struct;
    memory->arenas  =   (IFBEngineMemoryArenas*)addr_arenas;

    //we're done
    return(memory);
}

inline IFBMEMReservation
ifb_engine::memory_reserve_system_memory(
    IFBMEMStack global_stack_handle) {

    //reserve the memory
    IFBMEMReservation system_reservation_handle = ifb_memory::reserve_system_memory(
        global_stack_handle,
        ifb_engine::_memory_sizes.total_reservation,
        ifb_engine::_memory_sizes.total_arena);

    //sanity check
    ifb_macro_assert(system_reservation_handle);

    //we're done
    return(system_reservation_handle);
}

inline IFBVoid
ifb_engine::memory_init_stack(
    IFBEngineMemory* memory) {

    //get the stack
    IFBEngineMemoryStack* stack = memory->stack;

    //calculate the start
    stack->start = ((IFBAddr)stack) + ifb_engine::_memory_sizes.struct_stack;
}

inline IFBVoid
ifb_engine::memory_init_arenas(
    IFBEngineMemory* memory) {

    //get the arenas and reservation handle
    IFBEngineMemoryArenas* arenas      = memory->arenas;
    IFBMEMReservation      reservation = memory->handles->system_reservation;

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
