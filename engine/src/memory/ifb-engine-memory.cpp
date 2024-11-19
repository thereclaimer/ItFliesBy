#pragma once

#include "ifb-engine-internal.hpp"
#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal-platform.hpp"

#include "ifb-engine-memory-manager.cpp"
#include "ifb-engine-memory-arena.cpp"

/**********************************************************************************/
/* API                                                                            */
/**********************************************************************************/

ifb_api const ifb_memory 
ifb_engine::memory_pointer_from_page_offset(
    const ifb_u32 page_number,
    const ifb_u32 page_offset) {

    const ifb_u32 page_size   = ifb_engine::context_platform_page_size();
    const ifb_u32 page_start  = page_number * page_size;
    const ifb_u32 base_offset = page_start + page_offset;     

    const ifb_memory base_pointer   = ifb_engine::context_base_pointer();
    const ifb_memory memory_pointer = base_pointer + base_offset;

    return(memory_pointer); 
}

ifb_api const ifb_memory 
ifb_engine::memory_pointer_from_page(
    const ifb_u32 page_number) {
    
    const ifb_u32 page_size   = ifb_engine::context_platform_page_size();
    const ifb_u32 page_start  = page_number * page_size;

    const ifb_memory base_pointer   = ifb_engine::context_base_pointer();
    const ifb_memory memory_pointer = base_pointer + page_start;

    return(memory_pointer);
}

ifb_api const ifb_memory 
ifb_engine::memory_pointer_from_handle(
    const ifb_u32 handle) {
    
    const ifb_memory base_pointer   = ifb_engine::context_base_pointer();
    const ifb_memory memory_pointer = base_pointer + handle; 

    return(memory_pointer);
}

ifb_api const ifb_u32 
ifb_engine::memory_handle(
    const ifb_u32 page_number,
    const ifb_u32 page_offset) {
    
    const ifb_u32 page_size  = ifb_engine::context_platform_page_size();
    const ifb_u32 page_start = page_number * page_size;
    const ifb_u32 handle     = page_start + page_offset;     

    return(handle);
}

ifb_api const ifb_b8
ifb_engine::memory_handle_valid(
    const ifb_u32 memory_handle) {
    
    //TODO(SAM): should also have a upper bound
    return(memory_handle > IFB_ENGINE_MEMORY_HANDLE_INVALID);
}

ifb_api const ifb_u32 
ifb_engine::memory_size_page_aligned(
    const ifb_u32 size) {

    const ifb_u32 page_size    = ifb_engine::context_platform_page_size();
    const ifb_u32 size_aligned = ifb_macro_align_a_to_b(size,page_size);    

    return(size_aligned);
}

ifb_api const ifb_u32 
ifb_engine::memory_page_count(
    const ifb_u32 size) {

    const ifb_u32 page_size    = ifb_engine::context_platform_page_size();
    const ifb_u32 size_aligned = ifb_macro_align_a_to_b(size,page_size);    
    const ifb_u32 page_count   = size_aligned / page_size;  

    return(page_count);
}

ifb_api const ifb_u32 
ifb_engine::memory_page_size(
    const ifb_u32 page_count) {

    const ifb_u32 page_size       = ifb_engine::context_platform_page_size();
    const ifb_u32 page_size_count = page_count * page_size;  

    return(page_size_count);
}

ifb_api const ifb_u32 
ifb_engine::memory_page_commit(
    const ifb_u32 page_count) {

    //calculate page sizes
    const ifb_u32 page_size       = ifb_engine::context_platform_page_size();
    const ifb_u32 page_current    = ifb_engine::context_platform_page_count_used();
    const ifb_u32 page_start      = page_current * page_size;

    //calculate commit    
    const ifb_memory base_pointer = ifb_engine::context_base_pointer();
    const ifb_memory commit_start = base_pointer + page_start;
    const ifb_size   commit_size  = page_size * page_count;

    //do the commit
    const ifb_memory commit_result = ifb_engine::platform_memory_pages_commit(commit_start,commit_size);

    //if that failed, we're done
    if (commit_start != commit_result) {
        return(0);
    } 

    //otherwise, update the context
    const ifb_u32 page_count_new = page_current + page_count;
    ifb_engine::context_platform_page_count_used_update(page_count_new);

    //we're done, return the page start
    return(page_current);
}