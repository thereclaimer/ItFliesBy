#pragma once

#include "itfliesby-memory.hpp"

external ItfliesbyMemoryAllocatorLinear* 
itfliesby_memory_allocator_linear_create(
    ItfliesbyMemoryPartition*       partition,
    char                            allocator_tag[32],
    u64                             allocator_size,
    ItfliesbyMemoryReturnCode*      result) {

    ItfliesbyMemoryReturnCode result_local = ITFLIESBY_MEMORY_RETURN_CODE_SUCCESS; 

    u64 partition_space_available = itfliesby_memory_partition_space_free(partition);

    //check arguments
    if (!partition) {
        result_local = ITFLIESBY_MEMORY_RETURN_CODE_INVALID_ARGUMENT;
    }
    if ((sizeof(ItfliesbyMemoryAllocatorHeader) + allocator_size) > partition_space_available) {
        result_local = ITFLIESBY_MEMORY_RETURN_CODE_NOT_ENOUGH_PARTITION_MEMORY;
    }

    //determine the address of our next allocator
    ItfliesbyMemoryAllocatorHeader* allocator_header = NULL;
    ItfliesbyMemoryAllocatorHeader* previous_allocator_header = NULL;

    for (
        previous_allocator_header;
        previous_allocator_header != NULL && previous_allocator_header->next != NULL;
        previous_allocator_header = previous_allocator_header->next) {
    }

    allocator_header = previous_allocator_header 
        ? previous_allocator_header + sizeof(ItfliesbyMemoryAllocatorHeader) + previous_allocator_header->size
        : (ItfliesbyMemoryAllocatorHeader*)(partition + sizeof(ItfliesbyMemoryPartition));

    ITFLIESBY_ASSERT(allocator_header);

    //initialize linear allocator
    ItfliesbyMemoryAllocatorLinear linear_allocator = {0};
    linear_allocator.header = allocator_header;

    allocator_header->allocator.linear = linear_allocator;
    allocator_header->next             = NULL;
    allocator_header->partition        = partition;
    allocator_header->size             = allocator_size;
    allocator_header->type             = ITFLIESBY_MEMORY_ALLOCATOR_TYPE_LINEAR;
    strcpy(allocator_header->tag,allocator_tag);

    if (result) {
        *result = result_local;
    }

    //add the allocator to the list in the partition
    if (previous_allocator_header) {
        previous_allocator_header->next = allocator_header;
    } 
    else {
        partition->allocators = allocator_header;
    }

    //return the address to the new linear allocator
    return(&allocator_header->allocator.linear);
}

external memory
itfliesby_memory_allocator_linear_allocate(
    ItfliesbyMemoryAllocatorLinear* allocator,
    u64                             allocation_size,
    ItfliesbyMemoryReturnCode*      result) {

    if (!allocator || allocation_size == 0) {
        *result = ITFLIESBY_MEMORY_RETURN_CODE_INVALID_ARGUMENT;
        return(NULL);
    }

    ItfliesbyMemoryAllocatorHeader* allocator_header = allocator->header;

    //check available space
    u64 space_available = allocator_header->size - allocator->used_space;
    if (space_available < allocation_size) {
        *result = ITFLIESBY_MEMORY_RETURN_CODE_NOT_ENOUGH_ALLOCATOR_MEMORY;
        return(NULL);
    }

    memory allocation = (memory)allocator_header + sizeof(ItfliesbyMemoryAllocatorHeader) + allocator->used_space;

    return(allocation);
}

external ItfliesbyMemoryReturnCode
itfliesby_memory_allocator_linear_reset(
    ItfliesbyMemoryAllocatorLinear* allocator) {

    if (!allocator) {
        return(ITFLIESBY_MEMORY_RETURN_CODE_INVALID_ARGUMENT);
    }

    allocator->used_space = 0;

    return(ITFLIESBY_MEMORY_RETURN_CODE_SUCCESS);
}

external u64
itfliesby_memory_allocator_linear_space_total(
    ItfliesbyMemoryAllocatorLinear* allocator) {
    
    u64 space_total = allocator
        ? allocator->header->size
        : 0;

    return(space_total);
}

external u64
itfliesby_memory_allocator_linear_space_clear(
    ItfliesbyMemoryAllocatorLinear* allocator) {

    u64 space_available = allocator
        ? allocator->header->size - allocator->used_space
        : 0;

    return(space_available);
}

external u64
itfliesby_memory_allocator_linear_space_occupied(
    ItfliesbyMemoryAllocatorLinear* allocator) {

    u64 space_used = allocator
        ? allocator->used_space
        : 0;

    return(space_used);
}