#pragma once

#include <ifb-memory.hpp>

#include "ifb-engine-api.hpp"

//reset
ifb_engine_api IFBVoid
ifb_engine::arena_reset_all(
    const IFBHNDEngineArena arena_handle) {

    ifb_memory::arena_reset_all(arena_handle);
}

ifb_engine_api IFBVoid
ifb_engine::arena_reset_committed_space(
    const IFBHNDEngineArena arena_handle) {

    ifb_memory::arena_reset_committed_space(arena_handle);
}

ifb_engine_api IFBVoid
ifb_engine::arena_reset_reserved_space(
    const IFBHNDEngineArena arena_handle) {

    ifb_memory::arena_reset_reserved_space(arena_handle);
}
    
//pointers
ifb_engine_api const IFBPtr
ifb_engine::arena_get_pointer(
    const IFBHNDEngineArena arena_handle,
    const IFBU32            offset) {

    const IFBPtr pointer = ifb_memory::arena_get_pointer(arena_handle,offset);
    return(pointer);
}

ifb_engine_api const IFBB8
ifb_engine::arena_get_info(
    const IFBHNDEngineArena   arena_handle,
          IFBEngineArenaInfo* arena_info_ptr) {

    const IFBB8 result = ifb_memory::arena_get_info(
        arena_handle,
        arena_info_ptr);

    return(result);
}

ifb_engine_api const IFBAddr
ifb_engine::arena_get_start(
    const IFBHNDEngineArena arena_handle) {

    const IFBAddr result = ifb_memory::arena_get_start(arena_handle);
    return(result);
}

//reserve/release    
ifb_engine_api const IFBPtr
ifb_engine::arena_reserve_bytes_absolute(
    const IFBHNDEngineArena arena_handle,
    const IFBU32            size,
    const IFBU32            alignment) {

    const IFBPtr result = ifb_memory::arena_reserve_bytes_absolute(
        arena_handle,
        size,
        alignment);

    return(result);
}

ifb_engine_api const IFBU32
ifb_engine::arena_reserve_bytes_relative(
    const IFBHNDEngineArena arena_handle,
    const IFBU32            size,
    const IFBU32            alignment) {
    
    const IFBU32 result = ifb_memory::arena_reserve_bytes_relative(
        arena_handle,
        size,
        alignment);

    return(result);
}

ifb_engine_api const IFBB8
ifb_engine::arena_release_bytes(
    const IFBHNDEngineArena arena_handle,
    const IFBU32            size,
    const IFBU32            alignment) {

    const IFBB8 result = ifb_memory::arena_release_bytes(
        arena_handle,
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

    const IFBPtr result = ifb_memory::arena_commit_bytes_absolute(
        arena_handle,
        size,
        alignment);

    return(result);
}

ifb_engine_api const IFBU32
ifb_engine::arena_commit_bytes_relative(
    const IFBHNDEngineArena arena_handle,
    const IFBU32            size,
    const IFBU32            alignment) {

    const IFBU32 result = ifb_memory::arena_commit_bytes_relative(
        arena_handle,
        size,
        alignment);
    
    return(result);
}