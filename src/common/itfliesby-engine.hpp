#ifndef ITFLIESBY_ENGINE_HPP
#define ITFLIESBY_ENGINE_HPP

#include "itfliesby-types.hpp"

typedef handle itfliesby_engine;

api itfliesby_engine
itfliesby_engine_create(
    ItfliesbyPlatformApi* platform
);

api void
itfliesby_engine_destroy(
    itfliesby_engine engine
);

#endif //ITFLIESBY_ENGINE_HPP