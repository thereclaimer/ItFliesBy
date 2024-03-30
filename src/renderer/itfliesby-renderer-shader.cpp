#pragma once

#include "itfliesby-renderer.hpp"

internal void
itfliesby_renderer_shaders_init(
    ItfliesbyRendererShaders* shaders) {

    ITFLIESBY_ASSERT(shaders);
    *shaders = {0};

    ItfliesbyRendererShaderStageStore* shader_store = &shaders->shader_stage_store;

    b8 shader_init_success = true;

    s32* gl_id_shader_stage_vertex = shader_store->gl_id_shader_stage_vertex;
    s32* fragment_shader_gl_id     = shader_store->gl_id_shader_stage_fragment;

    //let's ask the GPU to give us shader handles ahead of time
    for (
        u32 shader_index = 0;
        shader_index < ITFLIESBY_RENDERER_SHADER_STAGE_MAX;
        ++shader_index) {
        
        shader_init_success &= (gl_id_shader_stage_vertex[shader_index]   = glCreateShader(GL_VERTEX_SHADER))   != 0;
        shader_init_success &= (fragment_shader_gl_id[shader_index] = glCreateShader(GL_FRAGMENT_SHADER)) != 0;
    }

    ITFLIESBY_ASSERT(shader_init_success);
}

internal void
itfliesby_renderer_shader_compile_vertex_shaders(
    ItfliesbyRendererShaderStageStore* shader_store,
    const char*                   shader_buffer,
    const u32*                    shader_offsets,
    const u32                     shader_count,
    s32*                          shader_results) {

    ITFLIESBY_ASSERT(
        shader_store       &&
        shader_buffer      &&
        shader_offsets     &&
        shader_count   > 0 &&
        shader_count   < ITFLIESBY_RENDERER_SHADER_STAGE_MAX
    );

    //cache our stuff
    const char** current_shader        = NULL;
    GLint*       vertex_shader_gl_id   = shader_store->gl_id_shader_stage_vertex;
    u32          current_shader_offset;
    GLint        current_shader_gl_id;
    GLint        current_compile_status;
    b8           compile_success = true;
    u32          shader_store_count = shader_store->count_gl_id_shader_stage_vertex;

    for (
        u32 shader_index = 0;
        shader_index < shader_count;
        ++shader_index) {

        //get our next shader buffer
        current_shader_offset = shader_offsets[shader_index];
        current_shader        = (const char**)&shader_buffer[current_shader_offset];
        
        //compile the shader
        glShaderSource( vertex_shader_gl_id[shader_index],1,current_shader,NULL);
        glCompileShader(vertex_shader_gl_id[shader_index]);
        glGetShaderiv(  vertex_shader_gl_id[shader_index], GL_COMPILE_STATUS, &current_compile_status);

        //store the result
        shader_results[shader_index] = shader_store_count;
        ++shader_store_count;

        compile_success &= (current_compile_status == GL_TRUE);
    }

    ITFLIESBY_ASSERT(compile_success);

    shader_store->count_gl_id_shader_stage_vertex = shader_store_count;
}

internal void
itfliesby_renderer_shader_compile_fragment_shaders(
    ItfliesbyRendererShaderStageStore* shader_store,
    const char*                   shader_buffer,
    const u32*                    shader_offsets,
    const u32                     shader_count,
    s32*                          shader_results) {

    ITFLIESBY_ASSERT(
        shader_store       &&
        shader_buffer      &&
        shader_offsets     &&
        shader_count   > 0 &&
        shader_count   < ITFLIESBY_RENDERER_SHADER_STAGE_MAX
    );

    //cache our stuff
    const char** current_shader        = NULL;
    GLint*       fragment_shader_gl_id = shader_store->gl_id_shader_stage_fragment;
    u32          current_shader_offset;
    GLint        current_shader_gl_id;
    GLint        current_compile_status;
    b8           compile_success = true;
    u32          shader_store_count = shader_store->count_gl_id_shader_stage_fragment;

    for (
        u32 shader_index = 0;
        shader_index < shader_count;
        ++shader_index) {

        //get our next shader buffer
        current_shader_offset = shader_offsets[shader_index];
        current_shader        = (const char**)&shader_buffer[current_shader_offset];
        
        //compile the shader
        glShaderSource( fragment_shader_gl_id[shader_index],1,current_shader,NULL);
        glCompileShader(fragment_shader_gl_id[shader_index]);
        glGetShaderiv(  fragment_shader_gl_id[shader_index], GL_COMPILE_STATUS, &current_compile_status);

        //store the result
        shader_results[shader_index] = shader_store_count;
        ++shader_store_count;

        compile_success &= (current_compile_status == GL_TRUE);
    }

    ITFLIESBY_ASSERT(compile_success);

    shader_store->count_gl_id_shader_stage_fragment = shader_store_count;
}

