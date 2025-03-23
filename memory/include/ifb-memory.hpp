#ifndef IFB_MEMORY_HPP
#define IFB_MEMORY_HPP

#include <ifb.hpp>
#include <ifb-platform.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBMemoryStack;
struct IFBMemoryManager;
struct IFBMemoryContext;
struct IFBMemoryContextStack;
struct IFBMemoryArena;
struct IFBMemoryReservation;
struct IFBMemoryBlock;

typedef IFBAddr IFBMemoryStackStart;
typedef IFBU32  IFBMemoryManagerHandle;
typedef IFBU32  IFBMemoryArenaIndex;

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

#define IFB_MEMORY_STACK_INVALID_OFFSET 0xFFFFFFFF

namespace ifb_memory {

    const IFBMemoryStackStart
    stack_create(
        const IFBByte* stack_memory,
        const IFBU32   stack_size);

    const IFBU32 stack_push_bytes_relative (const IFBMemoryStackStart, const IFBU32 size, const IFBU32 alignment = 0);
    const IFBPtr stack_push_bytes_absolute (const IFBMemoryStackStart, const IFBU32 size, const IFBU32 alignment = 0);
    const IFBB8  stack_pull_bytes          (const IFBMemoryStackStart, const IFBU32 size, const IFBU32 alignment = 0);
    const IFBPtr stack_get_pointer         (const IFBMemoryStackStart, const IFBU32 offset);
};

/**********************************************************************************/
/* MEMORY MANAGER                                                                 */
/**********************************************************************************/

namespace ifb_memory {

    const IFBMemoryManagerHandle
    manager_create(
        const IFBMemoryStackStart stack_start,
        const IFBU64              size_reservation,
        const IFBU32              size_arena);
    
    const IFBB8
    manager_destroy(
        const IFBMemoryStackStart    stack_start,
        const IFBMemoryManagerHandle memory_manager_handle);
};

/**********************************************************************************/
/* ARENA                                                                          */
/**********************************************************************************/

#define IFB_MEMORY_ARENA_INDEX_INVALID 0xFFFFFFFF

namespace ifb_memory {

    //commit/decommit
    const IFBMemoryArenaIndex arena_commit              (IFBMemoryManager* memory_manager);
    const IFBB8               arena_decommit            (IFBMemoryManager* memory_manager, const IFBMemoryArenaIndex arena_index);

    //operations
    const IFBB8               arena_reset               (IFBMemoryManager* memory_manager, const IFBMemoryArenaIndex arena_index, const IFBU32 size, const IFBU32 alignment = 0);
    const IFBU32              arena_push_bytes_relative (IFBMemoryManager* memory_manager, const IFBMemoryArenaIndex arena_index, const IFBU32 size, const IFBU32 alignment = 0);
    const IFBPtr              arena_push_bytes_absolute (IFBMemoryManager* memory_manager, const IFBMemoryArenaIndex arena_index, const IFBU32 size, const IFBU32 alignment = 0);
    const IFBB8               arena_pull_bytes          (IFBMemoryManager* memory_manager, const IFBMemoryArenaIndex arena_index, const IFBU32 size, const IFBU32 alignment = 0);
};


struct IFBMemoryBlock {
    IFBAddr start;
    IFBU64  size;
};


#endif //IFB_MEMORY_HPP