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

inline const IFBCommitId 
ifb_engine::memory_commit(
          IFBEngineMemory* ptr_memory, 
    const ifb_u32          commit_size_minimum) {

    ifb_macro_assert(ptr_memory->commit_count_current != ptr_memory->commit_count_max);

    //page align the commit size
    const ifb_u32 page_size         = ptr_memory->system_page_size;
    const ifb_u32 commit_size       = ifb_engine::memory_align_size_to_page(ptr_memory); 
    const ifb_u32 commit_page_count = commit_size / page_size; 

    //get the next commit id
    IFBCommitId commit_id;
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
    ref_new_commit.page_count       = commit_page_count;
    ref_new_commit.page_start       = commit_page_start;

    //update the commit count
    ++ptr_memory->commit_count_current;

    //we're done
    return(commit_id);
}

inline const ifb_u32 
ifb_engine::memory_get_commit_page_number(
    const IFBEngineMemory* ptr_memory,
    const IFBCommitId      commit_id) {

    //get the commit array
    const IFBCommit* commit_array_ptr = ifb_engine::memory_get_commit_array_pointer(ptr_memory);

    //get the commit page number
    const ifb_u32 commit_page_number = commit_array_ptr[commit_id.index].page_start; 

    //we're done
    return(commit_page_number)
}

inline const ifb_u32 
ifb_engine::memory_get_commit_page_count(
    const IFBEngineMemory* ptr_memory,
    const IFBCommitId      commit_id) {

    //get the commit array
    const IFBCommit* commit_array_ptr = ifb_engine::memory_get_commit_array_pointer(ptr_memory);

    //get the commit page count
    const ifb_u32 commit_page_count = commit_array_ptr[commit_id.index].page_count; 

    //we're done
    return(commit_page_count);
}

inline const ifb_u32 
ifb_engine::memory_get_commit_size(
    const IFBEngineMemory* ptr_memory,
    const IFBCommitId      commit_id) {

    //get the page count
    const ifb_u32 commit_page_count = ifb_engine::memory_get_commit_page_count(
        ptr_memory,
        commit_id);
    
    //get the commit size
    const ifb_u32 commit_size = commit_page_count * ptr_memory->system_page_size;

    //we're done
    return(commit_size);
}

inline const ifb_u32 
ifb_engine::memory_get_commit_offset(
    const IFBEngineMemory* ptr_memory,
    const IFBCommitId      commit_id) {

    //get the page start
    const ifb_u32 page_start = ifb_engine::memory_get_commit_page_number(
        ptr_memory,
        commit_id);

    //get the page offset
    const ifb_u32 commit_offset = page_start * ptr_memory->system_page_size;

    //we're done
    return(commit_offset);
}

inline const ifb_address
ifb_engine::memory_get_commit_address(
    const IFBEngineMemory* ptr_memory,
    const IFBCommitId      commit_id) {

    //cache the reservation start
    const ifb_address reservation_start = ptr_memory->reservation_start;

    //get the commit offset
    const ifb_u32 commit_offset = ifb_engine::memory_get_commit_offset(
        ptr_memory,
        commit_id);

    //calculate the commit starting address
    const ifb_address commit_start_address = reservation_start + commit_offset;

    //we're done
    return(commit_start_address);
}

inline const ifb_ptr 
ifb_engine::memory_get_commit_pointer(
    const IFBEngineMemory* ptr_memory,
    const IFBCommitId      commit_id) {

    //get the commit address
    const ifb_address commit_address = ifb_engine::memory_get_commit_address(
        ptr_memory,
        commit_id);

    //cast the address to a pointer
    const ifb_ptr commit_pointer = (ifb_ptr)commit_address;

    //we're done
    return(commit_pointer);
}

inline const ifb_ptr 
ifb_engine::memory_get_commit_pointer(
    const IFBEngineMemory* ptr_memory,
    const IFBCommitId      commit_id,
    const ifb_u32          commit_offset) {

    //get the commit address
    const ifb_address commit_address = ifb_engine::memory_get_commit_address(
        ptr_memory,
        commit_id);

    //get the commit size
    const ifb_u32 commit_size = ifb_engine::memory_get_commit_size(
        ptr_memory,
        commit_id);

    //sanity check, make sure the offset is inside the arena
    ifb_macro_assert(commit_offset < commit_size);

    //add the offset to the commit
    const ifb_address commit_offset_address = commit_address + commit_offset;

    //cast that to a pointer
    const ifb_ptr commit_offset_pointer = (ifb_ptr)commit_offset_address;

    //we're done
    return(commit_offset_pointer);
}

inline const ifb_u32 
ifb_engine::memory_align_size_to_page(
    const IFBEngineMemory* ptr_memory,
    const ifb_size         size) {

    //align the size to a page
    const ifb_u32 size_page_aligned = ifb_macro_align_a_to_b(
        size,
        ptr_memory->system_page_size);

    //we're done
    return(size_page_aligned);
}

inline const ifb_size 
ifb_engine::memory_align_size_to_granularity(
    const IFBEngineMemory* ptr_memory,
    const ifb_size         size) {

    //align the size to system granularity
    const ifb_u32 size_granularity_aligned = ifb_macro_align_a_to_b(
        size,
        ptr_memory->system_page_size);

    //we're done
    return(size_granularity_aligned);
}

inline const IFBCommit* 
ifb_engine::memory_get_commit_array_pointer(
    const IFBEngineMemory* ptr_memory) {

    IFBCommit* commit_array_ptr = (IFBCommit*)ifb_engine::global_stack_get_pointer(ptr_memory->global_handle_commit_array);

    return(commit_array_ptr);
}
