#pragma once

#include "ifb-memory-internal.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb_memory {

    inline IFBMemoryLinearArena* linear_arena_handle_to_pointer(const IFBMemoryLinearArenaHandle linear_arena_handle);
};

/**********************************************************************************/
/* SAVE POINT                                                                     */
/**********************************************************************************/

ifb_internal inline ifb_void
ifb_memory::linear_arena_save_point_set(
    const IFBMemoryLinearArenaHandle linear_arena_handle) {

    //get the pointer
    IFBMemoryLinearArena* linear_arena_ptr = ifb_memory::linear_arena_handle_to_pointer(linear_arena_handle);
    
    //update the save point to the position
    linear_arena_ptr->save_point = linear_arena_ptr->position; 
}

ifb_internal inline ifb_void
ifb_memory::linear_arena_save_point_clear(
    const IFBMemoryLinearArenaHandle linear_arena_handle) {

    //get the pointer
    IFBMemoryLinearArena* linear_arena_ptr = ifb_memory::linear_arena_handle_to_pointer(linear_arena_handle);
    
    //clear the save point
    linear_arena_ptr->save_point = 0; 
}

/**********************************************************************************/
/* RESET                                                                          */
/**********************************************************************************/

ifb_internal inline ifb_void
ifb_memory::linear_arena_reset_to_start(
    const IFBMemoryLinearArenaHandle linear_arena_handle) {

    //get the pointer
    IFBMemoryLinearArena* linear_arena_ptr = ifb_memory::linear_arena_handle_to_pointer(linear_arena_handle);
    
    //clear the position
    linear_arena_ptr->position = 0;
}

ifb_internal inline ifb_void
ifb_memory::linear_arena_reset_to_save_point(
    const IFBMemoryLinearArenaHandle linear_arena_handle) {
    
    //get the pointer
    IFBMemoryLinearArena* linear_arena_ptr = ifb_memory::linear_arena_handle_to_pointer(linear_arena_handle);

    //sanity check
    //make sure the save point isn't beyond the position
    const ifb_u32 save_point                    = linear_arena_ptr->save_point;
    const ifb_u32 current_position              = linear_arena_ptr->position;
    const ifb_b8  is_save_point_within_position = save_point <= current_position;
    ifb_macro_assert(is_save_point_within_position);

    //update the position to the save point
    linear_arena_ptr->position = save_point;
}

/**********************************************************************************/
/* RESERVE/RELEASE                                                                */
/**********************************************************************************/

ifb_internal inline const ifb_ptr
ifb_memory::linear_arena_reserve_bytes_absolute(
    const IFBMemoryLinearArenaHandle linear_arena_handle,
    const ifb_u32                    size,
    const ifb_u32                    alignment) {

    //get the pointer
    IFBMemoryLinearArena* linear_arena_ptr = ifb_memory::linear_arena_handle_to_pointer(linear_arena_handle);
    
    //sanity check
    if (size == 0)  return(NULL);

    //align the size
    const ifb_u32 size_aligned = ifb_macro_align_a_to_b(size,alignment); 

    //calculate the new position
    const ifb_u32 position_current = linear_arena_ptr->position;
    const ifb_u32 position_new     = position_current + size_aligned;

    //if the position overflows the arena, we're done
    if (position_new >= linear_arena_ptr->size_total) return(NULL);

    //otherwise, get the pointer
    const ifb_address arena_start      = linear_arena_ptr->start;
    const ifb_address arena_end        = arena_start + linear_arena_ptr->size_total;
    const ifb_address position_address = arena_start + position_new;

    //sanity check, this should never happen
    ifb_macro_assert(position_address < arena_end);

    //update the position
    linear_arena_ptr->position = position_new;

    //cast the pointer
    const ifb_ptr position_pointer = (ifb_ptr)position_address;

    //we're done
    return(position_pointer);
}

ifb_internal inline const ifb_u32
ifb_memory::linear_arena_reserve_bytes_relative(
    const IFBMemoryLinearArenaHandle linear_arena_handle,
    const ifb_u32                    size, 
    const ifb_u32                    alignment) {
    
    //get the pointer
    IFBMemoryLinearArena* linear_arena_ptr = ifb_memory::linear_arena_handle_to_pointer(linear_arena_handle);
    
    //sanity check
    if (size == 0)  return(NULL);

    //align the size
    const ifb_u32 size_aligned = ifb_macro_align_a_to_b(size,alignment); 

    //calculate the new position
    const ifb_u32 position_current = linear_arena_ptr->position;
    const ifb_u32 position_new     = position_current + size_aligned;
    

    //if the position overflows the arena, we're done
    if (position_new >= linear_arena_ptr->size_total) {

        //since the pointer at the total size will be null
        //we can use it as an invalid offset    
        const ifb_u32 offset_invalid = linear_arena_ptr->size_total;
        return(offset_invalid);
    }

    //otherwise, update the position
    linear_arena_ptr->position = position_new;

    //return the new position as the relative offset
    return(position_new);
}


