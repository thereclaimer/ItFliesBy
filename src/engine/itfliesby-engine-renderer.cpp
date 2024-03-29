#include "itfliesby-engine-renderer.hpp"

#pragma once

internal void
itfliesby_engine_renderer_programs_init(
    ItfliesbyEngineRendererShaderProgramStore* programs) {

    ItfliesbyEngineRendererShaderStageVertex*   engine_vertex_stage   = programs->engine_vertex_stage; 
    ItfliesbyEngineRendererShaderStageFragment* engine_fragment_stage = programs->engine_fragment_stage; 
    itfliesby_renderer_shader_program*          render_shader_program = programs->render_shader_program; 
    ItfliesbyEngineRendererShaderProgramStatus* status                = programs->status; 

    //textured quad
    engine_vertex_stage[ITFLIESBY_ENGINE_RENDERER_SHADER_PROGRAM_TEXTURED_QUAD]   = ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_VERTEX_TEXTURED_QUAD;
    engine_fragment_stage[ITFLIESBY_ENGINE_RENDERER_SHADER_PROGRAM_TEXTURED_QUAD] = ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_FRAGMENT_TEXTURED_QUAD;
    render_shader_program[ITFLIESBY_ENGINE_RENDERER_SHADER_PROGRAM_TEXTURED_QUAD] = 0;
    status[ITFLIESBY_ENGINE_RENDERER_SHADER_PROGRAM_TEXTURED_QUAD]                = ITFLIESBY_ENGINE_RENDERER_SHADER_PROGRAM_STATUS_UNLOADED;

}

internal void
itfliesby_engine_renderer_fragment_shaders_init(
    ItfliesbyEngineRendererShaderStageStoreFragment* fragment_shader_store) {

    itfliesby_renderer_vertex_shader*         renderer_stage = fragment_shader_store->renderer_stage; 
    ItfliesbyEngineAssetsShader*              asset          = fragment_shader_store->asset; 
    ItfliesbyEngineRendererShaderStageStatus* status         = fragment_shader_store->status; 

    //textured quad
    renderer_stage[ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_FRAGMENT_TEXTURED_QUAD] = 0;
    asset[ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_FRAGMENT_TEXTURED_QUAD]          = ITFLIESBY_ENGINE_ASSETS_SHADER_TEXTURED_QUAD_FRAGMENT_SHADER;
    status[ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_FRAGMENT_TEXTURED_QUAD]         = ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_STATUS_UNLOADED;
}

internal void
itfliesby_engine_renderer_vertex_shaders_init(
    ItfliesbyEngineRendererShaderStageStoreVertex* vertex_shader_store) {

    itfliesby_renderer_vertex_shader*         renderer_stage = vertex_shader_store->renderer_stage; 
    ItfliesbyEngineAssetsShader*              asset          = vertex_shader_store->asset; 
    ItfliesbyEngineRendererShaderStageStatus* status         = vertex_shader_store->status; 

    //textured quad
    renderer_stage[ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_VERTEX_TEXTURED_QUAD] = 0;
    asset[ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_VERTEX_TEXTURED_QUAD]          = ITFLIESBY_ENGINE_ASSETS_SHADER_TEXTURED_QUAD_VERTEX_SHADER;
    status[ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_VERTEX_TEXTURED_QUAD]         = ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_STATUS_UNLOADED;
}

internal void
itfliesby_engine_renderer_init(
    ItfliesbyEngineRenderer* renderer,
    itfliesby_memory_arena   arena) {
    
    *renderer = {0};
    
    auto renderer_memory = &renderer->memory;

    renderer_memory->partition = itfliesby_memory_partition_create(arena,"ENGINE RENDERER PRTN",ITFLIESBY_ENGINE_RENDERER_MEMORY_PARTITION_SIZE);
    ITFLIESBY_ASSERT(renderer_memory->partition);

    renderer_memory->shader_asset_composite_allocator = itfliesby_memory_allocator_linear_create(renderer_memory->partition,"SHADER ASSET ALCTR",512);
    ITFLIESBY_ASSERT(renderer_memory->shader_asset_composite_allocator);

    //shaders
    auto vertex_store   = &renderer->shader_stage_store.vertex;
    auto fragment_store = &renderer->shader_stage_store.fragment;
    auto program_store  = &renderer->shader_programs;

    //initialize the shader definitions
    itfliesby_engine_renderer_vertex_shaders_init(vertex_store);
    itfliesby_engine_renderer_fragment_shaders_init(fragment_store);
    itfliesby_engine_renderer_programs_init(program_store);


    ITFLIESBY_NOP();
}

struct ItfliesbyEngineRendererShaderStageAssetComposite {
    s32* render_shader_id;
    s32* engine_shader_id;
    s32* asset_id;
    u32  count;
};

