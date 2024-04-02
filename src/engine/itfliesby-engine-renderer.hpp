#ifndef ITFLIESBY_ENGINE_RENDERER_HPP
#define ITFLIESBY_ENGINE_RENDERER_HPP

#include "itfliesby-engine.hpp"
#include "itfliesby-engine-globals.hpp"

#define ITFLIESBY_ENGINE_RENDERER_MEMORY_PARTITION_SIZE             ITFLIESBY_MATH_MEGABYTES(64)
#define ITFLIESBY_ENGINE_RENDERER_MEMORY_PARTITION_CONTEXT_SIZE     ITFLIESBY_MATH_MEGABYTES(64)
#define ITFLIESBY_ENGINE_RENDERER_MEMORY_ALLOCATOR_SIZE_SHADER_DATA ITFLIESBY_MATH_MEGABYTES(4)

enum ItfliesbyEngineRendererShaderStageVertex : s32 {
    ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_VERTEX_INVALID       = -1,
    ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_VERTEX_TEXTURED_QUAD = 0,
    ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_VERTEX_COUNT         = 1,
};

enum ItfliesbyEngineRendererShaderStageFragment : s32 {
    ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_FRAGMENT_INVALID       = -1,
    ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_FRAGMENT_TEXTURED_QUAD = 0,
    ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_FRAGMENT_COUNT         = 1,
};


enum ItfliesbyEngineRendererShaderProgram : s32 {
    ITFLIESBY_ENGINE_RENDERER_SHADER_PROGRAM_INVALID       = -1,
    ITFLIESBY_ENGINE_RENDERER_SHADER_PROGRAM_TEXTURED_QUAD = 0,
    ITFLIESBY_ENGINE_RENDERER_SHADER_PROGRAM_COUNT         = 1,
};

struct ItfliesbyEngineRendererShaderStageStore {
    itfliesby_renderer_vertex_shader           renderer_stage_id_vertex[ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_FRAGMENT_COUNT];
    itfliesby_renderer_fragment_shader         renderer_stage_id_fragment[ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_VERTEX_COUNT];
};

struct ItfliesbyEngineRendererShaderProgramStore {
    ItfliesbyEngineRendererShaderStageVertex   shader_stage_store_id_vertex[ITFLIESBY_ENGINE_RENDERER_SHADER_PROGRAM_COUNT];
    ItfliesbyEngineRendererShaderStageFragment shader_stage_store_id_fragment[ITFLIESBY_ENGINE_RENDERER_SHADER_PROGRAM_COUNT];
    itfliesby_renderer_shader_program          shader_program_id[ITFLIESBY_ENGINE_RENDERER_SHADER_PROGRAM_COUNT];
};

struct ItfliesbyEngineRendererMemory {
    itfliesby_memory_partition        partition;
    itfliesby_memory_partition        rendering_context_partition;
    itfliesby_memory_allocator_linear shader_asset_data_allocator;
};

struct ItfliesbyEngineRenderer {
    ItfliesbyEngineRendererMemory             memory;
    itfliesby_renderer                        renderer_handle;
    ItfliesbyEngineRendererShaderStageStore   shader_stage_store;
    ItfliesbyEngineRendererShaderProgramStore shader_program_store;
    ItfliesbyEngineAssets*                    assets;
};

void 
itfliesby_engine_renderer_shader_store_init(
    ItfliesbyEngineRendererShaderStageStore* shader_stage_store,
    ItfliesbyEngineRendererMemory*           renderer_memory,
    ItfliesbyEngineAssets*                   assets,
    itfliesby_renderer                       render_context);

void
itfliesby_engine_renderer_init(
    ItfliesbyEngineRenderer* renderer,
    ItfliesbyEngineAssets*   assets,
    itfliesby_memory_arena   arena);

 void
itfliesby_engine_renderer_update(
    ItfliesbyEngineRenderer* renderer,
    ItfliesbyEngineAssets*   assets);

#endif //ITFLIESBY_ENGINE_RENDERER_HPP