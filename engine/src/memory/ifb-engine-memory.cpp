#pragma once

#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal-platform.hpp"

inline const ifb_memory
ifb_engine::memory_get_pointer(
          IFBEngineContext* context,
    const ifb_u32           page_number,
    const ifb_u32           page_offset) {

    if (!context) {
        return(NULL);
    }

    //calculate the pointer offset from the page
    const ifb_size   base_offset = (context->memory.page_size * page_number) + page_offset;
    const ifb_memory base_ptr    = (ifb_memory)context;
    const ifb_memory ptr         = base_ptr + base_offset;

    return(ptr);
}

inline const ifb_memory
ifb_engine::memory_get_page_pointer(
          IFBEngineContext* context,
    const ifb_u32           page_number) {

    //get the page pointer, with no offset
    const ifb_memory page_ptr = ifb_engine::memory_get_pointer(
        context,
        page_number,
        0);

    return(page_ptr);
}

inline const ifb_memory
ifb_engine::memory_get_current_page_pointer(
    IFBEngineContext* context) {

    //get the address of the next unused page
    const ifb_memory page_ptr = 
        context
        ? ifb_engine::memory_get_page_pointer(context,context->memory.page_count_used)
        : NULL;

    return(page_ptr);
}

inline const ifb_u32
ifb_engine::memory_size_page_aligned(
          IFBEngineContext* context,
    const ifb_u32           memory_size) {

    const ifb_u32 memory_size_aligned = context
        ? ifb_engine_macro_align_a_to_b(memory_size,context->memory.page_size)
        : 0;
    
    return(memory_size_aligned);
}

inline const ifb_u32
ifb_engine::memory_page_count_aligned(
          IFBEngineContext* context,
    const ifb_size          memory_size) {

    const ifb_u32 memory_size_aligned = ifb_engine::memory_size_page_aligned(
        context,
        memory_size);

    const ifb_u32 page_count = context
       ? memory_size_aligned / context->memory.page_size
       : 0;

    return(page_count);
}

inline const ifb_size
ifb_engine::memory_page_size(
          IFBEngineContext* context,
    const ifb_u32           page_count) {

    const ifb_size memory_size =
        context 
            ? context->memory.page_size * page_count
            : 0;

    return(memory_size);
}

inline const ifb_memory
ifb_engine::memory_commit_pages(
          IFBEngineContext* in_context,
    const ifb_u32           in_page_count,                
          ifb_u32&         out_page_start_ref) {

    if (!in_context) {
        return(false);
    }

    //calculate the commit start and size
    const ifb_u32    commit_page         = in_context->memory.page_count_used; 
    const ifb_u32    new_used_page_count = commit_page + in_page_count;
    const ifb_memory commit_start        = ifb_engine::memory_get_current_page_pointer(in_context);
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

const ifb_b8
ifb_engine::memory_commit_size(
          IFBEngineContext*           in_context,
    const ifb_size                    in_memory_size,
          IFBEngineMemoryPageCommit& out_memory_page_commit) {

    //sanity check
    if (
        in_context     == NULL ||
        in_memory_size == 0) {
        
        return(false);
    }

    //determine the page count
    out_memory_page_commit.page_count = ifb_engine::memory_page_count_aligned(
        in_context,
        in_memory_size);

    //do the commit
    out_memory_page_commit.memory_start = ifb_engine::memory_commit_pages(
        in_context,
        out_memory_page_commit.page_count,        
        out_memory_page_commit.page_start);

    const ifb_b8 result = out_memory_page_commit.memory_start != NULL;

    //we're done
    return(result);
}

inline const ifb_memory
ifb_engine::memory_commit_immediate(
          IFBEngineContext* context,
    const ifb_size          memory_size) {

    //sanity check
    if (
        context     == NULL ||
        memory_size == 0) {
        
        return(false);
    }

    //determine the page count
    const ifb_size page_count = ifb_engine::memory_page_count_aligned(
        context,
        memory_size);

    //do the commit
    ifb_u32 page_number;
    const ifb_memory commit_memory = ifb_engine::memory_commit_pages(
        context,
        page_count,        
        page_number);

    //we're done
    return(commit_memory);
}