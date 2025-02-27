#pragma once

#include "ifb-rendering-gl.hpp"

inline const IFBB8
ifb_gl::shader_stage_compile(
    const GLuint              shader_stage_type,
    const IFBU32              shader_stage_count,
    const IFBChar**           shader_stage_buffers,
          IFBGLIDShaderStage* shader_stage_array) {

    //sanity check
    ifb_macro_assert(shader_stage_count   != 0);
    ifb_macro_assert(shader_stage_buffers != NULL);
    ifb_macro_assert(shader_stage_array   != NULL);

    //forward declarations
    IFBB8 result                = true;
    GLint  shader_stage_compiled = 0;

    //iterate over the shader stage buffers and compile each one
    for (
        IFBU32 shader_stage_index = 0;
        shader_stage_index < shader_stage_count;
        ++shader_stage_index) {

        //get the current shader stage and buffer
        IFBGLIDShaderStage& shader_stage_ref    = shader_stage_array[shader_stage_index];
        const IFBChar*     shader_stage_buffer = shader_stage_buffers[shader_stage_index];
        
        //compile the shader stage
        shader_stage_ref.gl_id = glCreateShader(shader_stage_type); 

        //check the shader stage status
        const GLenum last_error = glGetError();
        glGetShaderiv(shader_stage_ref.gl_id,GL_COMPILE_STATUS,&shader_stage_compiled);

        //update the result
        result &= shader_stage_ref.gl_id != GL_ZERO;     // the shader stage id should be non-zero
        result &= last_error             == GL_NO_ERROR; // OpenGL should have no errors
        result &= shader_stage_compiled  == GL_TRUE;     // the shader stage should be compiled 
    }

    //we're done
    return(result);
}

inline const IFBB8
ifb_gl::shader_stage_compile_vertex(
    const IFBU32                   shader_stage_vertex_count,
    const IFBChar**                shader_stage_vertex_buffers,
          IFBGLIDShaderStageVertex* shader_stage_vertex_array) {

    const IFBB8 result = ifb_gl::shader_stage_compile(
        GL_VERTEX_SHADER,
        shader_stage_vertex_count,
        shader_stage_vertex_buffers,
        shader_stage_vertex_array);

    return(result);
}

inline const IFBB8
ifb_gl::shader_stage_compile_fragment(
    const IFBU32                     shader_stage_fragment_count,
    const IFBChar**                  shader_stage_fragment_buffers,
          IFBGLIDShaderStageFragment* shader_stage_fragment_array) {

    const IFBB8 result = ifb_gl::shader_stage_compile(
        GL_FRAGMENT_SHADER,
        shader_stage_fragment_count,
        shader_stage_fragment_buffers,
        shader_stage_fragment_array);

    return(result);
}

inline const IFBB8
ifb_gl::shader_stage_delete(
    const IFBU32             shader_stage_count,
    const IFBGLIDShaderStage* shader_stage_array) {

    ifb_macro_assert(shader_stage_count != 0);
    ifb_macro_assert(shader_stage_array != NULL);

    IFBB8 result = true;

    for (
        IFBU32 shader_stage_index = 0;
        shader_stage_index < shader_stage_count;
        ++shader_stage_index) {

        const GLuint gl_shader_id = shader_stage_array[shader_stage_index].gl_id;

        glDeleteShader(gl_shader_id);

        const GLenum last_error = glGetError();

        result &= last_error == GL_NO_ERROR;
    }

    return(result);
}