#include "ifb-memory.hpp"
#include "ifb-memory-internal.hpp"

/**********************************************************************************/
/* PUSH                                                                           */
/**********************************************************************************/

const IFBU32
ifb_memory::stack_push(
    const IFBU32 size,
    const IFBU32 alignment) {

    //cache the stack
    IFBMemoryStack& stack_ref = ifb_memory::context_get_stack();

    //align the size
    const IFBU32 size_aligned = (alignment == 0) 
        ? size 
        : ifb_macro_align_a_to_b(size,alignment);

    //make sure we can fit the push
    const IFBU32 new_position = stack_ref.position + size_aligned; 
    if (new_position >= stack_ref.size) return(0);

    //get the current position as the offset
    const IFBU32 offset = stack_ref.position;

    //update the stack position
    stack_ref.position = new_position;

    //we're done
    return(offset);
}

/**********************************************************************************/
/* POINTERS                                                                       */
/**********************************************************************************/

const IFBPtr
ifb_memory::stack_get_pointer(
    const IFBU32 offset) {

    //cache the stack
    IFBMemoryStack& stack_ref = ifb_memory::context_get_stack();

    //make sure the offset is valid
    IFBB8 offset_valid = true;                          // the offset is valid                      IF...
    offset_valid &= offset >= IFB_MEMORY_HANDLE_MINIMUM; // the offset is ahead of the memory struct AND...
    offset_valid &= offset <  stack_ref.position;        // the offset is before the current stack position

    //calculate the address
    const IFBAddr address = offset_valid
        ? stack_ref.start + offset
        : 0;

    //get the pointer
    const IFBPtr pointer = (IFBPtr)address;

    //we're done
    return(pointer);
}

/**********************************************************************************/
/* INFO                                                                           */
/**********************************************************************************/

const IFBB8
ifb_memory::stack_get_info(
    IFBMemoryStackInfo* stack_info_ptr) {

    //get the stack
    IFBMemoryStack& stack_ref = ifb_memory::context_get_stack();

    //sanity check
    if (!stack_info_ptr) return(false);

    //set the stack info
    stack_info_ptr->size_total = stack_ref.size;
    stack_info_ptr->size_used  = stack_ref.position;

    //we're done
    return(true);
}
