#pragma once

#include "itfliesby-renderer.hpp"

const f32 SIMPLE_QUAD_VERTEX_BUFFER[] = {
    -0.5f,  0.5f,  // Top-left
    -0.5f, -0.5f,  // Bottom-left
     0.5f, -0.5f,  // Bottom-right

    -0.5f,  0.5f,  // Top-left
     0.5f,  0.5f,  // Top-right
     0.5f, -0.5f   // Bottom-right
};

internal ItfliesbyRendererShaderBuffersSimpleQuad
itfliesby_renderer_shader_simple_quad_buffers_create() {

    ItfliesbyRendererShaderBuffersSimpleQuad simple_quad_buffers = {0};

    //create and bind the VAO
    glGenVertexArrays(1,&simple_quad_buffers.gl_vao);
    glBindVertexArray(simple_quad_buffers.gl_vao);

    //create the buffer
    glGenBuffers(1,&simple_quad_buffers.gl_vbo_quad_indices);
    glBindBuffer(
        GL_ARRAY_BUFFER,
        simple_quad_buffers.gl_vbo_quad_indices);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(f32) * 12,
        SIMPLE_QUAD_VERTEX_BUFFER,
        GL_STATIC_DRAW);

    //define layout of the vertices
    glVertexAttribPointer(
        0,
        2,
        GL_FLOAT,
        GL_FALSE,
        2 * sizeof(f32),
        NULL);
    glEnableVertexAttribArray(0);

    //unbind the vao
    glBindVertexArray(0);

    return(simple_quad_buffers);
}

external u32
itfliesby_renderer_simple_quad_push(
          ItfliesbyRenderer*          renderer,
    const ItfliesbyRendererSimpleQuad simple_quad) {

    ItfliesbyRendererBatchSimpleQuad* simple_quad_batch = &renderer->batches.simple_quad;

    if (simple_quad_batch->count == ITFLIESBY_RENDERER_TEST_BATCH_COUNT_MAX) {
        //TODO: we should have proper error codes
        return(-1);
    }

    u32 new_quad_index = simple_quad_batch->count;

    simple_quad_batch->color[new_quad_index]     = simple_quad.color;
    simple_quad_batch->transform[new_quad_index] = simple_quad.transform;

    ++simple_quad_batch->count;

    return(new_quad_index);
}

external void
itfliesby_renderer_simple_quad_push_batch(
    ItfliesbyRenderer*                 renderer,
    const size_t                       simple_quad_count,
    const ItfliesbyRendererSimpleQuad* simple_quad,
          u32*                         simple_quad_indices) {

    ItfliesbyRendererBatchSimpleQuad* simple_quad_batch = &renderer->batches.simple_quad;

    //TODO: we could push ones that actually fit
    if (simple_quad_batch->count + simple_quad_count >= ITFLIESBY_RENDERER_TEST_BATCH_COUNT_MAX) {
        for (
            size_t index = 0;
            index < simple_quad_count;
            ++index) {
                simple_quad_indices[index] = -1;
        }
    }

    u32 starting_quad_index = simple_quad_batch->count;
    ItfliesbyRendererSimpleQuad i_simple_quad = {0};
    size_t simple_quad_index = 0;

    for (
        size_t index = 0;
        index < simple_quad_count;
        ++index) {

        simple_quad_index = index + starting_quad_index;

        i_simple_quad = simple_quad[simple_quad_index];
        simple_quad_batch->color[simple_quad_index]     = i_simple_quad.color;
        simple_quad_batch->transform[simple_quad_index] = i_simple_quad.transform;
        
        simple_quad_indices[index] = simple_quad_index;
    }
}

internal void
itfliesby_renderer_simple_quad_render(
    ItfliesbyRendererShaderUniformsSimpleQuad* uniforms,
    ItfliesbyRendererShaderBuffersSimpleQuad*  buffers,
    ItfliesbyRendererBatchSimpleQuad*          batch,
    GLuint                                     gl_program) {

    ItfliesbyMathMat3*                batch_transforms = batch->transform;
    ItfliesbyRendererColorNormalized* batch_colors     = batch->color; 

    //use program
    glUseProgram(gl_program);

    //bind vao
    glBindVertexArray(buffers->gl_vao);

    //bind the vertex buffer
    glBindBuffer(
        GL_ARRAY_BUFFER,
        buffers->gl_vbo_quad_indices);
    
    ItfliesbyMathMat3                current_transform = {0};
    ItfliesbyRendererColorNormalized current_color     = {0};

    for (
        u32 index = 0;
        index < batch->count;
        ++index) {

        current_color     = batch_colors[index];
        current_transform = batch_transforms[index];

        //update the color
        glUniform4fv(
            uniforms->index_color,
            1,
            (f32*)&current_color);
    
        //update the transform
        glUniformMatrix3fv(
            uniforms->index_transform,
            1,
            true,
            (f32*)current_transform.m);

        //draw the arrays
        glDrawArrays(
            GL_TRIANGLES,
            0,
            12);
    }

    //unbind vao
    glBindVertexArray(0);

    //reset
    batch->count = 0;
}