#include "ifb-memory-internal.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb_memory {

    inline IFBMemoryBlockArena* block_arena_handle_to_pointer(const IFBMemoryBlockArenaHandle block_arena_handle);
};

/**********************************************************************************/
/* RESET                                                                          */
/**********************************************************************************/

ifb_void
ifb_memory::block_arena_reset(
    const IFBMemoryBlockArenaHandle block_arena_handle) {

    //get the arena pointer
    IFBMemoryBlockArena* block_arena_ptr = ifb_memory::block_arena_handle_to_pointer(block_arena_handle);

    //cache the addresses
    ifb_address* address_array = block_arena_ptr->block_address_array;
    
    //set all the block start addresses to zero, and we're done
    for (
        ifb_u32 block_index = 0;
        block_index < block_arena_ptr->block_count;
        ++block_index) {

        //a block address of 0 means its unreserved
        address_array[block_index] = 0;
    }
}

/**********************************************************************************/
/* RESERVE/RELEASE                                                                */
/**********************************************************************************/

const ifb_b8
ifb_memory::block_arena_block_reserve(
    const IFBMemoryBlockArenaHandle block_arena_handle,
          ifb_u32&                  block_index_ref) {

    //get the arena pointer
    IFBMemoryBlockArena* block_arena_ptr = ifb_memory::block_arena_handle_to_pointer(block_arena_handle);

    //cache the properties
    ifb_address*      address_array     = block_arena_ptr->block_address_array;
    const ifb_u32     block_count       = block_arena_ptr->block_count;
    const ifb_u32     block_size        = block_arena_ptr->block_size;
    const ifb_address block_arena_start = block_arena_ptr->start;     

    //find the next available block
    for (
        block_index_ref = 0;
        block_index_ref < block_arena_ptr->block_count;
        ++block_index_ref) {

        //a block address of 0 means its unreserved
        if (address_array[block_index_ref] == 0) {

            //calculate the starting address
            const ifb_u32     block_offset = block_index_ref   * block_size;
            const ifb_address block_start  = block_arena_start + block_offset;

            //update the block
            address_array[block_index_ref] = block_start;

            //we're done
            return(true); 
        }
    }

    //if we made it here, we didn't find an available block
    //we're done
    return(false);
}

const ifb_b8
ifb_memory::block_arena_block_reserve_index(
    const IFBMemoryBlockArenaHandle block_arena_handle,
    const ifb_u32                   block_index) {
    
    //get the arena pointer
    IFBMemoryBlockArena* block_arena_ptr = ifb_memory::block_arena_handle_to_pointer(block_arena_handle);

    //if the index isn't valid, we're done
    if (block_index < block_arena_ptr->block_count) return(false);

    //cache the properties
    ifb_address*      address_array     = block_arena_ptr->block_address_array;
    const ifb_u32     block_count       = block_arena_ptr->block_count;
    const ifb_u32     block_size        = block_arena_ptr->block_size;
    const ifb_address block_arena_start = block_arena_ptr->start;     

    //if its already reserved, we're done
    if (address_array[block_index] != 0) return(false);

    //calculate the starting address
    const ifb_u32     block_offset = block_index       * block_size; 
    const ifb_address block_start  = block_arena_start + block_offset; 

    //update the block
    address_array[block_index] = block_start;
    
    //we're done
    return(true);
}

const ifb_b8
ifb_memory::block_arena_block_release(
    const IFBMemoryBlockArenaHandle block_arena_handle,
    const ifb_u32                   block_index) {
    
    //get the arena pointer
    IFBMemoryBlockArena* block_arena_ptr = ifb_memory::block_arena_handle_to_pointer(block_arena_handle);

    //if the index isn't valid, we're done
    if (block_index < block_arena_ptr->block_count) return(false);

    //set the block address to 0
    ifb_address* block_address_array = block_arena_ptr->block_address_array;
    block_address_array[block_index] = 0;

    //we're done
    return(true);
}

