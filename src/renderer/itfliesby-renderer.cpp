#pragma once

#include "itfliesby-renderer.hpp"
#include "itfliesby-renderer-shader.cpp"
#include "itfliesby-renderer-memory.cpp"

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
    ITFLIESBY_ASSERT(glewInit() == GLEW_OK);

    //set the clear color
    glClearColor(
        0.157f,
        0.157f,
        0.157f,
        1.0f
    );

    return(renderer);
}

external void
itfliesby_renderer_update_and_render(
    ItfliesbyRenderer* renderer) {

    //clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}