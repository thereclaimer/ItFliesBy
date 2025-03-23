#pragma once

#include "ifb-memory.hpp"
#include "ifb-memory-manager-init.cpp"

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
    init.args.stack_start      = memory_manager->handle_stack;
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
    memory_manager->handle_manager = init.manager_handle;
    const IFBB8 result             = init.result ? true : false;

    //we're done
    return(result);
}

const IFBB8      
ifb_memory::manager_destroy(
    const IFBMemoryManager* memory_manager) {

    return(false);
}
