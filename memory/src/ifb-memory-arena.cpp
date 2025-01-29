#pragma once

#include "ifb-memory-internal.hpp"

/**********************************************************************************/
/* COMMIT                                                                         */
/**********************************************************************************/

inline const IFBMemoryArenaHandle
ifb_memory::arena_commit(
    const IFBMemoryHandle memory_handle,
    const ifb_u32         arena_size_minimum) {

    //get the next available arena
    IFBMemoryArena* arena_ptr = ifb_memory::arena_get_next(memory_handle);
    if (!arena_ptr) return(NULL);

    //commit the pages for the arena
    arena_ptr->page_commit.size = arena_size_minimum;
    if (!ifb_memory::reservation_page_commit(memory_ptr,arena_ptr->page_commit)) {
        //if that failed, we're done
        return({0});
    }

    //initialize the rest of the arena properties
    arena_ptr->allocators = {0};
    arena_ptr->position   = 0;

    //update the arena table
    ++arena_table_ref.count_used;

    //we're done
    return(arena_ptr);
}

inline const IFBMemoryArenaHandle
ifb_memory::arena_commit(
    const IFBMemoryHandle              memory_handle,
    const IFBMemoryArenaCommitRequest& arena_commit_request_ref,
          IFBMemoryArenaCommitResult&  arena_commit_result_ref) {

    //get the next available arena
    IFBMemoryArena* arena_ptr = ifb_memory::arena_get_next(memory_handle);
    if (!arena_ptr) return(NULL);

    //calculate the scratch space size, if we have any
    const ifb_u32 scratch_size_minimum = arena_commit_request_ref.scratch_space_minimum; 
    const ifb_u32 scratch_size         = scratch_size_minimum > 0
        ? ifb_memory::reservation_size_align_to_page(memory_ptr,scratch_size_minimum)
        : 0;

    //calculate the linear allocator array size
     

}

/**********************************************************************************/
/* RESET                                                                          */
/**********************************************************************************/

inline const ifb_b8 ifb_memory::arena_reset_all            (const IFBMemoryArenaId arena_id);
inline const ifb_b8 ifb_memory::arena_reset_allocators     (const IFBMemoryArenaId arena_id);
inline const ifb_b8 ifb_memory::arena_reset_scratch_space  (const IFBMemoryArenaId arena_id);

/**********************************************************************************/
/* PUSH / PULL                                                                    */
/**********************************************************************************/

inline const ifb_ptr ifb_memory::arena_scratch_push         (const IFBMemoryArenaId arena_id, const ifb_u32 size);
inline const ifb_ptr ifb_memory::arena_scratch_pull         (const IFBMemoryArenaId arena_id, const ifb_u32 size);
inline const ifb_ptr ifb_memory::arena_scratch_push_aligned (const IFBMemoryArenaId arena_id, const ifb_u32 size, const ifb_u32 alignment);
inline const ifb_ptr ifb_memory::arena_scratch_pull_aligned (const IFBMemoryArenaId arena_id, const ifb_u32 size, const ifb_u32 alignment);

/**********************************************************************************/
/* SIZE / COUNT                                                                   */
/**********************************************************************************/

inline const ifb_u32 ifb_memory::arena_get_page_count       (const IFBMemoryArenaId arena_id);
inline const ifb_u32 ifb_memory::arena_get_page_start       (const IFBMemoryArenaId arena_id);    
inline const ifb_u32 ifb_memory::arena_get_size_total       (const IFBMemoryArenaId arena_id);    
inline const ifb_u32 ifb_memory::arena_get_size_allocators  (const IFBMemoryArenaId arena_id);    
inline const ifb_u32 ifb_memory::arena_get_size_scratch     (const IFBMemoryArenaId arena_id);

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline IFBMemoryArena*
ifb_memory::arena_get_next(
    const IFBMemory* memory_ptr) {

    //sanity check
    if (!memory_ptr) return(NULL);

    //cache the arena table
    IFBMemoryArenaTable& arena_table_ref = memory_ptr->arena_table;
    
    //make sure we have an available arena
    const ifb_u32 arena_index     = arena_table_ref.count_used; 
    const ifb_b8  arena_available = arena_index < arena_table_ref.count_total; 
    if (!arena_available) return(NULL);

    //get the next arena from the table
    IFBMemoryArena* arena_ptr = &arena_table_ref.arena_array[arena_index]; 

    //we're done
    return(arena_ptr);
}

inline const ifb_ptr
ifb_memory::arena_get_pointer(
    const IFBMemoryArenaHandle arena_handle,
    const ifb_u32              offset) {

    //cast the arena
    IFBMemoryArena* arena_ptr = (IFBMemoryArena*)arena_handle;
    
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