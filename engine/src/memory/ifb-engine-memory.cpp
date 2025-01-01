#pragma once

#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal-platform.hpp"

inline ifb_void 
ifb_engine::memory_reserve(
          IFBEngineMemory* memory_ptr,
    const ifb_size         reservation_size_minimum,
    const ifb_u32          commit_count_maximum) {

    //get the system info
    memory_ptr->system_info.page_size              = ifb_engine::platform_system_page_size();
    memory_ptr->system_info.allocation_granularity = ifb_engine::platform_system_allocation_granularity();
    ifb_macro_assert(memory_ptr->system_info.page_size             );
    ifb_macro_assert(memory_ptr->system_info.allocation_granularity);

    //get the reservation size and page count
    const ifb_size reservation_size = ifb_engine::memory_align_large_size_to_granularity(memory_ptr, reservation_size_minimum);
    memory_ptr->reservation.page_count_total = reservation_size / memory_ptr->system_info.page_size;

    //make the reservation
    const ifb_ptr ptr_reservation = ifb_engine::platform_memory_reserve(reservation_size);    
    ifb_macro_assert(ptr_reservation);
    memory_ptr->reservation.start = (ifb_address)ptr_reservation;

    //set the commit count
    memory_ptr->reservation.commit_count_max = commit_count_maximum;

    //set the global stack size
    memory_ptr->global_stack.size = IFB_ENGINE_CONFIG_GLOBAL_MEMORY_STACK_SIZE;

    //push the commit array on the context stack
    const ifb_u32 commit_array_size = ifb_macro_size_array(IFBCommit,commit_count_maximum);
    ifb_engine::memory_global_push(
        memory_ptr,
        memory_ptr->reservation.commit_array_handle,
        commit_array_size);
}

inline const IFBIDCommit 
ifb_engine::memory_commit(
          IFBEngineMemory* memory_ptr, 
    const ifb_u32          commit_size_minimum) {

    ifb_macro_assert(memory_ptr->reservation.commit_count_current != memory_ptr->reservation.commit_count_max);

    //page align the commit size
    const ifb_u32 page_size         = memory_ptr->system_info.page_size;
    const ifb_u32 commit_size       = ifb_macro_align_a_to_b(commit_size_minimum,page_size); 
    const ifb_u32 commit_page_count = commit_size / page_size; 

    //get the next commit id
    IFBIDCommit commit_id;
    commit_id.index = memory_ptr->reservation.commit_count_current;

    //get the start for the commit
    const ifb_u32     commit_offset        = ifb_engine::memory_get_size_committed(memory_ptr);
    const ifb_u32     commit_page_start    = commit_offset / page_size;
    const ifb_address commit_start_address = commit_offset + memory_ptr->reservation.start;
    const ifb_ptr     commit_start_pointer = (ifb_ptr)commit_start_address;    

    //do the commit
    const ifb_ptr commit_result_pointer = ifb_engine::platform_memory_commit(commit_start_pointer, commit_size);
    ifb_macro_assert(commit_start_pointer == commit_result_pointer);

    //update the commit array
    IFBCommit* commit_array_pointer = ifb_engine::memory_get_commit_array_pointer(memory_ptr);
    IFBCommit& ref_new_commit       = commit_array_pointer[commit_id.index];
    ref_new_commit.page_count       = commit_page_count;
    ref_new_commit.page_start       = commit_page_start;

    //update the commit count
    ++memory_ptr->reservation.commit_count_current;
    memory_ptr->reservation.page_count_committed += commit_page_count;

    //we're done
    return(commit_id);
}

inline const ifb_u32 
ifb_engine::memory_get_page_count(
    const IFBEngineMemory* memory_ptr, 
    const ifb_u32          size) {

    const ifb_u32 size_page_aligned = ifb_macro_align_a_to_b(
        size,
        memory_ptr->system_info.page_size);

    const ifb_u32 page_count = size_page_aligned / memory_ptr->system_info.page_size;

    return(page_count);
}

