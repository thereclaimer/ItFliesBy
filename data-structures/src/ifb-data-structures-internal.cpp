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
