#pragma once

#include "ifb-engine-memory.hpp"

#define macro_calculate_stack_pointer(memory,singleton,type) (type*)&memory->stack.singleton_buffer[singleton]

inline engine_context_t*
engine::memory_stack_get_context(
    const engine_memory_t* memory) {

    engine_context_t* pointer = macro_calculate_stack_pointer(
        memory, 
        engine_memory_singleton_e_context,
        engine_context_t);

    return(pointer);
}

inline engine_core_graphics_t*
engine::memory_stack_get_core_graphics(
    const engine_memory_t* memory) {

    engine_core_graphics_t* pointer = macro_calculate_stack_pointer(
        memory,
        engine_memory_arena_e_core_graphics,
        engine_core_graphics_t);
    
    return(pointer);
}

inline engine_core_files_t*
engine::memory_stack_get_core_files(
    const engine_memory_t* memory) {

    engine_core_files_t* pointer = macro_calculate_stack_pointer(
        memory,
        engine_memory_arena_e_core_threads,
        engine_core_files_t);
    
    return(pointer);
}

inline engine_core_threads_t*
engine::memory_stack_get_core_threads(
    const engine_memory_t* memory) {

    engine_core_threads_t* pointer = macro_calculate_stack_pointer(
        memory,
        engine_memory_arena_e_core_files,
        engine_core_threads_t);

    return(pointer);
}