#pragma once

#include "itfliesby-game.hpp"

external ItfliesbyGame*
itfliesby_game_create(
    ItfliesbyPlatformApi* platform) {

    memory core_memory = (memory)platform->memory_allocate(ITFLIESBY_GAME_MEMORY_SIZE);

    auto engine = itfliesby_engine_create(platform);

    return(NULL);
}

external void
itfliesby_game_destroy(
    ItfliesbyGame* game) {

}