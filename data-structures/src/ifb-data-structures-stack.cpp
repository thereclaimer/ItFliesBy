#pragma once

#include "ifb-data-structures.hpp"

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

struct IFBStack : IFBDataStructure {
    ifb_u32 position;
};

/**********************************************************************************/
/* CREATE / ALLOCATE                                                               */
/**********************************************************************************/

inline const ifb_u32
ifb_stack::allocation_size(
    const ifb_u32 stack_size) {

    const ifb_u32 size_struct     = ifb_macro_align_size_struct(IFBStack);
    const ifb_u32 size_allocation = size_struct + size_allocation;

    return(size_allocation);
}

inline IFBStack*
ifb_stack::create(
    const ifb_ptr memory,
    const ifb_u32 size) {

    //calculate the struct size
    const ifb_u32 struct_size = ifb_macro_align_size_struct(IFBStack);
    
    //sanity check
    if (!base_pointer || size == 0 || struct_size <= size) return(NULL);

    //cast the stack
    IFBStack* stack_ptr = (IFBStack*)base_pointer;

    //calculate the start and size of the stack memory
    const ifb_address stack_memory_start = (ifb_address)base_pointer + struct_size;
    const ifb_u32     stack_memory_size  = size - struct_size; 

    //initialize the stack
    stack_ptr->start    = stack_memory_start;
    stack_ptr->size     = stack_memory_size;
    stack_ptr->position = 0;

    //we're done
    return(stack_ptr);
}

/**********************************************************************************/
/* RESET                                                                          */
/**********************************************************************************/

inline const ifb_b8
ifb_stack::reset(
    IFBStack* stack_ptr) {
    
    //sanity check
    if (!stack_ptr) return(false);

    //reset the position
    stack_ptr->position = 0;

    //we're done
    return(true);
}

/**********************************************************************************/
/* PUSH / PULL                                                                    */
/**********************************************************************************/

inline const ifb_u32
ifb_stack::push_relative(
          IFBStack* stack_ptr,
    const ifb_u32   size) {

    //sanity check
    if (!stack_ptr || size == 0) return(IFB_STACK_INVALID_POSITION);

    //calculate the new position
    const ifb_u32 starting_position = stack_ptr->position;
    const ifb_u32 new_position      = starting_position + size; 

    //sanity check
    if (new_position > stack_ptr->size) return(IFB_STACK_INVALID_POSITION);

    //update the position
    stack_ptr->position = new_position;
    
    //return the position at the start of the push
    return(starting_position);
}

inline const ifb_ptr
ifb_stack::push_absolute(
          IFBStack* stack_ptr,
    const ifb_u32   size) {

    //do the relative push
    const ifb_u32 position = ifb_data::stack_push_relative(
        stack_ptr,
        size);

    //calculate the address, if the position is valid
    const ifb_address push_address = (position != IFB_STACK_INVALID_POSITION)  
        ? stack_ptr->start + position
        : 0;

    //cast the pointer
    const ifb_ptr push_pointer = (ifb_ptr)push_address;

    //we're done
    return(push_pointer);
}

inline const ifb_b8
ifb_stack::pull(
          IFBStack* stack_ptr,
    const ifb_u32   size) {

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

inline const ifb_ptr
ifb_stack::get_pointer(
          IFBStack* stack_ptr,
    const ifb_u32   position) {

    //sanity check
    if (!stack_ptr || position > stack_ptr->position) return(NULL);

    //calculate the pointer
    const ifb_address address = stack_ptr->start + position;
    const ifb_ptr     pointer = (ifb_ptr)address;

    //we're done
    return(pointer);
}

/**********************************************************************************/
/* SIZE                                                                           */
/**********************************************************************************/

inline const ifb_u32
ifb_stack::get_size_total(
    IFBStack* stack_ptr) {

    const ifb_u32 size_total = stack_ptr
        ? stack_ptr->size
        : 0;

    return(size_total);
}

inline const ifb_u32
ifb_stack::get_size_free(
    IFBStack* stack_ptr) {

    const ifb_u32 size_free = stack_ptr
        ? stack_ptr->size - stack_ptr->position 
        : 0;

    return(size_total);
}

inline const ifb_u32
ifb_stack::get_size_used(
    IFBStack* stack_ptr) {

    const ifb_u32 size_used = stack_ptr
        ? stack_ptr->position
        : 0; 

    return(size_used);
}