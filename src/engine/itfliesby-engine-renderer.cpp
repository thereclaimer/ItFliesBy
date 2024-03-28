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

internal void
itfliesby_engine_renderer_update(
) {
    
}