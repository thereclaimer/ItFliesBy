#pragma once

#include "ifb-memory.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBMemoryManagerInternal;

/**********************************************************************************/
/* DEFINITIONS                                                                    */
/**********************************************************************************/

struct IFBMemoryManagerInternal {
    IFBAddr reserved_memory_start;
    IFBU32  count_arenas;
    IFBU32  size_arena;
    IFBU32  size_page;
    IFBU32  size_granularity;
    IFBU32  offset_arena_array_start;
    IFBU32  offset_arena_array_position;
};