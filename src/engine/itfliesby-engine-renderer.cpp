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

    //initialize partitions
    renderer_memory->partition                   = itfliesby_memory_partition_create(arena,"ENGINE RENDERER PRTN",ITFLIESBY_ENGINE_RENDERER_MEMORY_PARTITION_SIZE);
    renderer_memory->rendering_context_partition = itfliesby_memory_partition_create(arena,"RNDR CNTXT PRTN"     ,ITFLIESBY_ENGINE_RENDERER_MEMORY_PARTITION_CONTEXT_SIZE);
    ITFLIESBY_ASSERT(renderer_memory->partition);
    ITFLIESBY_ASSERT(renderer_memory->rendering_context_partition);

    //initialize allocators
    renderer_memory->shader_asset_composite_allocator = itfliesby_memory_allocator_linear_create(renderer_memory->partition,"SHADER ASSET ALCTR",     512);
    renderer_memory->shader_asset_data_allocator      = itfliesby_memory_allocator_linear_create(renderer_memory->partition,"SHADER ASSET DATA ALCTR",ITFLIESBY_ENGINE_RENDERER_MEMORY_ALLOCATOR_SIZE_SHADER_DATA);
    ITFLIESBY_ASSERT(renderer_memory->shader_asset_composite_allocator);
    ITFLIESBY_ASSERT(renderer_memory->shader_asset_data_allocator);

    //initialize the shader definitions
    auto vertex_store   = &renderer->shader_stage_store.vertex;
    auto fragment_store = &renderer->shader_stage_store.fragment;
    auto program_store  = &renderer->shader_programs;

    itfliesby_engine_renderer_vertex_shaders_init(vertex_store);
    itfliesby_engine_renderer_fragment_shaders_init(fragment_store);
    itfliesby_engine_renderer_programs_init(program_store);

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
}

//TODO: these can all be converted to u8*

struct ItfliesbyEngineRendererShaderStageAssetComposite {
    u8*  render_shader_id;
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
    composite.render_shader_id = (u8*)itfliesby_memory_allocator_linear_allocate(linear_allocator,sizeof(u8) * count_stages);
    composite.engine_shader_id = (s32*)itfliesby_memory_allocator_linear_allocate(linear_allocator,mem_size);
    composite.count            = 0;

    return(composite);
}

internal void
itfliesby_engine_renderer_shader_stages_vertex_update(
    ItfliesbyEngineRendererShaderStageStoreVertex* vertex_shader_store,
    ItfliesbyEngineRendererMemory*                 renderer_memory,
    ItfliesbyEngineAssets*                         assets,
    itfliesby_renderer                             renderer) {

    itfliesby_renderer_vertex_shader*              vertex_renderer_stage = vertex_shader_store->renderer_stage; 
    ItfliesbyEngineAssetsShader*                   vertex_asset          = vertex_shader_store->asset; 
    ItfliesbyEngineRendererShaderStageStatus*      vertex_status         = vertex_shader_store->status; 

    ItfliesbyEngineRendererShaderStageAssetComposite vertex_shader_asset_composite = 
        itfliesby_engine_renderer_shader_stage_asset_composite_reset(
            renderer_memory->shader_asset_composite_allocator,
            ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_VERTEX_COUNT
        );

    s32* composite_engine_shaders   = vertex_shader_asset_composite.engine_shader_id;
    u8*  composite_renderer_shaders = vertex_shader_asset_composite.render_shader_id;
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

    //get the size of our shader data
    u64 allocation_size = itfliesby_engine_assets_index_allocation_size(
        assets->file_index_store.shader_indexes,
        composite_assets,
        composite_count
    );

    //TODO: we may have the ability to support doing a second allocation next frame
    //if we don't have enough space, but for now we are assuming we can fit everything here

    //allocate space for the shader data    
    // ITFLIESBY_ASSERT(allocation_size < ITFLIESBY_ENGINE_RENDERER_MEMORY_ALLOCATOR_SIZE_SHADER_DATA);
    // memory shader_memory = 
    //     itfliesby_memory_allocator_linear_allocate(
    //         renderer_memory->shader_asset_data_allocator,
    //         allocation_size
    // );
    // ITFLIESBY_ASSERT(shader_memory);

    // //IDGAF
    // u64 offsets[ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_VERTEX_COUNT];

    // //read the shader data
    // itfliesby_engine_assets_load_shaders(
    //     assets,
    //     composite_assets,
    //     shader_memory,
    //     offsets,
    //     composite_count
    // );

    // //now we can compile the shaders
    // itfliesby_renderer_api_shader_compile_vertex_shaders(
    //     renderer,
    //     (const char*)shader_memory,
    //     offsets,
    //     composite_count,
    //     composite_renderer_shaders
    // );

    // //write the results back to our shader store
    // u32 current_renderer_vertex_id;
    // u32 current_engine_vertex_shader_index;
    // for (
    //     u32 composite_index = 0;
    //     composite_index < composite_count;
    //     ++composite_index) {
        
    //     current_engine_vertex_shader_index = composite_engine_shaders[composite_index];
    //     current_renderer_vertex_id         = composite_renderer_shaders[composite_index];

    //     vertex_renderer_stage[current_engine_vertex_shader_index] = current_renderer_vertex_id;
    //     vertex_status[current_engine_vertex_shader_index]         = ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_STATUS_COMPILED;
    // }

    // //reset the memory
    // itfliesby_memory_allocator_linear_reset(renderer_memory->shader_asset_data_allocator);
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
    u8* composite_renderer_shaders = fragment_shader_asset_composite.render_shader_id;
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
    ItfliesbyEngineAssets*                   assets,
    itfliesby_renderer                       renderer) {


    //update the vertex shaders
    ItfliesbyEngineRendererShaderStageStoreVertex*   vertex_shader_store   = &shader_stages->vertex; 
    ItfliesbyEngineRendererShaderStageStoreFragment* fragment_shader_store = &shader_stages->fragment;

    itfliesby_engine_renderer_shader_stages_vertex_update(vertex_shader_store,memory,assets,renderer);
    itfliesby_engine_renderer_shader_stages_fragment_update(fragment_shader_store,memory,assets);
}

internal void
itfliesby_engine_renderer_update(
    ItfliesbyEngineRenderer* renderer,
    ItfliesbyEngineAssets*   assets) {

    itfliesby_engine_renderer_shader_stages_update(
        &renderer->shader_stage_store,
        &renderer->memory,
        assets,
        renderer->renderer_handle
    );

    itfliesby_renderer_api_update_and_render(renderer->renderer_handle);
}