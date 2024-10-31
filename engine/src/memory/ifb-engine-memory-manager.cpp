#pragma once

#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal-platform.hpp"


ifb_internal const ifb_b8
ifb_engine::memory_manager_start_up(
    IFBEngineMemoryManager& memory_manager_ref) {

    ifb_b8 result = true;

    //get platform memory info
    memory_manager_ref.platform_info.page_size              = ifb_engine::platform_system_page_size();
    memory_manager_ref.platform_info.allocation_granularity = ifb_engine::platform_system_allocation_granularity();

    //get the reservation
    result &= ifb_engine::memory_reserve(memory_manager_ref.reservation);

    //initialize the tables
    memory_manager_ref.arena_tables.header = {0};
    memory_manager_ref.arena_tables.detail = {0};

    //we're done
    return(result);
}

ifb_internal const ifb_b8
ifb_engine::memory_manager_shut_down(
    IFBEngineMemoryManager& memory_manager_ref) {

    //release the memory
    const ifb_b8 result = ifb_engine::memory_release(memory_manager_ref.reservation);

    return(result);
}