#pragma once

#include "ifb-data-structures.hpp"

struct IFBDataStructure {
    ifb::addr start;
    ifb::u64  size;
};

struct IFBStack : IFBDataStructure {
    ifb::u64 position;
};

struct IFBQueue : IFBDataStructure {
    ifb::u32 position;
};

struct IFBHashTable : IFBDataStructure {
    ifb::u32 element_array_start;
    ifb::u32 element_size;
    ifb::u32 element_count_max;
    ifb::u32 key_length_max;
};