#pragma once

#include <ifb-memory.hpp>

#include "ifb-engine-api.hpp"
#include "ifb-engine-internal-context.hpp"

namespace ifb_engine {

    IFBMemoryArena* arena_from_handle(const IFBHNDEngineArena arena_handle);
};


//reset
ifb_engine_api IFBVoid
ifb_engine::arena_reset_all(
    const IFBHNDEngineArena arena_handle) {

    IFBMemoryArena* ptr_arena = ifb_engine::arena_from_handle(arena_handle);
    ifb_memory::arena_reset_all(ptr_arena);
}

ifb_engine_api IFBVoid
ifb_engine::arena_reset_committed_space(
    const IFBHNDEngineArena arena_handle) {

    IFBMemoryArena* ptr_arena = ifb_engine::arena_from_handle(arena_handle);
    ifb_memory::arena_reset_committed_space(ptr_arena);
}

ifb_engine_api IFBVoid
ifb_engine::arena_reset_reserved_space(
    const IFBHNDEngineArena arena_handle) {

    IFBMemoryArena* ptr_arena = ifb_engine::arena_from_handle(arena_handle);
    ifb_memory::arena_reset_reserved_space(ptr_arena);
}
    
//pointers
ifb_engine_api const IFBPtr
ifb_engine::arena_get_pointer(
    const IFBHNDEngineArena arena_handle,
    const IFBU32            offset) {

    IFBMemoryArena* ptr_arena = ifb_engine::arena_from_handle(arena_handle);
    const IFBPtr pointer = ifb_memory::arena_get_pointer(ptr_arena,offset);
    return(pointer);
}

ifb_engine_api const IFBAddr
ifb_engine::arena_get_start(
    const IFBHNDEngineArena arena_handle) {

    IFBMemoryArena* ptr_arena = ifb_engine::arena_from_handle(arena_handle);
    const IFBAddr result = ifb_memory::arena_get_start(ptr_arena);
    return(result);
}

//reserve/release    
ifb_engine_api const IFBPtr
ifb_engine::arena_reserve_bytes_absolute(
    const IFBHNDEngineArena arena_handle,
    const IFBU32            size,
    const IFBU32            alignment) {

    IFBMemoryArena* ptr_arena = ifb_engine::arena_from_handle(arena_handle);

    const IFBPtr result = ifb_memory::arena_reserve_bytes_absolute(
        ptr_arena,
        size,
        alignment);

    return(result);
}

ifb_engine_api const IFBU32
ifb_engine::arena_reserve_bytes_relative(
    const IFBHNDEngineArena arena_handle,
    const IFBU32            size,
    const IFBU32            alignment) {

    IFBMemoryArena* ptr_arena = ifb_engine::arena_from_handle(arena_handle);

    const IFBU32 result = ifb_memory::arena_reserve_bytes_relative(
        ptr_arena,
        size,
        alignment);

    return(result);
}

ifb_engine_api const IFBB8
ifb_engine::arena_release_bytes(
    const IFBHNDEngineArena arena_handle,
    const IFBU32            size,
    const IFBU32            alignment) {

    IFBMemoryArena* ptr_arena = ifb_engine::arena_from_handle(arena_handle);

    const IFBB8 result = ifb_memory::arena_release_bytes(
        ptr_arena,
        size,
        alignment);

    return(result);
}
    
//commit
ifb_engine_api const IFBPtr
ifb_engine::arena_commit_bytes_absolute(
    const IFBHNDEngineArena arena_handle,
    const IFBU32            size,
    const IFBU32            alignment) {

    IFBMemoryArena* ptr_arena = ifb_engine::arena_from_handle(arena_handle);

    const IFBPtr result = ifb_memory::arena_commit_bytes_absolute(
        ptr_arena,
        size,
        alignment);

    return(result);
}

ifb_engine_api const IFBU32
ifb_engine::arena_commit_bytes_relative(
    const IFBHNDEngineArena arena_handle,
    const IFBU32            size,
    const IFBU32            alignment) {

    IFBMemoryArena* ptr_arena = ifb_engine::arena_from_handle(arena_handle);

    const IFBU32 result = ifb_memory::arena_commit_bytes_relative(
        ptr_arena,
        size,
        alignment);
    
    return(result);
}

inline IFBMemoryArena*
ifb_engine::arena_from_handle(
    const IFBHNDEngineArena arena_handle) {

    IFBMemoryArena* ptr_arena = (IFBMemoryArena*)arena_handle.pointer;
    ifb_macro_assert(ptr_arena);
    return(ptr_arena);
}
