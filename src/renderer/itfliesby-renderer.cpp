#pragma once

#include "itfliesby-renderer.hpp"
#include "itfliesby-renderer-shader.cpp"
#include "itfliesby-renderer-memory.cpp"
#include "itfliesby-renderer-quad.cpp"

external ItfliesbyRenderer*
itfliesby_renderer_create_and_init(
    ItfliesbyPlatformApi platform_api,
    memory               core_memory,
    u64                  core_memory_size_bytes) {

    platform = platform_api;

    //initialize the arena
    itfliesby_renderer_memory_create(
            core_memory,
            core_memory_size_bytes);
    
    //allocate the core renderer
    ItfliesbyRenderer* renderer = itfliesby_renderer_memory_allocate_core();
    ITFLIESBY_ASSERT(renderer);

    //initialize opengl
    renderer->gl_context = platform.graphics_api_init(platform.window);    
    ITFLIESBY_ASSERT(renderer->gl_context);
    glewExperimental = TRUE;
    ITFLIESBY_ASSERT(glewInit() == GLEW_OK);

    //set the clear color
    glClearColor(
        0.157f,
        0.157f,
        0.157f,
        1.0f
    );

    //initialize our quad buffers
    renderer->quad_manager = itfliesby_renderer_quad_manager_init();
    
    return(renderer);
}

external void
itfliesby_renderer_render(
    ItfliesbyRenderer* renderer) {

    ItfliesbyRendererShader*                  solid_quad_shader   = &renderer->shader_store.types.solid_quad; 
    ItfliesbyRendererQuadManager*             quad_manager        = &renderer->quad_manager; 
    ItfliesbyRendererShaderUniformsSolidQuad* solid_quad_uniforms = &renderer->shader_store.uniforms.solid_quad_uniforms;
    ItfliesbyRendererSolidQuadUpdateBatch*    solid_quad_batch    = &renderer->quad_manager.solid_quad_batch;  

    //clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    itfliesby_renderer_quad_solid_quads_render(
        solid_quad_shader,
        quad_manager,
        solid_quad_uniforms,
        solid_quad_batch
    );
}