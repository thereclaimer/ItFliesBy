#pragma once

#include "itfliesby-memory.hpp"

external ItfliesbyMemoryReturnCode
itfliesby_memory_partition_create(
    ItfliesbyMemoryArena*     arena,
    char                      partition_tag[16],
    u64                       partition_size,
    ItfliesbyMemoryPartition* partition) {

    //check arguments
    if (!arena || partition_size < sizeof(ItfliesbyMemoryPartition)) {
        return(ITFLIESBY_MEMORY_RETURN_CODE_INVALID_ARGUMENT);
    }
    if ((sizeof(ItfliesbyMemoryPartition) + partition_size) < arena->size) {
        return(ITFLIESBY_MEMORY_RETURN_CODE_NOT_ENOUGH_ALLOCATOR_MEMORY);
    }

    //if this is the first partition, set it and we're done
    if (!arena->partitions) {
        
        partition             = (ItfliesbyMemoryPartition*)(arena + sizeof(ItfliesbyMemoryArena));
        partition->allocators = NULL;
        partition->arena      = arena;
        partition->next       = NULL;
        partition->size       = partition_size;
        strcpy(partition->tag,partition_tag);

        arena->partitions = partition;

        return(ITFLIESBY_MEMORY_RETURN_CODE_SUCCESS);
    }
    
    //go to the end of the partitions
    ItfliesbyMemoryPartition* current_partition = arena->partitions;
    for (
        current_partition;
        current_partition->next != NULL;
        current_partition = current_partition->next) {
    }

    //put the new partition at the end of the list
    partition = current_partition + sizeof(ItfliesbyMemoryPartition) + current_partition->size;
    partition->allocators = NULL;
    partition->arena      = arena;
    partition->next       = NULL;
    partition->size       = partition_size;

    current_partition->next = partition;

    return(ITFLIESBY_MEMORY_RETURN_CODE_SUCCESS);
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
        current_allocator_header->next != NULL;
        current_allocator_header = current_allocator_header->next) {
        
        space_free -= sizeof(ItfliesbyMemoryAllocatorHeader) + current_allocator_header->size; 
    }

    return(space_free);
}

external u64
itfliesby_memory_partition_space_occupied(
    ItfliesbyMemoryPartition* partition) {

    if (!partition) {
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