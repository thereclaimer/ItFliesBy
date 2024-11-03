#pragma once

#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal-platform.hpp"

ifb_internal const ifb_b8
ifb_engine::memory_manager_start_up(
    IFBEngineMemoryManager& memory_manager_ref) {

    ifb_b8 result = true;

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

ifb_internal const ifb_memory 
ifb_engine::memory_manager_page_commit(
          IFBEngineMemoryManager& memory_manager_ref,
    const ifb_size                page_size,
    const ifb_size                page_offset) {

    //calculate the page start
    const ifb_memory page_start = ifb_engine::memory_reservation_get_pointer(
        memory_manager_ref.reservation,
        page_offset); 

    //commit the pages
    const ifb_memory commit_result = ifb_engine::platform_memory_pages_commit(page_start,page_size);

    //we're done
    return(commit_result);
}

ifb_internal const ifb_b8 
ifb_engine::memory_manager_page_decommit(
          IFBEngineMemoryManager& memory_manager_ref,
    const ifb_size                page_size,
    const ifb_size                page_offset) {

    //calculate the page start
    const ifb_memory page_start = ifb_engine::memory_reservation_get_pointer(
        memory_manager_ref.reservation,
        page_offset); 

    //decommit the pages
    const ifb_b8 decommit_result = ifb_engine::platform_memory_pages_decommit(page_start,page_size);

    //we're done
    return(decommit_result);

}