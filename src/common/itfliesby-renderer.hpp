#ifndef ITFLIESBY_RENDERER
#define ITFLIESBY_RENDERER

#include "itfliesby-types.hpp"

typedef handle itfliesby_renderer;

api itfliesby_renderer
itfliesby_renderer_create();

api void
itfliesby_renderer_destroy(
    itfliesby_renderer renderer
);

#endif //ITFLIESBY_RENDERER