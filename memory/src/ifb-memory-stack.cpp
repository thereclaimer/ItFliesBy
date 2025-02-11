#pragma once

#include "ifb-memory.hpp"
#include "ifb-memory-internal.hpp"

/**********************************************************************************/
/* PUSH ABSOLUTE                                                                  */
/**********************************************************************************/

ifb_internal inline const ifb_ptr
ifb_memory::stack_push(
          IFBMemory* memory_ptr,
    const ifb_u32    size) {

    //sanity check
    ifb_macro_assert(memory_ptr);
    if (size == 0) return(NULL);

    //cache the stack
    IFBMemoryStack& stack_ref = memory_ptr->stack;

    //make sure we can fit the push
    const ifb_u32 new_size = stack_ref.position + size; 
    if (new_size >= stack_ref.size) return(NULL);

    //get the pointer at the current position
    const ifb_address stack_address = (ifb_address)memory_ptr;
    const ifb_ptr     pointer       = (ifb_ptr)(stack_address + stack_ref.position); 

    //update the stack position
    stack_ref.position += new_size;

    //we're done
    return(pointer);
}

ifb_internal inline const ifb_ptr
ifb_memory::stack_push_aligned(
          IFBMemory* memory_ptr,
    const ifb_u32    size,
    const ifb_u32    alignment) {

    //align the size
    const ifb_u32 size_aligned = ifb_macro_align_a_to_b(size,alignment);

    //do the push
    const ifb_ptr pointer = ifb_memory::stack_push(
        memory_ptr,
        size_aligned);

    //we're done
    return(pointer);
}

/**********************************************************************************/
/* PUSH OFFSET                                                                    */
/**********************************************************************************/

ifb_internal inline const ifb_u32
ifb_memory::stack_push_offset(
          IFBMemory* memory_ptr,
    const ifb_u32    size) {

    //sanity check
    ifb_macro_assert(memory_ptr);
    if (size == 0) return(NULL);

    //cache the stack
    IFBMemoryStack& stack_ref = memory_ptr->stack;

    //make sure we can fit the push
    const ifb_u32 new_position = stack_ref.position + size; 
    if (new_position >= stack_ref.size) return(NULL);

    //get the position
    const ifb_u32 position = stack_ref.position; 

    //update the stack
    stack_ref.position += new_position;

    //we're done
    return(position);
}

ifb_internal inline const ifb_u32
ifb_memory::stack_push_offset_aligned(
          IFBMemory* memory_ptr,
    const ifb_u32    size,
    const ifb_u32    alignment) {

    const ifb_u32 size_aligned = ifb_macro_align_a_to_b(size,alignment);
    const ifb_u32 offset       = ifb_memory::stack_push_offset(
        memory_ptr,
        size_aligned);

    return(offset);
}

/**********************************************************************************/
/* PUSH RELATIVE                                                                  */
/**********************************************************************************/

ifb_internal inline const ifb_u32
ifb_memory::stack_push_relative(
          IFBMemory* memory_ptr,
    const ifb_ptr    reference, 
    const ifb_u32    size) {

    //sanity check
    ifb_macro_assert(memory_ptr);
    if (!reference || size == 0) return(0);

    //cast the handle and cache the stack
    IFBMemoryStack& stack_ref  = memory_ptr->stack;

    //calculate the addresses
    const ifb_address address_stack             = (ifb_address)memory_ptr; 
    const ifb_address address_reference         = (ifb_address)reference;
    const ifb_address address_reference_minimum = address_stack     + sizeof(IFBMemory);
    const ifb_address address_relative          = address_reference + stack_ref.position;

    //calculate the new stack position
    const ifb_u32 new_position = stack_ref.position + size; 

    //sanity check everything
    ifb_b8 result = true;                                     // this is a valid push                                   IF...
    result &= address_reference >= address_reference_minimum; // the reference is ahead of the memory structure         AND...
    result &= address_relative  <  stack_ref.end;             // the result address is before the end of the stack      AND... 
    result &= address_relative  >  address_reference;         // the relative address is ahead of the reference address AND...
    result &= new_position      <  stack_ref.size;            // the new stack position is within the stack size
    if (!result) return(0);

    //get the relative position
    const ifb_u32 relative_position = (ifb_u32)(address_relative - address_reference);

    //we're done
    return(relative_position);
}   

ifb_internal inline const ifb_u32
ifb_memory::stack_push_relative_aligned(
          IFBMemory* memory_ptr,
    const ifb_ptr    reference, 
    const ifb_u32    size,
    const ifb_u32    alignment) {

    const ifb_u32 size_aligned      = ifb_macro_align_a_to_b(size,alignment);
    const ifb_u32 relative_position = ifb_memory::stack_push_relative(
        memory_ptr,
        reference,
        size_aligned);

    return(relative_position);
}

