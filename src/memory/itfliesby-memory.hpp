#ifndef ITFLIESBY_MEMORY_HPP
#define ITFLIESBY_MEMORY_HPP

#include <itfliesby.hpp>

//this is the base unit that the allocators return
struct ItfliesbyMemoryBlock {
    u64    size;
    memory memory
};

//the arenas are a linked list of distinct partitions, where the allocators live
struct ItfliesbyMemoryArena {
    u64                       size;
    char[32]                  tag;
    ItfliesbyMemoryArena*     next;
    memory                    memory;
};  

//the memory structure is a collection of all the arenas
struct ItfliesbyMemory {
    u64                       size;
    memory                    memory;
    ItfliesbyMemoryArena*     arenas;
};

//allocator that allocates in a stack/LIFO structure
struct ItfliesbyMemoryStackAllocator {
    ItfliesbyMemoryArena*                   arena;
    struct ItfliesbyMemoryStackAllocatorNode {
        ItfliesbyMemoryBlock*              block;
        ItfliesbyMemoryStackAllocatorNode* next;
    } *nodes;
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