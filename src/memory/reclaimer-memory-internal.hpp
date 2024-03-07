#ifndef RECLAIMER_MEMORY_HPP
#define RECLAIMER_MEMORY_HPP

#include <reclaimer.hpp>

struct ReclaimerMemoryData {
    mem_handle handle; // handle to the data in core memory
    mem_data data;     // actual data in core memory
};

#define RECLAIMER_MEMORY_BLOCK_DATA_OFFSET (sizeof(ReclaimerMemoryBlock))

struct ReclaimerMemoryBlock {
    
    mem_handle index;                 // the index is where the data is located in the core memory
    mem_size block_size;              // this is the actual size the block plus data takes up in memory
    mem_size data_size;               // this is how many bytes the data takes up
    ReclaimerMemoryBlock* next; // this is the pointer to the next block in memory
    ReclaimerMemoryBlock* prev; // this is the pointer to the previous block in memory
    mem_data end;                     // this is the pointer to the last byte in the block
    mem_data data;                    // this is the pointer to the actual data in the core memory
};

struct ReclaimerMemory {
    ReclaimerPlatformApi  platform;
    mem_size              total_memory_size;
    mem_size              used_memory_size;
    mem_size              num_free_blocks;
    mem_size              num_occupied_blocks;
    ReclaimerMemoryBlock* free_blocks;
    ReclaimerMemoryBlock* occupied_blocks;
    mem_data              end_address;
    mem_data              core_memory;
};

#endif //RECLAIMER_MEMORY_HPP