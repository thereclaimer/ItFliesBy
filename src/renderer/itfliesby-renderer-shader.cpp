#pragma once

#include "itfliesby-renderer.hpp"

internal b8
itfliesby_renderer_shader_is_free(
    const ItfliesbyRendererShader* shader) {

    ITFLIESBY_ASSERT(shader);

    b8 shader_free = (
        shader->program_id      || 
        shader->stage_id_vertex || 
        shader->stage_id_fragment) == 0;

    return(shader_free);
}

internal ItfliesbyRendererShaderIndex
itfliesby_renderer_shader_next_free(
    ItfliesbyRendererShaderStore* shader_store) {

    ITFLIESBY_ASSERT(shader_store);

    ItfliesbyRendererShader* shaders = shader_store->shaders;
    
    ITFLIESBY_ASSERT(shaders);
    
    ItfliesbyRendererShader* current_shader = NULL;
    b8                       shader_free    = false;

    for (
        ItfliesbyRendererShaderIndex index = 0;
        index < ITFLIESBY_RENDERER_SHADER_COUNT;
        ++index) {

        current_shader = &shaders[index];

        shader_free = itfliesby_renderer_shader_is_free(current_shader);
        if (shader_free) {
            return(index);
        }
    }

    return(ITFLIESBY_RENDERER_SHADER_ERROR_MAX_SHADERS);
}

external void
itfliesby_renderer_shader_destroy(
    ItfliesbyRenderer*           renderer,
    ItfliesbyRendererShaderIndex shader_index) {

    ITFLIESBY_ASSERT(renderer);
    ITFLIESBY_ASSERT(shader_index > 0 && shader_index < ITFLIESBY_RENDERER_SHADER_COUNT);

    ItfliesbyRendererShaderStore* shader_store      = &renderer->shader_store;
    ItfliesbyRendererShader*      shaders           = shader_store->shaders;
    ItfliesbyRendererShader*      shader_to_destroy = &shaders[shader_index];

    glDeleteShader(shader_to_destroy->stage_id_vertex);
    glDeleteShader(shader_to_destroy->stage_id_fragment);
    glDeleteProgram(shader_to_destroy->program_id);

    shader_to_destroy->stage_id_vertex   = 0;
    shader_to_destroy->stage_id_fragment = 0;
    shader_to_destroy->program_id        = 0;
}

external ItfliesbyRendererShaderIndex
itfliesby_renderer_shader_compile_and_link(
    ItfliesbyRenderer*                  renderer,
    ItfliesbyRendererShaderStageBuffer* shader_stage_buffer_vertex,
    ItfliesbyRendererShaderStageBuffer* shader_stage_buffer_fragment) {

    ITFLIESBY_ASSERT(
        renderer         &&
        shader_stage_buffer_vertex &&
        shader_stage_buffer_fragment
    );

    ItfliesbyRendererShaderStore* shader_stage_store = &renderer->shader_store;

    //get the next free shader index
    ItfliesbyRendererShaderIndex shader_index = itfliesby_renderer_shader_next_free(shader_stage_store);
    if (shader_index < 0) {
        return(shader_index);
    }

    //create the ids for our shader
    GLuint shader_program_id        = glCreateProgram(); 
    GLuint shader_stage_id_vertex   = glCreateShader(GL_VERTEX_SHADER);
    GLuint shader_stage_id_fragment = glCreateShader(GL_FRAGMENT_SHADER);

    //upload the shader source
    glShaderSource(shader_stage_id_vertex,   1, (const char**)&shader_stage_buffer_vertex->shader_stage_data,   NULL);
    glShaderSource(shader_stage_id_fragment, 1, (const char**)&shader_stage_buffer_fragment->shader_stage_data, NULL);

    //compile the shaders
    glCompileShader(shader_stage_id_vertex);
    glCompileShader(shader_stage_id_fragment);

    //check the compile status
    GLint stage_status_vertex   = 0;
    GLint stage_status_fragment = 0;
    
    glGetShaderiv(shader_stage_id_vertex,   GL_COMPILE_STATUS, &stage_status_vertex);
    glGetShaderiv(shader_stage_id_fragment, GL_COMPILE_STATUS, &stage_status_fragment);
    
    b8 shader_compiled_vertex    = (stage_status_vertex   == GL_TRUE);
    b8 shader_compiled_fragement = (stage_status_fragment == GL_TRUE);

    shader_stage_buffer_vertex->result   = shader_compiled_vertex    ? ITFLIESBY_RENDERER_SHADER_ERROR_OKAY : ITFLIESBY_RENDERER_SHADER_ERROR_FAILED_TO_COMPILE_STAGE_VERTEX; 
    shader_stage_buffer_fragment->result = shader_compiled_fragement ? ITFLIESBY_RENDERER_SHADER_ERROR_OKAY : ITFLIESBY_RENDERER_SHADER_ERROR_FAILED_TO_COMPILE_STAGE_FRAGMENT; 
    
    //if we failed to compile, return    
    if (!shader_compiled_vertex || !shader_compiled_fragement) {
        itfliesby_renderer_shader_destroy(renderer,shader_index);
        return(ITFLIESBY_RENDERER_SHADER_ERROR_FAILED_TO_COMPILE);
    }    

    //now, link the program
    glAttachShader(shader_program_id,shader_stage_id_vertex);
    glAttachShader(shader_program_id,shader_stage_id_fragment);
    glLinkProgram(shader_program_id);
    
    //check the link status
    GLint program_status;
    glGetProgramiv(shader_program_id,GL_LINK_STATUS,(GLint*)&program_status);
    b8 program_linked = (program_status == GL_TRUE);

    //if we failed to link, return
    if (!program_linked) {
        itfliesby_renderer_shader_destroy(renderer,shader_index);
        return(ITFLIESBY_RENDERER_SHADER_ERROR_FAILED_TO_LINK);
    }    

    //sanity check
    ITFLIESBY_ASSERT(
        shader_compiled_vertex    &&
        shader_compiled_fragement &&
        program_linked
    );
    
    //detach shaders
    glDetachShader(shader_program_id,shader_stage_id_vertex);
    glDetachShader(shader_program_id,shader_stage_id_fragment);
    
    //write our shader ids back to the store
    ItfliesbyRendererShader* shader = &shader_stage_store->shaders[shader_index];
    shader->program_id        = shader_program_id;
    shader->stage_id_vertex   = shader_stage_id_vertex;
    shader->stage_id_fragment = shader_stage_id_fragment;

    return(shader_index);
}