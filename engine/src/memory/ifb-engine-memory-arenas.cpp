#pragma once

#include "ifb-engine-memory.hpp"

inline const IFBB8
ifb_engine::memory_arena_reset(
    const IFBEngineMemory* memory,
    const IFBEngineArena   arena) {

    const IFBB8 result = ifb_memory::arena_reset(memory->reservation.arena_handle_array[arena]);
    
    return(result);
}

inline const IFBU32
ifb_engine::memory_arena_push_bytes_relative(
    const IFBEngineMemory* memory,
    const IFBEngineArena   arena,
    const IFBU32           size) {

    const IFBU32 arena_offset = ifb_memory::arena_push_bytes_relative(
        memory->reservation.arena_handle_array[arena],
        size);

    return(arena_offset);
}

inline const IFBPtr
ifb_engine::memory_arena_push_bytes_absolute_pointer(
    const IFBEngineMemory* memory,
    const IFBEngineArena   arena,
    const IFBU32           size) {
    
    const IFBPtr pointer = ifb_memory::arena_push_bytes_absolute_pointer(
        memory->reservation.arena_handle_array[arena],
        size);

    return(pointer);
}

inline const IFBAddr
ifb_engine::memory_arena_push_bytes_absolute_address(
    const IFBEngineMemory* memory,
    const IFBEngineArena   arena,
    const IFBU32           size) {
    
    const IFBAddr address = ifb_memory::arena_push_bytes_absolute_address(
        memory->reservation.arena_handle_array[arena],
        size);

    return(address);
}

inline const IFBB8
ifb_engine::memory_arena_pull_bytes(
    const IFBEngineMemory* memory,
    const IFBEngineArena   arena,
    const IFBU32           size) {
    
    const IFBB8 result = ifb_memory::arena_pull_bytes(
        memory->reservation.arena_handle_array[arena],
        size);

    return(result);
}

inline const IFBPtr
ifb_engine::memory_arena_get_pointer(
    const IFBEngineMemory* memory,
    const IFBEngineArena   arena,
    const IFBU32           offset) {
    
    const IFBPtr result = ifb_memory::arena_get_pointer(
        memory->reservation.arena_handle_array[arena],
        offset);

    return(result);
}