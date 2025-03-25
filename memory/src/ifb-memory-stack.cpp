#pragma once

#include "ifb-memory.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

#define IFB_MEMORY_STACK_STRUCT_SIZE ifb_macro_align_size_struct(IFBMemoryStack)

struct IFBMemoryStack {
    IFBU32  size;
    IFBU32  position;
};

namespace ifb_memory {

    IFBMemoryStack* stack_cast_and_assert_valid (const IFBMEM64Stack stack_handle);
};

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

const IFBMEM64Stack
ifb_memory::stack_create(
    const IFBMemory& stack_memory) {

    IFBMEM64Stack stack_handle;
    stack_handle.h64 = IFB_MEMORY_INVALID_HANDLE_64;

    //check args
    IFBB8 can_create = true;                                            // we can create the stack IF...
    can_create &= (stack_memory.start != NULL);                         //...the memory isn't null AND
    can_create &= (stack_memory.size  >= IFB_MEMORY_STACK_STRUCT_SIZE); //...we can fit the struct in the memory
    if (!can_create) return(stack_handle);                              // if we can't create, we're done

    //cast the memory
    IFBMemoryStack* stack_internal = (IFBMemoryStack*)stack_memory.start;
    
    //initialize the stack
    stack_internal->size     = stack_memory.size;
    stack_internal->position = IFB_MEMORY_STACK_STRUCT_SIZE;

    //get the address
    stack_handle.h64 = (IFBAddr)stack_memory.start;

    //we're done
    return(stack_handle);
}

const IFBU32
ifb_memory::stack_push_bytes_relative(
    const IFBMEM64Stack stack,
    const IFBU32        size,
    const IFBU32        alignment) {

    //validate stack
    IFBMemoryStack* stack_internal = stack_cast_and_assert_valid(stack);

    //calculate the aligned size
    const IFBU32 size_aligned = ifb_macro_align_a_to_b(size,alignment);

    //calculate the new position
    const IFBU32 stack_size         = stack_internal->size;
    const IFBU32 stack_offset       = stack_internal->position;
    const IFBU32 stack_position_new = stack_offset + size_aligned;

    //make sure we can fit the commit
    const IFBB8 can_commit = (stack_position_new < stack_size); 
    if (!can_commit) return(NULL);

    //update the position
    stack_internal->position = stack_position_new;
    
    //we're done
    return(stack_offset);
}

const IFBPtr
ifb_memory::stack_push_bytes_absolute(
    const IFBMEM64Stack stack_handle,
    const IFBU32        size,
    const IFBU32        alignment) {

    //validate stack
    IFBMemoryStack* stack = ifb_memory::stack_cast_and_assert_valid(stack_handle);

    //calculate the aligned size
    const IFBU32 size_aligned = ifb_macro_align_a_to_b(size,alignment);

    //calculate the new position
    const IFBU32 stack_size         = stack->size;
    const IFBU32 stack_offset       = stack->position;
    const IFBU32 stack_position_new = stack_offset + size_aligned;

    //make sure we can fit the commit
    const IFBB8 can_commit = (stack_position_new < stack_size); 
    if (!can_commit) return(NULL);

    //update the position
    stack->position = stack_position_new;
    
    //calculate the pointer
    const IFBAddr stack_result_offset  = stack_handle.h64 + stack_offset;
    const IFBPtr  stack_result_pointer = (IFBPtr)stack_result_offset;

    //we're done
    return(stack_result_pointer);
}

const IFBPtr
ifb_memory::stack_get_pointer(
    const IFBMEM64Stack stack_handle,
    const IFBU32        offset) {

    //validate stack
    IFBMemoryStack* stack = ifb_memory::stack_cast_and_assert_valid(stack_handle);

    //calculate the pointer
    const IFBAddr stack_offset  = stack_handle.h64 + offset;
    const IFBPtr  stack_pointer = (stack_offset < stack->size) ? (IFBPtr)stack_offset : NULL; 
        
    //we're done
    return(stack_pointer);
}

const IFBB8
ifb_memory::stack_pull_bytes(
    const IFBMEM64Stack stack,
    const IFBU32        size,
    const IFBU32        alignment) {

    //validate stack
    IFBMemoryStack* stack_internal = ifb_memory::stack_cast_and_assert_valid(stack);

    //get sizes
    const IFBU32 size_aligned     = ifb_macro_align_a_to_b(size,alignment);
    const IFBU32 position_current = stack_internal->position;
    const IFBU32 position_dif     = position_current - IFB_MEMORY_STACK_STRUCT_SIZE; 
    const IFBU32 position_new     = stack_internal->position - size_aligned;

    //make sure we can pull
    //there has to be at least enough memory for the stack struct
    IFBB8 can_pull = (size <= position_dif);
    if (!can_pull) return(false);

    //update the stack position
    stack_internal->position = position_new;

    //we're done
    return(true);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline IFBMemoryStack*
ifb_memory::stack_cast_and_assert_valid(
    const IFBMEM64Stack stack_handle) {

    IFBMemoryStack* stack = (IFBMemoryStack*)stack_handle.h64;

    ifb_macro_assert(stack);
    ifb_macro_assert(stack->size     >= IFB_MEMORY_STACK_STRUCT_SIZE);
    ifb_macro_assert(stack->position >= IFB_MEMORY_STACK_STRUCT_SIZE);
    ifb_macro_assert(stack->position <  stack->size);

    return(stack);
}   