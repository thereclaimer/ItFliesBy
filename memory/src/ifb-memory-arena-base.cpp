#pragma once

#include "ifb-memory-internal.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb_memory {

    inline IFBMemoryArena* arena_handle_to_pointer(const IFBMemoryArenaHandle arena_handle);
};

/**********************************************************************************/
/* POINTERS                                                                       */
/**********************************************************************************/

ifb_internal inline const ifb_ptr
ifb_memory::arena_get_pointer(
    const IFBMemoryArenaHandle arena_handle,
    const ifb_u32              offset) {

    //get the arena and reservation
    IFBMemoryArena*       arena_ptr       = ifb_memory::arena_handle_to_pointer(arena_handle);
    IFBMemoryReservation* reservation_ptr = arena_ptr->reservation; 

    //sanity check
    ifb_macro_assert(reservation_ptr);

    //calcualte the addresses
    const ifb_u32     arena_offset      = ifb_memory::context_get_size_from_page_count(arena_ptr->page_start); 
    const ifb_u32     arena_size        = ifb_memory::context_get_size_from_page_count(arena_ptr->page_count);
    const ifb_address reservation_start = reservation_ptr->start;
    const ifb_address arena_start       = reservation_start + arena_offset;
    const ifb_address arena_end         = arena_start       + arena_size;
    const ifb_address pointer_offset    = arena_start       + offset;  

    //cast the pointer if its within the arena
    const ifb_b8  is_pointer_in_arena = pointer_offset < arena_end; 
    const ifb_ptr pointer             = is_pointer_in_arena ? (ifb_ptr)pointer_offset : NULL;

    //we're done
    return(pointer);
}

/**********************************************************************************/
/* INFO                                                                           */
/**********************************************************************************/

ifb_internal inline const ifb_b8
ifb_memory::arena_get_info(
    const IFBMemoryArenaHandle arena_handle,
          IFBMemoryArenaInfo*  arena_info_ptr) {

    //get the arena
    IFBMemoryArena* arena_ptr = ifb_memory::arena_handle_to_pointer(arena_handle);

    //sanity check
    if (!arena_info_ptr) return(false);

    //calculate the size
    const ifb_u32 page_count = arena_ptr->page_count; 
    const ifb_u32 arena_size = ifb_memory::context_get_size_from_page_count(page_count);

    //set the info
    arena_info_ptr->reservation_handle.offset = arena_ptr->reservation->stack_offset;
    arena_info_ptr->arena_handle.offset       = arena_ptr->stack_position;
    arena_info_ptr->page_start                = arena_ptr->page_start;
    arena_info_ptr->page_count                = arena_ptr->page_count;
    arena_info_ptr->size_total                = arena_size;

    //we're done
    return(true);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

ifb_internal inline IFBMemoryArena*
ifb_memory::arena_handle_to_pointer(
    const IFBMemoryArenaHandle arena_handle) {

    //get the pointer
    IFBMemoryArena* arena_ptr = ifb_memory_macro_stack_get_type_pointer(
        arena_handle.offset,
        IFBMemoryArena);

    //sanity check
    ifb_macro_assert(arena_ptr);

    //we're done
    return(arena_ptr);
}