inline const ifb_u32 
ifb_engine::memory_get_commit_page_number(
    const IFBEngineMemory* memory_ptr,
    const IFBIDCommit      commit_id) {

    //get the commit array
    const IFBCommit* commit_array_ptr = ifb_engine::memory_get_commit_array_pointer(memory_ptr);

    //get the commit page number
    const ifb_u32 commit_page_number = commit_array_ptr[commit_id.index].page_start; 

    //we're done
    return(commit_page_number);
}

inline const ifb_u32 
ifb_engine::memory_get_commit_page_count(
    const IFBEngineMemory* memory_ptr,
    const IFBIDCommit      commit_id) {

    //get the commit array
    const IFBCommit* commit_array_ptr = ifb_engine::memory_get_commit_array_pointer(memory_ptr);

    //get the commit page count
    const ifb_u32 commit_page_count = commit_array_ptr[commit_id.index].page_count; 

    //we're done
    return(commit_page_count);
}

inline const ifb_u32 
ifb_engine::memory_get_commit_size(
    const IFBEngineMemory* memory_ptr,
    const IFBIDCommit      commit_id) {

    //get the page count
    const ifb_u32 commit_page_count = ifb_engine::memory_get_commit_page_count(
        memory_ptr,
        commit_id);
    
    //get the commit size
    const ifb_u32 commit_size = commit_page_count * memory_ptr->system_info.page_size;

    //we're done
    return(commit_size);
}

inline const ifb_u32 
ifb_engine::memory_get_commit_offset(
    const IFBEngineMemory* memory_ptr,
    const IFBIDCommit      commit_id) {

    //get the page start
    const ifb_u32 page_start = ifb_engine::memory_get_commit_page_number(
        memory_ptr,
        commit_id);

    //get the page offset
    const ifb_u32 commit_offset = page_start * memory_ptr->system_info.page_size;

    //we're done
    return(commit_offset);
}

inline const ifb_address
ifb_engine::memory_get_commit_address(
    const IFBEngineMemory* memory_ptr,
    const IFBIDCommit      commit_id) {

    //cache the reservation start
    const ifb_address reservation_start = memory_ptr->reservation.start;

    //get the commit offset
    const ifb_u32 commit_offset = ifb_engine::memory_get_commit_offset(
        memory_ptr,
        commit_id);

    //calculate the commit starting address
    const ifb_address commit_start_address = reservation_start + commit_offset;

    //we're done
    return(commit_start_address);
}

inline const ifb_ptr 
ifb_engine::memory_get_commit_pointer(
    const IFBEngineMemory* memory_ptr,
    const IFBIDCommit      commit_id) {

    //get the commit address
    const ifb_address commit_address = ifb_engine::memory_get_commit_address(
        memory_ptr,
        commit_id);

    //cast the address to a pointer
    const ifb_ptr commit_pointer = (ifb_ptr)commit_address;

    //we're done
    return(commit_pointer);
}

