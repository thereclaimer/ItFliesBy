#include "reclaimer-memory-internal.hpp"

#pragma once

external mem_data
reclaimer_memory_data_get(
    ReclaimerMemory* memory,
    mem_handle       handle) {

    mem_data game_data = &memory->core_memory[handle];

    return(game_data);
}

external ReclaimerMemory*
reclaimer_memory_create_and_init(
    ReclaimerPlatformApi platform,
    mem_size             core_memory_size) {

    //first, we need to allocate memory for the game
    mem_data core_memory = (mem_data)platform.memory_allocate(core_memory_size);

    //our memory state will begin at the first byte in our core memory
    ReclaimerMemory* memory = (ReclaimerMemory*)core_memory;
    memory->total_memory_size = core_memory_size;
    memory->used_memory_size  = sizeof(ReclaimerMemory) + sizeof(ReclaimerMemoryBlock);
    memory->occupied_blocks   = NULL; 
    memory->core_memory       = core_memory; 
    memory->end_address       = &core_memory[core_memory_size - 1]; 
    memory->num_free_blocks   = 1;

    //we will now set our first free block
    mem_size first_block_size = core_memory_size - sizeof(ReclaimerMemory);
    ReclaimerMemoryBlock* first_memory_block = (ReclaimerMemoryBlock*)(core_memory + sizeof(ReclaimerMemory));
    first_memory_block->next       = NULL;
    first_memory_block->prev       = NULL;
    first_memory_block->data_size  = first_block_size - RECLAIMER_MEMORY_BLOCK_DATA_OFFSET;
    first_memory_block->block_size = first_block_size;
    first_memory_block->end        = (mem_data)(core_memory + (core_memory_size - 1));
    first_memory_block->data       = (mem_data)(&core_memory[first_block_size + RECLAIMER_MEMORY_BLOCK_DATA_OFFSET]);
    first_memory_block->index      = first_block_size + RECLAIMER_MEMORY_BLOCK_DATA_OFFSET;

    memory->free_blocks = first_memory_block;

    memory->platform = platform;

    return(memory);
}


internal mem_size
reclaimer_memory_allocation_size(
    mem_size memory_size) {
    
    return(memory_size + sizeof(ReclaimerMemoryBlock));
}

internal ReclaimerMemoryBlock*
reclaimer_memory_find_first_free_block(
    ReclaimerMemory* memory,
    mem_size memory_size) {

    ReclaimerMemoryBlock* free_block_to_use = NULL;
    
    for (ReclaimerMemoryBlock* current_block = memory->free_blocks;
        current_block != NULL;
        current_block = current_block->next) {
            
        if (reclaimer_memory_allocation_size(memory_size) <= current_block->data_size) {
            //we found a free block to use
            free_block_to_use = current_block;
            break;
        }
    }

    return(free_block_to_use);
}

internal ReclaimerMemoryBlock*
reclaimer_memory_partition_block(
    ReclaimerMemory*      memory,
    ReclaimerMemoryBlock* existing_block,
    mem_size                    memory_size) {

    //we are partitioning starting at the end of the block, so we're starting there
    mem_size new_block_size       = reclaimer_memory_allocation_size(memory_size); 
    mem_data new_block_end        = existing_block->end;
    mem_data new_block_start      = new_block_end - new_block_size;     
    mem_data new_block_data_start = new_block_start + RECLAIMER_MEMORY_BLOCK_DATA_OFFSET;
    mem_size new_block_data_index = new_block_data_start - memory->core_memory;

    //initialize the new block 
    ReclaimerMemoryBlock* new_block = (ReclaimerMemoryBlock*)new_block_start;
    *new_block            = {0};
    new_block->data_size  = memory_size;
    new_block->block_size = new_block_size;
    new_block->next       = NULL;
    new_block->prev       = NULL;
    new_block->data       = new_block_data_start; 
    new_block->index      = (mem_size)(new_block->data - memory->core_memory); 

    //now we can adjust the existing block
    existing_block->data_size  -= new_block_size;
    existing_block->block_size -= new_block_size;
    existing_block->end        -= (new_block_size + 1);

    return(new_block);
}

internal void
reclaimer_memory_add_used_block(
    ReclaimerMemory*      memory,
    ReclaimerMemoryBlock* used_block) {

    //find the spot for our new block
    if (memory->occupied_blocks) {

        //we have occupied blocks aleady, so insert it at the end of the list
        for (ReclaimerMemoryBlock* current_block = memory->occupied_blocks;
            current_block != NULL;
            current_block = current_block->next) {

            //go until we reach the end of the list
            if (current_block->next) {
                continue;
            }

            //we found the end of the list, so place the new block here
            current_block->next = used_block;
            used_block->prev    = current_block;

            ++memory->num_occupied_blocks;

            break;
        }
    }
    else {
        //if there are no occupied blocks, set it and we're done
        memory->occupied_blocks = used_block;
        ++memory->num_occupied_blocks;
    }
}

internal b32
reclaimer_memory_are_blocks_continuous(
    ReclaimerMemoryBlock* first_block,
    ReclaimerMemoryBlock* second_block) {

    if (first_block && second_block) {
        //if the first block data plus the data size is the same
        //address as the second block, these are continuous
        return ((first_block->data + first_block->data_size) == (mem_data)second_block);
    }

    return false;
}

