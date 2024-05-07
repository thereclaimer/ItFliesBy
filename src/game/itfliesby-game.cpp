#pragma once

#include "itfliesby-game.hpp"

external ItfliesbyGame*
itfliesby_game_create(
    ItfliesbyPlatformApi  platform,
    memory                game_memory,
    size                  game_memory_size) {

    //initialize the game memory
    ITFLIESBY_ASSERT(game_memory_size == ITFLIESBY_GAME_MEMORY_SIZE);

    ItfliesbyGameMemoryArena game_memory_arena = {0};

    game_memory_arena.arena = itfliesby_memory_arena_create("GAME ARENA",game_memory_size,game_memory);

    ITFLIESBY_ASSERT(game_memory_arena.arena);

    //partitions
    game_memory_arena.partitions.game_core   = itfliesby_memory_partition_create(game_memory_arena.arena, "GAME SYSTEMS", ITFLIESBY_MATH_KILOBYTES(1));
    game_memory_arena.partitions.game_engine = itfliesby_memory_partition_create(game_memory_arena.arena, "ENGINE PRTN",  ITFLIESBY_MATH_MEGABYTES(512));
    
    ITFLIESBY_ASSERT(game_memory_arena.partitions.game_core);
    ITFLIESBY_ASSERT(game_memory_arena.partitions.game_engine);

    //allocators
    game_memory_arena.allocators.game_core_system_allocator = itfliesby_memory_allocator_linear_create(game_memory_arena.partitions.game_core,"GAME SYSTEMS ALCTR",512);
    
    ITFLIESBY_ASSERT(game_memory_arena.allocators.game_core_system_allocator);

    //engine
    memory engine_memory    = itfliesby_memory_partition_raw_memory(game_memory_arena.partitions.game_engine);
    u64 engine_memory_size  = itfliesby_memory_partition_space_total(game_memory_arena.partitions.game_engine);
    
    itfliesby_engine engine = itfliesby_engine_create(platform,engine_memory,engine_memory_size); 
    ITFLIESBY_ASSERT(engine);

    //allocate core systems
    ItfliesbyGame* game = (ItfliesbyGame*)itfliesby_memory_allocator_linear_allocate(game_memory_arena.allocators.game_core_system_allocator,sizeof(ItfliesbyGame));
    ITFLIESBY_ASSERT(game);

    *game = {0};
    game->memory_arena = game_memory_arena;
    game->platform     = platform;
    game->engine       = engine;

    return(game);
}

external void
itfliesby_game_destroy(
    ItfliesbyGame* game) {
}

external void
itfliesby_game_update_and_render(
          ItfliesbyGame*      game,
    const ItfliesbyUserInput* user_input) {

    itfliesby_engine engine = game->engine;

    itfliesby_engine_update_and_render(
        engine,
        user_input);
}