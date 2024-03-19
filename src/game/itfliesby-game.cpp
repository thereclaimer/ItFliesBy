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
        "CORE SYS",
        ITFLIESBY_MATH_MEGABYTES(128),
        &memory_return_code
    );
    ITFLIESBY_ASSERT(memory_return_code == ITFLIESBY_MEMORY_RETURN_CODE_SUCCESS);
    ITFLIESBY_ASSERT(game_memory_arena.partitions.game_core);

    //allocators
    game_memory_arena.allocators.game_core_system_allocator = 
        itfliesby_memory_allocator_linear_create(
            game_memory_arena.partitions.game_core,
            "CORE SYS",
            512,
            &memory_return_code
    );
    ITFLIESBY_ASSERT(memory_return_code == ITFLIESBY_MEMORY_RETURN_CODE_SUCCESS);
    ITFLIESBY_ASSERT(game_memory_arena.allocators.game_core_system_allocator);


    //allocate core systems
    ItfliesbyGame* game = (ItfliesbyGame*)itfliesby_memory_allocator_linear_allocate(
        game_memory_arena.allocators.game_core_system_allocator,
        sizeof(ItfliesbyGame),
        &memory_return_code
    );
    ITFLIESBY_ASSERT(memory_return_code == ITFLIESBY_MEMORY_RETURN_CODE_SUCCESS);
    ITFLIESBY_ASSERT(game);

    return(game);
}

external void
itfliesby_game_destroy(
    ItfliesbyGame* game) {

}