#pragma once

#include "ifb-memory-internal.hpp"

/**********************************************************************************/
/* COMMIT                                                                         */
/**********************************************************************************/

ifb_internal IFBMemoryArena*
ifb_memory::arena_commit(
          IFBMemory* memory_ptr,
    const ifb_u32    arena_size_minimum) {

    //sanity check
    ifb_macro_assert(memory_ptr);
    if (arena_size_minimum == 0) return(NULL);

    //allocate the arena structure
    IFBMemoryArena* arena_ptr = ifb_memory::stack_push_arena_base(memory_ptr);
    if (!arena_ptr) return(NULL);

    //commit the pages for the arena
    arena_ptr->page_commit.size = arena_size_minimum;
    const ifb_b8 commit_result = ifb_memory::reservation_page_commit(memory_ptr,arena_ptr->page_commit);

    //this MUST work, or everything is fucked up
    ifb_macro_assert(commit_result);

    //set the arena type
    arena_ptr->type = IFBMemoryArenaType_Base;

    //add the arena to the list
    const ifb_b8 arena_list_result = ifb_memory::arena_list_add(
        memory_ptr->arena_list,
        arena_ptr);

    //again, MUST work
    ifb_macro_assert(arena_list_result);

    //we're done
    return(arena_ptr);
}

/**********************************************************************************/
/* RESET                                                                          */
/**********************************************************************************/

ifb_internal const ifb_b8
ifb_memory::arena_reset(
    IFBMemoryArena* arena_ptr) {

    //sanity check
    ifb_macro_assert(arena_ptr);

    //cache the commit
    IFBMemoryPageCommit& page_commit_ref = arena_ptr->page_commit;

    //get the commit pointer and size 
    const ifb_ptr commit_start = (ifb_ptr)page_commit_ref.start;
    const ifb_u32 commit_size  = page_commit_ref.size; 
    
    //clear the memory
    memset(
        commit_start,
        0,
        commit_size);

    //we're done
    return(true);
}

/**********************************************************************************/
/* POINTERS                                                                       */
/**********************************************************************************/

ifb_internal const ifb_ptr
ifb_memory::arena_get_pointer(
    const IFBMemoryArena* arena_ptr,
    const ifb_u32         offset) {

    //sanity check
    ifb_macro_assert(arena_ptr);

    //we can get the pointer if...
    ifb_b8 can_get_pointer = true;
    can_get_pointer &= arena_ptr != NULL;                    // ...the arena is valid
    can_get_pointer &= offset < arena_ptr->page_commit.size; // ...AND the offset is within the arena 

    //get the address
    const ifb_address address = can_get_pointer 
        ? arena_ptr->page_commit.start + offset
        : 0;

    //cast the pointer
    const ifb_ptr pointer = (ifb_ptr)address; 

    //we're done
    return(pointer);
}

/**********************************************************************************/
/* SIZE                                                                           */
/**********************************************************************************/

ifb_internal const ifb_u32
ifb_memory::arena_get_page_count(
    const IFBMemoryArena* arena_ptr) {

    //sanity check
    ifb_macro_assert(arena_ptr);

    //return the page count
    const ifb_u32 page_count = arena_ptr->page_commit.page_count;
    return(page_count);
}

ifb_internal const ifb_u32
ifb_memory::arena_get_page_start(
    const IFBMemoryArena* arena_ptr) {

    //sanity check
    ifb_macro_assert(arena_ptr);;

    //return the page start
    const ifb_u32 page_start = arena_ptr->page_commit.page_number;
    return(page_start);
}   

ifb_internal const ifb_u32
ifb_memory::arena_get_size_total(
    const IFBMemoryArena* arena_ptr) {

    //sanity check
    ifb_macro_assert(arena_ptr);

    //return the size
    const ifb_u32 arena_size = arena_ptr->page_commit.size;
    return(arena_size);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

ifb_internal const ifb_b8
ifb_memory::arena_list_add(
    IFBMemoryArenaList& arena_list_ref,
    IFBMemoryArena*     arena_base_ptr) {

    //set the next arena to null
    arena_base_ptr->next = NULL;

    //if this is the first arena, set it and we're done
    //otherwise, we will proceed to add it to the tail
    if (arena_list_ref.first == NULL) {
        arena_list_ref.first = arena_base_ptr;
        arena_list_ref.last  = arena_base_ptr;
        arena_list_ref.count = 1;
        return(true);
    }

    //make sure the tail is initialized
    if (!arena_list_ref.last) return(false);

    //add the arena to the tail and update the count
    arena_list_ref.last->next = arena_base_ptr;
    ++arena_list_ref.count;

    //we're done
    return(true);
}