internal ItfliesbyEngineRendererShaderStageAssetComposite
itfliesby_engine_renderer_shader_stage_asset_composite_reset(
    itfliesby_memory_allocator_linear linear_allocator,
    u32                               count_stages) {

    u32 mem_size = sizeof(s32) * count_stages; 

    ItfliesbyEngineRendererShaderStageAssetComposite composite = {0};
    
    itfliesby_memory_allocator_linear_reset(linear_allocator);

    composite.asset_id         = (s32*)itfliesby_memory_allocator_linear_allocate(linear_allocator,mem_size);
    composite.render_shader_id = (s32*)itfliesby_memory_allocator_linear_allocate(linear_allocator,mem_size);
    composite.engine_shader_id = (s32*)itfliesby_memory_allocator_linear_allocate(linear_allocator,mem_size);
    composite.count            = 0;

    return(composite);
}

internal void
itfliesby_engine_renderer_shader_stages_vertex_update(
    ItfliesbyEngineRendererShaderStageStoreVertex* vertex_shader_store,
    ItfliesbyEngineRendererMemory*                 memory,
    ItfliesbyEngineAssets*                         assets) {

    itfliesby_renderer_vertex_shader*              vertex_renderer_stage = vertex_shader_store->renderer_stage; 
    ItfliesbyEngineAssetsShader*                   vertex_asset          = vertex_shader_store->asset; 
    ItfliesbyEngineRendererShaderStageStatus*      vertex_status         = vertex_shader_store->status; 

    ItfliesbyEngineRendererShaderStageAssetComposite vertex_shader_asset_composite = 
        itfliesby_engine_renderer_shader_stage_asset_composite_reset(
            memory->shader_asset_composite_allocator,
            ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_VERTEX_COUNT
        );

    s32* composite_engine_shaders   = vertex_shader_asset_composite.engine_shader_id;
    s32* composite_renderer_shaders = vertex_shader_asset_composite.render_shader_id;
    s32* composite_assets           = vertex_shader_asset_composite.asset_id;
    u32  composite_count            = 0;

    for (
        s32 vertex_shader_index = 0;
        vertex_shader_index < ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_VERTEX_COUNT;
        ++vertex_shader_index) {
        
        if (vertex_status[vertex_shader_index] == ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_STATUS_UNLOADED) {
            composite_engine_shaders[composite_count]   = vertex_shader_index;
            composite_renderer_shaders[composite_count] = vertex_renderer_stage[vertex_shader_index];
            composite_assets[composite_count]           = vertex_asset[vertex_shader_index];
            ++composite_count;
        }
    }
    vertex_shader_asset_composite.count = composite_count;
}

internal void
itfliesby_engine_renderer_shader_stages_fragment_update(
    ItfliesbyEngineRendererShaderStageStoreFragment* fragment_shader_store,
    ItfliesbyEngineRendererMemory*                   memory,
    ItfliesbyEngineAssets*                           assets) {

    itfliesby_renderer_fragment_shader*              fragment_renderer_stage = fragment_shader_store->renderer_stage; 
    ItfliesbyEngineAssetsShader*                     fragment_asset          = fragment_shader_store->asset; 
    ItfliesbyEngineRendererShaderStageStatus*        fragment_status         = fragment_shader_store->status; 

    ItfliesbyEngineRendererShaderStageAssetComposite fragment_shader_asset_composite = 
        itfliesby_engine_renderer_shader_stage_asset_composite_reset(
            memory->shader_asset_composite_allocator,
            ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_FRAGMENT_COUNT
        );

    s32* composite_engine_shaders   = fragment_shader_asset_composite.engine_shader_id;
    s32* composite_renderer_shaders = fragment_shader_asset_composite.render_shader_id;
    s32* composite_assets           = fragment_shader_asset_composite.asset_id;
    u32  composite_count            = 0;

    for (
        s32 fragment_shader_index = 0;
        fragment_shader_index < ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_VERTEX_COUNT;
        ++fragment_shader_index) {
        
        if (fragment_status[fragment_shader_index] == ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_STATUS_UNLOADED) {
            composite_engine_shaders[composite_count]   = fragment_shader_index;
            composite_renderer_shaders[composite_count] = fragment_renderer_stage[fragment_shader_index];
            composite_assets[composite_count]           = fragment_asset[fragment_shader_index];
            ++composite_count;
        }
    }
    fragment_shader_asset_composite.count = composite_count;
}

internal void
itfliesby_engine_renderer_shader_stages_update(
    ItfliesbyEngineRendererShaderStageStore* shader_stages,
    ItfliesbyEngineRendererMemory*           memory,
    ItfliesbyEngineAssets*                   assets) {


    //update the vertex shaders
    ItfliesbyEngineRendererShaderStageStoreVertex*   vertex_shader_store   = &shader_stages->vertex; 
    ItfliesbyEngineRendererShaderStageStoreFragment* fragment_shader_store = &shader_stages->fragment;

    itfliesby_engine_renderer_shader_stages_vertex_update(vertex_shader_store,memory,assets);
    itfliesby_engine_renderer_shader_stages_fragment_update(fragment_shader_store,memory,assets);
}

internal void
itfliesby_engine_renderer_update(
    ItfliesbyEngineRenderer* renderer,
    ItfliesbyEngineAssets*   assets) {

    itfliesby_engine_renderer_shader_stages_update(
        &renderer->shader_stage_store,
        &renderer->memory,
        assets
    );
}