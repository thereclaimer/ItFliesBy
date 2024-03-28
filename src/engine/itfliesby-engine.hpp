#ifndef ITFLIESBY_ENGINE_HPP
#define ITFLIESBY_ENGINE_HPP

#include <itfliesby.hpp>
#include "itfliesby-engine-globals.hpp"
#include "itfliesby-engine-assets.hpp"
#include "itfliesby-engine-memory.hpp"
#include "itfliesby-engine-renderer.hpp"

struct ItfliesbyEngine {
    ItfliesbyEngineMemory   memory;
    ItfliesbyEngineAssets   assets;
    ItfliesbyEngineRenderer renderer;
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