#pragma once

#include "ifb-memory.hpp"

#include "ifb-memory-manager-internal.cpp"

/**********************************************************************************/
/* MEMORY MANAGER                                                                 */
/**********************************************************************************/

const IFBMemoryManagerHandle
ifb_memory::manager_create(
    const IFBMemoryStackStart stack_start,
    const IFBU64              size_reservation,
    const IFBU32              size_arena) {

    //init struct
    IFBMemoryManagerInit init;
    init.args.stack_start      = stack_start;
    init.args.size_reservation = size_reservation;
    init.args.size_arena       = size_arena;

    //initialize the memory manager
    manager_init_step_0_validate_args         (init);
    manager_init_step_1_get_system_info       (init);
    manager_init_step_3_calculate_sizes       (init);
    manager_init_step_2_allocate_manager      (init);
    manager_init_step_4_reserve_system_memory (init);
    manager_init_step_5_set_properties        (init);
    manager_init_step_6_cleanup               (init);

    //get the result
    const IFBMemoryManagerHandle result = init.result
        ? init.manager_handle
        : NULL;

    //we're done
    return(result);
}

const IFBB8      
ifb_memory::manager_destroy(
    const IFBMemoryStackStart    stack_start,
    const IFBMemoryManagerHandle memory_manager_handle) {

    return(false);
}
