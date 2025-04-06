#pragma once

#include "ifb-rendering-gl.hpp"

inline const ifb::b8 
ifb::gl::uniform_get_locations_in_shader_program(
    const gl_id_shader_program_t program,
    const ifb::u32               uniform_count,
    const ifb::utf8**            uniform_names,
          gl_id_uniform*      uniform_array) {

    //sanity check
    ifb_macro_assert(program.gl_id != GL_ZERO);
    ifb_macro_assert(uniform_count != 0);
    ifb_macro_assert(uniform_names != NULL);
    ifb_macro_assert(uniform_array != NULL);

    //forward declarations
    ifb::b8       result        = true;
    const GLuint gl_program_id = program.gl_id;

    //loop throught the uniform names and query the program for their location
    for (
        ifb::u32 uniform_index = 0;
        uniform_index < uniform_count;
        ++uniform_index) {

        //get the current uniform reference and name
        gl_id_uniform& uniform_ref  = uniform_array[uniform_index];  
        const ifb::utf8* uniform_name = uniform_names[uniform_index];

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

inline const ifb::b8 
ifb::gl::uniform_update_u32(
    const gl_id_uniform_u32_t uniform,     
    const ifb::u32           count,
    const ifb::u32*          u32) {

    glUniform1uiv(
        uniform.gl_id,
        count,
        u32);

    const GLenum error = glGetError();

    return(error == GL_NO_ERROR);
}

inline const ifb::b8 
ifb::gl::uniform_update_f32(
    const gl_id_uniform_f32_t uniform,     
    const ifb::u32           count,
    const ifb::f32*          f32) {

    glUniform1fv(
        uniform.gl_id,
        count,
        f32);

    const GLenum error = glGetError();

    return(error == GL_NO_ERROR);
}

inline const ifb::b8 
ifb::gl::uniform_update_vec2(
    const gl_id_uniform_vec2_t uniform,
    const ifb::u32            count,
    const ifb::vec2_t*           vec2) {

    glUniform2fv(
        uniform.gl_id,
        count,
        (ifb::f32*)vec2);

    const GLenum error = glGetError();

    return(error == GL_NO_ERROR);
}

inline const ifb::b8 
ifb::gl::uniform_update_vec3(
    const gl_id_uniform_vec3_t uniform,
    const ifb::u32            count,
    const ifb::vec3_t*           vec3) {

    glUniform3fv(
        uniform.gl_id,
        count,
        (ifb::f32*)vec3);

    const GLenum error = glGetError();

    return(error == GL_NO_ERROR);
}

inline const ifb::b8 
ifb::gl::uniform_update_mat3(
    const gl_id_uniform_mat3_t uniform,
    const ifb::u32            count,
    const ifb::mat3_t*           mat3) {

    glUniformMatrix3fv(
        uniform.gl_id,
        count,
        GL_FALSE, //no transpose
        (ifb::f32*)mat3);

    const GLenum error = glGetError();

    return(error == GL_NO_ERROR);
}