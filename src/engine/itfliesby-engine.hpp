#ifndef ITFLIESBY_ENGINE_HPP
#define ITFLIESBY_ENGINE_HPP

#include <itfliesby.hpp>

#define ITFLIESBY_ENGINE_MEMORY_SIZE ITFLIESBY_MATH_MEGABYTES(512)

#define ITFLIESBY_ENGINE_PARTITION_SIZE_ASSETS   ITFLIESBY_MATH_MEGABYTES(64)
#define ITFLIESBY_ENGINE_PARTITION_SIZE_PHYSICS  ITFLIESBY_MATH_MEGABYTES(64)
#define ITFLIESBY_ENGINE_PARTITION_SIZE_RENDERER ITFLIESBY_MATH_MEGABYTES(64)
#define ITFLIESBY_ENGINE_PARTITION_SIZE_CORE     ITFLIESBY_MATH_MEGABYTES(64)

#define ITFLIESBY_ENGINE_ALLOCATOR_SIZE_CORE_SYSTEMS  ITFLIESBY_MATH_KILOBYTES(1)

struct ItfliesbyEngineMemoryPartitions {
    itfliesby_memory_partition assets;
    itfliesby_memory_partition physics;
    itfliesby_memory_partition renderer;
    itfliesby_memory_partition core;
};

struct ItfliesbyEngineMemoryAllocators {
    itfliesby_memory_allocator_linear core_system_allocator;
};

struct ItfliesbyEngineMemory {
    itfliesby_memory_arena          arena;
    ItfliesbyEngineMemoryPartitions partitions;
    ItfliesbyEngineMemoryAllocators allocators;
};

struct ItfliesbyEngine {
    itfliesby_renderer    renderer;
    ItfliesbyEngineMemory memory;
};

api ItfliesbyEngine*
itfliesby_engine_create(
    ItfliesbyPlatformApi platform,
    memory               mem,
    u64                  mem_size
);

api void
itfliesby_engine_destroy(
    ItfliesbyEngine* engine
);


api void
itfliesby_engine_update_and_render(
    ItfliesbyEngine* engine
);


#endif //ITFLIESBY_ENGINE_HPP