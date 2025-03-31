#pragma once

#include "ifb-memory.hpp"
#include "ifb-memory-internal.cpp"

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

mem_stack_t*
ifb_memory::stack_create(
    const memory_t& stack_memory) {

    //check args
    b8 can_create = true;                                            // we can create the stack IF...
    can_create &= (stack_memory.start != NULL);                         //...the memory isn't null AND
    can_create &= (stack_memory.size  >= IFB_MEMORY_STRUCT_SIZE_STACK); //...we can fit the struct in the memory
    if (!can_create) return(NULL);                              // if we can't create, we're done

    //cast the memory
    mem_stack_t* stack = (mem_stack_t*)stack_memory.start;
    
    //initialize the stack
    stack->size     = stack_memory.size;
    stack->position = IFB_MEMORY_STRUCT_SIZE_STACK;

    //we're done
    return(stack);
}

const u32
ifb_memory::stack_push_bytes_relative(
          mem_stack_t* stack,
    const u32      size) {

    //validate stack
    ifb_memory::validate_stack(stack);

    //calculate the new position
    const u32 stack_size         = stack->size;
    const u32 stack_offset       = stack->position;
    const u32 stack_position_new = stack_offset + size;

    //make sure we can fit the commit
    const b8 can_commit = (stack_position_new < stack_size); 
    if (!can_commit) return(NULL);

    //update the position
    stack->position = stack_position_new;
    
    //we're done
    return(stack_offset);
}

const ptr
ifb_memory::stack_push_bytes_absolute_pointer(
          mem_stack_t* stack,
    const u32      size) {

    //validate stack
    ifb_memory::validate_stack(stack);

    //calculate the new position
    const u32 stack_size         = stack->size;
    const u32 stack_offset       = stack->position;
    const u32 stack_position_new = stack_offset + size;

    //make sure we can fit the commit
    const b8 can_commit = (stack_position_new < stack_size); 
    if (!can_commit) return(NULL);

    //update the position
    stack->position = stack_position_new;
    
    //calculate the pointer
    const addr stack_result_offset  = (addr)stack + stack_offset;
    const ptr  stack_result_pointer = (ptr)stack_result_offset;

    //we're done
    return(stack_result_pointer);
}

const addr
ifb_memory::stack_push_bytes_absolute_address(
          mem_stack_t* stack,
    const u32          size) {

    //validate stack
    ifb_memory::validate_stack(stack);

    //calculate the new position
    const u32 stack_size         = stack->size;
    const u32 stack_offset       = stack->position;
    const u32 stack_position_new = stack_offset + size;

    //make sure we can fit the commit
    const b8 can_commit = (stack_position_new < stack_size); 
    if (!can_commit) return(NULL);

    //update the position
    stack->position = stack_position_new;
    
    //calculate the address
    const addr stack_result_offset = (addr)stack + stack_offset;

    //we're done
    return(stack_result_offset);
}

const ptr
ifb_memory::stack_get_pointer(
          mem_stack_t* stack,
    const u32          offset) {

    //validate stack
    ifb_memory::validate_stack(stack);

    //calculate the pointer
    const addr stack_offset  = ((addr)stack) + offset;
    const ptr  stack_pointer = (stack_offset < stack->size) ? (ptr)stack_offset : NULL; 
        
    //we're done
    return(stack_pointer);
}

const b8
ifb_memory::stack_pull_bytes(
          mem_stack_t* stack,
    const u32          size) {

    //validate stack
    ifb_memory::validate_stack(stack);

    //get sizes
    const u32 position_current = stack->position;
    const u32 position_dif     = position_current - IFB_MEMORY_STRUCT_SIZE_STACK; 
    const u32 position_new     = stack->position - size;

    //make sure we can pull
    //there has to be at least enough memory for the stack struct
    b8 can_pull = (size <= position_dif);
    if (!can_pull) return(false);

    //update the stack position
    stack->position = position_new;

    //we're done
    return(true);
}
