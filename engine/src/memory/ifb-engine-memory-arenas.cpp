#pragma once

#include "ifb-engine-memory.hpp"

inline const ifb::b8
ifb_engine::memory_arena_reset(
    const IFBEngineMemory* memory,
    const IFBEngineArena   arena) {

    const ifb::b8 result = ifb_memory::arena_reset(memory->reservation.arena_handle_array[arena]);
    
    return(result);
}

inline const ifb::u32
ifb_engine::memory_arena_push_bytes_relative(
    const IFBEngineMemory* memory,
    const IFBEngineArena   arena,
    const ifb::u32           size) {

    const ifb::u32 arena_offset = ifb_memory::arena_push_bytes_relative(
        memory->reservation.arena_handle_array[arena],
        size);

    return(arena_offset);
}

inline const ifb::ptr
ifb_engine::memory_arena_push_bytes_absolute_pointer(
    const IFBEngineMemory* memory,
    const IFBEngineArena   arena,
    const ifb::u32           size) {
    
    const ifb::ptr pointer = ifb_memory::arena_push_bytes_absolute_pointer(
        memory->reservation.arena_handle_array[arena],
        size);

    return(pointer);
}

inline const ifb::addr
ifb_engine::memory_arena_push_bytes_absolute_address(
    const IFBEngineMemory* memory,
    const IFBEngineArena   arena,
    const ifb::u32           size) {
    
    const ifb::addr address = ifb_memory::arena_push_bytes_absolute_address(
        memory->reservation.arena_handle_array[arena],
        size);

    return(address);
}

inline const ifb::b8
ifb_engine::memory_arena_pull_bytes(
    const IFBEngineMemory* memory,
    const IFBEngineArena   arena,
    const ifb::u32           size) {
    
    const ifb::b8 result = ifb_memory::arena_pull_bytes(
        memory->reservation.arena_handle_array[arena],
        size);

    return(result);
}

inline const ifb::ptr
ifb_engine::memory_arena_get_pointer(
    const IFBEngineMemory* memory,
    const IFBEngineArena   arena,
    const ifb::u32           offset) {
    
    const ifb::ptr result = ifb_memory::arena_get_pointer(
        memory->reservation.arena_handle_array[arena],
        offset);

    return(result);
}