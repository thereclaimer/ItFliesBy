#ifndef ITFLIESBY_RENDERER_SHADER_HPP
#define ITFLIESBY_RENDERER_SHADER_HPP

#include <common/itfliesby-types.hpp>
#include "itfliesby-renderer-gl.hpp"

#define ITFLIESBY_RENDERER_SHADER_STAGE_MAX   128
#define ITFLIESBY_RENDERER_SHADER_PROGRAM_MAX 128

#define ITFLIESBY_RENDERER_SHADER_INVALID 0

struct ItfliesbyRendererShaderStageStore  {
    GLint gl_id_shader_stage_vertex[ITFLIESBY_RENDERER_SHADER_STAGE_MAX];
    GLint gl_id_shader_stage_fragment[ITFLIESBY_RENDERER_SHADER_STAGE_MAX];
    u32   count_gl_id_shader_stage_vertex;
    u32   count_gl_id_shader_stage_fragment;
};

struct ItfliesbyRendererShaderProgramStore {
    GLint gl_id_shader_program[ITFLIESBY_RENDERER_SHADER_PROGRAM_MAX];
    u32   shader_stage_store_index_vertex[ITFLIESBY_RENDERER_SHADER_PROGRAM_MAX];
    u32   shader_stage_store_index_fragment[ITFLIESBY_RENDERER_SHADER_PROGRAM_MAX];
    u32   count_gl_id_shader_program;
};

struct ItfliesbyRendererShaders {
    ItfliesbyRendererShaderStageStore   shader_stage_store;
    ItfliesbyRendererShaderProgramStore shader_program_store;
};

void
itfliesby_renderer_shader_compile_vertex_shaders(
    ItfliesbyRendererShaderStageStore* shader_store,
    const char*                        shader_buffer,
    const u32*                         shader_offsets,
    const u32                          shader_count,
    s32*                               shader_results);

void
itfliesby_renderer_shader_programs_create(
    ItfliesbyRendererShaderProgramStore*      program_store,    
    const ItfliesbyRendererShaderStageStore*  shader_store,
    const s32*                                vertex_stages,
    const s32*                                fragment_stages,
    s32                                       count_programs);

#endif //ITFLIESBY_RENDERER_SHADER_HPP