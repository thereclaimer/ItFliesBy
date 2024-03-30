#ifndef ITFLIESBY_RENDERER_HPP
#define ITFLIESBY_RENDERER_HPP

#include "itfliesby-types.hpp"
#include "math/itfliesby-math.hpp"

typedef handle itfliesby_renderer;

typedef u8 itfliesby_renderer_vertex_shader;
typedef u8 itfliesby_renderer_fragment_shader;
typedef u8 itfliesby_renderer_shader_program;
typedef s32 itfliesby_renderer_vertex_buffer;
typedef s32 itfliesby_renderer_texture_buffer;
typedef s32 itfliesby_renderer_object;

api itfliesby_renderer
itfliesby_renderer_api_create(
    ItfliesbyPlatformApi platform,
    memory               memory,
    u64                  memory_size
);

api void
itfliesby_renderer_api_destroy(
    itfliesby_renderer renderer
);

api void
itfliesby_renderer_api_update_and_render(
    itfliesby_renderer renderer
);

api void
itfliesby_renderer_api_shader_compile_vertex_shaders(
    itfliesby_renderer                renderer,
    const char*                       shader_buffer,
    const u64*                        shader_offsets,
    const u8                          shader_count,
    itfliesby_renderer_vertex_shader* shader_results);

api void
itfliesby_renderer_api_shader_compile_fragment_shaders(
    itfliesby_renderer                  renderer,
    const char*                         shader_buffer,
    const u64*                          shader_offsets,
    const u8                            shader_count,
    itfliesby_renderer_fragment_shader* shader_results);

api void
itfliesby_renderer_api_shader_programs_create(
    itfliesby_renderer                        renderer,
    const itfliesby_renderer_vertex_shader*   vertex_stages,
    const itfliesby_renderer_fragment_shader* fragment_stages,
    u8                                        count_programs,
    itfliesby_renderer_shader_program*        program_results);

#endif //ITFLIESBY_RENDERER_HPP