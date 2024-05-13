#ifndef ITFLIESBY_RENDERER_OPENGL_HPP
#define ITFLIESBY_RENDERER_OPENGL_HPP

#define GLEW_STATIC

#include <glew/glew.h>
#include <glew/wglew.h>
#include <glew/glew.c>
#include <common/itfliesby-types.hpp>

inline void
itfliesby_renderer_opengl_vertex_array_create(
    GLuint* gl_vertex_array_object) {

    glGenVertexArrays(1,gl_vertex_array_object);
}

inline void
itfliesby_renderer_opengl_array_buffer(
    GLuint buffer_id,
    u32    buffer_data_size_bytes,
    f32*   buffer_data) {

    glBindBuffer(
        GL_ARRAY_BUFFER,
        buffer_id);

    glBufferData(
        GL_ARRAY_BUFFER,
        buffer_data_size_bytes,
        (void*)buffer_data,
        GL_STATIC_DRAW);
}

inline void
itfliesby_renderer_opengl_enable_vertex_attribute_vec2(
    u32 attribute_index) {

    glVertexAttribPointer(
        attribute_index,//index
        2,              //size
        GL_FLOAT,       //type
        GL_FALSE,       //normalized
        2 * sizeof(f32),//stride
        NULL);          //pointer offset from NULL
    glEnableVertexAttribArray(attribute_index);
}

inline void
itfliesby_renderer_opengl_use_program_and_bind_vertex_array(
    GLuint gl_program_id,
    GLuint gl_vertex_array_id) {

    //use program
    glUseProgram(gl_program_id);

    //bind vao
    glBindVertexArray(gl_vertex_array_id);

}

inline void
itfliesby_renderer_opengl_unbind_program_and_vertex_array() {

    //reverse order of use and bind

    //unbind the vertex array
    glBindVertexArray(0);

    //stop using program
    glUseProgram(0);
}

inline void
itfliesby_renderer_opengl_bind_and_enable_array_buffer_vec2(
    u32    attribute_index,
    GLuint gl_buffer_id) {

    //bind the buffer
    glBindBuffer(
        GL_ARRAY_BUFFER,
        gl_buffer_id
    );

    u32 stride = 2 * sizeof(f32);

    //enable the attribute array
    glEnableVertexAttribArray(attribute_index);

    //specify the layout of this buffer as it appears in the array
    glVertexAttribPointer(
        attribute_index,//index
        2,              //size
        GL_FLOAT,       //type
        GL_FALSE,       //normalized
        stride,         //stride
        NULL);          //pointer offset from NULL
}

inline void
itfliesby_renderer_opengl_set_texture_slot_and_sampler(
    u32    gl_texture_slot,
    GLuint gl_sampler_uniform) {

    glActiveTexture(gl_texture_slot);

    glUniform1i(
        gl_sampler_uniform,
        gl_texture_slot);
}

inline void
itfliesby_renderer_opengl_bind_texture_2d(
    GLuint gl_texture_id) {

    glBindTexture(
        GL_TEXTURE_2D,
        gl_texture_id);
}

inline void
itfliesby_renderer_opengl_uniform_data_vec4(
    GLuint uniform,
    f32*   uniform_data) {
    
    glUniform4fv(
        uniform,
        1,
        uniform_data);
}

inline void
itfliesby_renderer_opengl_uniform_data_mat3(
    GLuint uniform,
    f32*   uniform_data) {

    glUniformMatrix3fv(
        uniform,
        1,
        true,
        uniform_data);
}

inline void
itfliesby_renderer_opengl_draw_quad_vertices() {

    //a non-indexed quad uses 12 vertices
    glDrawArrays(
        GL_TRIANGLES,
        0,
        12);
}

#endif //ITFLIESBY_RENDERER_OPENGL_HPP