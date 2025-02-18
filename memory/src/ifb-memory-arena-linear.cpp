#include "ifb-memory-internal.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb_memory {

    inline IFBMemoryArenaLinear* linear_arena_handle_to_pointer(const IFBHNDMemoryArenaLinear linear_arena_handle);
};

/**********************************************************************************/
/* SAVE POINT                                                                     */
/**********************************************************************************/

IFBVoid
ifb_memory::linear_arena_save_point_set(
    const IFBHNDMemoryArenaLinear linear_arena_handle) {

    //get the pointer
    IFBMemoryArenaLinear* linear_arena_ptr = ifb_memory::linear_arena_handle_to_pointer(linear_arena_handle);
    
    //update the save point to the position
    linear_arena_ptr->save_point = linear_arena_ptr->position; 
}

IFBVoid
ifb_memory::linear_arena_save_point_clear(
    const IFBHNDMemoryArenaLinear linear_arena_handle) {

    //get the pointer
    IFBMemoryArenaLinear* linear_arena_ptr = ifb_memory::linear_arena_handle_to_pointer(linear_arena_handle);
    
    //clear the save point
    linear_arena_ptr->save_point = 0; 
}

/**********************************************************************************/
/* RESET                                                                          */
/**********************************************************************************/

IFBVoid
ifb_memory::linear_arena_reset_to_start(
    const IFBHNDMemoryArenaLinear linear_arena_handle) {

    //get the pointer
    IFBMemoryArenaLinear* linear_arena_ptr = ifb_memory::linear_arena_handle_to_pointer(linear_arena_handle);
    
    //clear the position
    linear_arena_ptr->position = 0;
}

IFBVoid
ifb_memory::linear_arena_reset_to_save_point(
    const IFBHNDMemoryArenaLinear linear_arena_handle) {
    
    //get the pointer
    IFBMemoryArenaLinear* linear_arena_ptr = ifb_memory::linear_arena_handle_to_pointer(linear_arena_handle);

    //sanity check
    //make sure the save point isn't beyond the position
    const IFBU32 save_point                    = linear_arena_ptr->save_point;
    const IFBU32 current_position              = linear_arena_ptr->position;
    const IFBB8  is_save_point_within_position = save_point <= current_position;
    ifb_macro_assert(is_save_point_within_position);

    //update the position to the save point
    linear_arena_ptr->position = save_point;
}

/**********************************************************************************/
/* RESERVE/RELEASE                                                                */
/**********************************************************************************/

const IFBPtr
ifb_memory::linear_arena_reserve_bytes_absolute(
    const IFBHNDMemoryArenaLinear linear_arena_handle,
    const IFBU32                    size,
    const IFBU32                    alignment) {

    //get the pointer
    IFBMemoryArenaLinear* linear_arena_ptr = ifb_memory::linear_arena_handle_to_pointer(linear_arena_handle);
    
    //sanity check
    if (size == 0)  return(NULL);

    //align the size
    const IFBU32 size_aligned = ifb_macro_align_a_to_b(size,alignment); 

    //calculate the new position
    const IFBU32 position_current = linear_arena_ptr->position;
    const IFBU32 position_new     = position_current + size_aligned;

    //if the position overflows the arena, we're done
    if (position_new >= linear_arena_ptr->size_total) return(NULL);

    //otherwise, get the pointer
    const IFBAddr arena_start      = linear_arena_ptr->start;
    const IFBAddr arena_end        = arena_start + linear_arena_ptr->size_total;
    const IFBAddr position_address = arena_start + position_new;

    //sanity check, this should never happen
    ifb_macro_assert(position_address < arena_end);

    //update the position
    linear_arena_ptr->position = position_new;

    //cast the pointer
    const IFBPtr position_pointer = (IFBPtr)position_address;

    //we're done
    return(position_pointer);
}

const IFBU32
ifb_memory::linear_arena_reserve_bytes_relative(
    const IFBHNDMemoryArenaLinear linear_arena_handle,
    const IFBU32                    size, 
    const IFBU32                    alignment) {
    
    //get the pointer
    IFBMemoryArenaLinear* linear_arena_ptr = ifb_memory::linear_arena_handle_to_pointer(linear_arena_handle);
    
    //sanity check
    if (size == 0)  return(NULL);

    //align the size
    const IFBU32 size_aligned = ifb_macro_align_a_to_b(size,alignment); 

    //calculate the new position
    const IFBU32 position_current = linear_arena_ptr->position;
    const IFBU32 position_new     = position_current + size_aligned;

    //if the position overflows the arena, we're done
    if (position_new >= linear_arena_ptr->size_total) {

        //since the pointer at the total size will be null
        //we can use it as an invalid offset    
        const IFBU32 offset_invalid = linear_arena_ptr->size_total;
        return(offset_invalid);
    }

    //otherwise, update the position
    linear_arena_ptr->position = position_new;

    //return the new position as the relative offset
    return(position_new);
}


