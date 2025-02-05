#pragma once

#include "ifb-memory-internal.hpp"

/**********************************************************************************/
/* COMMIT                                                                         */
/**********************************************************************************/

const IFBMemoryLinearArenaHandle
ifb_memory::linear_arena_commit(
    const IFBMemoryHandle memory_handle,
    const ifb_u32         arena_size_minimum) {
    
    //cast the handle
    IFBMemory* memory_ptr = (IFBMemory*)memory_handle;
    if (!memory_ptr || arena_size_minimum == 0) return(NULL);

    //allocate the arena structure
    IFBMemoryLinearArena* linear_arena_ptr = ifb_memory::stack_push_arena_linear(memory_ptr);
    if (!linear_arena_ptr) return(NULL);

    //commit the pages for the arena
    linear_arena_ptr->page_commit.size = arena_size_minimum;
    const ifb_b8 commit_result = ifb_memory::reservation_page_commit(memory_ptr,linear_arena_ptr->page_commit);

    //this MUST work, or everything is fucked up
    ifb_macro_assert(commit_result);

    //set the arena properties
    linear_arena_ptr->type       = IFBMemoryArenaType_Linear;
    linear_arena_ptr->position   = 0; 
    linear_arena_ptr->save_point = 0; 

    //add the arena to the list
    const ifb_b8 arena_list_result = ifb_memory::arena_list_add(
        memory_ptr->arena_list,
        linear_arena_ptr);

    //again, MUST work
    ifb_macro_assert(arena_list_result);

    //we're done
    return(linear_arena_ptr);
}

/**********************************************************************************/
/* SAVE POINT                                                                     */
/**********************************************************************************/

inline const ifb_ptr
ifb_memory::linear_arena_save_point_set(
    const IFBMemoryLinearArenaHandle linear_arena_handle) {

    //cast the handle
    ifb_macro_assert(linear_arena_handle);
    IFBMemoryLinearArena* linear_arena_ptr = (IFBMemoryLinearArena*)linear_arena_handle;

    //update the save point to the position
    linear_arena_ptr->save_point = linear_arena_ptr->position; 

    //get the pointer at the save point
    const ifb_ptr save_point_ptr = ifb_memory::arena_get_pointer(
        linear_arena_handle,
        linear_arena_ptr->save_point);

    //we're done
    return(save_point_ptr);
}

inline const ifb_ptr
ifb_memory::linear_arena_save_point_clear(
    const IFBMemoryLinearArenaHandle linear_arena_handle) {

    //cast the handle
    ifb_macro_assert(linear_arena_handle);
    IFBMemoryLinearArena* linear_arena_ptr = (IFBMemoryLinearArena*)linear_arena_handle;

    //clear the save point
    linear_arena_ptr->save_point = 0;

    //get the pointer at the save point
    const ifb_ptr save_point_ptr = ifb_memory::arena_get_pointer(
        linear_arena_handle,
        linear_arena_ptr->save_point);

    //we're done
    return(save_point_ptr);
}

inline const ifb_ptr
ifb_memory::linear_arena_save_point_get(
    const IFBMemoryLinearArenaHandle linear_arena_handle) {

    //cast the handle
    ifb_macro_assert(linear_arena_handle);
    IFBMemoryLinearArena* linear_arena_ptr = (IFBMemoryLinearArena*)linear_arena_handle;

    //get the pointer at the save point
    const ifb_ptr save_point_ptr = ifb_memory::arena_get_pointer(
        linear_arena_handle,
        linear_arena_ptr->save_point);

    //we're done
    return(save_point_ptr);
}


/**********************************************************************************/
/* RESET                                                                          */
/**********************************************************************************/

inline const ifb_ptr
ifb_memory::linear_arena_reset(
    const IFBMemoryLinearArenaHandle linear_arena_handle) {

    //cast the handle
    ifb_macro_assert(linear_arena_handle);
    IFBMemoryLinearArena* linear_arena_ptr = (IFBMemoryLinearArena*)linear_arena_handle;

    //clear the position
    linear_arena_ptr->position = 0;

    //get the pointer at the position
    const ifb_ptr position = ifb_memory::arena_get_pointer(
        linear_arena_handle,
        linear_arena_ptr->position);

    //we're done
    return(position);    
}

inline const ifb_ptr
ifb_memory::linear_arena_reset_to_save_point(
    const IFBMemoryLinearArenaHandle linear_arena_handle) {

    //cast the handle
    ifb_macro_assert(linear_arena_handle);
    IFBMemoryLinearArena* linear_arena_ptr = (IFBMemoryLinearArena*)linear_arena_handle;

    //set the position to the save point
    linear_arena_ptr->position = linear_arena_ptr->save_point;

    //get the pointer at the position
    const ifb_ptr position = ifb_memory::arena_get_pointer(
        linear_arena_handle,
        linear_arena_ptr->position);

    //we're done
    return(position);
}

