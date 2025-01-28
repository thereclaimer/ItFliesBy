#ifndef IFB_MEMORY_INTERNAL_HPP
#define IFB_MEMORY_INTERNAL_HPP

#include "ifb-memory.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBMemoryStack;
struct IFBMemoryReservation;

/**********************************************************************************/
/* IMPLEMENTATIONS                                                                */
/**********************************************************************************/

struct IFBMemoryStack {
    ifb_byte* memory;
    ifb_u32   size;
    ifb_u32   position;
};

struct IFBMemoryReservation {
    ifb_address start;
    ifb_u32     page_size;
    ifb_u32     pages_total;
    ifb_u32     pages_committed;
};

struct IFBMemoryArena : IFBMemoryHandle {
    IFBMemoryArena*  next;
    ifb_address      start;
    ifb_u32          page_count;
    ifb_u32          page_number;
    ifb_u32          size;
    ifb_u32          position;
};

struct IFBMemoryArenaList {
    IFBMemoryArena* first;
};

struct IFBMemoryManager {
    IFBPlatformMemoryApi* platform_memory_api;
    IFBMemoryStack        stack;
    IFBMemoryReservation  reservation;
    IFBMemoryArenaList    arena_list;
};

struct IFBMemoryStackAllocator {
    ifb_address start;
    ifb_u32     size;
    ifb_u32     position;
    ifb_u32     save_point;    
};

struct IFBMemoryBlockAllocator {
    ifb_address start;
    ifb_u32     block_size;
    ifb_u32     block_count;
    ifb_u32*    block_flags_array;
};

#endif //IFB_MEMORY_INTERNAL_HPP