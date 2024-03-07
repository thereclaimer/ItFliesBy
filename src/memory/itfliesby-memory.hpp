#ifndef ITFLIESBY_MEMORY_HPP
#define ITFLIESBY_MEMORY_HPP

#include <itfliesby.hpp>

//my thoughts are this is a simple header only library
//we allocate memory on the platform, then pass it here to
//convert it to an arena. From there, we can create as 
//many sub arenas using whatever type of allocators we want


struct ItfliesByMemoryArena {
    u64    total_size;
    u64    used_size;
    memory memory;    
}

struct ItfliesbyMemoryPartition {
    u64                       total_size;
    char[32]                  tag;
    ItfliesbyMemoryPartition* next;
    memory                    memory;
};

struct ItfliesbyMemory {
    u64                       total_size;
    memory                    memory;
    ItfliesbyMemoryPartition* partitions;
};

#endif //ITFLIESBY_MEMORY_HPP