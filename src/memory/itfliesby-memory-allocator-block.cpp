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
    if (!partition || block_count == 0) {
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
    ItfliesbyMemoryAllocatorBlock* block_allocator = &new_allocator_header->allocator.block;
    block_allocator->header     = new_allocator_header;
    block_allocator->block_size = block_size;
    block_allocator->num_blocks = block_count;
    block_allocator->blocks     = NULL;

    new_allocator_header->next             = NULL;
    new_allocator_header->partition        = partition;
    new_allocator_header->size             = data_memory_size;
    new_allocator_header->type             = ITFLIESBY_MEMORY_ALLOCATOR_TYPE_BLOCK;
    strcpy(new_allocator_header->tag,allocator_tag);

    //these sizes will help us calculate our addresses
    u64 block_memory_size = 
        sizeof(ItfliesbyMemoryBlock) + 
        block_size;

    u64 block_node_size = 
        sizeof(ItfliesbyMemoryAllocatorBlockNode) + 
        sizeof(ItfliesbyMemoryBlock) +
        block_memory_size;

    //we are going to initialize the first node manually
    ItfliesbyMemoryAllocatorBlockNode* first_node = 
        (ItfliesbyMemoryAllocatorBlockNode*)(
            (memory)new_allocator_header + 
            sizeof(ItfliesbyMemoryAllocatorHeader)
        );
    
    //get our new block of memory
    ItfliesbyMemoryBlock* new_block =
        (ItfliesbyMemoryBlock*)(
            (memory)first_node + 
            sizeof(ItfliesbyMemoryAllocatorBlockNode)
    ); 
    new_block->allocator_header = new_allocator_header;
    new_block->size             = block_size;
    
    first_node->next = NULL;
    first_node->block = new_block;

    //initialize stuff we'll need for the rest of the nodes, if we have any
    ItfliesbyMemoryAllocatorBlockNode* previous_node = first_node;
    ItfliesbyMemoryAllocatorBlockNode* next_node     = first_node->next;

    for (
        u32 block_index = 1;
        block_index < block_count;
        ++block_index) {

        //find the address of our next node
        next_node = 
            (ItfliesbyMemoryAllocatorBlockNode*)(
                (memory)previous_node +
                block_node_size 
            );
        
        //find the address for the next memory block
        new_block = 
            (ItfliesbyMemoryBlock*)(
                next_node +
                sizeof(ItfliesbyMemoryAllocatorBlockNode)
            );

        
        //initialize the block
        new_block->allocator_header = new_allocator_header;
        new_block->size             = block_size;

        //initialize the node
        next_node->block = new_block;
        next_node->next = NULL;

        //update the previous node for the next iteration
        previous_node   = next_node;
    }


    //return the address to the new block allocator
    return(&new_allocator_header->allocator.block);
}

external memory 
itfliesby_memory_allocator_block_allocate(
    ItfliesbyMemoryAllocatorBlock* allocator,
    ItfliesbyMemoryReturnCode*     result) {
    
    if (!allocator) {
        if (result) *result = ITFLIESBY_MEMORY_RETURN_CODE_INVALID_ARGUMENT;
        return(NULL); 
    }



}