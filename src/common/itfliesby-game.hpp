#ifndef ITFLIESBY_GAME_HPP
#define ITFLIESBY_GAME_HPP

#include "itfliesby-types.hpp"

typedef handle itfliesby_game;

api itfliesby_game
itfliesby_game_create(
    ItfliesbyPlatformApi* platform
);

api void
itfliesby_game_destroy(
    itfliesby_game game
);

#endif //ITFLIESBY_GAME_HPP