const IFBB8
ifb_memory::linear_arena_release_bytes(
    const IFBHNDMemoryArenaLinear linear_arena_handle,
    const IFBU32                    size,
    const IFBU32                    alignment) {

    //get the pointer
    IFBMemoryArenaLinear* linear_arena_ptr = ifb_memory::linear_arena_handle_to_pointer(linear_arena_handle);

    //sanity check
    if (size == 0) return(false);

    //align the size
    const IFBU32 size_aligned = ifb_macro_align_a_to_b(size,alignment); 

    //make sure we can release the bytes
    const IFBU32 position_current = linear_arena_ptr->position;
    if (size_aligned > position_current) return(false);

    //update the position
    linear_arena_ptr->position -= size_aligned;

    //if the new position is greater than the save point
    //we need to clear it
    if (linear_arena_ptr->position > linear_arena_ptr->save_point) {
        linear_arena_ptr->save_point = 0;
    }

    //we're done
    return(true);
}

const IFBU32
ifb_memory::linear_arena_reserve_bytes_absolute(
    const IFBHNDMemoryArenaLinear linear_arena_handle,
    const IFBU32                    count,
    const IFBU32*                   size_array,
          IFBPtr*                   pointer_array) {

    //get the pointer
    IFBMemoryArenaLinear* linear_arena_ptr = ifb_memory::linear_arena_handle_to_pointer(linear_arena_handle);

    //sanity check
    if (count == 0 || !size_array || !pointer_array) return(false);

    //cache arena constants
    const IFBAddr arena_start = linear_arena_ptr->start;
    const IFBAddr arena_end   = arena_start + linear_arena_ptr->size_total;

    //keep track of how many bytes we reseved
    //if something goes wrong, we can release what we reserved
    IFBU32 total_bytes_reserved = 0;

    for (
        IFBU32 index = 0;
        index < count;
        ++index) {

        //get the current size
        const IFBU32 size = size_array[index];

        //calculate the new position
        const IFBU32 position_current = linear_arena_ptr->position;
        const IFBU32 position_new     = position_current + size;

        //if the position overflows the arena, we're done
        if (position_new >= linear_arena_ptr->size_total) {

            //if we reserved bytes, we need to release them
            if (total_bytes_reserved > 0) {
                
                //release the bytes
                const IFBB8 released = ifb_memory::linear_arena_release_bytes(linear_arena_handle,total_bytes_reserved);
                
                //sanity check, we should always be able to release what was just reserved
                ifb_macro_assert(released);
            }

            //return 0 bytes reserved
            return(0);
        } 

        //otherwise, get the pointer
        const IFBAddr position_address = arena_start + position_new;

        //sanity check, this should never happen
        ifb_macro_assert(position_address < arena_end);

        //update the position
        linear_arena_ptr->position = position_new;

        //cast the pointer
        const IFBPtr position_pointer = (IFBPtr)position_address;

        //update the array
        pointer_array[index] = position_pointer;

        //update the bytes reserved
        total_bytes_reserved += size;
    }

    //we're done
    return(total_bytes_reserved);
}

const IFBU32
ifb_memory::linear_arena_reserve_bytes_relative(
    const IFBHNDMemoryArenaLinear linear_arena_handle,
    const IFBU32                    count,
    const IFBU32*                   size_array,
          IFBU32*                   offset_array) {

    //get the pointer
    IFBMemoryArenaLinear* linear_arena_ptr = ifb_memory::linear_arena_handle_to_pointer(linear_arena_handle);

    //sanity check
    if (count == 0 || !size_array || !offset_array) return(false);

    //keep track of how many bytes we reseved
    //if something goes wrong, we can release what we reserved
    IFBU32 total_bytes_reserved = 0;

    for (
        IFBU32 index = 0;
        index < count;
        ++index) {

        //get the current size
        const IFBU32 size = size_array[index];

        //calculate the new position
        const IFBU32 position_current = linear_arena_ptr->position;
        const IFBU32 position_new     = size;

        //if the position overflows the arena, we're done
        if (position_new >= linear_arena_ptr->size_total) {

            //if we reserved bytes, we need to release them
            if (total_bytes_reserved > 0) {
                
                //release the bytes
                const IFBB8 released = ifb_memory::linear_arena_release_bytes(linear_arena_handle,total_bytes_reserved);
                
                //sanity check, we should always be able to release what was just reserved
                ifb_macro_assert(released);
            }

            //return 0 bytes reserved
            return(0);
        }

        //update the array
        offset_array[index] = position_current;

        //otherwise, update the position
        linear_arena_ptr->position = position_new;

        //update the total bytes reserved
        total_bytes_reserved += size;        
    }

    //we're done
    return(total_bytes_reserved);
}

/**********************************************************************************/
/* POINTERS                                                                       */
/**********************************************************************************/

