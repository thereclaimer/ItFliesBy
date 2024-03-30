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

#endif //ITFLIESBY_RENDERER_HPP