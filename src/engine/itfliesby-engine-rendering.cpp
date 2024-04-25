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

    const u64 memory_size_shader_stages_vertex   = itfliesby_engine_assets_shader_allocation_size(assets, &shader_stage_asset_id_vertex,   1);
    const u64 memory_size_shader_stages_fragment = itfliesby_engine_assets_shader_allocation_size(assets, &shader_stage_asset_id_fragment, 1);

    ITFLIESBY_ASSERT(memory_size_shader_stages_vertex > 0);
    ITFLIESBY_ASSERT(memory_size_shader_stages_fragment > 0);
}

internal ItfliesbyRendererHandle
itfliesby_engine_rendering_init() {

    memory renderer_memory           = itfliesby_engine_memory_renderer();
    ItfliesbyRendererHandle renderer = itfliesby_renderer_create_and_init(platform_api,renderer_memory,ITFLIESBY_RENDERER_MEMORY_SIZE_BYTES);
    ITFLIESBY_ASSERT(renderer);

    return(renderer);
}