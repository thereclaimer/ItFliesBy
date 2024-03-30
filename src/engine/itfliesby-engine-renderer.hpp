#ifndef ITFLIESBY_ENGINE_RENDERER_HPP
#define ITFLIESBY_ENGINE_RENDERER_HPP

#include "itfliesby-engine.hpp"
#include "itfliesby-engine-globals.hpp"

#define ITFLIESBY_ENGINE_RENDERER_MEMORY_PARTITION_SIZE         ITFLIESBY_MATH_MEGABYTES(64)
#define ITFLIESBY_ENGINE_RENDERER_MEMORY_PARTITION_CONTEXT_SIZE ITFLIESBY_MATH_MEGABYTES(64)

enum ItfliesbyEngineRendererShaderStageStatus : s32{
    ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_STATUS_UNLOADED = 0,
    ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_STATUS_COMPILED = 1,
    ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_STATUS_FAILED   = 2
};

enum ItfliesbyEngineRendererShaderStageVertex : s32 {
    ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_VERTEX_INVALID       = -1,
    ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_VERTEX_TEXTURED_QUAD = 0,
    ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_VERTEX_COUNT         = 1,
};

struct ItfliesbyEngineRendererShaderStageStoreVertex {
    itfliesby_renderer_vertex_shader         renderer_stage[ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_VERTEX_COUNT];
    ItfliesbyEngineAssetsShader              asset[ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_VERTEX_COUNT];
    ItfliesbyEngineRendererShaderStageStatus status[ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_VERTEX_COUNT];
};

enum ItfliesbyEngineRendererShaderStageFragment : s32 {
    ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_FRAGMENT_INVALID       = -1,
    ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_FRAGMENT_TEXTURED_QUAD = 0,
    ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_FRAGMENT_COUNT         = 1,
};

struct ItfliesbyEngineRendererShaderStageStoreFragment {
    itfliesby_renderer_fragment_shader         renderer_stage[ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_FRAGMENT_COUNT];
    ItfliesbyEngineAssetsShader                asset[ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_FRAGMENT_COUNT];
    ItfliesbyEngineRendererShaderStageStatus   status[ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_FRAGMENT_COUNT];
};

struct ItfliesbyEngineRendererShaderStageStore {
    ItfliesbyEngineRendererShaderStageStoreVertex   vertex;
    ItfliesbyEngineRendererShaderStageStoreFragment fragment;
};

enum ItfliesbyEngineRendererShaderProgram : s32 {
    ITFLIESBY_ENGINE_RENDERER_SHADER_PROGRAM_INVALID       = -1,
    ITFLIESBY_ENGINE_RENDERER_SHADER_PROGRAM_TEXTURED_QUAD = 0,
    ITFLIESBY_ENGINE_RENDERER_SHADER_PROGRAM_COUNT         = 1,
};

enum ItfliesbyEngineRendererShaderProgramStatus : s32{
    ITFLIESBY_ENGINE_RENDERER_SHADER_PROGRAM_STATUS_UNLOADED = 0,
    ITFLIESBY_ENGINE_RENDERER_SHADER_PROGRAM_STATUS_COMPILED = 1,
    ITFLIESBY_ENGINE_RENDERER_SHADER_PROGRAM_STATUS_FAILED   = 2
};

struct ItfliesbyEngineRendererShaderProgramStore {
    ItfliesbyEngineRendererShaderStageVertex   engine_vertex_stage[ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_VERTEX_COUNT];
    ItfliesbyEngineRendererShaderStageFragment engine_fragment_stage[ITFLIESBY_ENGINE_RENDERER_SHADER_STAGE_VERTEX_COUNT];
    itfliesby_renderer_shader_program          render_shader_program[ITFLIESBY_ENGINE_RENDERER_SHADER_PROGRAM_COUNT];
    ItfliesbyEngineRendererShaderProgramStatus status[ITFLIESBY_ENGINE_RENDERER_SHADER_PROGRAM_COUNT];
};

struct ItfliesbyEngineRendererMemory {
    itfliesby_memory_partition        partition;
    itfliesby_memory_partition        rendering_context_partition;
    itfliesby_memory_allocator_linear shader_asset_composite_allocator;
};

struct ItfliesbyEngineRenderer {
    ItfliesbyEngineRendererMemory             memory;
    itfliesby_renderer                        renderer_handle;
    ItfliesbyEngineRendererShaderStageStore   shader_stage_store;
    ItfliesbyEngineRendererShaderProgramStore shader_programs;
};


void
itfliesby_engine_renderer_init(
    ItfliesbyEngineRenderer* renderer,
    itfliesby_memory_arena   arena);

 void
itfliesby_engine_renderer_update(
    ItfliesbyEngineRenderer* renderer,
    ItfliesbyEngineAssets*   assets);

#endif //ITFLIESBY_ENGINE_RENDERER_HPP