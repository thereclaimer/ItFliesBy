#ifndef IFB_TYPES_DATA_STRUCTURES_HPP
#define IFB_TYPES_DATA_STRUCTURES_HPP

#include "ifb-types-primitives.hpp"
#include "ifb-types-memory.hpp"

/**********************************************************************************/
/* DATA STRUCTURES                                                                */
/**********************************************************************************/


struct IFBArray : IFBMemoryBlock {
    IFBU32 element_size;
    IFBU32 element_count;
};

struct IFBStack : IFBMemoryBlock {
    IFBU64 position;
};

struct IFBArrayList : IFBMemoryBlock {
    IFBU64 element_size;
    IFBU32 element_count_total;
    IFBU32 element_count_current;
};


struct IFBQueue : IFBMemoryBlock {
    IFBU32 position;
};

struct IFBHashTable : IFBMemoryBlock {
    IFBU32 element_array_start;
    IFBU32 element_size;
    IFBU32 element_count_max;
    IFBU32 key_length_max;
};

#endif //IFB_TYPES_DATA_STRUCTURES_HPP