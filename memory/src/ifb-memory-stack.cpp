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
/* PUSH OFFSET                                                                    */
/**********************************************************************************/

inline const ifb_u32
ifb_memory::stack_push_offset(
    const IFBMemoryHandle memory_handle,
    const ifb_u32         size) {

    //cast the memory
    IFBMemory* memory_ptr = (IFBMemory*)memory_handle;
    if (!memory_ptr || size == 0) return(NULL);

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

inline const ifb_u32
ifb_memory::stack_push_offset_aligned(
    const IFBMemoryHandle memory_handle,
    const ifb_u32         size,
    const ifb_u32         alignment) {

    const ifb_u32 size_aligned = ifb_macro_align_a_to_b(size,alignment);
    const ifb_u32 offset       = ifb_memory::stack_push_offset(
        memory_handle,
        size_aligned);

    return(offset);
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

    const ifb_u32 size_aligned      = ifb_macro_align_a_to_b(size,alignment);
    const ifb_u32 relative_position = ifb_memory::stack_push_relative(
        memory_handle,
        reference,
        size_aligned);

    return(relative_position);
}

/**********************************************************************************/
/* POINTERS                                                                       */
/**********************************************************************************/

inline const ifb_ptr
ifb_memory::stack_get_pointer(
    const IFBMemoryHandle memory_handle,
    const ifb_u32         offset) {
    
    //cast the handle
    IFBMemory* memory_ptr = (IFBMemory*)memory_handle;
    if (!memory_ptr) return(NULL);

    //cache the stack properties
    IFBMemoryStack&   stack_ref          = memory_ptr->stack;
    const ifb_u32     memory_struct_size = sizeof(IFBMemory); 
    const ifb_address stack_start        = (ifb_address)memory_ptr;

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

inline const ifb_ptr 
ifb_memory::stack_get_pointer_relative(
    const IFBMemoryHandle memory_handle,
    const ifb_u32         reference,
    const ifb_u32         offset) {

    const ifb_u32 offset_absolute = reference + offset;
    const ifb_ptr pointer         = ifb_memory::stack_get_pointer(
        memory_handle,
        pointer);

    return(pointer);
}


/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline IFBMemoryArena*
ifb_memory::stack_push_arena_base(
    const IFBMemoryHandle memory_handle) {

    //allocate base arena struct
    IFBMemoryArena* arena_ptr = ifb_memory_macro_stack_push_struct(
        memory_handle,
        IFBMemoryArena);
    
    //we're done
    return(arena_ptr);
}

inline IFBMemoryLinearArena*
ifb_memory::stack_push_arena_linear(
    const IFBMemoryHandle memory_handle) {

    //allocate linear arena struct
    IFBMemoryLinearArena* linear_arena_ptr = ifb_memory_macro_stack_push_struct(
        memory_handle,
        IFBMemoryLinearArena);

    //we're done
    return(linear_arena_ptr);
}


inline IFBMemoryBlockArena*
ifb_memory::stack_push_arena_block(
          IFBMemory* memory_ptr,
    const ifb_u32    block_count) {

    //sanity check
    if (block_count == 0) return(NULL);

    //calculate the push size
    const ifb_u32 block_flag_count      = ifb_macro_align_a_to_multiple_of_b(block_count, IFB_MEMORY_BLOCK_FLAG_BIT_COUNT);
    const ifb_u32 block_flag_array_size = ifb_macro_size_array(ifb_u32,block_flag_count);
    const ifb_u32 block_arena_size      = ifb_macro_align_size_struct(IFBMemoryBlockArena);
    const ifb_u32 push_size             = block_arena_size + block_flag_array_size;

    //do the push
    const ifb_address block_arena_start = (ifb_address)ifb_memory::stack_push(memory_ptr,push_size);
    if (block_arena_start == 0) return(NULL);

    //get the pointers
    IFBMemoryBlockArena* block_arena_ptr   = (IFBMemoryBlockArena*)block_arena_start;    
    ifb_u32*             block_flags_array = (ifb_u32*)(block_arena_start + block_arena_size); 

    //clear the flags
    for (
        ifb_u32 flag_index = 0;
        flag_index < block_flag_count;
        ++flag_index) {

        block_flags_array[flag_index] = 0;
    }

    //initialize the struct
    block_arena_ptr->block_count       = block_count;
    block_arena_ptr->block_flags_count = block_flag_count;
    block_arena_ptr->block_flags_array = block_flags_array;

    //we're done
    return(block_arena_ptr);
}