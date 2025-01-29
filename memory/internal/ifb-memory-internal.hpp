#ifndef IFB_MEMORY_INTERNAL_HPP
#define IFB_MEMORY_INTERNAL_HPP

#include "ifb-memory.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/



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

    const IFBMemoryStackAllocator* stack_push_stack_allocators (const IFBMemoryHandle memory_handle);
    const IFBMemoryBlockAllocator* stack_push_block_allocators (const IFBMemoryHandle memory_handle, const ifb_u32 block_count);
    const IFBMemoryArena*          stack_push_arenas           (const IFBMemoryHandle memory_handle, const ifb_u32 arena_count);
};

struct IFBMemoryReservation {
    ifb_address start;
    ifb_u64     size;
    ifb_u32     granularity;
    ifb_u32     page_size;
    ifb_u32     pages_total;
    ifb_u32     pages_committed;
};

struct IFBMemoryPage {
    ifb_u32     page_number;
    ifb_address page_address;
};


struct IFBMemoryPageCommit {
    ifb_address   start;
    ifb_u32       size;
    ifb_u32       page_number;
    ifb_u32       page_count;
};

namespace ifb_memory {

    const ifb_address reservation_get_start_address   (const IFBMemory* memory_ptr);
    const ifb_ptr     reservation_get_start_pointer   (const IFBMemory* memory_ptr);
    const ifb_ptr     reservation_get_page_start_next (const IFBMemory* memory_ptr);
    const ifb_ptr     reservation_get_page_start      (const IFBMemory* memory_ptr, const ifb_u32 page_number);

    const ifb_b8
    reservation_page_commit(
        IFBMemory*           memory_ptr,
        IFBMemoryPageCommit& page_commit_ref);

};

struct IFBMemoryArenaAllocators {
    IFBMemoryStackAllocator* stack_allocator_array;
    IFBMemoryBlockAllocator* block_allocator_array;
    ifb_u32                  stack_allocator_count;
    ifb_u32                  block_allocator_count;
    ifb_u32                  stack_allocator_memory_size;
    ifb_u32                  block_allocator_memory_size;
};

struct IFBMemoryArena {
    IFBMemoryArenaAllocators allocators;
    IFBMemoryPageCommit      page_commit;
    ifb_u32                  index;             
    ifb_u32                  position;
};


struct IFBMemoryArenaTable {
    IFBMemoryArena* arena_array;    
    IFBMemoryHandle arena_array_handle;
    ifb_u32         count_total;
    ifb_u32         count_used;    
};

namespace ifb_memory {

    const IFBMemoryArena* arena_get_next    (const IFBMemory* memory_ptr);
    const ifb_ptr         arena_get_pointer (const IFBMemoryArenaHandle arena_handle, const ifb_u32 offset);
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