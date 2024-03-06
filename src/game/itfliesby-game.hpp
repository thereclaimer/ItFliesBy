#ifndef ITFLIESBY_GAME_HPP
#define ITFLIESBY_GAME_HPP

#include <itfliesby.hpp>

struct ItfliesbyGame {
    ItfliesbyPlatformApi platform;
    itfliesby_engine     engine;
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

