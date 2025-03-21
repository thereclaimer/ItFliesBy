#pragma once

#include "ifb-memory.hpp"

#include "ifb-memory-manager-internal.cpp"

/**********************************************************************************/
/* MEMORY MANAGER                                                                 */
/**********************************************************************************/

IFBMemoryManager*
ifb_memory::manager_create(
    IFBMemoryManagerArgs* args) {

    //init struct
    IFBMemoryManagerInit init;
    init.result = true;
    init.args   = args;

    //initialize the memory manager
    manager_init_step_0_validate_args         (init);
    manager_init_step_1_get_system_info       (init);
    manager_init_step_3_calculate_sizes       (init);
    manager_init_step_2_allocate_manager      (init);
    manager_init_step_4_reserve_system_memory (init);
    manager_init_step_5_set_properties        (init);
    manager_init_step_6_cleanup               (init);

    //get the result
    IFBMemoryManager* result = init.result
        ? init.manager
        : NULL;

    //we're done
    return(result);
}

const IFBB8      
ifb_memory::manager_destroy(
    IFBMemoryManager* memory_manager) {

    return(false);
}
