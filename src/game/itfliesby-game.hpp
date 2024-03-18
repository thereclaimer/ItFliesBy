#ifndef ITFLIESBY_GAME_HPP
#define ITFLIESBY_GAME_HPP

#include <itfliesby.hpp>

#define ITFLIESBY_GAME_MEMORY_SIZE ITFLIESBY_MATH_GIGABYTES(2)

struct ItfliesbyGameMemoryAllocators {
    itfliesby_memory_allocator_linear game_core_system_allocator;
};

struct ItfliesbyGameMemoryPartitions {
    itfliesby_memory_partition game_core;
};

struct ItfliesbyGameMemoryArena {
    itfliesby_memory_arena        arena;
    ItfliesbyGameMemoryPartitions partitions;
    ItfliesbyGameMemoryAllocators allocators;
};

struct ItfliesbyGame {
    ItfliesbyPlatformApi     platform;
    itfliesby_engine         engine;
    ItfliesbyGameMemoryArena memory_arena;
};

api ItfliesbyGame*
itfliesby_game_create(
    ItfliesbyPlatformApi* platform,
    memory                game_memory,
    size                  game_memory_size
);

api void
itfliesby_game_destroy(
    ItfliesbyGame* game
);

#endif //ITFLIESBY_GAME_HPP

