#ifndef ITFLIESBY_GAME_HPP
#define ITFLIESBY_GAME_HPP

#include <itfliesby.hpp>

#define ITFLIESBY_GAME_MEMORY_SIZE ITFLIESBY_MATH_MEGABYTES(512)

struct ItfliesbyGame {
    ItfliesbyPlatformApi platform;
    itfliesby_engine     engine;
    memory               core_memory;
};

api ItfliesbyGame*
itfliesby_game_create(
    ItfliesbyPlatformApi* platform
);

api void
itfliesby_game_destroy(
    ItfliesbyGame* game
);


#endif //ITFLIESBY_GAME_HPP

