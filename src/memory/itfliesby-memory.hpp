#ifndef ITFLIESBY_MEMORY_HPP
#define ITFLIESBY_MEMORY_HPP

#include <cstring>
#include <itfliesby.hpp> 

typedef struct ItfliesbyMemoryArena;
typedef struct ItfliesbyMemoryPartition;
typedef struct ItfliesbyMemoryBlock;
typedef struct ItfliesbyMemoryAllocatorHeader;
typedef union  ItfliesbyMemoryAllocator;
typedef struct ItfliesbyMemoryAllocatorLinear;
typedef struct ItfliesbyMemoryAllocatorStack;
typedef struct ItfliesbyMemoryAllocatorBlock;
typedef struct ItfliesbyMemoryAllocatorHeap;

#define ITFLIESBY_MEMORY_ARENA_MINIMUM_SIZE (sizeof(ItfliesbyMemoryArena) + sizeof(ItfliesbyMemoryPartition) + sizeof(ItfliesbyMemoryAllocatorHeader) + sizeof(ItfliesbyMemoryAllocatorLinear) + 1)

enum ItfliesbyMemoryReturnCode : s32{
    ITFLIESBY_MEMORY_RETURN_CODE_SUCCESS                     = 0x00000001,
    ITFLIESBY_MEMORY_RETURN_CODE_NOT_ENOUGH_ARENA_MEMORY     = 0x80000000,
    ITFLIESBY_MEMORY_RETURN_CODE_NOT_ENOUGH_PARTITION_MEMORY = 0x80000001,
    ITFLIESBY_MEMORY_RETURN_CODE_NOT_ENOUGH_ALLOCATOR_MEMORY = 0x80000002,
    ITFLIESBY_MEMORY_RETURN_CODE_CORE_MEMORY_NULL            = 0x80000003,
    ITFLIESBY_MEMORY_RETURN_CODE_INVALID_ARGUMENT            = 0x80000005,

};

enum ItfliesbyMemoryAllocatorType {
    ITFLIESBY_MEMORY_ALLOCATOR_TYPE_STACK   = 0,
    ITFLIESBY_MEMORY_ALLOCATOR_TYPE_QUEUE   = 1,
    ITFLIESBY_MEMORY_ALLOCATOR_TYPE_BLOCK   = 2,
    ITFLIESBY_MEMORY_ALLOCATOR_TYPE_LINEAR = 3,
    ITFLIESBY_MEMORY_ALLOCATOR_TYPE_HEAP    = 4
};

struct ItfliesbyMemoryBlock {
    ItfliesbyMemoryAllocatorHeader* allocator_header;
    u64                             size;
};

/*-------------------------------------------------
 * MEMORY CORE
 *-------------------------------------------------*/

struct ItfliesbyMemoryArena {
    char                tag[16];
    u64                 size;
    ItfliesbyMemoryPartition* partitions;
};

api ItfliesbyMemoryReturnCode
itfliesby_memory_arena_create(
    char            arena_tag[16],
    u64             arena_size,
    memory          arena_memory,
    ItfliesbyMemoryArena* arena
);

api void
itfliesby_memory_arena_destroy(
    ItfliesbyMemoryArena*  arena
);


api u64
itfliesby_memory_arena_size_total(
    ItfliesbyMemoryArena*  arena
);

api u64
itfliesby_memory_arena_size_free(
    ItfliesbyMemoryArena*  arena
);

api u64
itfliesby_memory_arena_size_occupied(
    ItfliesbyMemoryArena*  arena
);

/*-------------------------------------------------
 * PARTITIONS
 *-------------------------------------------------*/

struct ItfliesbyMemoryPartition {
    char                            tag[16];
    u64                             size;
    ItfliesbyMemoryPartition*       next;
    ItfliesbyMemoryAllocatorHeader* allocators;
    ItfliesbyMemoryArena*           arena;
};  

api ItfliesbyMemoryReturnCode
itfliesby_memory_partition_create(
    ItfliesbyMemoryArena*     arena,
    char                      partition_tag[16],
    u64                       partition_size,
    ItfliesbyMemoryPartition* partition
);

api u64
itfliesby_memory_partition_space_total(
    ItfliesbyMemoryPartition* partition
);

api u64
itfliesby_memory_partition_space_free(
    ItfliesbyMemoryPartition* partition
);

api u64
itfliesby_memory_partition_space_occupied(
    ItfliesbyMemoryPartition* partition
);

/*-------------------------------------------------
 * LINEAR ALLOCATOR
 *-------------------------------------------------*/

struct ItfliesbyMemoryAllocatorLinear {
    ItfliesbyMemoryAllocatorHeader*  header;
    u64                              used_space;
};

api ItfliesbyMemoryReturnCode
itfliesby_memory_allocator_linear_create(
    ItfliesbyMemoryPartition*       partition,
    char                            allocator_tag[16],
    u64                             allocator_size,
    ItfliesbyMemoryAllocatorLinear* allocator
);

