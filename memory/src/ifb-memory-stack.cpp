#pragma once

#include "ifb-memory-internal.hpp"

/**********************************************************************************/
/* PUSH ABSOLUTE                                                                  */
/**********************************************************************************/

inline const ifb_ptr
ifb_memory::stack_push(
    const IFBMemoryHandle memory_handle,
    const ifb_u32         size) {

    //cast the memory
    IFBMemory* memory_ptr = (IFBMemory*)memory_handle;
    if (!memory_ptr || size == 0) return(NULL);

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

inline const ifb_ptr
ifb_memory::stack_push_aligned(
    const IFBMemoryHandle memory_handle,
    const ifb_u32         size,
    const ifb_u32         alignment) {

    //sanity check
    if (alignment == 0) return(NULL);

    //align the size
    const ifb_u32 size_aligned = ifb_macro_align_a_to_b(size,alignment);

    //do the push
    const ifb_ptr pointer = ifb_memory::stack_push(
        memory_handle,
        size_aligned);

    //we're done
    return(pointer);
}

/**********************************************************************************/
/* PUSH RELATIVE                                                                  */
/**********************************************************************************/

inline const ifb_u32
ifb_memory::stack_push_relative(
    const IFBMemoryHandle memory_handle,
    const ifb_ptr         reference, 
    const ifb_u32         size) {

    //sanity check
    if (
        memory_handle == NULL ||
        reference     == NULL ||
        size          == 0) {

        return(0);
    }

    //cast the handle and cache the stack
    IFBMemory*      memory_ptr = (IFBMemory*)memory_handle;
    IFBMemoryStack& stack_ref  = memory_ptr->stack;

    //calculate the addresses
    const ifb_address address_stack             = (ifb_address)memory_ptr; 
    const ifb_address address_reference         = (ifb_address)reference;
    const ifb_address address_reference_minimum = address_stack + sizeof(IFBMemory);
    const ifb_address address_relative          = reference_address + stack_ref.position;

    //calculate the new stack position
    const ifb_u32 new_position = stack_ref.position + size; 

    //sanity check everything
    ifb_b8 result = true;                                     // this is a valid push                                   IF...
    result &= address_reference >= address_reference_minimum; // the reference is ahead of the memory structure         AND...
    result &= address_relative  <  stack_ref.end;             // the result address is before the end of the stack      AND... 
    result &= address_relative  >  address_reference          // the relative address is ahead of the reference address AND...
    result &= new_position      <  stack_ref.size;            // the new stack position is within the stack size
    if (!result) return(0);

    //get the relative position
    const ifb_u32 relative_position = (ifb_u32)(address_relative - address_reference);

    //we're done
    return(relative_position);
}   

inline const ifb_u32
ifb_memory::stack_push_relative_aligned(
    const IFBMemoryHandle memory_handle,
    const ifb_ptr         reference, 
    const ifb_u32         size,
    const ifb_u32         alignment) {

}

/**********************************************************************************/
/* POINTERS                                                                       */
/**********************************************************************************/

inline const ifb_ptr
ifb_memory::stack_get_pointer(
          IFBMemory*      memory_ptr,
    const IFBMemoryHandle memory_handle) {
    
    //sanity check
    if (!memory_ptr                     || 
        memory_handle.stack_offset == 0 || 
        memory_handle.stack_offset >= memory_ptr->stack.size) {
        
        return(NULL);
    }

    //calculate the pointer address
    const ifb_address stack_start   = (ifb_address)memory_ptr;
    const ifb_address pointer_start = stack_start + memory_handle.stack_offset;
    const ifb_ptr     pointer       = (ifb_ptr)pointer_start;  

    //we're done
    return(pointer);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline const IFBMemoryHandle
ifb_memory::stack_push_arenas(
         IFBMemory* memory_ptr,
    const ifb_u32   arena_count) {

    //sanity check
    if (arena_count == 0) {
        return({0});
    }

    //calculate the array size
    const ifb_u32 arena_array_size = ifb_macro_size_array(IFBMemoryArena,arena_count);

    //push the arenas on the stack
    const IFBMemoryHandle arena_array_handle = ifb_memory::stack_push(
        memory_ptr,
        arena_array_size);

    //we're done
    return(arena_array_handle);
}

inline const IFBMemoryBlockAllocatorHandle
ifb_memory::stack_push_block_allocator(
          IFBMemory* memory_ptr,
    const ifb_u32    block_count) {

    //sanity check
    if (block_count == 0) {
        return({0});
    }

    //calculate the push size
    const ifb_u32 block_flag_count          = ifb_macro_align_a_to_multiple_of_b(block_count, IFB_MEMORY_BLOCK_FLAG_BIT_COUNT);
    const ifb_u32 block_flag_array_size     = ifb_macro_size_array(ifb_u32,block_flag_count);
    const ifb_u32 block_allocator_size      = ifb_macro_align_size_struct(IFBMemoryBlockAllocator);
    const ifb_u32 block_allocator_push_size = block_allocator_size + block_flag_array_size;

    //do the push
    const IFBMemoryHandle memory_handle = ifb_memory::stack_push(memory_ptr,block_allocator_push_size);

    //get the pointer
    IFBMemoryBlockAllocator* block_allocator_ptr = ifb_memory::stack_get_pointer(
        memory_ptr,
        memory_handle);

    //calculate the handle
    IFBMemoryBlockAllocatorHandle block_allocator_handle;
    block_allocator_handle.allocator = (ifb_ptr)block_allocator_ptr; 

    //calculate the flags pointer and clear the flags
    ifb_u32* block_flags_array = (ifb_u32*)((ifb_address)block_allocator_handle + block_allocator_size); 
    for (
        ifb_u32 flag_index = 0;
        flag_index < block_flag_count;
        ++flag_index) {

        block_flags_array[flag_index] = 0;
    }

    //sanity check
    if (!block_allocator_ptr) {
        return({0});
    }

    //initialize the struct
    block_allocator_ptr->arena_handle      = {0};
    block_allocator_ptr->start             = 0;
    block_allocator_ptr->block_size        = 0;
    block_allocator_ptr->block_count       = block_count;
    block_allocator_ptr->block_flags_count = block_flag_count;
    block_allocator_ptr->block_flags_array = block_flags_array;

    //we're done
    return(block_allocator_handle);
}

inline const IFBMemoryStackAllocatorHandle
ifb_memory::stack_push_stack_allocator(
    IFBMemory* memory_ptr) {

    //do the push
    const IFBMemoryHandle memory_handle = ifb_memory_macro_stack_push_struct(memory_ptr,IFBMemoryStackAllocator);

    //get the pointer
    const ifb_ptr pointer = ifb_memory::stack_get_pointer(memory_ptr,memory_handle);

    //set the handle
    IFBMemoryStackAllocatorHandle allocator_handle;
    allocator_handle.allocator = pointer;

    //we're done
    return(allocator_handle);
}