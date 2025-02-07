#pragma once

#include "ifb-memory-internal.hpp"

/**********************************************************************************/
/* COMMIT                                                                         */
/**********************************************************************************/

inline IFBMemoryBlockArena*
block_arena_commit(
          IFBMemory* memory_ptr,
    const ifb_u32    block_size_minimum,
    const ifb_u32    block_count) {

    //sanity check
    ifb_macro_assert(memory_ptr);
    if (block_count == 0) return(NULL);

    //calculate the flag group array size
    const ifb_u32 block_size  = ifb_memory::reservation_size_align_to_page(memory_ptr,block_size_minimum);
    const ifb_u32 commit_size = block_size * block_count; 

    //allocate a block arena and flags
    IFBMemoryBlockArena* block_arena_ptr = ifb_memory::stack_push_arena_block       (memory_ptr);
    IFBMemoryBlock*      block_array     = ifb_memory::stack_push_arena_block_array (memory_ptr,block_count); 

    //commit the pages
    block_arena_ptr->page_commit.size = commit_size;
    const ifb_b8 commit_result = ifb_memory::reservation_page_commit(
        memory_ptr,
        block_arena_ptr->page_commit);

    //add the arena to the list
    const ifb_b8 arena_list_result = ifb_memory::arena_list_add(
        memory_ptr->arena_list,
        block_arena_ptr);
    
    //sanity check
    ifb_macro_assert(block_arena_ptr);
    ifb_macro_assert(block_array);
    ifb_macro_assert(commit_result);
    ifb_macro_assert(arena_list_result);

    //initialize the blocks
    for (
        ifb_u32 block_index = 0;
        block_index < block_count;
        ++block_index) {

        //a block address of 0 means its unreserved
        IFBMemoryBlock& block_ref = block_array[block_index];
        block_ref.start = 0;
    }

    //set the arena properties
    block_arena_ptr->next        = NULL;
    block_arena_ptr->type        = IFBMemoryArenaType_Block;
    block_arena_ptr->block_size  = block_size;
    block_arena_ptr->block_count = block_count;
    block_arena_ptr->block_array = block_array; 

    //we're done
    return(block_arena_ptr);
}

/**********************************************************************************/
/* RESET                                                                          */
/**********************************************************************************/

inline ifb_void
ifb_memory::block_arena_reset(
    IFBMemoryBlockArena* block_arena_ptr) {

    //sanity check
    ifb_macro_assert(block_arena_ptr);

    //cache the blocks
    IFBMemoryBlock* block_array = block_arena_ptr->block_array;
    
    //set all the block start addresses to zero, and we're done
    for (
        ifb_u32 block_index = 0;
        block_index < block_arena_ptr->block_count;
        ++block_index) {

        //a block address of 0 means its unreserved
        IFBMemoryBlock& block_ref = block_array[block_index];
        block_ref.start = 0;
    }
}

/**********************************************************************************/
/* RESERVE/RELEASE                                                                */
/**********************************************************************************/

inline const ifb_b8
ifb_memory::block_arena_block_reserve(
    IFBMemoryBlockArena* block_arena_ptr,
    ifb_u32&             block_index_ref) {

    //sanity check
    ifb_macro_assert(block_arena_ptr);

    //cache the blocks
    IFBMemoryBlock* block_array = block_arena_ptr->block_array;

    //find the next available block
    for (
        block_index_ref = 0;
        block_index_ref < block_arena_ptr->block_count;
        ++block_index_ref) {

        //a block address of 0 means its unreserved
        IFBMemoryBlock& block_ref = block_array[block_index_ref];
        if (block_ref.start == 0) {

            //calculate the starting address
            const ifb_u32     block_offset = block_index_ref * block_arena_ptr->block_size;
            const ifb_address block_start  = block_arena_ptr->page_commit.start + block_offset;

            //update the block
            block_ref.start = block_start;

            //we're done
            return(true); 
        }
    }

    //if we made it here, we didn't find an available block
    //we're done
    return(false);
}

inline const ifb_b8
ifb_memory::block_arena_block_reserve_index(
          IFBMemoryBlockArena* block_arena_ptr,
    const ifb_u32              block_index) {
    
    //sanity check
    ifb_macro_assert(block_arena_ptr);

    //if the index isn't valid, we're done
    if (block_index < block_arena_ptr->block_count) return(false);

    //get the block
    IFBMemoryBlock& block_ref = block_arena_ptr->block_array[block_index];

    //if its already reserved, we're done
    if (block_ref.start > 0) return(false);

    //calculate the starting address
    const ifb_u32     block_offset = block_index * block_arena_ptr->block_size;
    const ifb_address block_start  = block_arena_ptr->page_commit.start + block_offset;

    //update the block
    block_ref.start = block_start;

    //we're done
    return(true);
}