api ItfliesbyMemoryReturnCode
itfliesby_memory_allocator_linear_destroy(
    ItfliesbyMemoryAllocatorLinear*  allocator
);

api ItfliesbyMemoryReturnCode
itfliesby_memory_allocator_linear_allocate(
    ItfliesbyMemoryAllocatorLinear*  allocator,
    u64                         allocation_size,
    memory                      allocation
);

api ItfliesbyMemoryReturnCode
itfliesby_memory_allocator_linear_reset(
    ItfliesbyMemoryAllocatorLinear* allocator
);

api u64
itfliesby_memory_allocator_linear_space_total(
    ItfliesbyMemoryAllocatorLinear* allocator
);

api u64
itfliesby_memory_allocator_linear_space_clear(
    ItfliesbyMemoryAllocatorLinear* allocator
);

api u64
itfliesby_memory_allocator_linear_space_occupied(
    ItfliesbyMemoryAllocatorLinear* allocator
);

/*-------------------------------------------------
 * STACK ALLOCATOR
 *-------------------------------------------------*/

struct ItfliesbyMemoryAllocatorStackNode {
    ItfliesbyMemoryBlock*           block;
    ItfliesbyMemoryAllocatorStack*  next;
};

struct ItfliesbyMemoryAllocatorStack {
    ItfliesbyMemoryAllocatorHeader*    header;
    ItfliesbyMemoryAllocatorStackNode* nodes;
};

api ItfliesbyMemoryReturnCode
itfliesby_memory_allocator_stack_create(
    ItfliesbyMemoryPartition*      partition,
    char                     allocator_tag[16],
    u64                      allocator_size,
    ItfliesbyMemoryAllocatorStack* allocator
);

api void
itfliesby_memory_allocator_stack_destroy(
    ItfliesbyMemoryAllocatorStack* allocator
);

api ItfliesbyMemoryReturnCode
itfliesby_memory_allocator_stack_push(
    ItfliesbyMemoryAllocatorStack* allocator,
    u64                      allocation_size,
    memory                   allocation
);

api ItfliesbyMemoryReturnCode
itfliesby_memory_allocator_stack_pop(
    ItfliesbyMemoryAllocatorStack* allocator,
    memory                   allocation
);

api void
itfliesby_memory_allocator_stack_clear(
    ItfliesbyMemoryAllocatorStack* allocator
);

api void
itfliesby_memory_allocator_stack_space_total(
    ItfliesbyMemoryAllocatorStack* allocator
);

api void
itfliesby_memory_allocator_stack_space_free(
    ItfliesbyMemoryAllocatorStack* allocator
);

api void
itfliesby_memory_allocator_stack_space_occupied(
    ItfliesbyMemoryAllocatorStack* allocator
);

/*-------------------------------------------------
 * QUEUE ALLOCATOR
 *-------------------------------------------------*/

struct ItfliesbyMemoryAllocatorQueue {
    ItfliesbyMemoryAllocatorHeader* header;
    ItfliesbyMemoryBlock            block;           
    ItfliesbyMemoryAllocatorQueue*  next;
};

api ItfliesbyMemoryReturnCode
itfliesby_memory_allocator_queue_create(
    ItfliesbyMemoryPartition*        partition,
    char                       allocator_tag[16],
    u64                        allocator_size,
    ItfliesbyMemoryAllocatorQueue*   allocator
);

api void
itfliesby_memory_allocator_queue_destroy(
    ItfliesbyMemoryAllocatorQueue* allocator
);

api ItfliesbyMemoryReturnCode
itfliesby_memory_allocator_queue_push(
    ItfliesbyMemoryAllocatorQueue* allocator,
    memory                   allocation
);

api ItfliesbyMemoryReturnCode
itfliesby_memory_allocator_queue_pop(
    ItfliesbyMemoryAllocatorQueue* allocator,
    memory                   allocation
);

api void
itfliesby_memory_allocator_queue_clear(
    ItfliesbyMemoryAllocatorQueue* allocator
);

api void
itfliesby_memory_allocator_queue_space_total(
    ItfliesbyMemoryAllocatorQueue* allocator
);

api void
itfliesby_memory_allocator_queue_space_free(
    ItfliesbyMemoryAllocatorQueue* allocator
);

api void
itfliesby_memory_allocator_queue_space_occupied(
    ItfliesbyMemoryAllocatorQueue* allocator
);

/*-------------------------------------------------
 * BLOCK ALLOCATOR
 *-------------------------------------------------*/

struct ItfliesbyMemoryAllocatorBlock {
    ItfliesbyMemoryAllocatorHeader*  header;
    u64                        block_size;
    u64                        num_blocks;
    struct ItfliesbyMemoryAllocatorBlockList {
        ItfliesbyMemoryBlock*              block;
        ItfliesbyMemoryAllocatorBlockList* next;
    } *blocks;
};

