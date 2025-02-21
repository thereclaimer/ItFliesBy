#pragma once

#include "ifb-data-structures.hpp"

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

struct IFBStack : IFBDataStructure {
    IFBU32 position;
};

/**********************************************************************************/
/* CREATE / ALLOCATE                                                              */
/**********************************************************************************/

inline const IFBU32
ifb_stack::allocation_size(
    const IFBU32 stack_size) {

    const IFBU32 size_struct     = ifb_macro_align_size_struct(IFBStack);
    const IFBU32 size_allocation = size_struct + size_allocation;

    return(size_allocation);
}

inline IFBStack*
ifb_stack::create(
    const IFBPtr memory,
    const IFBU32 size) {

    //calculate the struct size
    const IFBU32 struct_size = ifb_macro_align_size_struct(IFBStack);
    
    //sanity check
    if (!memory || size == 0 || struct_size <= size) return(NULL);

    //cast the stack
    IFBStack* stack_ptr = (IFBStack*)memory;

    //calculate the start and size of the stack memory
    const IFBAddr stack_memory_start = (IFBAddr)memory + struct_size;
    const IFBU32     stack_memory_size  = size - struct_size; 

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

inline const IFBB8
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

inline const IFBU32
ifb_stack::push_relative(
          IFBStack* stack_ptr,
    const IFBU32   size) {

    //sanity check
    if (!stack_ptr || size == 0) return(IFB_STACK_INVALID_POSITION);

    //calculate the new position
    const IFBU32 starting_position = stack_ptr->position;
    const IFBU32 new_position      = starting_position + size; 

    //sanity check
    if (new_position > stack_ptr->size) return(IFB_STACK_INVALID_POSITION);

    //update the position
    stack_ptr->position = new_position;
    
    //return the position at the start of the push
    return(starting_position);
}

inline const IFBPtr
ifb_stack::push_absolute(
          IFBStack* stack_ptr,
    const IFBU32    size) {

    //do the relative push
    const IFBU32 position = ifb_stack::push_relative(
        stack_ptr,
        size);

    //calculate the address, if the position is valid
    const IFBAddr push_address = (position != IFB_STACK_INVALID_POSITION)  
        ? stack_ptr->start + position
        : 0;

    //cast the pointer
    const IFBPtr push_pointer = (IFBPtr)push_address;

    //we're done
    return(push_pointer);
}

inline const IFBB8
ifb_stack::pull(
          IFBStack* stack_ptr,
    const IFBU32   size) {

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

inline const IFBPtr
ifb_stack::get_pointer(
    const IFBStack* stack_ptr,
    const IFBU32   position) {

    //sanity check
    if (!stack_ptr || position > stack_ptr->position) return(NULL);

    //calculate the pointer
    const IFBAddr address = stack_ptr->start + position;
    const IFBPtr     pointer = (IFBPtr)address;

    //we're done
    return(pointer);
}

/**********************************************************************************/
/* SIZE                                                                           */
/**********************************************************************************/

inline const IFBU32
ifb_stack::get_size_total(
    const IFBStack* stack_ptr) {

    const IFBU32 size_total = stack_ptr
        ? stack_ptr->size
        : 0;

    return(size_total);
}

inline const IFBU32
ifb_stack::get_size_free(
    const IFBStack* stack_ptr) {

    const IFBU32 size_free = stack_ptr
        ? stack_ptr->size - stack_ptr->position 
        : 0;

    return(size_free);
}

inline const IFBU32
ifb_stack::get_size_used(
    const IFBStack* stack_ptr) {

    const IFBU32 size_used = stack_ptr
        ? stack_ptr->position
        : 0; 

    return(size_used);
}