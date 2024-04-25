#pragma once

#include "itfliesby-engine.hpp"

global ItfliesbyEngineMemory         engine_memory;
global ItfliesbyEngineAssetsMemory   asset_memory;
global ItfliesbyEngineRendererMemory renderer_memory;

internal void
itfliesby_engine_memory_create(
    memory core_memory,
    u64    core_memory_size_bytes) {

    engine_memory = {0};
    engine_memory.arena = itfliesby_memory_arena_create("ENGINE ARENA",core_memory_size_bytes,core_memory);

    ITFLIESBY_ASSERT(engine_memory.arena);

    //initialize partitions
    engine_memory.partitions.physics  = itfliesby_memory_partition_create(engine_memory.arena,"ENGINE PHYSICS PRTN", ITFLIESBY_ENGINE_PARTITION_SIZE_PHYSICS);
    engine_memory.partitions.core     = itfliesby_memory_partition_create(engine_memory.arena,"ENGINE CORE PRTN",    ITFLIESBY_ENGINE_PARTITION_SIZE_CORE);

    ITFLIESBY_ASSERT(engine_memory.partitions.physics);
    ITFLIESBY_ASSERT(engine_memory.partitions.core);

    //initialize allocators
    engine_memory.allocators.core_system_allocator = itfliesby_memory_allocator_linear_create(engine_memory.partitions.core,"ENGINE SYST ALCTR",ITFLIESBY_ENGINE_ALLOCATOR_SIZE_CORE_SYSTEMS);
}

internal memory
itfliesby_engine_memory_renderer_context() {
    
    memory renderer_context_memory = itfliesby_memory_partition_raw_memory(renderer_memory.rendering_context_partition);

    ITFLIESBY_ASSERT(renderer_context_memory);

    return(renderer_context_memory);
}

internal void
itfliesby_engine_memory_assets_create() {

    asset_memory = {0};

    //initialize memory
    asset_memory.partition = itfliesby_memory_partition_create(engine_memory.arena,"ENGINE ASSETS PRTN",  ITFLIESBY_ENGINE_ASSETS_MEMORY_PARTITION_SIZE);
    ITFLIESBY_ASSERT(asset_memory.partition);    

    //allocators
    asset_memory.index_allocator        = itfliesby_memory_allocator_block_create(asset_memory.partition,"ASSET INDEX ALCTR",ITFLIESBY_ENGINE_ASSETS_MEMORY_BLOCK_SIZE_INDEX,     ITFLIESBY_ASSETS_FILE_ID_COUNT);
    asset_memory.asset_data_allocator   = itfliesby_memory_allocator_block_create(asset_memory.partition,"ASSET DATA ALCTR", ITFLIESBY_ENGINE_ASSETS_MEMORY_BLOCK_SIZE_ASSET_DATA,ITFLIESBY_ASSETS_FILE_ID_COUNT);
    asset_memory.asset_header_allocator = itfliesby_memory_allocator_linear_create(asset_memory.partition,"ASSET HEADER ALCTR",ITFLIESBY_ENGINE_ASSETS_MEMORY_ALLOCATOR_HEADER_SIZE);
    
    ITFLIESBY_ASSERT(asset_memory.index_allocator);    
    ITFLIESBY_ASSERT(asset_memory.asset_data_allocator);    
    ITFLIESBY_ASSERT(asset_memory.asset_header_allocator);    
}

internal void
itfliesby_engine_memory_renderer_create() {

    renderer_memory = {0};

    //initialize partitions
    renderer_memory.partition                   = itfliesby_memory_partition_create(engine_memory.arena,"ENGINE RENDERER PRTN",ITFLIESBY_ENGINE_RENDERER_MEMORY_PARTITION_SIZE);
    renderer_memory.rendering_context_partition = itfliesby_memory_partition_create(engine_memory.arena,"RNDR CNTXT PRTN"     ,ITFLIESBY_ENGINE_RENDERER_MEMORY_PARTITION_CONTEXT_SIZE);
    
    ITFLIESBY_ASSERT(renderer_memory.partition);
    ITFLIESBY_ASSERT(renderer_memory.rendering_context_partition);

    //initialize allocators
    renderer_memory.shader_asset_data_allocator = itfliesby_memory_allocator_linear_create(renderer_memory.partition,"SHADER ASSET DATA ALCTR",ITFLIESBY_ENGINE_RENDERER_MEMORY_ALLOCATOR_SIZE_SHADER_DATA);
    ITFLIESBY_ASSERT(renderer_memory.shader_asset_data_allocator);
}

internal memory
itfliesby_engine_memory_renderer_shader_allocate(
    u64 shader_data_size_bytes) {

    memory shader_memory = 
        itfliesby_memory_allocator_linear_allocate(
            renderer_memory.shader_asset_data_allocator,
            shader_data_size_bytes);

    ITFLIESBY_ASSERT(shader_memory);

    return(shader_memory);
}

internal ItfliesbyEngine*
itfliesby_engine_memory_allocate_core() {

    //allocate engine systems
    ItfliesbyEngine* engine = 
        (ItfliesbyEngine*)itfliesby_memory_allocator_linear_allocate(
            engine_memory.allocators.core_system_allocator,
            sizeof(ItfliesbyEngine));

    ITFLIESBY_ASSERT(engine);

    *engine = {0};

    return(engine);
}

internal memory
itfliesby_engine_memory_assets_file_header_allocate(
    u64 file_header_size_bytes) {

    memory index_memory = 
        itfliesby_memory_allocator_linear_allocate(
            asset_memory.asset_header_allocator,
            file_header_size_bytes
    );

    ITFLIESBY_ASSERT(index_memory);

    return(index_memory);
}

internal void
itfliesby_engine_memory_assets_file_header_reset(
    memory asset_header_memory) {

    itfliesby_memory_allocator_linear_reset(asset_memory.asset_header_allocator);
    asset_header_memory = NULL;
}