const ifb_b8
ifb_memory::block_arena_block_is_free(
    const IFBMemoryBlockArenaHandle block_arena_handle,
    const ifb_u32                   block_index) {
    
    //get the arena pointer
    IFBMemoryBlockArena* block_arena_ptr = ifb_memory::block_arena_handle_to_pointer(block_arena_handle);

    //if the index isn't valid, we're done
    if (block_index < block_arena_ptr->block_count) return(false);

    //if the start is 0, the block is free
    const ifb_address* block_address_array = block_arena_ptr->block_address_array;
    const ifb_b8       block_free          = block_address_array[block_index] == 0;  

    //we're done
    return(block_free);
}

/**********************************************************************************/
/* POINTERS                                                                       */
/**********************************************************************************/

const ifb_ptr 
ifb_memory::block_get_pointer(
    const IFBMemoryBlockArenaHandle block_arena_handle,
    const ifb_u32                   block_index,
    const ifb_u32                   offset) {

    //get the arena pointer
    IFBMemoryBlockArena* block_arena_ptr = ifb_memory::block_arena_handle_to_pointer(block_arena_handle);

    //if the index isn't valid, we're done
    if (block_index < block_arena_ptr->block_count) return(false);

    //get the start of the block
    const ifb_address* block_address_array  = block_arena_ptr->block_address_array;
    const ifb_address  block_address_start  = block_address_array[block_index]; 
    const ifb_address  block_address_offset = block_address_start + offset;

    //if the block isn't reserved, the address will just be 0
    const ifb_address block_offset_address = block_address_start > 0
        ? block_address_offset
        : 0;

    //cast the address to a pointer
    const ifb_ptr block_offset_ptr = (ifb_ptr)block_offset_address;

    //we're done
    return(block_offset_ptr);
}

/**********************************************************************************/
/* INFO                                                                           */
/**********************************************************************************/

const ifb_b8 
ifb_memory::block_arena_get_info(
    const IFBMemoryBlockArenaHandle block_arena_handle,
          IFBMemoryBlockArenaInfo*  block_arena_info) {

    //get the arena pointer
    IFBMemoryBlockArena* block_arena_ptr = ifb_memory::block_arena_handle_to_pointer(block_arena_handle);

    //sanity check
    if (!block_arena_info) return(false);

    //calculate the free blocks
    const ifb_address* block_address_array = block_arena_ptr->block_address_array; 
    const ifb_u32      block_count         = block_arena_ptr->block_count; 
    ifb_u32            block_count_free    = 0;

    for (
        ifb_u32 block_index = 0;
        block_index < block_count;
        ++block_index) {

        const ifb_address block_address_current = block_address_array[block_index]; 

        if (block_address_current == 0) {
            ++block_count_free;
        } 
    }

    //set the block arena info properties
    block_arena_info->reservation_handle.offset = block_arena_ptr->reservation->stack_offset;
    block_arena_info->block_arena_handle.offset = block_arena_ptr->stack_position;
    block_arena_info->page_start                = block_arena_ptr->page_start;
    block_arena_info->page_count                = block_arena_ptr->page_count;
    block_arena_info->size_total                = block_arena_ptr->size_total;
    block_arena_info->block_size                = block_arena_ptr->block_size;
    block_arena_info->block_count_total         = block_count; 
    block_arena_info->block_count_free          = block_count_free;

    //we're done
    return(true);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

IFBMemoryBlockArena*
ifb_memory::block_arena_handle_to_pointer(
    const IFBMemoryBlockArenaHandle block_arena_handle) {

    //get the pointer
    IFBMemoryBlockArena* block_arena_ptr = ifb_memory_macro_stack_get_type_pointer(
        block_arena_handle.offset,
        IFBMemoryBlockArena);

    //sanity check
    ifb_macro_assert(block_arena_ptr);

    //we're done
    return(block_arena_ptr);
}