ifb_internal inline const ifb_b8
ifb_memory::linear_arena_release_bytes(
    const IFBMemoryLinearArenaHandle linear_arena_handle,
    const ifb_u32                    size,
    const ifb_u32                    alignment) {

    //get the pointer
    IFBMemoryLinearArena* linear_arena_ptr = ifb_memory::linear_arena_handle_to_pointer(linear_arena_handle);

    //sanity check
    if (size == 0) return(false);

    //align the size
    const ifb_u32 size_aligned = ifb_macro_align_a_to_b(size,alignment); 

    //make sure we can release the bytes
    const ifb_u32 position_current = linear_arena_ptr->position;
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

/**********************************************************************************/
/* POINTERS                                                                       */
/**********************************************************************************/

ifb_internal inline const ifb_ptr 
ifb_memory::linear_arena_get_pointer_at_offset(
    const IFBMemoryLinearArenaHandle linear_arena_handle,
    const ifb_u32                    offset) {

    //get the arena pointer
    IFBMemoryLinearArena* linear_arena_ptr = ifb_memory::linear_arena_handle_to_pointer(linear_arena_handle);

    //calculate addresses
    const ifb_address arena_start    = linear_arena_ptr->start;
    const ifb_address arena_end      = arena_start + linear_arena_ptr->size_total;
    const ifb_address offset_address = arena_start + offset;

    //get the pointer at the position, if its within the arena
    const ifb_ptr offset_pointer = offset_address < arena_end
        ? (ifb_ptr)offset_address
        : NULL;

    //we're done
    return(offset_pointer);
}

ifb_internal inline const ifb_ptr 
ifb_memory::linear_arena_get_pointer_at_position(
    const IFBMemoryLinearArenaHandle linear_arena_handle) {

    //get the arena pointer
    IFBMemoryLinearArena* linear_arena_ptr = ifb_memory::linear_arena_handle_to_pointer(linear_arena_handle);

    //calculate addresses
    const ifb_address arena_start      = linear_arena_ptr->start;
    const ifb_address arena_end        = arena_start + linear_arena_ptr->size_total;
    const ifb_address position_address = arena_start + linear_arena_ptr->position;

    //sanity check, this should never happen
    ifb_macro_assert(position_address < arena_end);

    //cast the pointer
    const ifb_ptr position_ptr = (ifb_ptr)position_address;

    //we're done
    return(position_ptr);
}

ifb_internal inline const ifb_ptr 
ifb_memory::linear_arena_get_pointer_at_save_point(
    const IFBMemoryLinearArenaHandle linear_arena_handle) {

    //get the arena pointer
    IFBMemoryLinearArena* linear_arena_ptr = ifb_memory::linear_arena_handle_to_pointer(linear_arena_handle);

    //calculate addresses
    const ifb_address arena_start        = linear_arena_ptr->start;
    const ifb_address arena_end          = arena_start + linear_arena_ptr->size_total;
    const ifb_address position_address   = arena_start + linear_arena_ptr->position;
    const ifb_address save_point_address = arena_start + linear_arena_ptr->save_point;

    //sanity check, this should never happen
    ifb_macro_assert(save_point_address < position_address);
    ifb_macro_assert(save_point_address < arena_end);

    //cast the pointer
    const ifb_ptr save_point_ptr = (ifb_ptr)save_point_address;

    //we're done
    return(save_point_ptr);
}

ifb_internal inline const ifb_ptr 
ifb_memory::linear_arena_get_pointer_at_start(
    const IFBMemoryLinearArenaHandle linear_arena_handle) {

    //get the arena pointer
    IFBMemoryLinearArena* linear_arena_ptr = ifb_memory::linear_arena_handle_to_pointer(linear_arena_handle);

    //get the pointer
    const ifb_address arena_start = linear_arena_ptr->start;
    const ifb_ptr     pointer     = (ifb_ptr)arena_start;

    //we're done
    return(pointer);
}

/**********************************************************************************/
/* INFO                                                                           */
/**********************************************************************************/

ifb_internal inline const ifb_b8 
ifb_memory::linear_arena_get_info(
    const IFBMemoryLinearArenaHandle linear_arena_handle,
          IFBMemoryLinearArenaInfo*  linear_arena_info_ptr) {

    //get the arena pointer
    IFBMemoryLinearArena* linear_arena_ptr = ifb_memory::linear_arena_handle_to_pointer(linear_arena_handle);

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

ifb_internal inline IFBMemoryLinearArena* 
ifb_memory::linear_arena_handle_to_pointer(
    const IFBMemoryLinearArenaHandle linear_arena_handle) {

    //get the pointer
    IFBMemoryLinearArena* linear_arena_ptr = ifb_memory_macro_stack_get_type_pointer(
        linear_arena_handle.offset,
        IFBMemoryLinearArena);

    //sanity check
    ifb_macro_assert(linear_arena_ptr);

    //we're done
    return(linear_arena_ptr);
}