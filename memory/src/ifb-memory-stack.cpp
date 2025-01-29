#pragma once

#include "ifb-memory-internal.hpp"

/**********************************************************************************/
/* PUSH                                                                           */
/**********************************************************************************/

inline const IFBMemoryHandle
ifb_memory::stack_push(
          IFBMemory* memory_ptr,
    const ifb_u32    size) {

    IFBMemoryHandle memory_handle = {0};

    //sanity check
    if (!memory_ptr || size == 0) {
        return(memory_handle);
    }

    //cache the stack
    IFBMemoryStack& stack_ref = memory_ptr->stack;

    //make sure we can fit the push
    const ifb_u32 new_size = stack_ref.position + size; 
    if (new_size >= stack_ref.size) {
        return(memory_handle);
    }

    //get the current offset
    memory_handle.stack_offset = stack_ref.position;

    //update the stack position
    stack_ref.position += size;

    //we're done
    return(memory_handle);
}

inline const IFBMemoryHandle
ifb_memory::stack_push_aligned(
          IFBMemory* memory_ptr,
    const ifb_u32    size,
    const ifb_u32    alignment) {

    //sanity check
    if (alignment == 0) {
        return({0});
    }

    //align the size
    const ifb_u32 size_aligned = ifb_macro_align_a_to_b(size,alignment);

    //do the push
    const IFBMemoryHandle memory_handle = ifb_memory::stack_push(
        memory_ptr,
        size_aligned);

    //we're done
    return(memory_handle);
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