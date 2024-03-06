#pragma once

#include "itfliesby-game.hpp"

external ItfliesbyGame*
itfliesby_game_create(
    ItfliesbyPlatformApi* platform) {

    auto engine = itfliesby_engine_create(platform);

    return(NULL);
}

external void
itfliesby_game_destroy(
    ItfliesbyGame* game) {

}