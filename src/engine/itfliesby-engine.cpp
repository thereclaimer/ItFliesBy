#pragma once

#include "itfliesby-engine.hpp"

external ItfliesbyEngine*
itfliesby_engine_create(
    ItfliesbyPlatformApi platform,
    memory               mem,
    u64                  mem_size) {

    ITFLIESBY_ASSERT(mem_size == ITFLIESBY_ENGINE_MEMORY_SIZE);

    //initialize engine memory
    ItfliesbyEngineMemory engine_memory = {0};
    engine_memory.arena = itfliesby_memory_arena_create("ENGINE ARENA",mem_size,mem);

    ITFLIESBY_ASSERT(engine_memory.arena);

    //initialize partitions
    engine_memory.partitions.assets   = itfliesby_memory_partition_create(engine_memory.arena,"ENGINE ASSETS PRTN",  ITFLIESBY_ENGINE_PARTITION_SIZE_ASSETS);
    engine_memory.partitions.physics  = itfliesby_memory_partition_create(engine_memory.arena,"ENGINE PHYSICS PRTN", ITFLIESBY_ENGINE_PARTITION_SIZE_PHYSICS);
    engine_memory.partitions.renderer = itfliesby_memory_partition_create(engine_memory.arena,"ENGINE RENDERER PRTN",ITFLIESBY_ENGINE_PARTITION_SIZE_RENDERER);
    engine_memory.partitions.core     = itfliesby_memory_partition_create(engine_memory.arena,"ENGINE CORE PRTN",    ITFLIESBY_ENGINE_PARTITION_SIZE_CORE);
    
    ITFLIESBY_ASSERT(engine_memory.partitions.assets);
    ITFLIESBY_ASSERT(engine_memory.partitions.physics);
    ITFLIESBY_ASSERT(engine_memory.partitions.renderer);
    ITFLIESBY_ASSERT(engine_memory.partitions.core);

    //initialize allocators
    engine_memory.allocators.core_system_allocator = itfliesby_memory_allocator_linear_create(engine_memory.partitions.core,"ENGINE SYST ALCTR",ITFLIESBY_ENGINE_ALLOCATOR_SIZE_CORE_SYSTEMS);
    
    //renderer
    memory renderer_memory = itfliesby_memory_partition_raw_memory(engine_memory.partitions.renderer);
    itfliesby_renderer renderer = itfliesby_renderer_create(platform,renderer_memory,ITFLIESBY_ENGINE_PARTITION_SIZE_RENDERER);
    ITFLIESBY_ASSERT(renderer);

    //allocate engine systems
    ItfliesbyEngine* engine = (ItfliesbyEngine*)itfliesby_memory_allocator_linear_allocate(engine_memory.allocators.core_system_allocator,sizeof(ItfliesbyEngine));
    ITFLIESBY_ASSERT(engine);

    engine->memory   = engine_memory;
    engine->renderer = renderer;

    return(engine);
}

external void
itfliesby_engine_destroy(
    ItfliesbyEngine* engine) {

}

external void
itfliesby_engine_update_and_render(
    ItfliesbyEngine* engine) {

    itfliesby_renderer renderer = engine->renderer;

    itfliesby_renderer_update_and_render(renderer);
}