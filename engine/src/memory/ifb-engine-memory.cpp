#pragma once

#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal-platform.hpp"


inline IFBEngineMemory*
ifb_engine::memory_create(
    const ifb_memory start,
    const ifb_u32    page_size,
    const ifb_u32    page_count) {

    //sanity check
    if (
        start      == NULL ||
        page_size  == 0    ||
        page_count == 0) {

        return(NULL);
    }

    //commit the first page for the memory
    IFBEngineMemory* engine_memory = ifb_engine::platform_memory_pages_commit(start,page_size);
    if (engine_memory != start) {
        return(NULL);
    }
    
    //if that worked, initialized the struct
    engine_memory->page_size        = page_size;
    engine_memory->page_count_total = page_count;
    engine_memory->page_count_used  = 1;    

    return(engine_memory);
}

inline const ifb_memory
ifb_engine::memory_get_pointer(
          IFBEngineMemory* memory_ptr,
    const ifb_u32          page_number,
    const ifb_u32          page_offset) {

    if (!memory_ptr) {
        return(NULL);
    }

    //calculate the pointer offset from the page
    const ifb_size   base_offset = (memory_ptr->page_size * page_number) + page_offset;
    const ifb_memory base_ptr    = (ifb_memory)memory_ptr;
    const ifb_memory ptr         = base_ptr + base_offset;

    return(ptr);
}

inline const ifb_memory
ifb_engine::memory_get_page_pointer(
          IFBEngineMemory* memory_ptr,
    const ifb_u32          page_number) {

    //get the page pointer, with no offset
    const ifb_memory page_ptr = ifb_engine::memory_get_pointer(
        memory_ptr,
        page_number,
        0);

    return(page_ptr);
}

inline const ifb_memory
ifb_engine::memory_get_current_page_pointer(
    IFBEngineMemory* memory_ptr) {

    //get the address of the next unused page
    const ifb_memory page_ptr = 
        memory_ptr 
        ? ifb_engine::memory_get_page_pointer(memory_ptr,memory_ptr->page_count_used)
        : NULL;

    return(page_ptr);
}

inline const ifb_size
ifb_engine::memory_size_page_aligned(
            IFBEngineMemory* memory_ptr,
    const ifb_size           memory_size) {

    const ifb_u32 memory_size_aligned = memory_ptr
        ? ifb_engine_macro_align_a_to_b(memory_size,memory_ref.page_size)
        : 0;
    
    return(memory_size_aligned);
}

inline const ifb_u32
ifb_engine::memory_page_count_aligned(
          IFBEngineMemory* memory_ptr,
    const ifb_size         memory_size) {

    const ifb_u32 memory_size_aligned = ifb_engine::memory_size_page_aligned(
        memory_ptr,
        memory_size);

    const ifb_u32 page_count = memory_ptr
       ? memory_size_aligned / memory_ptr->page_size
       : 0;

    return(page_count);
}

inline const ifb_size
ifb_engine::memory_page_size(
          IFBEngineMemory* memory_ptr,
    const ifb_u32          page_count) {

    const ifb_size memory_size =
        memory_ptr 
            ? memory_ptr->page_size * page_count
            : 0;

    return(memory_size);
}

inline const ifb_b8
ifb_engine::memory_commit_pages(
          IFBEngineMemory* in_memory_ptr,
    const ifb_u32          in_page_count,                
          ifb_u32&        out_page_start_ref) {

    if (!in_memory_ptr) {
        return(false);
    }

    //calculate the commit start and size
    const ifb_u32    commit_page         = in_memory_ptr->page_count_used; 
    const ifb_u32    new_used_page_count = commit_page + in_page_count;
    const ifb_memory commit_start        = ifb_engine::memory_get_current_page_pointer(in_memory_ptr);
    const ifb_size   commit_size         = ifb_engine::memory_page_size(in_memory_ptr,in_page_count); 

    //if we have enough pages available, do the commit
    const ifb_memory commit_result = 
        new_used_page_count > in_memory_ptr->page_count_used
        ? ifb_engine::platform_memory_pages_commit(commit_start,commit_size)
        : NULL;

    //if that worked, update the page count
    const ifb_b8 result = (commit_start == commit_result);
    if (result) {
        in_memory_ptr->page_count_used = new_used_page_count;
    } 

    //we're done
    return(result);
}

const ifb_b8
ifb_engine::memory_commit_size(
          IFBEngineMemory*            in_memory_ptr,
    const ifb_size                    in_memory_size,
          IFBEngineMemoryPageCommit& out_memory_page_commit) {

    //sanity check
    if (
        in_memory_ptr  == NULL ||
        in_memory_size == 0) {
        
        return(false);
    }

    //determine the page count
    out_memory_page_commit.page_count = ifb_engine::memory_page_count_aligned(
        in_memory_ptr,
        in_memory_size);

    //do the commit
    const ifb_b8 result = ifb_engine::memory_commit_pages(
        in_memory_ptr,
        out_memory_page_commit.page_count,        
        out_memory_page_commit.page_start);

    //we're done
    return(result);
}

inline const ifb_memory
ifb_engine::memory_commit_immediate(
          IFBEngineMemory* memory_ptr,
    const ifb_size         memory_size) {

    //sanity check
    if (
        in_memory_ptr  == NULL ||
        in_memory_size == 0) {
        
        return(false);
    }

    //determine the page count
    const ifb_size page_count = ifb_engine::memory_page_count_aligned(
        memory_ptr,
        memory_size);

    //do the commit
    ifb_u32 page_number;
    const ifb_b8 result = ifb_engine::memory_commit_pages(
        memory_ptr,
        page_count,        
        page_number);

    //get the pointer
    const ifb_memory commit_memory = result
        ? ifb_engine::memory_get_page_pointer(memory_ptr,page_number)
        : NULL;

    //we're done
    return(commit_memory);
}