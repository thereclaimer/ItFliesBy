#pragma once

#include "ifb-data-structures.hpp"

struct IFBDataStructure {
    IFBAddr start;
    IFBU64  size;
};


struct IFBArrayList : IFBDataStructure {
    IFBU64 element_size;
    IFBU32 element_count_total;
    IFBU32 element_count_current;
};

struct IFBStack : IFBDataStructure {
    IFBU64 position;
};

struct IFBQueue : IFBDataStructure {
    IFBU32 position;
};

struct IFBHashTable : IFBDataStructure {
    IFBU32 element_array_start;
    IFBU32 element_size;
    IFBU32 element_count_max;
    IFBU32 key_length_max;
};