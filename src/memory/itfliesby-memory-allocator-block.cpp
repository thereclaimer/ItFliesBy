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
    block_allocator->header          = new_allocator_header;
    block_allocator->block_size      = block_size;
    block_allocator->num_blocks      = block_count;
    block_allocator->num_free_blocks = block_count;
    block_allocator->blocks          = NULL;

    //these free blocks are offsets relative to the address of the allocator
    block_allocator->free_blocks = 
        (s64*)(
            (memory)block_allocator + 
            sizeof(ItfliesbyMemoryAllocatorBlock)
        );

    //initialize the header
    new_allocator_header->next      = NULL;
    new_allocator_header->partition = partition;
    new_allocator_header->size      = data_memory_size;
    new_allocator_header->type      = ITFLIESBY_MEMORY_ALLOCATOR_TYPE_BLOCK;
    strcpy(new_allocator_header->tag,allocator_tag);

    //these sizes will help us calculate our addresses
    u64 block_memory_size = 
        sizeof(ItfliesbyMemoryBlock) + 
        block_size;

    u64 block_node_size = 
        sizeof(ItfliesbyMemoryAllocatorBlockNode) + 
        sizeof(ItfliesbyMemoryBlock) +
        block_memory_size;

    u64 free_block_info_size = 
        sizeof(s64) * 
        block_count;

    u64 header_size =
        sizeof(ItfliesbyMemoryAllocatorHeader) + 
        free_block_info_size;

    //we are going to initialize the first node manually
    ItfliesbyMemoryAllocatorBlockNode* first_node = 
        (ItfliesbyMemoryAllocatorBlockNode*)(
            (memory)new_allocator_header + 
            header_size
        );
    
    //get our new block of memory
    ItfliesbyMemoryBlock* new_block =
        (ItfliesbyMemoryBlock*)(
            (memory)first_node + 
            sizeof(ItfliesbyMemoryAllocatorBlockNode)
    ); 
    new_block->allocator_header = new_allocator_header;
    new_block->size             = block_size;
    
    first_node->next  = NULL;
    first_node->block = new_block;

    block_allocator->free_blocks[0] = 
        (s64)(
            ((memory)new_block + sizeof(ItfliesbyMemoryBlock)) -
            (memory)block_allocator 
        );

    //initialize stuff we'll need for the rest of the nodes, if we have any
    ItfliesbyMemoryAllocatorBlockNode* current_node = first_node;
    ItfliesbyMemoryAllocatorBlockNode* new_node     = NULL; 
    ItfliesbyMemoryAllocatorBlockNode* last_node    = NULL;

    for (
        u32 block_index = 1;
        block_index < block_count;
        ++block_index) {

        //find the address of our next node
        new_node = 
            (ItfliesbyMemoryAllocatorBlockNode*)(
                (memory)current_node +
                block_node_size 
            );
        
        //find the address for the next memory block
        new_block = 
            (ItfliesbyMemoryBlock*)(
                (memory)new_node +
                sizeof(ItfliesbyMemoryAllocatorBlockNode)
            );

        s64 new_block_offset = 
            (s64)(
                ((memory)new_block + sizeof(ItfliesbyMemoryBlock)) -
                (memory)block_allocator 
            );

        block_allocator->free_blocks[block_index] = new_block_offset;

        //initialize the block
        new_block->allocator_header = new_allocator_header;
        new_block->size             = block_size;

        //initialize the node
        new_node->block = new_block;
        new_node->next  = NULL;

        //update the previous node for the next iteration
        current_node->next = new_node;
        current_node       = current_node->next;
    }

    // block_allocator->blocks = first_node;

    //check our calculcations
    memory allocator_end_from_last_node = (memory)current_node + block_node_size;
    

    //return the address to the new block allocator
    return(block_allocator);
}

external memory 
itfliesby_memory_allocator_block_allocate(
    ItfliesbyMemoryAllocatorBlock* allocator,
    ItfliesbyMemoryReturnCode*     result) {
    
    if (!allocator) {
        if (result) *result = ITFLIESBY_MEMORY_RETURN_CODE_INVALID_ARGUMENT;
        return(NULL); 
    }

    if (allocator->num_free_blocks == 0) {
        if (result) *result = ITFLIESBY_MEMORY_RETURN_CODE_NOT_ENOUGH_ALLOCATOR_MEMORY;
        return(NULL); 
    }

    //find the next available relative address
    s64* addresses     = allocator->free_blocks;
    u32  num_blocks    = allocator->num_blocks;
    s64  free_address  = -1;
    u32  address_index = 0;

    for (
        address_index = 0;
        address_index < num_blocks && !free_address;
        ++address_index) {

        free_address = addresses[address_index];
    }

    //we already did a check for available addresses, so we should have one
    ITFLIESBY_ASSERT(free_address);

    //mark this address as unavailable
    --allocator->num_free_blocks;
    addresses[address_index] = -1;

    //return the block memory
    memory block_memory = (memory)allocator + free_address;
    return(block_memory);
}

external void
itfliesby_memory_allocator_block_free(
    ItfliesbyMemoryAllocatorBlock* allocator,
    memory                         block) {

    //check arguments 
    if (!allocator || !block) {
        return;
    }

    //check the bounds of this memory
    b8 out_of_bounds = false;

    out_of_bounds |= ((memory)allocator > block);

    //TODO: bounds checking not complete, fuck around and find out
    if (out_of_bounds) {
        return;
    }

    //calculate our relative address
    u64 address = (u64)(block - (memory)allocator);

    //find the next unavailable relative address index
    s64* addresses     = allocator->free_blocks;
    u32  num_blocks    = allocator->num_blocks;
    s64  used_address  = 1;
    u32  address_index = 0;

    for (
        address_index = 0;
        address_index < num_blocks && used_address;
        ++address_index) {

        used_address = addresses[address_index];
    }

    addresses[address_index] = used_address;
    ++allocator->num_free_blocks;
}
