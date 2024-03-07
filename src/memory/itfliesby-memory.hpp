#ifndef ITFLIESBY_MEMORY_HPP
#define ITFLIESBY_MEMORY_HPP

#include <itfliesby.hpp>

//this is the base unit that the allocators return
struct ItfliesbyMemoryBlock {
    handle allocator;
    u64    size;
    memory memory
};

//an arena is a distinct partition managed by a collection of allocators
struct ItfliesbyMemoryArena {
    u64                           size;
    char[32]                      tag;
    ItfliesbyMemoryArena*         next;
    memory                        memory;
    ItfliesbyMemoryAllocatorNode* allocators;
};  

//the memory structure is a collection of all the arenas
struct ItfliesbyMemory {
    u64                       size;
    memory                    memory;
    ItfliesbyMemoryArena*     arenas;
};


enum ItfliesbyMemoryAllocatorType {
    ITFLIESBY_MEMORY_ALLOCATOR_TYPE_BLOCK
    ITFLIESBY_MEMORY_ALLOCATOR_TYPE_STACK
    ITFLIESBY_MEMORY_ALLOCATOR_TYPE_LIST
};


//allocator that allocates in a stack/LIFO structure
struct ItfliesbyMemoryAllocatorStack { 
    struct ItfliesbyMemoryStackAllocatorNode {
        ItfliesbyMemoryBlock*              block;
        ItfliesbyMemoryStackAllocatorNode* next;
    } *nodes;
};

//a block allocator divides its memory space by a number of blocks of the same size
//we contain a linked list of blocks for easy reference of which ones are allocated
struct ItfliesbyMemoryAllocatorBlock {
    u64    block_size;
    u64    num_blocks;
    memory block_memory;
    struct ItfliesbyMemoryAllocatorBlockNode {
        ItfliesbyMemoryBlock*              block;
        ItfliesbyMemoryAllocatorBlockNode* next;
    } *nodes;
};

struct ItfliesbyMemoryAllocatorNode {
    ItfliesbyMemoryAllocatorType  type;
    ItfliesbyMemoryArena*         arena;
    ItfliesbyMemoryAllocatorNode* next;
    union ItfliesbyMemoryAllocator {
        ItfliesbyMemoryAllocatorStack stack;
        ItfliesbyMemoryAllocatorBlock block;
    } allocator;
};

api ItfliesbyMemory* 
itfliesby_memory_create(
    memory core_memory,                                    
    u64 size);

api void 
itfliesby_memory_destroy(
    ItfliesbyMemoryArena* memory);

api ItfliesbyMemoryArena* 
itfliesby_memory_arena_create(
    ItfliesbyMemory* memory,
    u64              size);

api void 
itfliesby_memory_arena_destroy(
    ItfliesbyMemoryArena*
);

api ItfliesbyMemoryStackAllocator* 
itfliesby_memory_stack_allocator_create(
    ItfliesbyMemory* memory,
    u64 size);

api void
itfliesby_memory_stack_allocator_destroy(
    ItfliesbyMemoryStackAllocator* stack_allocator);

api ItfliesbyMemoryBlock*
itfliesby_memory_stack_allocator_push(
    ItfliesbyMemoryStackAllocator* stack_allocator,
    u64 size);

void
itfliesby_memory_stack_allocator_pop(
    ItfliesbyMemoryStackAllocator* stack_allocator);

void
itfliesby_memory_stack_allocator_clear(
    ItfliesbyMemoryStackAllocator* stack_allocator);

u64
itfliesby_memory_stack_allocator_size_total(
    ItfliesbyMemoryStackAllocator* stack_allocator);

u64
itfliesby_memory_stack_allocator_size_free(
    ItfliesbyMemoryStackAllocator* stack_allocator);

u64
itfliesby_memory_stack_allocator_size_occupied(
    ItfliesbyMemoryStackAllocator* stack_allocator);

#endif //ITFLIESBY_MEMORY_HPP