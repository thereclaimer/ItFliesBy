#pragma once

#include "ifb-data-structures.hpp"

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

IFBStack*    
ifb_stack::arena_load_pointer(
          IFBMemoryArena* ptr_arena,
    const ifb::u32          arena_offset) {

    IFBStack* pointer = (IFBStack*)ifb_memory::arena_get_pointer(
        ptr_arena,
        arena_offset);

    ifb_macro_assert(pointer);

    return(pointer);
}

IFBStack*    
ifb_stack::arena_commit_absolute(
          IFBMemoryArena* ptr_arena,
    const ifb::u32          stack_size) {

    //calculate the commit size
    const ifb::u32 struct_size = ifb_macro_align_size_struct(IFBStack);
    const ifb::u32 commit_size = struct_size + stack_size;

    //do the commit
    IFBStack* pointer = (IFBStack*)ifb_memory::arena_commit_bytes_absolute(
        ptr_arena,
        commit_size);

    //we're done
    return(pointer);
}

const ifb::u32 
ifb_stack::arena_commit_relative(
          IFBMemoryArena* ptr_arena,
    const ifb::u32          stack_size) {

    //calculate the commit size
    const ifb::u32 struct_size = ifb_macro_align_size_struct(IFBStack);
    const ifb::u32 commit_size = struct_size + stack_size;

    //do the commit
    ifb::u32 offset = ifb_memory::arena_commit_bytes_relative(
        ptr_arena,
        commit_size);

    //we're done
    return(offset);
}

/**********************************************************************************/
/* OPERATIONS                                                                     */
/**********************************************************************************/

const ifb::b8
ifb_stack::reset(
    IFBStack* stack_ptr) {
    
    //sanity check
    if (!stack_ptr) return(false);

    //reset the position
    stack_ptr->position = 0;

    //we're done
    return(true);
}

const ifb::u32
ifb_stack::push_relative(
          IFBStack* stack_ptr,
    const ifb::u32    size) {

    //sanity check
    if (!stack_ptr || size == 0) return(IFB_HANDLE_INVALID_U32);

    //calculate the new position
    const ifb::u32 starting_position = stack_ptr->position;
    const ifb::u32 new_position      = starting_position + size; 

    //sanity check
    if (new_position > stack_ptr->size) return(IFB_HANDLE_INVALID_U32);

    //update the position
    stack_ptr->position = new_position;
    
    //return the position at the start of the push
    return(starting_position);
}

const ifb::ptr
ifb_stack::push_absolute(
          IFBStack* stack_ptr,
    const ifb::u32    size) {

    //do the relative push
    const ifb::u32 position = ifb_stack::push_relative(
        stack_ptr,
        size);

    //calculate the address, if the position is valid
    const ifb::addr push_address = (position != IFB_HANDLE_INVALID_U32)  
        ? stack_ptr->start + position
        : 0;

    //cast the pointer
    const ifb::ptr push_pointer = (ifb::ptr)push_address;

    //we're done
    return(push_pointer);
}

const ifb::b8
ifb_stack::pull(
          IFBStack* stack_ptr,
    const ifb::u32   size) {

    //sanity check
    if (!stack_ptr || size > stack_ptr->position) return(false);

    //update the position
    stack_ptr->position -= size;

    //we're done
    return(true);
}

/**********************************************************************************/
/* POINTERS                                                                       */
/**********************************************************************************/

const ifb::ptr
ifb_stack::get_pointer(
    const IFBStack* stack_ptr,
    const ifb::u32    position) {

    //sanity check
    if (!stack_ptr || position > stack_ptr->position) return(NULL);

    //calculate the pointer
    const ifb::addr address = stack_ptr->start + position;
    const ifb::ptr  pointer = (ifb::ptr)address;

    //we're done
    return(pointer);
}

/**********************************************************************************/
/* SIZE                                                                           */
/**********************************************************************************/

const ifb::u32
ifb_stack::get_size_total(
    const IFBStack* stack_ptr) {

    const ifb::u32 size_total = stack_ptr
        ? stack_ptr->size
        : 0;

    return(size_total);
}

const ifb::u32
ifb_stack::get_size_free(
    const IFBStack* stack_ptr) {

    const ifb::u32 size_free = stack_ptr
        ? stack_ptr->size - stack_ptr->position 
        : 0;

    return(size_free);
}

const ifb::u32
ifb_stack::get_size_used(
    const IFBStack* stack_ptr) {

    const ifb::u32 size_used = stack_ptr
        ? stack_ptr->position
        : 0; 

    return(size_used);
}