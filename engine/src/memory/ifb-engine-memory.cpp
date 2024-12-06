#pragma once

#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal-platform.hpp"

inline ifb_void 
ifb_engine::memory_reserve(
          IFBEngineMemory* ptr_memory,
    const ifb_size         reservation_size_minimum,
    const ifb_size         commit_count_maximum) {

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

    //set the commit count
    ptr_memory->commit_count_max = commit_count_maximum;
}

inline const IFBMemoryCommitId 
ifb_engine::memory_commit(
          IFBEngineMemory* ptr_memory, 
    const ifb_u32          commit_size_minimum) {

    ifb_macro_assert(ptr_memory->commit_count_current != ptr_memory->commit_count_max);

    //page align the commit size
    const ifb_u32 page_size         = ptr_memory->system_page_size;
    const ifb_u32 commit_size       = ifb_engine::memory_align_size_to_page(ptr_memory); 
    const ifb_u32 commit_page_count = commit_size / page_size; 

    //get the next commit id
    IFBMemoryCommitId commit_id;
    commit_id.index = ptr_memory->commit_count_current;

    //get the start for the commit
    const ifb_u32     commit_offset        = ifb_engine::memory_get_size_committed(ptr_memory);
    const ifb_u32     commit_page_start    = commit_offset / page_size;
    const ifb_address commit_start_address = commit_offset + ptr_memory->reservation_start;
    const ifb_ptr     commit_start_pointer = (ifb_ptr)commit_start_address;    

    //do the commit
    const ifb_ptr commit_result_pointer = ifb_engine::platform_memory_commit(commit_start, commit_size);
    ifb_macro_assert(commit_start_pointer == commit_result_pointer);

    //update the commit array
    IFBMemory* commit_array_pointer = ifb_engine::memory_get_commit_array_pointer(ptr_memory);
    IFBMemory& ref_new_commit       = commit_array_pointer[commit_id.index];
    ref_new_commit.page_count = commit_page_count;
    ref_new_commit.page_start = commit_page_start;

    //update the commit count
    ++ptr_memory->commit_count_current;

    //we're done
    return(commit_id);
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
