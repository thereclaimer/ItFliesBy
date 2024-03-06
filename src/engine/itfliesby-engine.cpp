#pragma once

#include "itfliesby-engine.hpp"

external ItfliesbyEngine*
itfliesby_engine_create(
    ItfliesbyPlatformApi* platform) {

    auto renderer = itfliesby_renderer_create(platform);

    return(NULL);
}

external void
itfliesby_engine_destroy(
    ItfliesbyEngine* engine) {

}