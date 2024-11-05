#pragma once

#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal-platform.hpp"

inline const ifb_b8
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

inline const ifb_b8
ifb_engine::memory_manager_shut_down(
    IFBEngineMemoryManager& memory_manager_ref) {

    //release the memory
    const ifb_b8 result = ifb_engine::memory_release(memory_manager_ref.reservation);

    return(result);
}

inline const ifb_b8 
ifb_engine::memory_manager_page_commit(
          IFBEngineMemoryManager& memory_manager_ref,
    const ifb_size                page_start,
    const ifb_size                page_count) {

    //get the page start
    const ifb_memory page_start_pointer = ifb_engine::memory_reservation_page_start_pointer(
        memory_manager_ref.reservation,
        page_start);

    //get the total size of the pages
    const ifb_size pages_size = ifb_engine::memory_reservation_page_count_aligned(
        memory_manager_ref.reservation,
        page_count);

    //commit the pages
    const ifb_memory commit = ifb_engine::platform_memory_pages_commit(
        page_start_pointer,
        pages_size);

    //we're done
    //we succeeded if the commit is the same as the page start
    return(commit == page_start_pointer);
}

inline const ifb_b8 
ifb_engine::memory_manager_page_decommit(
          IFBEngineMemoryManager& memory_manager_ref,
    const ifb_size                page_start,
    const ifb_size                page_count) {

    //get the page start
    const ifb_memory page_start_pointer = ifb_engine::memory_reservation_page_start_pointer(
        memory_manager_ref.reservation,
        page_start);

    //get the total size of the pages
    const ifb_size pages_size = ifb_engine::memory_reservation_page_count_aligned(
        memory_manager_ref.reservation,
        page_count);

    //decommit the pages
    const ifb_b8 decommit_result = ifb_engine::platform_memory_pages_decommit(
        page_start_pointer,
        pages_size);

    //we're done
    return(decommit_result);

}