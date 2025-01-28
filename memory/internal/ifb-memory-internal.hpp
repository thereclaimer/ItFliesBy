#ifndef IFB_MEMORY_INTERNAL_HPP
#define IFB_MEMORY_INTERNAL_HPP

#include "ifb-memory.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBMemoryStack;
struct IFBMemoryReservation;
struct IFBMemoryArena;
struct IFBMemoryArenaTable;
struct IFBMemoryStackAllocator;
struct IFBMemoryBlockAllocator;

/**********************************************************************************/
/* PLATFORM                                                                       */
/**********************************************************************************/

namespace ifb_memory {

    ifb_global funcptr_ifb_platform_memory_reserve                platform_memory_reserve;
    ifb_global funcptr_ifb_platform_memory_release                platform_memory_release;
    ifb_global funcptr_ifb_platform_memory_commit                 platform_memory_commit;
    ifb_global funcptr_ifb_platform_system_page_size              platform_page_size;
    ifb_global funcptr_ifb_platform_system_allocation_granularity platform_allocation_granularity;
};

/**********************************************************************************/
/* IMPLEMENTATIONS                                                                */
/**********************************************************************************/

struct IFBMemoryStack {
    ifb_u32   size;
    ifb_u32   position;
};

namespace ifb_memory {

    const IFBMemoryHandle               stack_push_arenas          (IFBMemory* memory_ptr, const ifb_u32 arena_count);
    const IFBMemoryBlockAllocatorHandle stack_push_block_allocator (IFBMemory* memory_ptr, const ifb_u32 block_count);
    const IFBMemoryStackAllocatorHandle stack_push_stack_allocator (IFBMemory* memory_ptr);
};

struct IFBMemoryReservation {
    ifb_address start;
    ifb_u64     size;
    ifb_u32     page_size;
    ifb_u32     pages_total;
    ifb_u32     pages_committed;
};

struct IFBMemoryArenaAllocators {
    IFBMemoryStackAllocator* stack_allocator_array;
    IFBMemoryBlockAllocator* block_allocator_array;
    ifb_u32                  stack_allocator_count;
    ifb_u32                  block_allocator_count;
};

struct IFBMemoryArena : IFBMemoryArenaHandle {
    IFBMemoryArenaAllocators allocators;
    ifb_address              start;
    ifb_u32                  index;             
    ifb_u32                  position;
    ifb_u32                  page_count;
    ifb_u32                  page_start;
};

struct IFBMemoryArenaTable {
    IFBMemoryArena* arena_array;    
    IFBMemoryHandle arena_array_handle;
    ifb_u32         count_total;
    ifb_u32         count_used;    
};

struct IFBMemoryStackAllocator {
    IFBMemoryArenaHandle arena_handle;
    ifb_address          start;
    ifb_u32              size;
    ifb_u32              position;
    ifb_u32              save_point;
};

#define IFB_MEMORY_BLOCK_FLAG_BIT_COUNT 32

struct IFBMemoryBlockAllocator  {
    IFBMemoryArenaHandle arena_handle;
    ifb_address          start;
    ifb_u32              block_size;
    ifb_u32              block_count;
    ifb_u32              block_flags_count;
    ifb_u32*             block_flags_array;
};

struct IFBMemory {
    IFBMemoryStack        stack;
    IFBMemoryReservation  reservation;
    IFBMemoryArenaTable   arena_table;
};

#endif //IFB_MEMORY_INTERNAL_HPP