inline const ifb_ptr 
ifb_engine::memory_get_commit_pointer(
    const IFBEngineMemory* memory_ptr,
    const IFBIDCommit      commit_id,
    const ifb_u32          commit_offset) {

    //get the commit address
    const ifb_address commit_address = ifb_engine::memory_get_commit_address(
        memory_ptr,
        commit_id);

    //get the commit size
    const ifb_u32 commit_size = ifb_engine::memory_get_commit_size(
        memory_ptr,
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
    const IFBEngineMemory* memory_ptr,
    const ifb_u32         size) {

    //align the size to a page
    const ifb_u32 size_page_aligned = ifb_macro_align_a_to_b(
        size,
        memory_ptr->system_info.page_size);

    //we're done
    return(size_page_aligned);
}

inline const ifb_u32 
ifb_engine::memory_align_size_to_granularity(
    const IFBEngineMemory* memory_ptr,
    const ifb_u32          size) {

    //align the size to system granularity
    const ifb_u32 size_granularity_aligned = ifb_macro_align_a_to_b(
        size,
        memory_ptr->system_info.allocation_granularity);

    //we're done
    return(size_granularity_aligned);
}

inline const ifb_size
ifb_engine::memory_align_large_size_to_page(
    const IFBEngineMemory* memory_ptr, 
    const ifb_size         size) {

    //align the size to a page
    const ifb_size size_page_aligned = ifb_macro_align_a_to_b(
        size,
        (ifb_size)memory_ptr->system_info.page_size);

    //we're done
    return(size_page_aligned);
}

inline const ifb_size
ifb_engine::memory_align_large_size_to_granularity(
    const IFBEngineMemory* memory_ptr, 
    const ifb_size         size) {
    
    //align the size to system granularity
    const ifb_size size_granularity_aligned = ifb_macro_align_a_to_b(
        size,
        (ifb_size)memory_ptr->system_info.allocation_granularity);

    //we're done
    return(size_granularity_aligned);
}

inline IFBCommit* 
ifb_engine::memory_get_commit_array_pointer(
    const IFBEngineMemory* memory_ptr) {

    IFBCommit* commit_array_ptr = (IFBCommit*)ifb_engine::memory_get_pointer(
        memory_ptr,
        memory_ptr->reservation.commit_array_handle);

    return(commit_array_ptr);
}

inline ifb_void 
ifb_engine::memory_get_handle(
    const IFBEngineMemory* memory_ptr, 
    const IFBIDCommit      commit_id, 
    const ifb_u32          commit_offset, 
          IFBHND&          handle_ref) {

    const ifb_u32 commit_start = ifb_engine::memory_get_commit_offset(
        memory_ptr,
        commit_id);

    handle_ref.offset = commit_start + commit_offset;
}

inline const ifb_ptr 
ifb_engine::memory_get_pointer(
    const IFBEngineMemory* memory_ptr,
    const ifb_u32          offset) {

    const ifb_address start   = memory_ptr->reservation.start + offset;
    const ifb_ptr     pointer = (ifb_ptr)start; 

    return(pointer);
}

inline const ifb_ptr 
ifb_engine::memory_get_pointer(
    const IFBEngineMemory* memory_ptr, 
    const IFBHND&          handle_ref) {

    const ifb_ptr pointer = ifb_engine::memory_get_pointer(memory_ptr,handle_ref.offset);

    return(pointer);
}

inline const ifb_ptr 
ifb_engine::memory_get_pointer(
    const IFBEngineMemory* memory_ptr, 
    const IFBGHND&         global_handle_ref) {

    const ifb_ptr pointer = (ifb_ptr)&memory_ptr->global_stack.memory[global_handle_ref.offset];

    return(pointer);
}

inline const ifb_size 
ifb_engine::memory_get_size_committed(
    const IFBEngineMemory* memory_ptr) {

    const ifb_size count_pages_committed = memory_ptr->reservation.page_count_committed;
    const ifb_size page_size             = memory_ptr->system_info.page_size;
    const ifb_size size_committed        = count_pages_committed * page_size;

    return(size_committed);
}

inline const ifb_void 
ifb_engine::memory_global_push(
          IFBEngineMemory* memory_ptr, 
          IFBGHND&         global_handle_ref, 
    const ifb_u32          size) {

    IFBEngineMemoryGlobalStack& ref_stack = memory_ptr->global_stack;

    const ifb_u32 new_position = ref_stack.position + size;

    ifb_macro_assert(new_position <= ref_stack.size);

    global_handle_ref.offset = ref_stack.position;

    ref_stack.position = new_position;
}

inline const ifb_void 
ifb_engine::memory_global_push_aligned(
          IFBEngineMemory* memory_ptr, 
          IFBGHND&         global_handle_ref, 
    const ifb_u32          size,
    const ifb_u32          alignment) {

    const ifb_u32 size_aligned = ifb_macro_align_a_to_b(size,alignment);

    ifb_engine::memory_global_push(
        memory_ptr,
        global_handle_ref,
        size_aligned);
}