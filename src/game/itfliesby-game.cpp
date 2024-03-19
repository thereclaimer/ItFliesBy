#pragma once

#include "itfliesby-game.hpp"

external ItfliesbyGame*
itfliesby_game_create(
    ItfliesbyPlatformApi* platform,
    memory                game_memory,
    size                  game_memory_size) {

    //initialize the game memory
    ITFLIESBY_ASSERT(game_memory_size == ITFLIESBY_GAME_MEMORY_SIZE);

    itfliesby_memory_return_code memory_return_code;
    ItfliesbyGameMemoryArena game_memory_arena = {0};

    game_memory_arena.arena = 
        itfliesby_memory_arena_create(
            "GAME ARENA",
            game_memory_size,
            game_memory,
            &memory_return_code
    );

    ITFLIESBY_ASSERT(memory_return_code == ITFLIESBY_MEMORY_RETURN_CODE_SUCCESS);
    ITFLIESBY_ASSERT(game_memory_arena.arena);

    //core partition
    game_memory_arena.partitions.game_core = itfliesby_memory_partition_create(
        game_memory_arena.arena,
        "CORE SYSTEMS",
        ITFLIESBY_MATH_MEGABYTES(128),
        &memory_return_code
    );
    ITFLIESBY_ASSERT(memory_return_code == ITFLIESBY_MEMORY_RETURN_CODE_SUCCESS);
    ITFLIESBY_ASSERT(game_memory_arena.partitions.game_core);

    //allocators

    return(NULL);
}

external void
itfliesby_game_destroy(
    ItfliesbyGame* game) {

}