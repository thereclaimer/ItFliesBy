#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-internal-context.hpp"

inline const ifb_void
ifb_engine::context_stack_push(
          IFBHND& ref_handle, 
    const ifb_u32 size) {

    IFBEngineContextStack& ref_stack = ifb_engine::context_get_stack();

    const ifb_u32 new_position = ref_stack.position + size;

    ifb_macro_assert(new_position <= ref_stack.size);

    ref_handle.offset = ref_stack.position;

    ref_global_stack.position = new_position;
}

inline const ifb_void
ifb_engine::context_stack_push_aligned(
          IFBHND& ref_handle,
    const ifb_u32 size,
    const ifb_u32 alignment) {

    const ifb_u32 size_aligned = ifb_macro_align_a_to_b(size,alignment);
    
    ifb_engine::context_stack_push(
        ref_handle,
        size_aligned);
}

inline const ifb_ptr
ifb_engine::context_stack_get_pointer(
    const IFBHND& ref_handle) {

    IFBEngineContextStack& stack_ref ifb_engine::context_get_stack();

    const ifb_ptr stack_ptr = &stack_ref.memory[ref_handle.offset];

    return(stack_ptr);
}