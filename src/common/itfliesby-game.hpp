#ifndef ITFLIESBY_GAME_HPP
#define ITFLIESBY_GAME_HPP

#include "itfliesby-types.hpp"

typedef handle itfliesby_game;

#define ITFLIESBY_GAME_MEMORY_SIZE ITFLIESBY_MATH_GIGABYTES(2)

api itfliesby_game
itfliesby_game_create(
    ItfliesbyPlatformApi* platform,
    memory                game_memory,
    size                  game_memory_size
);

api void
itfliesby_game_destroy(
    itfliesby_game game
);

#endif //ITFLIESBY_GAME_HPP