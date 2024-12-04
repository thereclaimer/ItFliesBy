#pragma once 

#include "ifb-engine-internal-memory.hpp"

inline const IFBEngineMemoryHandle 
ifb_engine::memory_global_push(
    const ifb_u32 size) {

    const ifb_u32 new_position = _global_stack.position + size;

    ifb_macro_assert(new_position <= _global_stack.size);

    IFBEngineMemoryHandle memory_handle;
    memory_handle.stack_position = _global_stack.position;

    _global_stack.position = new_position;

    return(handle);    
}

inline const IFBEngineMemoryHandle 
ifb_engine::memory_global_push_aligned(
    const ifb_u32 size,
    const ifb_u32 alignment) {

    const ifb_u32 size_aligned = ifb_macro_align_a_to_b(size,alignment);

    const IFBEngineMemoryHandle memory_handle = ifb_engine::memory_global_push(size_aligned);

    return(memory_handle);
}

inline const ifb_memory 
ifb_engine::memory_global_push_immediate(
    const ifb_u32 size) {

    const IFBEngineMemoryHandle memory_handle  = ifb_engine::memory_global_push(size);
    const ifb_memory            memory_pointer = ifb_engine::memory_global_pointer(memory_handle); 

    return(memory_pointer);
}

inline const ifb_memory 
ifb_engine::memory_global_push_aligned_immediate(
    const ifb_u32 size, 
    const ifb_u32 alignment) {

    const IFBEngineMemoryHandle memory_handle  = ifb_engine::memory_global_push_aligned(size,alignment);
    const ifb_memory            memory_pointer = ifb_engine::memory_global_pointer(memory_handle); 

    return(memory_pointer);
}

inline const ifb_memory
ifb_engine::memory_global_pointer(
    const IFBEngineMemoryHandle memory_handle) {

    const ifb_memory stack_memory = (ifb_memory)&_global_stack.memory[memory_handle.stack_position];

    return(stack_memory);
}