#pragma once

#include "ifb-engine-memory.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb_engine {

    IFBEngineMemory*  memory_initialize            (IFBMEMStack global_stack_handle);
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
    const IFBMemory& stack_memory) {

    //create stack handle 
    IFBMEMStack memory_handle_global_stack = ifb_memory::stack_create(stack_memory);

    //initialize the engine memory
    IFBEngineMemory* engine_memory = ifb_engine::memory_initialize(memory_handle_global_stack);

    //allocate engine systems
    ifb_engine::memory_allocate_core(engine_memory);

    //we're done
    return(engine_memory);
}    

inline IFBVoid
ifb_engine::memory_allocate_core(
    const IFBEngineMemory* engine_memory) {

    //get the core stack memory
    IFBEngineCore engine_core;
    ifb_engine::memory_stack_get_core(engine_memory, &engine_core);

    //memory struct for tracking allocations
    IFBMemory memory;

    //graphics memory
    IFBEngineGraphicsManager* graphics_manager = engine_core.graphics;
    IFBMEMArena               graphics_arena   = engine_memory->reservation.arena_handle_array[IFBEngineArena_Core_ManagerGraphics]; 
    
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
ifb_engine::memory_initialize(
    IFBMEMStack global_stack_handle) {

    //memory sizes
    const IFBU32  memory_size_total        = ifb_engine::_global_memory_sizes.total_memory;
    const IFBU32  memory_size_struct       = ifb_engine::_global_memory_sizes.memory_struct;
    const IFBU16  memory_size_engine_stack = ifb_engine::_global_memory_sizes.engine_stack_64k;
    const IFBU64  memory_size_reservation  = ifb_engine::_global_memory_sizes.total_reservation;
    const IFBU32  memory_size_arena        = ifb_engine::_global_memory_sizes.total_arena;

    //allocate stack memory
    const IFBAddr memory_start = ifb_memory::stack_push_bytes_absolute_address(
        global_stack_handle,
        memory_size_total);
    
    //cast pointer
    IFBEngineMemory* engine_memory = (IFBEngineMemory*)memory_start;
    
    //initialize stack
    engine_memory->stack.global_stack_handle     = global_stack_handle;
    engine_memory->stack.stack_memory_64k.start  = memory_start + memory_size_struct; 
    engine_memory->stack.stack_memory_64k.stride = memory_size_engine_stack / IFBEngineStackOffset_Count;

    //reserve system memory
    engine_memory->reservation.system_reservation_handle = ifb_memory::reserve_system_memory(
        global_stack_handle,
        memory_size_reservation,
        memory_size_arena);

    //commit arenas
    IFBMEMArena* arena_handle_array = engine_memory->reservation.arena_handle_array;
    for (
        IFBU32 index = 0;
               index < IFBEngineArena_Count;
             ++index) {

        arena_handle_array[index] = ifb_memory::arena_commit(engine_memory->reservation.system_reservation_handle);
    }

    //we're done
    return(engine_memory);
}