/**********************************************************************************/
/* RESERVE/RELEASE                                                                */
/**********************************************************************************/

inline const ifb_ptr
ifb_memory::linear_arena_bytes_reserve(
    const IFBMemoryLinearArenaHandle linear_arena_handle,
    const ifb_u32                    size) {

    //cast the handle
    ifb_macro_assert(linear_arena_handle);
    IFBMemoryLinearArena* linear_arena_ptr = (IFBMemoryLinearArena*)linear_arena_handle;
    
    //sanity check
    if (size == 0)  return(NULL);

    //make sure we can reserve the bytes
    const ifb_u32 reservation_position  = linear_arena_ptr->position;
    const ifb_u32 new_position          = reservation_position + size;
    if (new_position >= linear_arena_ptr->page_commit.size) return(NULL);

    //update the position
    linear_arena_ptr->position = new_position;

    //get the reservation pointer
    const ifb_ptr reservation_ptr = ifb_memory::arena_get_pointer(
        linear_arena_handle,
        reservation_position);

    //we're done
    return(reservation_ptr);
}

inline const ifb_ptr
ifb_memory::linear_arena_bytes_release(
    const IFBMemoryLinearArenaHandle linear_arena_handle,
    const ifb_u32                    size) {
    
    //cast the handle
    ifb_macro_assert(linear_arena_handle);
    IFBMemoryLinearArena* linear_arena_ptr = (IFBMemoryLinearArena*)linear_arena_handle;

    //make sure we can release the bytes
    if (size == 0 || size > linear_arena_ptr->page_commit.size) return(NULL);

    //update the position
    linear_arena_ptr->position -= size;

    //get the pointer
    const ifb_ptr pointer = ifb_memory::arena_get_pointer(
        linear_arena_handle,
        linear_arena_ptr->position);

    //we're done
    return(pointer);
}

inline const ifb_ptr
ifb_memory::linear_arena_bytes_reserve_aligned(
    const IFBMemoryLinearArenaHandle linear_arena_handle,
    const ifb_u32                    size, 
    const ifb_u32                    alignment) {

    //cast the handle
    ifb_macro_assert(linear_arena_handle);
    IFBMemoryLinearArena* linear_arena_ptr = (IFBMemoryLinearArena*)linear_arena_handle;

    //align the size
    const ifb_u32 size_aligned = ifb_macro_align_a_to_b(size,alignment);

    //do the reservation
    const ifb_ptr reservation_ptr = ifb_memory::linear_arena_bytes_reserve(
        linear_arena_handle,
        size_aligned);

    //we're done
    return(reservation_ptr);
}

inline const ifb_ptr
ifb_memory::linear_arena_bytes_release_aligned(
    const IFBMemoryLinearArenaHandle linear_arena_handle,
    const ifb_u32                    size, 
    const ifb_u32                    alignment) {

    //cast the handle
    ifb_macro_assert(linear_arena_handle);
    IFBMemoryLinearArena* linear_arena_ptr = (IFBMemoryLinearArena*)linear_arena_handle;

    //align the size
    const ifb_u32 size_aligned = ifb_macro_align_a_to_b(size,alignment);

    //do the release
    const ifb_ptr release_ptr = ifb_memory::linear_arena_bytes_release(
        linear_arena_handle,
        size_aligned);

    //we're done
    return(release_ptr);
}

/**********************************************************************************/
/* SIZE                                                                           */
/**********************************************************************************/

inline const ifb_u32
ifb_memory::linear_arena_get_size_total(
    const IFBMemoryLinearArenaHandle linear_arena_handle) {

    //cast the handle
    ifb_macro_assert(linear_arena_handle);
    IFBMemoryLinearArena* linear_arena_ptr = (IFBMemoryLinearArena*)linear_arena_handle;

    //return the size
    const ifb_u32 arena_size = linear_arena_ptr->page_commit.size;
    return(arena_size);
}

inline const ifb_u32
ifb_memory::linear_arena_get_size_used(
    const IFBMemoryLinearArenaHandle linear_arena_handle) {

    //cast the handle
    ifb_macro_assert(linear_arena_handle);
    IFBMemoryLinearArena* linear_arena_ptr = (IFBMemoryLinearArena*)linear_arena_handle;

    //return the position
    const ifb_u32 position = linear_arena_ptr->position;
    return(position);
}

inline const ifb_u32
ifb_memory::linear_arena_get_size_free(
    const IFBMemoryLinearArenaHandle linear_arena_handle) {

    //cast the handle
    ifb_macro_assert(linear_arena_handle);
    IFBMemoryLinearArena* linear_arena_ptr = (IFBMemoryLinearArena*)linear_arena_handle;

    //calculate the free size
    const ifb_u32 arena_size = linear_arena_ptr->page_commit.size;
    const ifb_u32 position   = linear_arena_ptr->position;
    const ifb_u32 size_free  = arena_size - position; 

    //we're done
    return(size_free);
}