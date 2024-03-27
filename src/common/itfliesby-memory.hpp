#ifndef ITFLIESBY_MEMORY_HPP
#define ITFLIESBY_MEMORY_HPP

#include <common/itfliesby-types.hpp>

typedef void ItfliesbyMemoryArena;
typedef void ItfliesbyMemoryPartition;
typedef void ItfliesbyMemoryBlock;
typedef void ItfliesbyMemoryAllocatorHeader;
typedef void ItfliesbyMemoryAllocator;
typedef void ItfliesbyMemoryAllocatorLinear;
typedef void ItfliesbyMemoryAllocatorStack;
typedef void ItfliesbyMemoryAllocatorBlock;
typedef void ItfliesbyMemoryAllocatorHeap;

typedef ItfliesbyMemoryArena*           itfliesby_memory_arena;
typedef ItfliesbyMemoryPartition*       itfliesby_memory_partition;
typedef ItfliesbyMemoryBlock*           itfliesby_memory_block;
typedef ItfliesbyMemoryAllocatorStack*  itfliesby_memory_allocator_stack;
typedef handle                          itfliesby_memory_allocator_queue;
typedef ItfliesbyMemoryAllocatorBlock*  itfliesby_memory_allocator_block;
typedef ItfliesbyMemoryAllocatorLinear* itfliesby_memory_allocator_linear;
typedef ItfliesbyMemoryAllocatorHeap*   itfliesby_memory_allocator_heap;

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

api itfliesby_memory_arena 
itfliesby_memory_arena_create(
    char                          arena_tag[32],
    u64                           arena_size,
    memory                        arena_memory,
    itfliesby_memory_return_code* result = NULL
);

api void
itfliesby_memory_arena_destroy(
    itfliesby_memory_arena arena
);

api u64
itfliesby_memory_arena_size_total(
    itfliesby_memory_arena arena
);

api u64
itfliesby_memory_arena_size_free(
    itfliesby_memory_arena arena
);

api u64
itfliesby_memory_arena_size_occupied(
    itfliesby_memory_arena arena
);

/*-------------------------------------------------
 * PARTITIONS
 *------------------------------------------------- 
 * Distinct chunks of the core memory, partitions
 * are managed by a linked list of allocators 
-------------------------------------------------*/

api itfliesby_memory_partition 
itfliesby_memory_partition_create(
    itfliesby_memory_arena        arena,
    char                          partition_tag[32],
    u64                           partition_size,
    itfliesby_memory_return_code* result = NULL
);

api memory
itfliesby_memory_partition_raw_memory(
    itfliesby_memory_partition partition
);

api u64
itfliesby_memory_partition_space_total(
    itfliesby_memory_partition partition
);

api u64
itfliesby_memory_partition_space_free(
    itfliesby_memory_partition partition
);

api u64
itfliesby_memory_partition_space_occupied(
    itfliesby_memory_partition partition
);

/*-------------------------------------------------
 * LINEAR ALLOCATOR
 *-------------------------------------------------*/

api itfliesby_memory_allocator_linear 
itfliesby_memory_allocator_linear_create(
    itfliesby_memory_partition    partition,
    char                          allocator_tag[32],
    u64                           allocator_size,
    itfliesby_memory_return_code* result = NULL
);


api memory
itfliesby_memory_allocator_linear_allocate(
    itfliesby_memory_allocator_linear allocator,
    u64                               allocation_size,
    itfliesby_memory_return_code*     result = NULL
);

api itfliesby_memory_return_code
itfliesby_memory_allocator_linear_reset(
    itfliesby_memory_allocator_linear allocator
);

api u64
itfliesby_memory_allocator_linear_space_total(
    itfliesby_memory_allocator_linear allocator
);

api u64
itfliesby_memory_allocator_linear_space_clear(
    itfliesby_memory_allocator_linear allocator
);

api u64
itfliesby_memory_allocator_linear_space_occupied(
    itfliesby_memory_allocator_linear allocator
);

/*-------------------------------------------------
 * BLOCK ALLOCATOR
 *-------------------------------------------------*/

api itfliesby_memory_allocator_block 
itfliesby_memory_allocator_block_create(
    itfliesby_memory_partition    partition,
    char                          allocator_tag[32],
    u64                           block_size,
    u64                           block_count,
    itfliesby_memory_return_code* result = NULL
);

api memory 
itfliesby_memory_allocator_block_allocate(
    itfliesby_memory_allocator_block allocator,
    itfliesby_memory_return_code*    result = NULL
);

#endif //ITFLIESBY_MEMORY_HPP