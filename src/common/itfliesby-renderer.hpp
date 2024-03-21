#ifndef ITFLIESBY_RENDERER_HPP
#define ITFLIESBY_RENDERER_HPP

#include "itfliesby-types.hpp"
#include "math/itfliesby-math.hpp"

typedef handle itfliesby_renderer;

typedef s32 itfliesby_renderer_vertex_shader;
typedef s32 itfliesby_renderer_fragment_shader;
typedef s32 itfliesby_renderer_shader_program;
typedef s32 itfliesby_renderer_vertex_buffer;
typedef s32 itfliesby_renderer_texture_buffer;
typedef s32 itfliesby_renderer_object;

api itfliesby_renderer
itfliesby_renderer_create(
    ItfliesbyPlatformApi platform,
    memory               memory,
    u64                  memory_size
);

api void
itfliesby_renderer_destroy(
    itfliesby_renderer renderer
);

api void
itfliesby_renderer_update_and_render(
    itfliesby_renderer renderer
);

api itfliesby_renderer_vertex_shader
itfliesby_renderer_shader_compile_vertex(
    const char* vertex_shader_code_buffer,
    const u32   vertex_shader_code_buffer_size_bytes
);

api itfliesby_renderer_fragment_shader
itfliesby_renderer_shader_compile_fragment(
    const char* fragment_shader_code_buffer,
    const u32   fragment_shader_code_buffer_size_bytes
);

api itfliesby_renderer_shader_program
itfliesby_renderer_shader_program_create(
    const itfliesby_renderer_vertex_shader   vertex_shader_stage,
    const itfliesby_renderer_fragment_shader fragment_shader_stage
);

api itfliesby_renderer_vertex_buffer
itfliesby_renderer_buffer_vertex_2d_create(
    const f32* vertex_buffer,
    const u32  vertex_buffer_size_bytes
);

api itfliesby_renderer_texture_buffer
itfliesby_renderer_buffer_texture_create(
    const f32* texture_buffer,
    const u32  texture_buffer_size_bytes
);

api itfliesby_renderer_object
itfliesby_renderer_object_create(
    const itfliesby_renderer_vertex_buffer  vertex_buffer,
    const itfliesby_renderer_texture_buffer texture_buffer,
    const itfliesby_renderer_shader_program shader_program
);

void
itfliesby_renderer_object_add_to_draw_buffer(
    const itfliesby_renderer_object
);

#endif //ITFLIESBY_RENDERER_HPP