inline const ifb_b8
ifb_memory::block_arena_block_release(
          IFBMemoryBlockArena* block_arena_ptr,
    const ifb_u32              block_index) {
    
    //sanity check
    ifb_macro_assert(block_arena_ptr);

    //if the index isn't valid, we're done
    if (block_index < block_arena_ptr->block_count) return(false);

    //get the block
    IFBMemoryBlock& block_ref = block_arena_ptr->block_array[block_index];

    //set the start to 0
    block_ref.start = 0;

    //we're done
    return(true);
}

inline const ifb_b8
ifb_memory::block_arena_block_is_free(
          IFBMemoryBlockArena* block_arena_ptr,
    const ifb_u32              block_index) {
    
    //sanity check
    ifb_macro_assert(block_arena_ptr);

    //if the index isn't valid, we're done
    if (block_index < block_arena_ptr->block_count) return(false);

    //get the block
    IFBMemoryBlock& block_ref = block_arena_ptr->block_array[block_index];

    //if the start is 0, the block is free
    const ifb_b8 block_free = block_ref.start == 0;  

    //we're done
    return(block_free);
}

/**********************************************************************************/
/* POINTERS                                                                       */
/**********************************************************************************/

inline const ifb_ptr 
ifb_memory::block_get_pointer(
    const IFBMemoryBlockArena* block_arena_ptr,
    const ifb_u32              block_index,
    const ifb_u32              offset) {

    //sanity check
    ifb_macro_assert(block_arena_ptr);

    //if the index isn't valid, we're done
    if (block_index < block_arena_ptr->block_count) return(false);

    //get the block
    IFBMemoryBlock& block_ref = block_arena_ptr->block_array[block_index];

    //if the block isn't reserved, the address will just be 0
    const ifb_address block_offset_address = block_ref.start > 0
        ? block_ref.start + offset
        : 0;

    //cast the address to a pointer
    const ifb_ptr block_offset_ptr = (ifb_ptr)block_offset_address;

    //we're done
    return(block_offset_ptr);
}

/**********************************************************************************/
/* SIZE/COUNT                                                                     */
/**********************************************************************************/

inline const ifb_u32
ifb_memory::block_arena_get_size_total(
    const IFBMemoryBlockArena* block_arena_ptr) {

    //sanity check
    ifb_macro_assert(block_arena_ptr);

    //return the commit size
    return(block_arena_ptr->page_commit.size);
}

inline const ifb_u32
ifb_memory::block_arena_get_block_size(
    const IFBMemoryBlockArena* block_arena_ptr) {

    //sanity check
    ifb_macro_assert(block_arena_ptr);

    //return the block size
    return(block_arena_ptr->block_size);
}

inline const ifb_u32
ifb_memory::block_arena_get_block_count_total(
    const IFBMemoryBlockArena* block_arena_ptr) {

    //sanity check
    ifb_macro_assert(block_arena_ptr);

    //return the block count
    return(block_arena_ptr->block_count);
}

inline const ifb_u32
ifb_memory::block_arena_get_block_count_used(
    const IFBMemoryBlockArena* block_arena_ptr) {

    //sanity check
    ifb_macro_assert(block_arena_ptr);

    //cache the array
    IFBMemoryBlock* block_array = block_arena_ptr->block_array;

    //loop through the blocks and count the ones with addresses
    ifb_u32 block_count_used = 0;
    for (
        ifb_u32 block_index = 0;
        block_index < block_arena_ptr->block_count;
        ++block_index) {

        //if the block has a starting address, its used
        if (block_array[block_index].start > 0) ++block_count_used;
    }

    //we're done
    return(block_count_used);
}

inline const ifb_u32
ifb_memory::block_arena_get_block_count_free(
    const IFBMemoryBlockArena* block_arena_ptr) {

    //sanity check
    ifb_macro_assert(block_arena_ptr);

    //cache the array
    IFBMemoryBlock* block_array = block_arena_ptr->block_array;

    //loop through the blocks and count the ones without addresses
    ifb_u32 block_count_free = 0;
    for (
        ifb_u32 block_index = 0;
        block_index < block_arena_ptr->block_count;
        ++block_index) {

        //if the block has a starting address, its used
        if (block_array[block_index].start == 0) ++block_count_free;
    }

    //we're done
    return(block_count_free);
}