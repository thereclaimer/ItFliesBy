#pragma once

#include "itfliesby-engine.hpp"
#include "itfliesby-engine-globals.hpp"
#include "itfliesby-engine-memory.cpp"

internal void
itfliesby_engine_rendering_shader_programs_init(
    ItfliesbyRendererHandle     renderer,
    ItfliesbyEngineAssets*      assets,
    ItfliesbyEngineShaderStore* shader_store) {

    ITFLIESBY_ASSERT(
        renderer &&
        shader_store);
    
    //textured quad shader
    ItfliesbyEngineAssetsShader shader_stage_asset_id_vertex   = ITFLIESBY_ENGINE_ASSETS_SHADER_TEXTURED_QUAD_VERTEX_SHADER;
    ItfliesbyEngineAssetsShader shader_stage_asset_id_fragment = ITFLIESBY_ENGINE_ASSETS_SHADER_TEXTURED_QUAD_FRAGMENT_SHADER;

    //allocate space for the shaders
    const u64 memory_size_shader_stages_vertex   = itfliesby_engine_assets_shader_allocation_size(assets, &shader_stage_asset_id_vertex,   1);
    const u64 memory_size_shader_stages_fragment = itfliesby_engine_assets_shader_allocation_size(assets, &shader_stage_asset_id_fragment, 1);

    ITFLIESBY_ASSERT(memory_size_shader_stages_vertex   > 0);
    ITFLIESBY_ASSERT(memory_size_shader_stages_fragment > 0);

    memory memory_shader_stage_vertex   = itfliesby_engine_memory_renderer_shader_allocate(memory_size_shader_stages_vertex);
    memory memory_shader_stage_fragment = itfliesby_engine_memory_renderer_shader_allocate(memory_size_shader_stages_fragment);

    //load the shaders
    u64 offsets_vertex   = 0;
    u64 offsets_fragment = 0;

    itfliesby_engine_assets_load_shaders(assets, &shader_stage_asset_id_vertex,   memory_shader_stage_vertex,   &offsets_vertex,   1);
    itfliesby_engine_assets_load_shaders(assets, &shader_stage_asset_id_fragment, memory_shader_stage_fragment, &offsets_fragment, 1);

    //compile the shaders
    ItfliesbyRendererShaderStageBuffer renderer_shader_stage_buffer_vertex   = {0};
    ItfliesbyRendererShaderStageBuffer renderer_shader_stage_buffer_fragment = {0};
    
    renderer_shader_stage_buffer_vertex.shader_stage_data   = memory_shader_stage_vertex;
    renderer_shader_stage_buffer_fragment.shader_stage_data = memory_shader_stage_fragment;

    shader_store->textured_quad_shader_index = 
        itfliesby_renderer_shader_compile_and_link(
            renderer,
            &renderer_shader_stage_buffer_vertex,
            &renderer_shader_stage_buffer_fragment);

    ITFLIESBY_NOP();
}

internal ItfliesbyRendererHandle
itfliesby_engine_rendering_init(
    ItfliesbyEngineAssets*      assets,
    ItfliesbyEngineShaderStore* shader_store) {

    //init rendering memory
    itfliesby_engine_memory_renderer_create();

    //initialize renderer
    memory renderer_memory           = itfliesby_engine_memory_renderer_context();
    ItfliesbyRendererHandle renderer = itfliesby_renderer_create_and_init(platform_api,renderer_memory,ITFLIESBY_ENGINE_RENDERER_MEMORY_PARTITION_CONTEXT_SIZE);
    ITFLIESBY_ASSERT(renderer);

    //load shaders
    itfliesby_engine_rendering_shader_programs_init(
        renderer,
        assets,
        shader_store
    );

    return(renderer);
}