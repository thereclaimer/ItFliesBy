#pragma once

#include "ifb-memory.hpp"
#include "ifb-memory-manager-init.cpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBMemoryManagerArrays {
    IFBAddr* arena_start;
    IFBU32*  arena_position;
};

namespace ifb_memory {

    IFBVoid                   manager_assert_valid              (IFBMemoryManagerInternal* memory_manager);
    IFBMemoryManagerInternal* manager_load                      (const IFBAddr stack_handle, const IFBU32 manager_offset);
    IFBAddr*                  manager_load_array_arena_start    (IFBMemoryManagerInternal* memory_manager);
    IFBU32*                   manager_load_array_arena_position (IFBMemoryManagerInternal* memory_manager);
    IFBVoid                   manager_load_arrays               (IFBMemoryManagerInternal* memory_manager, IFBMemoryManagerArrays* arrays);
};

/**********************************************************************************/
/* MEMORY MANAGER                                                                 */
/**********************************************************************************/

const IFBB8
ifb_memory::manager_create(
          IFBMemoryManager* memory_manager,
    const IFBU64            size_reservation,
    const IFBU32            size_arena) {

    //sanity check
    ifb_macro_assert(memory_manager);

    //init struct
    IFBMemoryManagerInit init;
    init.args.stack_start      = memory_manager->stack;
    init.args.size_reservation = size_reservation;
    init.args.size_arena       = size_arena;

    //initialize the memory manager
    ifb_memory::manager_init_step_0_validate_args         (init);
    ifb_memory::manager_init_step_1_get_system_info       (init);
    ifb_memory::manager_init_step_3_calculate_sizes       (init);
    ifb_memory::manager_init_step_2_allocate_manager      (init);
    ifb_memory::manager_init_step_4_reserve_system_memory (init);
    ifb_memory::manager_init_step_5_set_properties        (init);
    ifb_memory::manager_init_step_6_cleanup               (init);

    //get the handle and result
    memory_manager->manager_id = init.manager_handle;
    const IFBB8 result         = init.result ? true : false;

    //we're done
    return(result);
}

const IFBB8      
ifb_memory::manager_destroy(
    const IFBMemoryManager* memory_manager) {

    return(false);
}

inline IFBMemoryManagerInternal*
ifb_memory::manager_load(
    const IFBAddr handle_stack,
    const IFBU32  handle_manager) {

    //get the memory manager
    IFBMemoryManagerInternal* memory_manager = (IFBMemoryManagerInternal*)ifb_memory::stack_get_pointer(
        handle_stack,
        handle_manager);

    return(memory_manager);
}

inline IFBAddr*
ifb_memory::manager_load_array_arena_start(
    IFBMemoryManagerInternal* memory_manager) {

    const IFBU32  offset  = memory_manager->offset_arena_array_start;
    const IFBAddr start   = (IFBAddr)memory_manager;
    const IFBAddr address = start + offset;
    IFBAddr*      pointer = (IFBAddr*)address;
    
    return(pointer); 
}

inline IFBU32* 
ifb_memory::manager_load_array_arena_position(
    IFBMemoryManagerInternal* memory_manager) {

    const IFBU32  offset  = memory_manager->offset_arena_array_position;
    const IFBAddr start   = (IFBAddr)memory_manager;
    const IFBAddr address = start + offset;
    IFBAddr*      pointer = (IFBAddr*)address;
}

inline IFBVoid
ifb_memory::manager_load_arrays(
    IFBMemoryManagerInternal* memory_manager,
    IFBMemoryManagerArrays*   arrays) {

    ifb_macro_assert(memory_manager);
    ifb_macro_assert(arrays);

    const IFBAddr start    = (IFBAddr)memory_manager;
    arrays->arena_start    = (IFBAddr*)(start + memory_manager->offset_arena_array_start);
    arrays->arena_position =  (IFBU32*)(start + memory_manager->offset_arena_array_position);
}
