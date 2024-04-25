#pragma once

#include "itfliesby-renderer.hpp"

global ItfliesbyRendererMemory renderer_memory;

internal void
itfliesby_renderer_memory_create(
    memory core_memory,
    u64    core_memory_size_bytes) {

    ITFLIESBY_ASSERT(
        core_memory && 
        core_memory_size_bytes == ITFLIESBY_RENDERER_MEMORY_SIZE_BYTES);

    //initialize the arena
    renderer_memory = {0};
    renderer_memory.arena = itfliesby_memory_arena_create("RENDERER ARENA",core_memory_size_bytes,core_memory);

    //initialize partitions
    renderer_memory.partitions.core = 
        itfliesby_memory_partition_create(
            renderer_memory.arena,
            "RENDERER CORE PRTN",
            ITFLIESBY_RENDERER_MEMORY_PARTITION_CORE_SIZE_BYTES);

    ITFLIESBY_ASSERT(renderer_memory.partitions.core);

    //initialize allocators
    renderer_memory.allocators.core_system_allocator = 
        itfliesby_memory_allocator_linear_create(
            renderer_memory.partitions.core,
            "RENDERER CORE ALCTR",
            ITFLIESBY_RENDERER_MEMORY_ALLOCATOR_CORE_SYSTEM_SIZE_BYTES);

    ITFLIESBY_ASSERT(renderer_memory.allocators.core_system_allocator);
}

internal ItfliesbyRenderer*
itfliesby_renderer_memory_allocate_core() {

    ItfliesbyRenderer* renderer = 
        (ItfliesbyRenderer*)itfliesby_memory_allocator_linear_allocate(
            renderer_memory.allocators.core_system_allocator,
            sizeof(ItfliesbyRenderer)
        );

    ITFLIESBY_ASSERT(renderer);

    *renderer = {0};

    return(renderer);
}