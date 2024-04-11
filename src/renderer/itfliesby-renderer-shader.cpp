#pragma once

#include "itfliesby-renderer.hpp"

internal void
itfliesby_renderer_shaders_init(
    ItfliesbyRendererShaders* shaders) {

    ITFLIESBY_ASSERT(shaders);
    *shaders = {0};

    ItfliesbyRendererShaderStageStore* shader_store =    &shaders->shader_stage_store;
    ItfliesbyRendererShaderProgramStore* program_store = &shaders->shader_program_store;

    b8 shader_init_success = true;

    GLuint* gl_id_shader_stage_vertex   = shader_store->gl_id_shader_stage_vertex;
    GLuint* gl_id_shader_stage_fragment = shader_store->gl_id_shader_stage_fragment;

    //get gl shader ids
    for (
        u8 shader_index = 0;
        shader_index < ITFLIESBY_RENDERER_SHADER_STAGE_MAX;
        ++shader_index) {
        
        shader_init_success &= (gl_id_shader_stage_vertex[shader_index]   = glCreateShader(GL_VERTEX_SHADER))   != 0;
        shader_init_success &= (gl_id_shader_stage_fragment[shader_index] = glCreateShader(GL_FRAGMENT_SHADER)) != 0;
    }
    ITFLIESBY_ASSERT(shader_init_success);

    //get gl program ids
    GLuint* programs = program_store->gl_id_shader_program;
    b8 program_init_success = true; 
    for (
        u8 program_index = 0;
        program_index < ITFLIESBY_RENDERER_SHADER_PROGRAM_MAX;
        ++program_index) {

        program_init_success &= (programs[program_index] = glCreateProgram() != 0);
    }
    ITFLIESBY_ASSERT(program_init_success);
}

internal void
itfliesby_renderer_shader_compile_vertex_shaders(
    ItfliesbyRendererShaderStageStore* shader_store,
    const char*                        shader_buffer,
    const u64*                         shader_offsets,
    const u8                           shader_count,
    u8*                                shader_results) {

    ITFLIESBY_ASSERT(
        shader_store       &&
        shader_buffer      &&
        shader_offsets     &&
        shader_results     &&
        shader_count   > 0 &&
        shader_count   < ITFLIESBY_RENDERER_SHADER_STAGE_MAX
    );

    //cache our stuff
    GLuint* vertex_shader_gl_id   = shader_store->gl_id_shader_stage_vertex;
    u64     current_shader_offset;
    GLuint  current_shader_gl_id;
    GLint   current_compile_status;
    b8      compile_success = true;

    for (
        u8 shader_index = 0;
        shader_index < shader_count;
        ++shader_index) {

        // get our next shader buffer
        current_shader_offset = shader_offsets[shader_index];
        auto current_shader   = &shader_buffer[current_shader_offset];

        // compile the shader
        glShaderSource( vertex_shader_gl_id[shader_index],1,&current_shader,NULL);
        glCompileShader(vertex_shader_gl_id[shader_index]);
        glGetShaderiv(  vertex_shader_gl_id[shader_index], GL_COMPILE_STATUS, &current_compile_status);

        //store the result
        shader_results[shader_index] = shader_index;

        compile_success &= (current_compile_status == GL_TRUE);
    }

    ITFLIESBY_ASSERT(compile_success);

}

internal void
itfliesby_renderer_shader_compile_fragment_shaders(
    ItfliesbyRendererShaderStageStore* shader_store,
    const char*                        shader_buffer,
    const u64*                         shader_offsets,
    const u8                           shader_count,
    u8*                                shader_results) {

    ITFLIESBY_ASSERT(
        shader_store       &&
        shader_buffer      &&
        shader_offsets     &&
        shader_results     &&
        shader_count   > 0 &&
        shader_count   < ITFLIESBY_RENDERER_SHADER_STAGE_MAX
    );

    //cache our stuff
    GLuint* fragment_shader_gl_id = shader_store->gl_id_shader_stage_fragment;
    u64     current_shader_offset;
    GLuint  current_shader_gl_id;
    GLuint  current_compile_status;
    b8      compile_success = true;

    for (
        u8 shader_index = 0;
        shader_index < shader_count;
        ++shader_index) {

        //get our next shader buffer
        current_shader_offset = shader_offsets[shader_index];
        auto current_shader   = &shader_buffer[current_shader_offset];
        
        //compile the shader
        glShaderSource( fragment_shader_gl_id[shader_index],1,&current_shader,NULL);
        glCompileShader(fragment_shader_gl_id[shader_index]);
        glGetShaderiv(  fragment_shader_gl_id[shader_index], GL_COMPILE_STATUS, &current_compile_status);

        //store the result
        shader_results[shader_index] = shader_index;

        compile_success &= (current_compile_status == GL_TRUE);
    }

    ITFLIESBY_ASSERT(compile_success);

}

internal void
itfliesby_renderer_shader_programs_create(
    ItfliesbyRendererShaderProgramStore*     program_store,    
    const ItfliesbyRendererShaderStageStore* shader_store,
    const u8*                                vertex_stage_indexes,
    const u8*                                fragment_stage_indexes,
    u8                                       count_programs,
    u8*                                      program_results) {

    ITFLIESBY_ASSERT(
        program_store          &&
        shader_store           &&
        vertex_stage_indexes   &&
        fragment_stage_indexes &&
        program_results        &&
        count_programs > 0     &&
        count_programs < ITFLIESBY_RENDERER_SHADER_PROGRAM_MAX
    );

    //cache our stage info
    const GLuint* stage_store_vertex_shader_gl_id   = shader_store->gl_id_shader_stage_vertex; 
    const GLuint* stage_store_fragment_shader_gl_id = shader_store->gl_id_shader_stage_fragment; 

    //cache our program info
    GLuint* program_gl_ids                            = program_store->gl_id_shader_program;
    u8*     program_vertex_shader_stage_store_index   = program_store->shader_stage_store_index_vertex;
    u8*     program_fragment_shader_stage_store_index = program_store->shader_stage_store_index_fragment;
    
    //first, lets prefetch a list of gl ids for our programs
    GLuint program_gl_id_vertex[ITFLIESBY_RENDERER_SHADER_PROGRAM_MAX];
    GLuint program_gl_id_fragment[ITFLIESBY_RENDERER_SHADER_PROGRAM_MAX];
    u8     current_shader_store_vertex_index;
    u8     current_shader_store_fragment_index;
    for (
        u8 program_index = 0;
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
    GLuint current_program_gl_id_vertex;
    GLuint current_program_gl_id_fragment;
    GLuint current_program_gl_id;
    GLint  current_shader_link_status;
    b8     shader_create_succes = true;
    for (
        u8 program_index = 0;
        program_index < count_programs;
        ++program_index) {

        current_program_gl_id_vertex   = program_gl_id_vertex[program_index]; 
        current_program_gl_id_fragment = program_gl_id_fragment[program_index]; 
        current_program_gl_id          = program_gl_ids[program_index];
        program_results[program_index] = current_program_gl_id;

        glAttachShader(current_program_gl_id, current_program_gl_id_vertex);
        glAttachShader(current_program_gl_id, current_program_gl_id_fragment);
        glLinkProgram(current_program_gl_id);   
        u32 program_error = glGetError();

        glGetProgramiv(current_program_gl_id, GL_LINK_STATUS, &current_shader_link_status);
        shader_create_succes &= (current_shader_link_status == GL_TRUE);

    }

    ITFLIESBY_ASSERT(shader_create_succes);
}