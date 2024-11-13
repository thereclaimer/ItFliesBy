#pragma once

#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal-platform.hpp"

/**********************************************************************************/
/* API                                                                            */
/**********************************************************************************/

ifb_api const ifb_memory
ifb_engine::memory_pointer_from_handle(
    IFBEngineMemoryHandle& memory_handle_ref) {

    //calculate the pointer offset from the pag
    const ifb_u32    page_size   = ifb_engine::context_memory_page_size();
    const ifb_size   base_offset = (page_size * memory_handle_ref.page_start) + memory_handle_ref.page_offset;
    const ifb_memory ptr         = ifb_engine::context_base_pointer() + base_offset;

    return(ptr);
}

ifb_api const ifb_memory
ifb_engine::memory_pointer_from_page(
    const ifb_u32 page_number) {

    const ifb_u32    page_size   = ifb_engine::context_memory_page_size();
    const ifb_u32    offset      = page_size * page_number;
    const ifb_memory context_ptr = ifb_engine::context_base_pointer();  
    const ifb_memory page_ptr    = context_ptr + offset;  

    return(page_ptr);
}

ifb_api const ifb_memory
ifb_engine::memory_pointer_from_current_page(
    ifb_void) {

    //get the address of the next unused page
    const ifb_u32    page_number = ifb_engine::context_memory_page_count_used();
    const ifb_memory page_ptr    = ifb_engine::memory_pointer_from_page(page_number);

    return(page_ptr);
}

ifb_api const ifb_u32
ifb_engine::memory_size_page_aligned(
    const ifb_u32 size) {

    const ifb_u32 page_size    = ifb_engine::context_memory_page_size();
    const ifb_u32 size_aligned = ifb_engine_macro_align_a_to_b(size,page_size);

    return(size_aligned);
}

ifb_api const ifb_u32
ifb_engine::memory_page_count(
    const ifb_u32 size) {

    const ifb_u32 size_aligned = ifb_engine::memory_size_page_aligned(size);
    const ifb_u32 page_size    = ifb_engine::context_memory_page_size();
    const ifb_u32 page_count   = size_aligned / page_size; 

    return(page_count);
}

ifb_api const ifb_u32
ifb_engine::memory_page_size(
    const ifb_u32 page_count) {

    const ifb_size memory_size =
        ifb_engine::context_initialized() 
            ? ifb_engine::context_memory_page_size() * page_count
            : 0;

    return(memory_size);
}

ifb_api const ifb_memory
ifb_engine::memory_commit_pages(
    const ifb_u32                 in_commit_page_count, 
          IFBEngineMemoryCommit& out_commit_ref) {

    //calculate the commit start and size
    const ifb_memory commit_start        = ifb_engine::memory_pointer_from_current_page();
    const ifb_size   commit_size         = ifb_engine::memory_page_size(in_context,in_page_count); 

    //if we have enough pages available, do the commit
    const ifb_memory commit_result = 
        new_used_page_count > in_context->memory.page_count_used
        ? ifb_engine::platform_memory_pages_commit(commit_start,commit_size)
        : NULL;

    if (commit_result) {
        in_context->memory.page_count_used = new_used_page_count;
    } 

    //we're done
    return(commit_result);
}

ifb_api const ifb_b8
ifb_engine::memory_commit_size(
    const ifb_u32                 in_commit_size_minimum,
          IFBEngineMemoryCommit& out_commit_ref) {

    //determine the page count
    out_commit_ref.page_count = ifb_engine::memory_page_count(in_commit_size_minimum);

    //do the commit
    out_memory_page_commit.memory_start = ifb_engine::memory_commit_pages(
        out_memory_page_commit.page_count,        
        out_memory_page_commit.page_start);

    const ifb_b8 result = out_memory_page_commit.memory_start != NULL;

    //we're done
    return(result);
}
