#ifndef ITFLIESBY_RENDERER_HPP
#define ITFLIESBY_RENDERER_HPP

#include <itfliesby.hpp>

struct ItfliesbyRenderer {
    handle gl_context;
};

api ItfliesbyRenderer*
itfliesby_renderer_create(
    ItfliesbyPlatformApi* platform);

api void
itfliesby_renderer_destroy(
    ItfliesbyRenderer* renderer);

#endif //ITFLIESBY_RENDERER_HPP