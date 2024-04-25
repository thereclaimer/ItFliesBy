#pragma once

#include "itfliesby-renderer.hpp"

internal void
itfliesby_renderer_quad_index_buffer_create(
    GLuint vbo,
    const u32 quad_vertices[6]) {
    
    glBindBuffer(
        GL_ELEMENT_ARRAY_BUFFER,
        vbo);

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, 
        sizeof(u32) * 6, 
        quad_vertices, 
        GL_STATIC_DRAW);

}

internal void
itfliesby_renderer_quad_vertex_buffer_create(
    GLuint vbo,
    const f32 quad_vertices[8]) {
    
    glBindBuffer(
        GL_ARRAY_BUFFER,
        vbo);

    glBufferData(
        GL_ARRAY_BUFFER, 
        sizeof(f32) * 8, 
        quad_vertices, 
        GL_STATIC_DRAW);

}

internal ItfliesbyRendererQuadBuffers
itfliesby_renderer_quad_buffers_init() {

    ItfliesbyRendererQuadBuffers quad_buffers = {0};

    glGenBuffers(
        ITFLIESBY_RENDERER_QUAD_BUFFERS_COUNT,
        quad_buffers.array
    );

    itfliesby_renderer_quad_index_buffer_create(
        quad_buffers.instances.indices,
        ITFLIESBY_RENDERER_INDICES_QUAD
    );

    itfliesby_renderer_quad_vertex_buffer_create(
        quad_buffers.instances.square_quad_vertices,
        ITFLIESBY_RENDERER_VERTICES_SQUARE_QUAD
    );

    return(quad_buffers);
};