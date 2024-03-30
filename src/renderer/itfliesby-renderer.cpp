#pragma

#include "itfliesby-renderer.hpp"

#include "itfliesby-renderer-shader.cpp"

external ItfliesbyRenderer*
itfliesby_renderer_create(
    ItfliesbyPlatformApi platform,
    memory               mem,
    u64                  mem_size) {

    //initialize memory arena
    ITFLIESBY_ASSERT(mem && mem_size == ITFLIESBY_RENDERER_MEMORY_SIZE_ARENA);
    ItfliesbyRendererMemory renderer_memory = {0};
    renderer_memory.arena = itfliesby_memory_arena_create("RENDERER ARENA",ITFLIESBY_RENDERER_MEMORY_SIZE_ARENA,mem);
    ITFLIESBY_ASSERT(renderer_memory.arena);

    //initialize partitions
    renderer_memory.partitions.core = itfliesby_memory_partition_create(renderer_memory.arena,"RENDERER CORE PRTN",ITFLIESBY_RENDERER_MEMORY_SIZE_PARTITION_CORE);
    ITFLIESBY_ASSERT(renderer_memory.partitions.core);

    //initialize allocators
    renderer_memory.allocators.core_system_allocator = itfliesby_memory_allocator_linear_create(renderer_memory.partitions.core,"RENDERER CORE ALCTR",ITFLIESBY_RENDERER_MEMORY_SIZE_ALLLOCATOR_CORE);
    ITFLIESBY_ASSERT(renderer_memory.allocators.core_system_allocator);

    //allocate and initiate renderer
    ItfliesbyRenderer* renderer = (ItfliesbyRenderer*)itfliesby_memory_allocator_linear_allocate(renderer_memory.allocators.core_system_allocator,sizeof(ItfliesbyRenderer));
    ITFLIESBY_ASSERT(renderer_memory.allocators.core_system_allocator);

    *renderer = {0};
    renderer->memory = renderer_memory;
    renderer->platform = platform;

    //initialize opengl
    renderer->gl_context = platform.graphics_api_init(platform.window);

    glClearColor(
        0.157f,
        0.157f,
        0.157f,
        1.0f
    );

    return(renderer);
}

external void
itfliesby_renderer_destroy(
    ItfliesbyRenderer* renderer) {

}

external void
itfliesby_renderer_update_and_render(
    ItfliesbyRenderer* renderer) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}