#ifndef ITFLIESBY_ENGINE_HPP
#define ITFLIESBY_ENGINE_HPP

#include <itfliesby.hpp>

struct ItfliesbyEngine {
    itfliesby_renderer renderer;
};

api ItfliesbyEngine*
itfliesby_engine_create(
    ItfliesbyPlatformApi* platform);

api void
itfliesby_engine_destroy(
    ItfliesbyEngine* engine);

#endif //ITFLIESBY_ENGINE_HPP