internal void
itfliesby_rendering_shader_programs_create(
    ItfliesbyRendererShaderProgramStore* program_store,    
    const ItfliesbyRendererShaderStageStore*  shader_store,
    const s32*                           vertex_stage_indexes,
    const s32*                           fragment_stage_indexes,
    s32                                  count_programs) {

    ITFLIESBY_ASSERT(
        program_store          &&
        shader_store           &&
        vertex_stage_indexes   &&
        fragment_stage_indexes &&
        count_programs > 0     &&
        count_programs < ITFLIESBY_RENDERER_SHADER_PROGRAM_MAX
    );

    //cache our stage info
    const GLint* stage_store_vertex_shader_gl_id   = shader_store->gl_id_shader_stage_vertex; 
    const GLint* stage_store_fragment_shader_gl_id = shader_store->gl_id_shader_stage_fragment; 

    //cache our program info
    u32    program_gl_ids_count                      = program_store->count_gl_id_shader_program;
    GLint* program_gl_ids                            = &program_store->gl_id_shader_program[program_gl_ids_count];
    u32*   program_vertex_shader_stage_store_index   = &program_store->shader_stage_store_index_vertex[program_gl_ids_count];
    u32*   program_fragment_shader_stage_store_index = &program_store->shader_stage_store_index_fragment[program_gl_ids_count];
    
    //first, lets prefetch a list of gl ids for our programs
    GLint program_gl_id_vertex[ITFLIESBY_RENDERER_SHADER_PROGRAM_MAX];
    GLint program_gl_id_fragment[ITFLIESBY_RENDERER_SHADER_PROGRAM_MAX];
    u32   current_shader_store_vertex_index;
    u32   current_shader_store_fragment_index;
    for (
        u32 program_index = 0;
        program_index < count_programs;
        ++program_index) {

        current_shader_store_vertex_index   = vertex_stage_indexes[program_index]; 
        current_shader_store_fragment_index = fragment_stage_indexes[program_index]; 

        program_gl_id_vertex[program_index]   = stage_store_vertex_shader_gl_id[current_shader_store_vertex_index]; 
        program_gl_id_fragment[program_index] = stage_store_fragment_shader_gl_id[current_shader_store_fragment_index];

        //while we're here, we can set the program stage info
        program_vertex_shader_stage_store_index[program_index]   = current_shader_store_vertex_index;
        program_fragment_shader_stage_store_index[program_index] = current_shader_store_fragment_index;
    }

    //now we can create our programs
    GLint current_program_gl_id_vertex;
    GLint current_program_gl_id_fragment;
    GLint current_program_gl_id;
    GLint current_shader_link_status;
    b8    shader_create_succes = true;
    for (
        u32 program_index = 0;
        program_index < count_programs;
        ++program_index) {

        current_program_gl_id_vertex   = program_gl_id_vertex[program_index]; 
        current_program_gl_id_fragment = program_gl_id_fragment[program_index]; 
        current_program_gl_id          = program_gl_ids[program_index];

        glAttachShader(current_program_gl_id, current_program_gl_id_vertex);
        glAttachShader(current_program_gl_id, current_program_gl_id_fragment);
        glLinkProgram(current_program_gl_id);   

        glGetProgramiv(current_program_gl_id, GL_LINK_STATUS, &current_shader_link_status);
        shader_create_succes &= (current_shader_link_status == GL_TRUE);
    }

    ITFLIESBY_ASSERT(shader_create_succes);

    program_store->count_gl_id_shader_program += count_programs;
}