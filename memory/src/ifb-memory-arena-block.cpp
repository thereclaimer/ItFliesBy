#pragma once

#include "ifb-memory-internal.hpp"

/**********************************************************************************/
/* COMMIT                                                                         */
/**********************************************************************************/

const IFBMemoryBlockArena
block_arena_commit(
    const IFBMemoryHandle memory_handle,
    const ifb_u32         block_size_minimum,
    const ifb_u32         block_count) {

    //sanity check
    ifb_macro_assert(memory_handle && block_count > 1);        

    //calculate the flag group array size
    const ifb_u32 block_flag_group_count = ifb_macro_align_a_to_multiple_of_b(block_count, IFB_MEMORY_BLOCK_FLAG_BIT_COUNT);
    const ifb_u32 block_flag_group_size  = ifb_macro_size_array(ifb_u32,block_flag_count);
    const ifb_u32 block_size             = ifb_memory::reservation_size_align_to_page(memory_handle,block_size_minimum);
    const ifb_u32 commit_size            = block_size * block_count; 

    //allocate a block arena and flags
    IFBMemoryBlockArena* block_arena_ptr         = ifb_memory::stack_push_arena_block       (memory_handle);
    ifb_u32*             block_arena_flags_array = ifb_memory::stack_push_arena_block_flags (memory_handle,block_flag_group_size); 

    //commit the pages
    block_arena_ptr->page_commit.size = commit_size;
    const ifb_b8 commit_result = ifb_memory::reservation_page_commit(
        memory_handle,
        block_arena_ptr->page_commit);

    //sanity check
    ifb_macro_assert(block_arena_ptr);
    ifb_macro_assert(block_arena_flags_array);
    ifb_macro_assert(commit_result);

    //clear the flags
    for (
        ifb_u32 flag_index = 0;
        flag_index < block_flag_count;
        ++flag_index) {

        block_arena_flags_array[flag_index] = 0;
    }

    //set the arena properties
    block_arena_ptr->next                   = NULL;
    block_arena_ptr->type                   = IFBMemoryArenaType_Block;
    block_arena_ptr->block_size             = block_size;
    block_arena_ptr->block_count            = block_count;
    block_arena_ptr->block_flag_group_count = block_flag_group_count;
    block_arena_ptr->block_flag_group_array = block_arena_flags_array;

    //we're done
    return(block_arena_ptr);
}

/**********************************************************************************/
/* RESET                                                                          */
/**********************************************************************************/

const ifb_b8  block_arena_reset                 (const IFBMemoryBlockArenaHandle block_arena_handle);

/**********************************************************************************/
/* RESERVE/RELEASE                                                                */
/**********************************************************************************/

const ifb_ptr block_arena_block_reserve         (const IFBMemoryBlockArenaHandle block_arena_handle);
const ifb_b8  block_arena_block_release         (const IFBMemoryBlockArenaHandle block_arena_handle);

/**********************************************************************************/
/* SIZE/COUNT                                                                     */
/**********************************************************************************/

const ifb_u32 block_arena_get_size_total        (const IFBMemoryBlockArenaHandle block_arena_handle);
const ifb_u32 block_arena_get_block_size        (const IFBMemoryBlockArenaHandle block_arena_handle);
const ifb_u32 block_arena_get_block_count_total (const IFBMemoryBlockArenaHandle block_arena_handle);
const ifb_u32 block_arena_get_block_count_used  (const IFBMemoryBlockArenaHandle block_arena_handle);
const ifb_u32 block_arena_get_block_count_free  (const IFBMemoryBlockArenaHandle block_arena_handle);