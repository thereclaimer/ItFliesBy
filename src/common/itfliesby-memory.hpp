#ifndef ITFLIESBY_MEMORY_HPP
#define ITFLIESBY_MEMORY_HPP

#include <common/itfliesby-types.hpp>

typedef handle itfliesby_memory_arena;
typedef handle itfliesby_memory_partition;
typedef handle itfliesby_memory_block;
typedef handle itfliesby_memory_allocator_stack;
typedef handle itfliesby_memory_allocator_queue;
typedef handle itfliesby_memory_allocator_block;
typedef handle itfliesby_memory_allocator_linear;
typedef handle itfliesby_memory_allocator_heap;

enum itfliesby_memory_return_code {
    ITFLIESBY_MEMORY_RETURN_CODE_SUCCESS                     = 0x00000001,
    ITFLIESBY_MEMORY_RETURN_CODE_NOT_ENOUGH_ARENA_MEMORY     = 0x80000000,
    ITFLIESBY_MEMORY_RETURN_CODE_NOT_ENOUGH_PARTITION_MEMORY = 0x80000001,
    ITFLIESBY_MEMORY_RETURN_CODE_NOT_ENOUGH_ALLOCATOR_MEMORY = 0x80000002,
    ITFLIESBY_MEMORY_RETURN_CODE_CORE_MEMORY_NULL            = 0x80000003,
    ITFLIESBY_MEMORY_RETURN_CODE_INVALID_ARGUMENT            = 0x80000005,
};

/*-------------------------------------------------
 * MEMORY CORE
 *------------------------------------------------- 
 * this is the root structure, it contains the
 * core memory that is divided into a linked
 * list of partitions
-------------------------------------------------*/

api itfliesby_memory_return_code
itfliesby_memory_arena_create(
    char                   arena_tag[16],
    u64                    arena_size,
    memory                 arena_core,
    itfliesby_memory_arena arena
);

api void
itfliesby_memory_arena_destroy(
    itfliesby_memory_arena  arena
);

api u64
itfliesby_memory_arena_size_total(
    itfliesby_memory_arena  arena
);

api u64
itfliesby_memory_arena_size_free(
    itfliesby_memory_arena  arena
);

api u64
itfliesby_memory_arena_size_occupied(
    itfliesby_memory_arena  arena
);


#endif //ITFLIESBY_MEMORY_HPP