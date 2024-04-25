#include "itfliesby-engine-renderer.hpp"

#pragma once

internal void
itfliesby_engine_renderer_shader_program_store_init(
    ItfliesbyEngineRendererShaderProgramStore* shader_program_store,
    ItfliesbyEngineRendererShaderStageStore*   shader_stage_store,
    itfliesby_renderer                         render_context) {

    ITFLIESBY_ASSERT(
        shader_program_store &&
        shader_stage_store
    );

    //cache our stuff
    ItfliesbyEngineRendererShaderStageVertex*   engine_shader_stage_store_id_vertex   = shader_program_store->shader_stage_store_id_vertex;
    ItfliesbyEngineRendererShaderStageFragment* engine_shader_stage_store_id_fragment = shader_program_store->shader_stage_store_id_fragment;

    itfliesby_renderer_vertex_shader*   shader_stage_store_renderer_stage_id_vertex   = shader_stage_store->renderer_stage_id_vertex; 
    itfliesby_renderer_fragment_shader* shader_stage_store_renderer_stage_id_fragment = shader_stage_store->renderer_stage_id_fragment;
    itfliesby_renderer_shader_program*  render_shader_program_id   = shader_program_store->shader_program_id;

    //initialize the collection of shader stages we're using
    const u8 shader_program_count = ITFLIESBY_ENGINE_RENDERER_SHADER_PROGRAM_COUNT;
    itfliesby_renderer_vertex_shader   renderer_stage_id_vertex[shader_program_count];
    itfliesby_renderer_fragment_shader renderer_stage_id_fragment[shader_program_count];

    //textured quad
    engine_shader_stage_store_id_vertex[ITFLIESBY_ENGINE_RENDERER_SHADER_PROGRAM_TEXTURED_QUAD]   = ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_VERTEX_TEXTURED_QUAD;
    engine_shader_stage_store_id_fragment[ITFLIESBY_ENGINE_RENDERER_SHADER_PROGRAM_TEXTURED_QUAD] = ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_FRAGMENT_TEXTURED_QUAD;
    renderer_stage_id_vertex[ITFLIESBY_ENGINE_RENDERER_SHADER_PROGRAM_TEXTURED_QUAD]              = shader_stage_store_renderer_stage_id_vertex[ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_VERTEX_TEXTURED_QUAD];
    renderer_stage_id_fragment[ITFLIESBY_ENGINE_RENDERER_SHADER_PROGRAM_TEXTURED_QUAD]            = shader_stage_store_renderer_stage_id_fragment[ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_FRAGMENT_TEXTURED_QUAD];

    //initialize the programs
    itfliesby_renderer_api_shader_programs_create(
        render_context,
        renderer_stage_id_vertex,
        renderer_stage_id_fragment,
        shader_program_count,
        render_shader_program_id
    );

}

internal void 
itfliesby_engine_renderer_shader_store_init(
    ItfliesbyEngineRendererShaderStageStore* shader_stage_store,
    ItfliesbyEngineRendererMemory*           renderer_memory,
    ItfliesbyEngineAssets*                   assets,
    itfliesby_renderer                       render_context) {

    ITFLIESBY_ASSERT(
        shader_stage_store &&
        renderer_memory    &&
        assets
    );

    //get the info and allocation sizes of our shaders
    auto shader_stage_id_vertex   = shader_stage_store->renderer_stage_id_vertex;
    auto shader_stage_id_fragment = shader_stage_store->renderer_stage_id_fragment;

    const u32 count_shader_stages_vertex   = 1;
    const u32 count_shader_stages_fragment = 1;

    ItfliesbyEngineAssetsShader shader_stage_asset_id_vertex[count_shader_stages_vertex] = {
        ITFLIESBY_ENGINE_ASSETS_SHADER_TEXTURED_QUAD_VERTEX_SHADER
    };

    ItfliesbyEngineAssetsShader shader_stage_asset_id_fragment[count_shader_stages_fragment] = {
        ITFLIESBY_ENGINE_ASSETS_SHADER_TEXTURED_QUAD_FRAGMENT_SHADER
    };

    const u64 memory_size_shader_stages_vertex   = itfliesby_engine_assets_shader_allocation_size(assets, shader_stage_asset_id_vertex,   count_shader_stages_vertex);
    const u64 memory_size_shader_stages_fragment = itfliesby_engine_assets_shader_allocation_size(assets, shader_stage_asset_id_fragment, count_shader_stages_fragment);

    ITFLIESBY_ASSERT(memory_size_shader_stages_vertex > 0);
    ITFLIESBY_ASSERT(memory_size_shader_stages_fragment > 0);

    //allocate space for the shaders
    auto shader_asset_data_allocator = renderer_memory->shader_asset_data_allocator;

    memory memory_shader_stage_vertex   = itfliesby_memory_allocator_linear_allocate(shader_asset_data_allocator,memory_size_shader_stages_vertex);
    memory memory_shader_stage_fragment = itfliesby_memory_allocator_linear_allocate(shader_asset_data_allocator,memory_size_shader_stages_fragment);

    ITFLIESBY_ASSERT(memory_shader_stage_vertex);
    ITFLIESBY_ASSERT(memory_size_shader_stages_fragment);

    u64 offsets_vertex[count_shader_stages_vertex]     = {0};
    u64 offsets_fragment[count_shader_stages_fragment] = {0};

    //load the shaders
    itfliesby_engine_assets_load_shaders(assets, shader_stage_asset_id_vertex,   memory_shader_stage_vertex,   offsets_vertex,   count_shader_stages_vertex);
    itfliesby_engine_assets_load_shaders(assets, shader_stage_asset_id_fragment, memory_shader_stage_fragment, offsets_fragment, count_shader_stages_fragment);

    //compile the shaders
    itfliesby_renderer_api_shader_compile_vertex_shaders(  render_context,(const char*)memory_shader_stage_vertex,   offsets_vertex,   count_shader_stages_vertex, shader_stage_id_vertex);
    itfliesby_renderer_api_shader_compile_fragment_shaders(render_context,(const char*)memory_shader_stage_fragment, offsets_fragment, count_shader_stages_fragment, shader_stage_id_fragment);
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


    //initialize shader stage store
    itfliesby_engine_renderer_shader_store_init(
        &renderer->shader_stage_store,
        &renderer->memory,
        assets,
        renderer->renderer_handle
    );

    //initialize shader program store
    itfliesby_engine_renderer_shader_program_store_init(
        &renderer->shader_program_store,
        &renderer->shader_stage_store,
        renderer->renderer_handle
    );
}


internal void
itfliesby_engine_renderer_update(
    ItfliesbyEngineRenderer* renderer,
    ItfliesbyEngineAssets*   assets) {

    itfliesby_renderer_api_update_and_render(renderer->renderer_handle);
}