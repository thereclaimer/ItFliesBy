#pragma once

#include "itfliesby-memory.hpp"

external ItfliesbyMemory*
itfliesby_memory_create(
    memory memory,
    u64    size){

    //first, we are going to cast this memory to the core memory structure
    ItfliesbyMemory* core_memory = (ItfliesbyMemory*)memory;
    core_memory->total_size = size - sizeof(ItfliesbyMemory);
    core_memory->arenas     = NULL;
    core_memory->memory     += sizeof(ItfliesbyMemory);

    return(core_memory);
}

external void
itfliesby_memory_destroy(
    ItfliesbyMemory* memory){

    for (
        ItfliesbyMemoryArena* arena = memory->arenas;
        arena != NULL;
        arena = arena->next;
    ) {
        itfliesby_memory_arena_destroy(arena);
    }

    *memory = {0};
    memory = NULL;
}

external u64
itfliesby_memory_size_free(
    ItfliesbyMemory* memory) {
    
    u64 free_space = memory->size;

    for (
        ItfliesbyMemoryArena* arena = memory->arenas;
        arena != NULL;
        arena = arena->next
    ) {
        free_space -= sizeof(ItfliesbyMemoryArena);
        free_space -= sizeof(arena->size);
    }

    return(free_space);
}

external s64
itfliesby_memory_arena_space_between(
    ItfliesbyMemoryArena* arena_a,
    ItfliesbyMemoryArena* arena_b) {

    //first, get the end of arena a
    memory end_a = arena_a->memory + arena_a->size;

    s64 space = (s64)((void*)arena_b - (void*)end_a);

    return(space);

}

external ItfliesbyMemoryArena*
itfliesby_memory_arena_create(
    ItfliesbyMemory* memory,
    u64              size) {

    ItfliesbyMemoryArena* new_arena;

    u64 allocation_size = size += sizeof(ItfliesbyMemoryArena);

    //if we don't have any arenas yet, just cast the starting memory to an arena and
    //we're done
    if (memory->arenas == NULL) {
        new_arena = (ItfliesbyMemoryArena*)memory->memory;
        new_arena->memory = new_arena + sizeof(ItfliesbyMemoryArena);
        new_arena->size   = size;
        new_arena->next   = NULL;
        memory->arenas = new_arena;
        return(new_arena);
    }

    //otherwise, we should first check to see if we're out of memory
    if (itfliesby_memory_size_free(memory) < allocation_size) {
        return(NULL);
    }
    
    //check for either the next available space, or go to the end of the list
    ItfliesbyMemoryArena* current_arena = memory->arenas;
    ItfliesbyMemoryArena* next_arena    = current_arena->next;

    while (next_arena->next != NULL && new_arena == NULL) {

        //first, determine if we have space between arenas
        if (itfliesby_memory_arena_space_bettween(current_arena,next_arena) >= allocation_size) {

            //the new arena will be at the tail end of the current arena
            new_arena = current_arena->memory + current_arena->size + 1;
            
            current_arena->next = new_arena;
            new_arena->next = new_arena;
            return(new_arena);
        }
    }

    //we should have reached the end of the list, if not our logic is wrong
    ITFLIESBY_ASSERT(next_arena && next_arena->next);

    //we are at the end of the list, so we need to make sure we can add it with the space we have left
    void* memory_end     = memory + memory->size;
    void* next_arena_end = next_arena + next_arena->size; 

    u64 space_left = memory_end - next_arena_end;

    if (space_left < allocation_size) {
        return(NULL);
    }

    //at this point, we should know for certain we can add it to the end of the list
    //so we're gonna do that
    new_arena = next_arena_end + 1;
    new_arena->size   = size;
    new_arena->next   = NULL;
    new_arena->memory = new_arena + sizeof(ItfliesbyMemoryArena);
    
    next_arena->next = new_arena;

    return(new_arena); 
}