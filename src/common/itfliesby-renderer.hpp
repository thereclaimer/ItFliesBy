#ifndef ITFLIESBY_RENDERER_HPP
#define ITFLIESBY_RENDERER_HPP

#include "itfliesby-types.hpp"

typedef handle itfliesby_renderer;

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