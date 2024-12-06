#pragma once

#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal-platform.hpp"

inline ifb_void 
ifb_engine::memory_reserve(
          IFBEngineMemory* ptr_memory,
    const ifb_size         reservation_size_minimum) {

    //get the system info
    ptr_memory->system_page_size              = ifb_engine::platform_system_page_size();
    ptr_memory->system_allocation_granularity = ifb_engine::platform_system_allocation_granularity();
    ifb_macro_assert(ptr_memory->system_page_size);
    ifb_macro_assert(ptr_memory->system_allocation_granularity);

    //get the reservation size and page count
    const ifb_size reservation_size = ifb_engine::memory_align_size_to_granularity(reservation_size);
    ptr_memory->page_count_total = reservation_size / ptr_memory->system_page_size;

    //make the reservation
    const ifb_ptr ptr_reservation = ifb_engine::platform_memory_reserve(reservation_size);    
    ifb_macro_assert(ptr_reservation);
    ptr_memory->reservation_start = (ifb_address)ptr_reservation;
}

inline const IFBMemoryCommitId 
ifb_engine::memory_commit(
          IFBEngineMemory* ptr_memory, 
    const ifb_u32          commit_size_minimum) {


    //page align the commit size
    const ifb_u32 commit_size = ifb_engine::memory_align_size_to_page(ptr_memory); 
}

inline const ifb_u32 
ifb_engine::memory_get_commit_size(
    const IFBEngineMemory*  ptr_memory,
    const IFBMemoryCommitId commit_id) {

}

inline const ifb_u32 
ifb_engine::memory_get_commit_page_number(
    const IFBEngineMemory*  ptr_memory,
    const IFBMemoryCommitId commit_id) {

}

inline const ifb_u32 
ifb_engine::memory_get_commit_page_count(
    const IFBEngineMemory*  ptr_memory,
    const IFBMemoryCommitId commit_id) {

}

inline const ifb_ptr 
ifb_engine::memory_get_pointer(
    const IFBEngineMemory*  ptr_memory,
    const IFBMemoryCommitId commit_id) {

}

inline const ifb_ptr 
ifb_engine::memory_get_pointer(
    const IFBEngineMemory*  ptr_memory,
    const IFBMemoryCommitId commit_id,
    const ifb_u32           commit_offset) {

}

inline const ifb_u32 
ifb_engine::memory_align_size_to_page(
    const IFBEngineMemory* ptr_memory) {

}

inline const ifb_u32 
ifb_engine::memory_align_size_to_page(
    const IFBEngineMemory* ptr_memory) {

}
