#pragma once

#include "ifb-data-structures.hpp"

struct IFBDataStructure {
    IFBAddr start;
    IFBU64  size;
};

struct IFBArray : IFBDataStructure {
    IFBU32 element_size;
    IFBU32 element_count;
};

struct IFBArrayList : IFBDataStructure {
    IFBU64 element_size;
    IFBU32 element_count_total;
    IFBU32 element_count_current;
};
