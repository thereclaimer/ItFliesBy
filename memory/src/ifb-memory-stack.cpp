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

    IFBVoid stack_assert_valid (const IFBMemoryStack* stack);
};

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

IFBMemoryStack*
ifb_memory::stack_create(
    const IFBByte* stack_memory,
    const IFBU32   stack_size) {

    //check args
    IFBB8 can_create = true;                                      // we can create the stack IF...
    can_create &= (stack_memory != NULL);                         //...the memory isn't null AND
    can_create &= (stack_size   >= IFB_MEMORY_STACK_STRUCT_SIZE); //...we can fit the struct in the memory
    if (!can_create) return(NULL);                                // if we can't create, we're done

    //cast the memory
    IFBMemoryStack* stack = (IFBMemoryStack*)stack_memory;
    
    //initialize the stack
    stack->size     = stack_size;
    stack->position = IFB_MEMORY_STACK_STRUCT_SIZE;

    //we're done
    return(stack);
}

const IFBU32
ifb_memory::stack_commit_bytes_relative(
          IFBMemoryStack* stack,
    const IFBU32          size,
    const IFBU32          alignment) {

    //validate stack
    ifb_memory::stack_assert_valid(stack);

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
    
    //we're done
    return(stack_offset);
}

const IFBPtr
ifb_memory::stack_commit_bytes_absolute(
          IFBMemoryStack* stack,
    const IFBU32          size,
    const IFBU32          alignment) {

    //validate stack
    ifb_memory::stack_assert_valid(stack);

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
    const IFBAddr stack_start          = (IFBAddr)stack;
    const IFBAddr stack_result_offset  = stack_start + stack_offset;
    const IFBPtr  stack_result_pointer = (IFBPtr)stack_result_offset;

    //we're done
    return(stack_result_pointer);
}

const IFBPtr
ifb_memory::stack_get_pointer(
          IFBMemoryStack* stack,
    const IFBU32          offset) {

    //validate stack
    ifb_memory::stack_assert_valid(stack);

    //calculate the pointer
    const IFBAddr stack_start   = (IFBAddr)stack;
    const IFBAddr stack_offset  = stack_start + offset;
    const IFBPtr  stack_pointer = (stack_offset < stack->size) ? (IFBPtr)stack_offset : NULL; 
        
    //we're done
    return(stack_pointer);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline IFBVoid
ifb_memory::stack_assert_valid(
    const IFBMemoryStack* stack) {

    ifb_macro_assert(stack);
    ifb_macro_assert(stack->size     >= IFB_MEMORY_STACK_STRUCT_SIZE);
    ifb_macro_assert(stack->position >= IFB_MEMORY_STACK_STRUCT_SIZE);
    ifb_macro_assert(stack->position <  stack->size);
}