#include "itfliesby-engine-renderer.hpp"

#pragma once

void 
itfliesby_engine_renderer_shader_store_init(
    ItfliesbyEngineRendererShaderStageStore* shader_stage_store,
    ItfliesbyEngineRendererMemory*           renderer_memory,
    ItfliesbyEngineAssets*                   assets) {

    

}

internal void
itfliesby_engine_renderer_init(
    ItfliesbyEngineRenderer* renderer,
    ItfliesbyEngineAssets*   assets,
    itfliesby_memory_arena   arena) {
    
    *renderer = {0};
    renderer->assets = assets;

    auto renderer_memory = &renderer->memory;

    //initialize partitions
    renderer_memory->partition                   = itfliesby_memory_partition_create(arena,"ENGINE RENDERER PRTN",ITFLIESBY_ENGINE_RENDERER_MEMORY_PARTITION_SIZE);
    renderer_memory->rendering_context_partition = itfliesby_memory_partition_create(arena,"RNDR CNTXT PRTN"     ,ITFLIESBY_ENGINE_RENDERER_MEMORY_PARTITION_CONTEXT_SIZE);
    ITFLIESBY_ASSERT(renderer_memory->partition);
    ITFLIESBY_ASSERT(renderer_memory->rendering_context_partition);

    //initialize allocators
    renderer_memory->shader_asset_data_allocator      = itfliesby_memory_allocator_linear_create(renderer_memory->partition,"SHADER ASSET DATA ALCTR",ITFLIESBY_ENGINE_RENDERER_MEMORY_ALLOCATOR_SIZE_SHADER_DATA);
    ITFLIESBY_ASSERT(renderer_memory->shader_asset_data_allocator);

    //initialize the renderer
    memory render_context_memory = itfliesby_memory_partition_raw_memory(renderer_memory->rendering_context_partition);
    ITFLIESBY_ASSERT(render_context_memory);
    renderer->renderer_handle =
        itfliesby_renderer_api_create(
            platform_api,
            render_context_memory,
            ITFLIESBY_ENGINE_RENDERER_MEMORY_PARTITION_CONTEXT_SIZE
    );
    ITFLIESBY_ASSERT(renderer->renderer_handle);


    itfliesby_engine_renderer_shader_store_init(
        &renderer->shader_stage_store,
        &renderer->memory,
        assets
    );
}


internal void
itfliesby_engine_renderer_update(
    ItfliesbyEngineRenderer* renderer,
    ItfliesbyEngineAssets*   assets) {

    itfliesby_renderer_api_update_and_render(renderer->renderer_handle);
}