#pragma once

#include "itfliesby-memory.hpp"

external ItfliesbyMemoryPartition* 
itfliesby_memory_partition_create(
    ItfliesbyMemoryArena*      arena,
    char                       partition_tag[32],
    u64                        partition_size,
    ItfliesbyMemoryReturnCode* result) {

    u64 arena_space_available = itfliesby_memory_arena_size_free(arena);

    if (result) *result = ITFLIESBY_MEMORY_RETURN_CODE_SUCCESS;

    //check arguments
    if (!arena) {
        if (result) *result = ITFLIESBY_MEMORY_RETURN_CODE_INVALID_ARGUMENT; 
        return(NULL);
    }
    if ((sizeof(ItfliesbyMemoryPartition) + partition_size) > arena_space_available) {
        if (result) *result = ITFLIESBY_MEMORY_RETURN_CODE_NOT_ENOUGH_ARENA_MEMORY;
        return(NULL);
    }

    //find the previous partition, if we have one
    ItfliesbyMemoryPartition* previous_partition = arena->partitions;
    for (
        previous_partition;
        previous_partition != NULL && previous_partition->next != NULL;
        previous_partition = previous_partition->next);

    //determine the address of our new partition
    ItfliesbyMemoryPartition* new_partition = NULL;
    if (previous_partition) {

        u64 partition_offset = sizeof(ItfliesbyMemoryPartition) + previous_partition->size;
        new_partition = (ItfliesbyMemoryPartition*)((memory)previous_partition + partition_offset); 
        previous_partition->next = new_partition;
    }
    else {

        new_partition = (ItfliesbyMemoryPartition*)((memory)arena + sizeof(ItfliesbyMemoryArena));
        arena->partitions = new_partition;
    }

    //we need to have a usable address at this point
    ITFLIESBY_ASSERT(new_partition);

    //initialize the partition
    new_partition->allocators = NULL;
    new_partition->arena      = arena;
    new_partition->next       = NULL;
    new_partition->size       = partition_size;
    strcpy(new_partition->tag,partition_tag);

    return(new_partition);
}

external memory
itfliesby_memory_partition_raw_memory(
    ItfliesbyMemoryPartition* partition) {

    if (!partition) {
        return(NULL);
    }

    memory partition_memory = (memory)partition + sizeof(ItfliesbyMemoryPartition);
        
    return(partition_memory);
}

external u64
itfliesby_memory_partition_space_total(
    ItfliesbyMemoryPartition* partition) {

    if (!partition) {
        return(0L);
    }

    return(partition->size);
}

external u64
itfliesby_memory_partition_space_free(
    ItfliesbyMemoryPartition* partition) {

    if (!partition) {
        return(0L);
    }

    u64 space_free = partition->size;

    for (
        ItfliesbyMemoryAllocatorHeader* current_allocator_header = partition->allocators;
        current_allocator_header != NULL && current_allocator_header->next != NULL;
        current_allocator_header = current_allocator_header->next) {
        
        space_free -= sizeof(ItfliesbyMemoryAllocatorHeader) + current_allocator_header->size; 
    }

    return(space_free);
}

external u64
itfliesby_memory_partition_space_occupied(
    ItfliesbyMemoryPartition* partition) {

    if (!partition || !partition->allocators) {
        return(0L);
    }

    u64 space_occupied = 0;

    for (
        ItfliesbyMemoryAllocatorHeader* current_allocator_header = partition->allocators;
        current_allocator_header->next != NULL;
        current_allocator_header = current_allocator_header->next) {
        
        space_occupied += (sizeof(ItfliesbyMemoryAllocatorHeader) + current_allocator_header->size);
    }

    return(space_occupied);
}
