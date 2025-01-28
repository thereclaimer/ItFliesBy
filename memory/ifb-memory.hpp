#ifndef IFB_MEMORY_HPP
#define IFB_MEMORY_HPP

#include <ifb.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBMemoryManager;
struct IFBMemoryStack;
struct IFBMemoryStackIndex;
struct IFBMemoryReservation;
struct IFBMemoryArena;
struct IFBMemoryStackAllocator;
struct IFBMemoryBlockAllocator;

/**********************************************************************************/
/* GLOBAL STACK                                                                   */
/**********************************************************************************/

#define IFB_MEMORY_GLOBAL_STACK_SIZE          ifb_macro_size_kilobytes(64)
#define IFB_MEMORY_GLOBAL_STACK_INDEX_INVALID IFB_MEMORY_GLOBAL_STACK_SIZE 


struct IFBMemoryStackIndex {
    ifb_u32 value;
};

struct IFBMemoryStack {
    ifb_byte byte_array [IFB_MEMORY_GLOBAL_STACK_SIZE];
    ifb_u32  size;
    ifb_u32  position;
};

namespace ifb_memory {

    const IFBMemoryStackIndex global_stack_push         (IFBMemoryManager* memory_manager_ptr, ifb_u32 size);
    const IFBMemoryStackIndex global_stack_push_aligned (IFBMemoryManager* memory_manager_ptr, ifb_u32 size, ifb_u32 alignment);
    const ifb_ptr             global_stack_get_pointer  (IFBMemoryManager* memory_manager_ptr, const IFBMemoryStackIndex stack_index);
};

/**********************************************************************************/
/* MEMORY MANAGER                                                                    */
/**********************************************************************************/

struct IFBMemoryManager {
    IFBPlatformMemoryApi* platform_memory_api;
    IFBMemoryStack        stack;
    IFBMemoryReservation  reservation;
    IFBMemoryArenaId      first_arena;
};

namespace ifb_memory {

    const ifb_b8
    memory_manager_create(
        IFBMemoryManager*     memory_manager_ptr,
        IFBPlatformMemoryApi* platform_memory_api_ptr);
    
    const ifb_b8
    memory_manager_destroy(
        IFBMemoryManager* memory_manager_ptr);
};

/**********************************************************************************/
/* RESERVATION                                                                    */
/**********************************************************************************/

struct IFBMemoryReservation {
    ifb_address start;
    ifb_u64     size;
    ifb_u32     page_size;
    ifb_u32     pages_total;
    ifb_u32     pages_committed;
    ifb_u32     allocation_granularity;
};

namespace ifb_memory {

    const ifb_b8
    memory_reserve(
              IFBMemoryManager* memory_manager_ptr,
        const ifb_u64           size,
        const ifb_u32           page_size,
        const ifb_u32           allocation_granularity);
    
    const ifb_b8 memory_release(IFBMemoryManager* memory_manager_ptr);
};

/**********************************************************************************/
/* ARENA                                                                          */
/**********************************************************************************/

struct IFBMemoryArenaId : IFBMemoryStackIndex { };

struct IFBMemoryArena {
    IFBMemoryArenaId next;
    IFBMemoryArenaId id;
    ifb_u32          page_count;
    ifb_u32          page_number;
};

namespace ifb_memory {

    const IFBMemoryArenaId
    memory_arena_commit(
              IFBMemoryManager* memory_manager_ptr,
        const ifb_u32           arena_size_minimum);

    const ifb_u32 memory_arena_get_page_count  (IFBMemoryManager* memory_manager_ptr, const IFBMemoryArenaId arena_id);
    const ifb_u32 memory_arena_get_page_number (IFBMemoryManager* memory_manager_ptr, const IFBMemoryArenaId arena_id);    
    const ifb_u32 memory_arena_get_size        (IFBMemoryManager* memory_manager_ptr, const IFBMemoryArenaId arena_id);    
};

#endif //IFB_MEMORY_HPP