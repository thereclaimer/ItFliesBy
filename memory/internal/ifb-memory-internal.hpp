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
/* STACK                                                                          */
/**********************************************************************************/

struct IFBMemoryStack {
    ifb_address end;
    ifb_u32     size;
    ifb_u32     position;
};

namespace ifb_memory {
    
    IFBMemoryArena*       stack_push_arena_base   (const IFBMemoryHandle memory_handle);
    IFBMemoryLinearArena* stack_push_arena_linear (const IFBMemoryHandle memory_handle);
    IFBMemoryBlockArena*  stack_push_arena_block  (const IFBMemoryHandle memory_handle, const ifb_u32 block_count);
};

/**********************************************************************************/
/* RESERVATION                                                                    */
/**********************************************************************************/

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

    const ifb_b8 reservation_page_commit (IFBMemory* memory_ptr, IFBMemoryPageCommit& page_commit_ref);
};

/**********************************************************************************/
/* ARENA BASE                                                                     */
/**********************************************************************************/

enum IFBMemoryArenaType_ {
    IFBMemoryArenaType_Base   = 0,
    IFBMemoryArenaType_Linear = 1,
    IFBMemoryArenaType_Block  = 2
};

struct IFBMemoryArena {
    IFBMemoryArena*     next;
    IFBMemoryPageCommit page_commit;
    IFBMemoryArenaType  type;    
};

struct IFBMemoryArenaList {
    IFBMemoryArena* first;    
    IFBMemoryArena* last;    
    ifb_u32         count;
};

namespace ifb_memory {

    const ifb_b8 arena_list_add (IFBMemoryArenaList& arena_list_ref, IFBMemoryArena* arena_base_ptr);
};

/**********************************************************************************/
/* ARENA LINEAR                                                                   */
/**********************************************************************************/

struct IFBMemoryLinearArena : IFBMemoryArena {
    ifb_u32 position;
    ifb_u32 save_point;
};

/**********************************************************************************/
/* ARENA BLOCK                                                                    */
/**********************************************************************************/

#define IFB_MEMORY_BLOCK_FLAG_BIT_COUNT 32

struct IFBMemoryBlockArena : IFBMemoryArena  {
    ifb_u32  block_size;
    ifb_u32  block_count;
    ifb_u32  block_flags_count;
    ifb_u32* block_flags_array;
};

struct IFBMemory {
    IFBMemoryStack       stack;
    IFBMemoryReservation reservation;
    IFBMemoryArenaList   arena_list;
};

#endif //IFB_MEMORY_INTERNAL_HPP