#include "ifb-memory-internal.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb_memory {

    inline IFBMemoryArena* arena_handle_to_pointer(const IFBHNDMemoryArena arena_handle);
};

/**********************************************************************************/
/* POINTERS                                                                       */
/**********************************************************************************/

const IFBPtr
ifb_memory::arena_get_pointer(
    const IFBHNDMemoryArena arena_handle,
    const IFBU32              offset) {

    //get the arena and reservation
    IFBMemoryArena*       arena_ptr       = ifb_memory::arena_handle_to_pointer(arena_handle);
    IFBMemoryReservation* reservation_ptr = arena_ptr->reservation; 

    //sanity check
    ifb_macro_assert(arena_ptr->reservation);

    //calcualte the addresses
    const IFBU32     arena_size        = arena_ptr->size_total;
    const IFBAddr arena_start       = arena_ptr->start;
    const IFBAddr arena_end         = arena_start + arena_size;
    const IFBAddr pointer_offset    = arena_start + offset;  

    //cast the pointer if its within the arena
    const IFBB8  is_pointer_in_arena = pointer_offset < arena_end; 
    const IFBPtr pointer             = is_pointer_in_arena ? (IFBPtr)pointer_offset : NULL;

    //we're done
    return(pointer);
}

/**********************************************************************************/
/* INFO                                                                           */
/**********************************************************************************/

const IFBB8
ifb_memory::arena_get_info(
    const IFBHNDMemoryArena arena_handle,
          IFBMemoryArenaInfo*  arena_info_ptr) {

    //get the arena
    IFBMemoryArena* arena_ptr = ifb_memory::arena_handle_to_pointer(arena_handle);

    //sanity check
    if (!arena_info_ptr) return(false);

    //set the info
    arena_info_ptr->reservation_handle.offset = arena_ptr->reservation->stack_offset;
    arena_info_ptr->arena_handle.offset       = arena_ptr->stack_position;
    arena_info_ptr->page_start                = arena_ptr->page_start;
    arena_info_ptr->page_count                = arena_ptr->page_count;
    arena_info_ptr->size_total                = arena_ptr->size_total;

    //we're done
    return(true);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

IFBMemoryArena*
ifb_memory::arena_handle_to_pointer(
    const IFBHNDMemoryArena arena_handle) {

    //get the pointer
    IFBMemoryArena* arena_ptr = ifb_memory_macro_stack_get_type_pointer(
        arena_handle.offset,
        IFBMemoryArena);

    //sanity check
    ifb_macro_assert(arena_ptr);

    //we're done
    return(arena_ptr);
}
