#ifndef ITFLIESBY_ENGINE_HPP
#define ITFLIESBY_ENGINE_HPP

#include <itfliesby.hpp>
#include "itfliesby-engine-assets.hpp"
#include "itfliesby-engine-memory.hpp"

global ItfliesbyPlatformApi platform_api;

struct ItfliesbyEngine {
    itfliesby_renderer    renderer;
    ItfliesbyEngineMemory memory;
    ItfliesbyEngineAssets assets;
};

api ItfliesbyEngine*
itfliesby_engine_create(
    ItfliesbyPlatformApi platform,
    memory               mem,
    u64                  mem_size
);

api void
itfliesby_engine_destroy(
    ItfliesbyEngine* engine
);


api void
itfliesby_engine_update_and_render(
    ItfliesbyEngine* engine
);


#endif //ITFLIESBY_ENGINE_HPP