#pragma once

#include "ifb-engine-internal-global.hpp"


inline const IFBEngineGlobalHandle 
ifb_engine::global_stack_push(
    const ifb_u32 size) {

    IFBEngineGlobalStack& ref_global_stack = ifb_engine::globals_get_stack_reference();

    const ifb_u32 new_position = ref_global_stack.position + size;

    ifb_macro_assert(new_position <= ref_global_stack.size);

    IFBEngineGlobalHandle global_handle;
    global_handle.stack_position = ref_global_stack.position;

    ref_global_stack.position = new_position;

    return(handle);    
}

inline const IFBEngineGlobalHandle 
ifb_engine::global_stack_push_aligned(
    const ifb_u32 size,
    const ifb_u32 alignment) {

    const ifb_u32               size_aligned  = ifb_macro_align_a_to_b(size,alignment);
    const IFBEngineGlobalHandle global_handle = ifb_engine::global_stack_push(size_aligned);

    return(global_handle);
}

inline const ifb_ptr 
ifb_engine::global_stack_push_immediate(
    const ifb_u32 size) {

    const IFBEngineGlobalHandle global_handle  = ifb_engine::global_stack_push(size);
    const ifb_ptr               global_pointer = ifb_engine::global_stack_pointer(global_handle); 

    return(global_pointer);
}

inline const ifb_memory 
ifb_engine::global_stack_push_aligned_immediate(
    const ifb_u32 size, 
    const ifb_u32 alignment) {

    const IFBEngineGlobalHandle global_handle  = ifb_engine::global_stack_push_aligned(size,alignment);
    const ifb_ptr               global_pointer = ifb_engine::global_stack_pointer(global_handle); 

    return(memory_pointer);
}

inline const ifb_memory
ifb_engine::global_stack_pointer(
    const IFBEngineGlobalHandle& ref_global_handle) {

    IFBEngineGlobalStack& ref_global_stack = ifb_engine::globals_get_stack_reference();

    const ifb_ptr global_pointer = &ref_global_stack.memory[ref_global_handle.stack_position];

    return(global_pointer);
}