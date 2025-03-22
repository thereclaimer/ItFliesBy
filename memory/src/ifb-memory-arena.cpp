
#pragma once

#include "ifb-memory.hpp"

#include "ifb-memory-manager-internal.cpp"

const IFBHNDMemoryArena
ifb_memory::arena_commit(
    IFBMemoryManager* memory_manager) {
    
    


    IFBHNDMemoryArena arena;
    arena.offset = 0;

    return(arena);
}

const IFBB8
ifb_memory::arena_decommit(
          IFBMemoryManager* memory_manager,
    const IFBHNDMemoryArena arena_handle) {

    //validate the memory manager
    ifb_memory::manager_assert_valid(memory_manager);

    return(false);
}

const IFBB8
ifb_memory::arena_reset(
          IFBMemoryManager* memory_manager,
    const IFBHNDMemoryArena arena_handle,
    const IFBU32            size,
    const IFBU32            alignment) {

    //validate the memory manager
    ifb_memory::manager_assert_valid(memory_manager);

    return(false);
}


const IFBU32
ifb_memory::arena_push_bytes_relative(
          IFBMemoryManager* memory_manager,
    const IFBHNDMemoryArena arena_handle,
    const IFBU32            size,
    const IFBU32            alignment) {

    //validate the memory manager
    ifb_memory::manager_assert_valid(memory_manager);

    return(0);
}

const IFBPtr
ifb_memory::arena_push_bytes_absolute(
          IFBMemoryManager* memory_manager,
    const IFBHNDMemoryArena arena_handle,
    const IFBU32            size,
    const IFBU32            alignment) {

    //validate the memory manager
    ifb_memory::manager_assert_valid(memory_manager);

    return(NULL);
}

const IFBB8
ifb_memory::arena_pull_bytes(
          IFBMemoryManager* memory_manager,
    const IFBHNDMemoryArena arena_handle,
    const IFBU32            size,
    const IFBU32            alignment) {

    //validate the memory manager
    ifb_memory::manager_assert_valid(memory_manager);

    return(false);
}
