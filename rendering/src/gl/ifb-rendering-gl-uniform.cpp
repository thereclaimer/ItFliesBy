#pragma once

#include "ifb-rendering-gl.hpp"

inline const IFBB8 
ifb_gl::uniform_get_locations_in_shader_program(
    const IFBGLIDShaderProgram program,
    const IFBU32               uniform_count,
    const IFBChar**            uniform_names,
          IFBGLIDUniform*      uniform_array) {

    //sanity check
    ifb_macro_assert(program.gl_id != GL_ZERO);
    ifb_macro_assert(uniform_count != 0);
    ifb_macro_assert(uniform_names != NULL);
    ifb_macro_assert(uniform_array != NULL);

    //forward declarations
    IFBB8       result        = true;
    const GLuint gl_program_id = program.gl_id;

    //loop throught the uniform names and query the program for their location
    for (
        IFBU32 uniform_index = 0;
        uniform_index < uniform_count;
        ++uniform_index) {

        //get the current uniform reference and name
        IFBGLIDUniform& uniform_ref  = uniform_array[uniform_index];  
        const IFBChar* uniform_name = uniform_names[uniform_index];

        //query for the uniform location
        uniform_ref.gl_id = glGetUniformLocation(gl_program_id,uniform_name);

        //check for errors        
        const GLenum error = glGetError();
        
        //update the result
        result &= uniform_ref.gl_id != IFB_GL_INVALID_UNIFORM_LOCATION; // the location should be valid (not -1)
        result &= error             == GL_NO_ERROR;                     // no opengl errors
    }

    //we're done
    return(result);
}

inline const IFBB8 
ifb_gl::uniform_update_u32(
    const IFBGLIDUniformU32 uniform,     
    const IFBU32           count,
    const IFBU32*          u32) {

    glUniform1uiv(
        uniform.gl_id,
        count,
        u32);

    const GLenum error = glGetError();

    return(error == GL_NO_ERROR);
}

inline const IFBB8 
ifb_gl::uniform_update_f32(
    const IFBGLIDUniformF32 uniform,     
    const IFBU32           count,
    const IFBF32*          f32) {

    glUniform1fv(
        uniform.gl_id,
        count,
        f32);

    const GLenum error = glGetError();

    return(error == GL_NO_ERROR);
}

inline const IFBB8 
ifb_gl::uniform_update_vec2(
    const IFBGLIDUniformVec2 uniform,
    const IFBU32            count,
    const IFBVec2*           vec2) {

    glUniform2fv(
        uniform.gl_id,
        count,
        (IFBF32*)vec2);

    const GLenum error = glGetError();

    return(error == GL_NO_ERROR);
}

inline const IFBB8 
ifb_gl::uniform_update_vec3(
    const IFBGLIDUniformVec3 uniform,
    const IFBU32            count,
    const IFBVec3*           vec3) {

    glUniform3fv(
        uniform.gl_id,
        count,
        (IFBF32*)vec3);

    const GLenum error = glGetError();

    return(error == GL_NO_ERROR);
}

inline const IFBB8 
ifb_gl::uniform_update_mat3(
    const IFBGLIDUniformMat3 uniform,
    const IFBU32            count,
    const IFBMat3*           mat3) {

    glUniformMatrix3fv(
        uniform.gl_id,
        count,
        GL_FALSE, //no transpose
        (IFBF32*)mat3);

    const GLenum error = glGetError();

    return(error == GL_NO_ERROR);
}