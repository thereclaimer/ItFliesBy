#ifndef ITFLIESBY_RENDERER_OPENGL_HPP
#define ITFLIESBY_RENDERER_OPENGL_HPP

#define GLEW_STATIC

#include <glew/glew.h>
#include <glew/wglew.h>
#include <glew/glew.c>
#include <common/itfliesby-types.hpp>

inline void
itfliesby_renderer_opengl_array_buffer(
    GLuint buffer_id,
    u32    buffer_data_size_bytes,
    void*  buffer_data) {

    glBindBuffer(
        GL_ARRAY_BUFFER,
        buffer_id);

    glBufferData(
        GL_ARRAY_BUFFER,
        buffer_data_size_bytes,
        buffer_data,
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


#endif //ITFLIESBY_RENDERER_OPENGL_HPP