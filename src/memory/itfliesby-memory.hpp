#ifndef ITFLIESBY_MEMORY_HPP
#define ITFLIESBY_MEMORY_HPP

#include <itfliesby.hpp>

//my thoughts are this is a simple header only library
//we allocate memory on the platform, then pass it here to
//convert it to an arena. From there, we can create as 
//many sub arenas using whatever type of allocators we want

struct ItfliesbyMemoryBlock {
    u64    size;
    memory memory
};

struct ItfliesbyMemoryArena {
    u64                       size;
    char[32]                  tag;
    ItfliesbyMemoryArena*     next;
    memory                    memory;
};  

struct ItfliesbyMemory {
    u64                       size;
    memory                    memory;
    ItfliesbyMemoryArena*     arenas;
};

struct ItfliesbyMemoryBlockStackAllocatorNode {
    ItfliesbyMemoryBlock*                   block;
    ItfliesbyMemoryBlockStackAllocatorNode* next;
};

struct ItfliesbyMemoryBlockStackAllocator {
    ItfliesbyMemoryArena*                   arena;
    ItfliesbyMemoryBlockStackAllocatorNode* nodes;
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

api ItfliesbyMemoryBlockStackAllocator* 
itfliesby_memory_stack_allocator_create(
    ItfliesbyMemory* memory,
    u64 size);

api void
itfliesby_memory_stack_allocator_destroy(
    ItfliesbyMemoryBlockStackAllocator* stack_allocator);

api ItfliesbyMemoryBlock*
itfliesby_memory_stack_allocator_push(
    ItfliesbyMemoryBlockStackAllocator* stack_allocator,
    u64 size);

void
itfliesby_memory_stack_allocator_pop(
    ItfliesbyMemoryBlockStackAllocator* stack_allocator);

void
itfliesby_memory_stack_allocator_clear(
    ItfliesbyMemoryBlockStackAllocator* stack_allocator);

u64
itfliesby_memory_stack_allocator_size_total(
    ItfliesbyMemoryBlockStackAllocator* stack_allocator);

u64
itfliesby_memory_stack_allocator_size_free(
    ItfliesbyMemoryBlockStackAllocator* stack_allocator);

u64
itfliesby_memory_stack_allocator_size_occupied(
    ItfliesbyMemoryBlockStackAllocator* stack_allocator);

#endif //ITFLIESBY_MEMORY_HPP