const IFBPtr 
ifb_memory::linear_arena_get_pointer_at_offset(
    const IFBHNDMemoryArenaLinear linear_arena_handle,
    const IFBU32                    offset) {

    //get the arena pointer
    IFBMemoryArenaLinear* linear_arena_ptr = ifb_memory::linear_arena_handle_to_pointer(linear_arena_handle);

    //calculate addresses
    const IFBAddr arena_start    = linear_arena_ptr->start;
    const IFBAddr arena_end      = arena_start + linear_arena_ptr->size_total;
    const IFBAddr offset_address = arena_start + offset;

    //get the pointer at the position, if its within the arena
    const IFBPtr offset_pointer = offset_address < arena_end
        ? (IFBPtr)offset_address
        : NULL;

    //we're done
    return(offset_pointer);
}

const IFBPtr 
ifb_memory::linear_arena_get_pointer_at_position(
    const IFBHNDMemoryArenaLinear linear_arena_handle) {

    //get the arena pointer
    IFBMemoryArenaLinear* linear_arena_ptr = ifb_memory::linear_arena_handle_to_pointer(linear_arena_handle);

    //calculate addresses
    const IFBAddr arena_start      = linear_arena_ptr->start;
    const IFBAddr arena_end        = arena_start + linear_arena_ptr->size_total;
    const IFBAddr position_address = arena_start + linear_arena_ptr->position;

    //sanity check, this should never happen
    ifb_macro_assert(position_address < arena_end);

    //cast the pointer
    const IFBPtr position_ptr = (IFBPtr)position_address;

    //we're done
    return(position_ptr);
}

const IFBPtr 
ifb_memory::linear_arena_get_pointer_at_save_point(
    const IFBHNDMemoryArenaLinear linear_arena_handle) {

    //get the arena pointer
    IFBMemoryArenaLinear* linear_arena_ptr = ifb_memory::linear_arena_handle_to_pointer(linear_arena_handle);

    //calculate addresses
    const IFBAddr arena_start        = linear_arena_ptr->start;
    const IFBAddr arena_end          = arena_start + linear_arena_ptr->size_total;
    const IFBAddr position_address   = arena_start + linear_arena_ptr->position;
    const IFBAddr save_point_address = arena_start + linear_arena_ptr->save_point;

    //sanity check, this should never happen
    ifb_macro_assert(save_point_address < position_address);
    ifb_macro_assert(save_point_address < arena_end);

    //cast the pointer
    const IFBPtr save_point_ptr = (IFBPtr)save_point_address;

    //we're done
    return(save_point_ptr);
}

const IFBPtr 
ifb_memory::linear_arena_get_pointer_at_start(
    const IFBHNDMemoryArenaLinear linear_arena_handle) {

    //get the arena pointer
    IFBMemoryArenaLinear* linear_arena_ptr = ifb_memory::linear_arena_handle_to_pointer(linear_arena_handle);

    //get the pointer
    const IFBAddr arena_start = linear_arena_ptr->start;
    const IFBPtr     pointer     = (IFBPtr)arena_start;

    //we're done
    return(pointer);
}

/**********************************************************************************/
/* INFO                                                                           */
/**********************************************************************************/

const IFBB8 
ifb_memory::linear_arena_get_info(
    const IFBHNDMemoryArenaLinear linear_arena_handle,
          IFBMemoryArenaLinearInfo*  linear_arena_info_ptr) {

    //get the arena pointer
    IFBMemoryArenaLinear* linear_arena_ptr = ifb_memory::linear_arena_handle_to_pointer(linear_arena_handle);

    //sanity check
    if (!linear_arena_info_ptr) return(false);

    //set the arena info
    linear_arena_info_ptr->reservation_handle.offset  = linear_arena_ptr->reservation->stack_offset;
    linear_arena_info_ptr->linear_arena_handle.offset = linear_arena_ptr->stack_position;
    linear_arena_info_ptr->page_start                 = linear_arena_ptr->page_start;
    linear_arena_info_ptr->page_count                 = linear_arena_ptr->page_count;
    linear_arena_info_ptr->size_total                 = linear_arena_ptr->size_total;
    linear_arena_info_ptr->position                   = linear_arena_ptr->position;
    linear_arena_info_ptr->save_point                 = linear_arena_ptr->save_point;

    //we're done
    return(true);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

IFBMemoryArenaLinear* 
ifb_memory::linear_arena_handle_to_pointer(
    const IFBHNDMemoryArenaLinear linear_arena_handle) {

    //get the pointer
    IFBMemoryArenaLinear* linear_arena_ptr = ifb_memory_macro_stack_get_type_pointer(
        linear_arena_handle.offset,
        IFBMemoryArenaLinear);

    //sanity check
    ifb_macro_assert(linear_arena_ptr);

    //we're done
    return(linear_arena_ptr);
}