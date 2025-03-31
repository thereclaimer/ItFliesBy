#pragma once

#include "ifb-engine-memory.hpp"

inline const b8
engine::memory_arena_reset(
    const engine_memory_t*      memory,
    const engine_memory_arena_t arena) {

    const b8 result = memory::arena_reset(memory->reservation.arena_handle_array[arena]);
    
    return(result);
}

inline const u32
engine::memory_arena_push_bytes_relative(
    const engine_memory_t*      memory,
    const engine_memory_arena_t arena,
    const u32                   size) {

    const u32 arena_offset = memory::arena_push_bytes_relative(
        memory->reservation.arena_handle_array[arena],
        size);

    return(arena_offset);
}

inline const ptr
engine::memory_arena_push_bytes_absolute_pointer(
    const engine_memory_t*      memory,
    const engine_memory_arena_t arena,
    const u32                   size) {
    
    const ptr pointer = memory::arena_push_bytes_absolute_pointer(
        memory->reservation.arena_handle_array[arena],
        size);

    return(pointer);
}

inline const addr
engine::memory_arena_push_bytes_absolute_address(
    const engine_memory_t*      memory,
    const engine_memory_arena_t arena,
    const u32                   size) {
    
    const addr address = memory::arena_push_bytes_absolute_address(
        memory->reservation.arena_handle_array[arena],
        size);

    return(address);
}

inline const b8
engine::memory_arena_pull_bytes(
    const engine_memory_t*      memory,
    const engine_memory_arena_t arena,
    const u32                   size) {
    
    const b8 result = memory::arena_pull_bytes(
        memory->reservation.arena_handle_array[arena],
        size);

    return(result);
}

inline const ptr
engine::memory_arena_get_pointer(
    const engine_memory_t*      memory,
    const engine_memory_arena_t arena,
    const u32                   offset) {
    
    const ptr result = memory::arena_get_pointer(
        memory->reservation.arena_handle_array[arena],
        offset);

    return(result);
}