internal void
reclaimer_memory_add_free_block(
    ReclaimerMemory*      memory,
    ReclaimerMemoryBlock* free_block) {

    mem_size free_block_size = free_block->block_size; 

    //find the spot for our free block
    if (memory->free_blocks) {

        //we have free blocks already, so find where this memory
        //goes based on the index

        for (ReclaimerMemoryBlock* current_block = memory->free_blocks;
            current_block != NULL;
            current_block = current_block->next) {

            //we want the block to fit in the list sequentially
            if (current_block->index < free_block->index) {

                //in this case we've found the end of the list
                //so we can delete the free block and add its
                //free memory to the current block
                if (current_block->next == NULL) {

                    //add the size of the free block to the one we're adding it to
                    current_block->data_size  += free_block_size;
                    current_block->block_size += free_block_size;

                    //remove the size of the free block from the used memory
                    //and decrease the number of occupied blocks
                    memory->used_memory_size -= free_block_size;
                    --memory->num_occupied_blocks;
                    
                    break;
                }

                //we've found a spot between two blocks that the free block can fit
                if (current_block->next->index > free_block->index) {

                    //put the free block in the list like this
                    // [current block] --> [free block] --> [block to move up]
                    ReclaimerMemoryBlock* block_to_move_up = current_block->next;
                    current_block->next = free_block;
                    free_block->next = block_to_move_up;
                    memory->used_memory_size -= free_block_size;


                    //here, the consolidation logic gets a little weird...
                    
                    //check if the current block and the free block are continuous
                    if (reclaimer_memory_are_blocks_continuous(current_block, free_block)) {
                        
                        //[current block + free block] -> [block to move up]

                        current_block->data_size += free_block_size;
                        current_block->next = free_block->next;

                        //NOW, we set the free block equal to the current block
                        //because whether or not current and free block are free,
                        //the next step is to check the free block and the block that was moved up
                        //if the free block and current block are the same now, this will also
                        //consolidate the next two in the next step
                        free_block = current_block;
                    }

                    //now we check if the free block and the block to move are continuous
                    if (reclaimer_memory_are_blocks_continuous(free_block,block_to_move_up)) {

                        //[current block] -> [free block + block to move up]

                        free_block->data_size += block_to_move_up->data_size;
                        free_block->next  = block_to_move_up->next;
                    }

                    break;
                }
            }
        }
    }
}


internal ReclaimerMemoryData 
reclaimer_memory_allocate_internal(
    ReclaimerMemory* memory,
    mem_size               memory_size) {

    //find the first free block
    ReclaimerMemoryBlock* free_block_to_use = reclaimer_memory_find_first_free_block(memory, memory_size);
    reclaimer_assert(free_block_to_use);

    //partition our new block from the free block
    ReclaimerMemoryBlock* new_memory_block = 
        reclaimer_memory_partition_block(
            memory, 
            free_block_to_use, 
            memory_size
    );

    //add the new block to the used blocks
    reclaimer_memory_add_used_block(
        memory,
        new_memory_block);
    
    //finally, update the used memory
    memory->used_memory_size += new_memory_block->block_size;

    //return the data and memory handle
    ReclaimerMemoryData memory_data = {0};
    memory_data.handle = new_memory_block->index;
    memory_data.data   = new_memory_block->data;

    return(memory_data);
} 

external mem_handle 
reclaimer_memory_allocate(
    ReclaimerMemory* memory,
    mem_size         memory_size) {

    //find the first free block
    ReclaimerMemoryBlock* free_block_to_use = reclaimer_memory_find_first_free_block(memory, memory_size);
    reclaimer_assert(free_block_to_use);

    //partition our new block from the free block
    ReclaimerMemoryBlock* new_memory_block = 
        reclaimer_memory_partition_block(
            memory, 
            free_block_to_use, 
            memory_size
    );

    //add the new block to the used blocks
    reclaimer_memory_add_used_block(
        memory,
        new_memory_block);
    
    //finally, update the used memory
    memory->used_memory_size += new_memory_block->block_size;

    //return the data and memory handle
    ReclaimerMemoryData memory_data = {0};
    memory_data.handle = new_memory_block->index;
    memory_data.data   = new_memory_block->data;

    return(memory_data.handle);
}

internal void
reclaimer_memory_delete_occupied_block(
    ReclaimerMemory*      memory,
    ReclaimerMemoryBlock* block_to_free) {

    //remove the reference from used game memory
    if (memory->occupied_blocks == block_to_free) {

        //if the occupied block is the first in the list, make the
        //start of the list equal to the next block
        memory->occupied_blocks = block_to_free->next;
    }
    else {
        //otherwise, adjust the next and previous pointers
        ReclaimerMemoryBlock* next_block = block_to_free->next;
        ReclaimerMemoryBlock* prev_block = block_to_free->prev;

        prev_block->next = next_block;

        //if we just removed the last element in the list, we're done
        if (next_block) {
            next_block->prev = prev_block;
        }
    }

    block_to_free = {0};
    block_to_free = NULL;
}

external void
reclaimer_memory_deallocate(
    ReclaimerMemory* memory,
    mem_handle       handle) {

    //first, we need to get the memory block information
    mem_data data_to_free = 
        reclaimer_memory_data_get(
            memory,
            handle
    );

    ReclaimerMemoryBlock* block_to_free = (ReclaimerMemoryBlock*)(data_to_free - RECLAIMER_MEMORY_BLOCK_DATA_OFFSET);

    //now, add the block the the list of free blocks
    reclaimer_memory_add_free_block(
        memory,
        block_to_free
    );

    //finally, we can delete the occupied block
    reclaimer_memory_delete_occupied_block(
        memory,
        block_to_free
    );
}

external void
reclaimer_memory_destroy(
    ReclaimerMemory* memory) {

    memory->platform.memory_free(memory->core_memory, memory->total_memory_size);
}

