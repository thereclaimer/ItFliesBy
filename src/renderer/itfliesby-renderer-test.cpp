#pragma once

#include "itfliesby-renderer.hpp"

const f32 TEST_VERTEX_BUFFER[] = {
    -0.5f,  0.5f,  // Top-left
    -0.5f, -0.5f,  // Bottom-left
     0.5f, -0.5f,  // Bottom-right

    -0.5f,  0.5f,  // Top-left
     0.5f,  0.5f,  // Top-right
     0.5f, -0.5f   // Bottom-right
};

internal ItfliesbyRendererShaderBuffersTest
itfliesby_renderer_shader_test_buffers_create() {

    ItfliesbyRendererShaderBuffersTest test_buffers = {0};

    //create and bind the VAO
    glGenVertexArrays(1,&test_buffers.gl_vao);
    glBindVertexArray(test_buffers.gl_vao);

    //create the buffer
    glGenBuffers(1,&test_buffers.gl_vbo_quad_indices);
    glBindBuffer(
        GL_ARRAY_BUFFER,
        test_buffers.gl_vbo_quad_indices);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(f32) * 12,
        TEST_VERTEX_BUFFER,
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

    return(test_buffers);
}

external void
itfliesby_renderer_test_batch(
    ItfliesbyRenderer*          renderer,
    ItfliesbyRendererTestBatch* batch) {

    renderer->batches.test = *batch;
}

internal void
itfliesby_renderer_test_render(
    ItfliesbyRendererShaderUniformsTest* uniforms,
    ItfliesbyRendererShaderBuffersTest*  buffers,
    ItfliesbyRendererTestBatch*          batch,
    GLuint                               gl_program) {

    ItfliesbyMathMat3*         batch_transforms = batch->transform;
    ItfliesbyRendererColorHex* batch_colors     = batch->color; 

    //use program
    glUseProgram(gl_program);

    //bind vao
    glBindVertexArray(buffers->gl_vao);

    //bind the vertex buffer
    glBindBuffer(
        GL_ARRAY_BUFFER,
        buffers->gl_vbo_quad_indices);
    
    ItfliesbyMathMat3                current_transform        = {0};
    ItfliesbyRendererColorHex        current_color            = {0};
    ItfliesbyRendererColorNormalized current_color_normalized = {0};

    for (
        u32 index = 0;
        index < batch->count;
        ++index) {

        current_color     = batch_colors[index];
        current_transform = batch_transforms[index];

        //update the color
        current_color_normalized = itfliesby_renderer_color_normalize(current_color);
        glUniform4fv(
            uniforms->index_color,
            4,
            (f32*)&current_color_normalized);
    
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

}