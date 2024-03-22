#pragma once

#include "itfliesby-memory.hpp"

external ItfliesbyMemoryAllocatorBlock*
itfliesby_memory_allocator_block_create(
    ItfliesbyMemoryPartition*  partition,
    char                       allocator_tag[32],
    u64                        block_size,
    u64                        block_count,
    ItfliesbyMemoryReturnCode* result) {

    //check arguments
    if (!partition) {
        if (result) *result = ITFLIESBY_MEMORY_RETURN_CODE_INVALID_ARGUMENT;
        return(NULL);
    }
    
    u64 data_memory_size          = block_size * block_count;
    u64 total_memory_size         = sizeof(ItfliesbyMemoryAllocatorHeader) + data_memory_size; 
    u64 partition_space_available = itfliesby_memory_partition_space_free(partition);

    if (total_memory_size > partition_space_available) {
        if (result) *result = ITFLIESBY_MEMORY_RETURN_CODE_NOT_ENOUGH_PARTITION_MEMORY;
        return(NULL);
    }

    if (result) *result = ITFLIESBY_MEMORY_RETURN_CODE_SUCCESS; 

    //get the next available allocator
    ItfliesbyMemoryAllocatorHeader* new_allocator_header = 
        itfliesby_memory_allocator_header_create(partition);

    //initialize block allocator
    ItfliesbyMemoryAllocatorBlock block_allocator = {0};
    block_allocator.header     = new_allocator_header;
    block_allocator.block_size = block_size;
    block_allocator.num_blocks = block_count;
    block_allocator.blocks     = NULL;

    new_allocator_header->allocator.block  = block_allocator;
    new_allocator_header->next             = NULL;
    new_allocator_header->partition        = partition;
    new_allocator_header->size             = data_memory_size;
    new_allocator_header->type             = ITFLIESBY_MEMORY_ALLOCATOR_TYPE_BLOCK;
    strcpy(new_allocator_header->tag,allocator_tag);

    //return the address to the new block allocator
    return(&new_allocator_header->allocator.block);
}