/**********************************************************************************/
/* POINTERS                                                                       */
/**********************************************************************************/

ifb_internal inline const ifb_ptr
ifb_memory::stack_get_pointer(
    const IFBMemory* memory_ptr,
    const ifb_u32    offset) {

    //sanity check
    ifb_macro_assert(memory_ptr);

    //cache the stack properties
    const IFBMemoryStack&   stack_ref          = memory_ptr->stack;
    const ifb_u32           memory_struct_size = sizeof(IFBMemory); 
    const ifb_address       stack_start        = (ifb_address)memory_ptr;

    //make sure the offset is valid
    ifb_b8 offset_valid = true;                   // the offset is valid                      IF...
    offset_valid &= offset >= memory_struct_size; // the offset is ahead of the memory struct AND...
    offset_valid &= offset <  stack_ref.position; // the offset is before the current stack position

    //calculate the address
    const ifb_address address = offset_valid
        ? stack_start + offset
        : 0;

    //get the pointer
    const ifb_ptr pointer = (ifb_ptr)address;

    //we're done
    return(pointer);
}

ifb_internal inline const ifb_ptr 
ifb_memory::stack_get_pointer_relative(
    const IFBMemory* memory_ptr,
    const ifb_u32    reference,
    const ifb_u32    offset) {

    const ifb_u32 offset_absolute = reference + offset;
    const ifb_ptr pointer         = ifb_memory::stack_get_pointer(
        memory_ptr,
        offset_absolute);

    return(pointer);
}

/**********************************************************************************/
/* SIZE                                                                           */
/**********************************************************************************/

ifb_internal inline const ifb_u32
ifb_memory::stack_get_size_total(
    const IFBMemory* memory_ptr) {
       
    //sanity check
    ifb_macro_assert(memory_ptr);

    //return the stack size
    const ifb_u32 size_total = memory_ptr->stack.size;
    return(size_total);
}

ifb_internal inline const ifb_u32
ifb_memory::stack_get_size_free(
    const IFBMemory* memory_ptr) {
  
    //sanity check
    ifb_macro_assert(memory_ptr);

    //calculate the free size
    const ifb_u32 size_total = memory_ptr->stack.size;
    const ifb_u32 size_used  = memory_ptr->stack.position;
    const ifb_u32 size_free  = size_total - size_used;

    //we're done
    return(size_free);
}

ifb_internal inline const ifb_u32
ifb_memory::stack_get_size_used(
    const IFBMemory* memory_ptr) {
  
    //sanity check
    ifb_macro_assert(memory_ptr);

    //return the stack position
    const ifb_u32 size_used = memory_ptr->stack.position;
    return(size_used);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

IFBMemoryArena*
ifb_memory::stack_push_arena_base(
    IFBMemory* memory_ptr) {

    //allocate base arena struct
    IFBMemoryArena* arena_ptr = ifb_memory_macro_stack_push_struct(
        memory_ptr,
        IFBMemoryArena);
    
    //we're done
    return(arena_ptr);
}

IFBMemoryLinearArena*
ifb_memory::stack_push_arena_linear(
    IFBMemory* memory_ptr) {

    //allocate linear arena struct
    IFBMemoryLinearArena* linear_arena_ptr = ifb_memory_macro_stack_push_struct(
        memory_ptr,
        IFBMemoryLinearArena);

    //we're done
    return(linear_arena_ptr);
}


IFBMemoryBlockArena*
ifb_memory::stack_push_arena_block(
    IFBMemory* memory_ptr) {

    //calculate the push size
    const ifb_u32 block_arena_size = ifb_macro_align_size_struct(IFBMemoryBlockArena);

    //do the push
    IFBMemoryBlockArena* block_arena_ptr  = (IFBMemoryBlockArena*)ifb_memory::stack_push(memory_ptr,block_arena_size);

    //we're done
    return(block_arena_ptr);
}

IFBMemoryBlock*
ifb_memory::stack_push_arena_block_array(
          IFBMemory* memory_ptr,
    const ifb_u32    block_count) {

    //sanity check
    ifb_macro_assert(memory_ptr);
    if (block_count == 0) return(NULL);

    //calculate the push size
    const ifb_u32 push_size = ifb_macro_size_array(IFBMemoryBlock,block_count); 

    //do the push
    IFBMemoryBlock* block_array = (IFBMemoryBlock*)ifb_memory::stack_push(
        memory_ptr,
        push_size);

    //we're done
    return(block_array);
}