api ItfliesbyMemoryReturnCode
itfliesby_memory_allocator_block_create(
    ItfliesbyMemoryPartition*  partition,
    char                 allocator_tag[16],
    u64                  block_size,
    u64                  block_count
);

api void
itfliesby_memory_allocator_block_destroy(
    ItfliesbyMemoryAllocatorBlock* allocator
);

api ItfliesbyMemoryReturnCode
itfliesby_memory_allocator_block_allocate(
    ItfliesbyMemoryAllocatorBlock* allocator,
    memory                   memory
);

api void
itfliesby_memory_allocator_block_free(
    ItfliesbyMemoryAllocatorBlock* allocator,
    memory                   memory
);

api void
itfliesby_memory_allocator_block_clear(
    ItfliesbyMemoryAllocatorBlock* allocator,
    memory                   memory
);

api void
itfliesby_memory_allocator_block_blocks_total(
    ItfliesbyMemoryAllocatorBlock* allocator
);

api void
itfliesby_memory_allocator_block_blocks_free(
    ItfliesbyMemoryAllocatorBlock* allocator
);

api void
itfliesby_memory_allocator_block_blocks_occupied(
    ItfliesbyMemoryAllocatorBlock* allocator
);

api void
itfliesby_memory_allocator_block_space_total(
    ItfliesbyMemoryAllocatorBlock* allocator
);

api void
itfliesby_memory_allocator_block_space_free(
    ItfliesbyMemoryAllocatorBlock* allocator
);

api void
itfliesby_memory_allocator_block_space_occupied(
    ItfliesbyMemoryAllocatorBlock* allocator
);

api ItfliesbyMemoryReturnCode
itfliesby_memory_allocator_block_at_index(
    ItfliesbyMemoryAllocatorBlock*   allocator,
    u64                        block_index,
    memory                     allocation
);

api ItfliesbyMemoryReturnCode
itfliesby_memory_allocator_block_iterate(
    ItfliesbyMemoryAllocatorBlock* allocator,
    memory                   allocation
);

/*-------------------------------------------------
 * HEAP ALLOCATOR
 *-------------------------------------------------*/

struct ItfliesbyMemoryAllocatorHeap {
    ItfliesbyMemoryAllocatorHeader* header;

    struct ItfliesbyMemoryAllocatorHeapList {
        ItfliesbyMemoryBlock              block;
        ItfliesbyMemoryAllocatorHeapList* next;
    } *blocks;
    
    struct ItfliesbyMemoryAllocatorHeapAddressMap {
        memory                            old_address;
        memory                            new_address;
        ItfliesbyMemoryAllocatorHeapAddressMap* next;
    } *address_map;
};


api ItfliesbyMemoryReturnCode
itfliesby_memory_allocator_heap_create(
    ItfliesbyMemoryPartition*       partition,
    char                      allocator_tag[16],
    u64                       allocator_size,
    ItfliesbyMemoryAllocatorHeap*   allocator
);

api ItfliesbyMemoryReturnCode
itfliesby_memory_allocator_heap_destroy(
    ItfliesbyMemoryAllocatorHeap* allocator
);

api ItfliesbyMemoryReturnCode
itfliesby_memory_allocator_heap_allocate(
    ItfliesbyMemoryAllocatorHeap* allocator,
    u64                       allocation_size,
    memory                    allocation
);

api ItfliesbyMemoryReturnCode
itfliesby_memory_allocator_heap_free(
    ItfliesbyMemoryAllocatorHeap* allocator,
    u64                     allocation_size,
    memory                  allocation
);

api ItfliesbyMemoryReturnCode
itfliesby_memory_allocator_heap_register_pointer(
    ItfliesbyMemoryAllocatorHeap* allocator,
    handle                  pointer,
    memory                  allocation
);

api void
itfliesby_memory_allocator_heap_defrag(
    ItfliesbyMemoryAllocatorHeap* allocator
);

api void
itfliesby_memory_allocator_heap_space_total(
    ItfliesbyMemoryAllocatorHeap* allocator
);

api void
itfliesby_memory_allocator_heap_space_free(
    ItfliesbyMemoryAllocatorHeap* allocator
);

api void
itfliesby_memory_allocator_heap_space_occupied(
    ItfliesbyMemoryAllocatorHeap* allocator
);

union ItfliesbyMemoryAllocator {
    ItfliesbyMemoryAllocatorLinear linear;
    ItfliesbyMemoryAllocatorStack   stack;
    ItfliesbyMemoryAllocatorBlock   block;
    ItfliesbyMemoryAllocatorHeap    heap;
};

struct ItfliesbyMemoryAllocatorHeader {
    ItfliesbyMemoryAllocatorType    type;
    char                      tag[16];
    u64                       size;
    ItfliesbyMemoryAllocator        allocator;
    ItfliesbyMemoryPartition*       partition;
    ItfliesbyMemoryAllocatorHeader* next;
};

#endif //ITFLIESBY_MEMORY_HPP
