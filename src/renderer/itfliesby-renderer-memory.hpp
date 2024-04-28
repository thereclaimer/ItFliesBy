#ifndef ITFLIESBY_RENDERER_MEMORY_HPP
#define ITFLIESBY_RENDERER_MEMORY_HPP

#include <common/itfliesby-types.hpp>
#include <common/itfliesby-memory.hpp>

#define ITFLIESBY_RENDERER_MEMORY_SIZE_BYTES                       ITFLIESBY_MATH_MEGABYTES(64)
#define ITFLIESBY_RENDERER_MEMORY_PARTITION_CORE_SIZE_BYTES        ITFLIESBY_MATH_KILOBYTES(32)
#define ITFLIESBY_RENDERER_MEMORY_ALLOCATOR_CORE_SYSTEM_SIZE_BYTES ITFLIESBY_MATH_KILOBYTES(16)

struct ItfliesbyRendererMemory {

    itfliesby_memory_arena arena;
    
    struct {
        itfliesby_memory_partition core;
    } partitions;

    struct {
        itfliesby_memory_allocator_linear core_system_allocator;
    } allocators;
};

#endif //ITFLIESBY_RENDERER_MEMORY_HPP