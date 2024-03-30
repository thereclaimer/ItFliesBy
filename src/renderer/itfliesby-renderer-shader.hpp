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
    u8    count_gl_id_shader_stage_vertex;
    u8    count_gl_id_shader_stage_fragment;
};

struct ItfliesbyRendererShaderProgramStore {
    GLint gl_id_shader_program[ITFLIESBY_RENDERER_SHADER_PROGRAM_MAX];
    u8    shader_stage_store_index_vertex[ITFLIESBY_RENDERER_SHADER_PROGRAM_MAX];
    u8    shader_stage_store_index_fragment[ITFLIESBY_RENDERER_SHADER_PROGRAM_MAX];
    u8    count_gl_id_shader_program;
};

struct ItfliesbyRendererShaders {
    ItfliesbyRendererShaderStageStore   shader_stage_store;
    ItfliesbyRendererShaderProgramStore shader_program_store;
};

void
itfliesby_renderer_shader_compile_vertex_shaders(
    ItfliesbyRendererShaderStageStore* shader_store,
    const char*                        shader_buffer,
    const u64*                         shader_offsets,
    const u8                           shader_count,
    u8*                                shader_results);

void
itfliesby_renderer_shader_compile_fragment_shaders(
    ItfliesbyRendererShaderStageStore* shader_store,
    const char*                        shader_buffer,
    const u64*                         shader_offsets,
    const u8                           shader_count,
    u8*                                shader_results);

void
itfliesby_renderer_shader_programs_create(
    ItfliesbyRendererShaderProgramStore*     program_store,    
    const ItfliesbyRendererShaderStageStore* shader_store,
    const u8*                                vertex_stages,
    const u8*                                fragment_stages,
    u8                                       count_programs,
    u8*                                      program_results);

#endif //ITFLIESBY_RENDERER_SHADER_HPP