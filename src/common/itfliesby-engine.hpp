#ifndef ITFLIESBY_ENGINE_HPP
#define ITFLIESBY_ENGINE_HPP

#include "itfliesby-types.hpp"

typedef handle itfliesby_engine;

api itfliesby_engine
itfliesby_engine_create(
    ItfliesbyPlatformApi platform,
    memory               mem,
    u64                  mem_size
);

api void
itfliesby_engine_destroy(
    itfliesby_engine engine
);

api void
itfliesby_engine_update_and_render(
    itfliesby_engine engine
);

#endif //ITFLIESBY_ENGINE_HPP