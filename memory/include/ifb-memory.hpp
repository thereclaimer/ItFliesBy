#ifndef IFB_MEMORY_HPP
#define IFB_MEMORY_HPP

#include <ifb.hpp>
#include <ifb-platform.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBMemoryStack;
struct IFBMemoryArena;
struct IFBMemoryBlock;

typedef IFBAddr IFBMemoryHandleStack;
typedef IFBU32  IFBMemoryHandleManager;
typedef IFBU32  IFBMemoryHandleArena;

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

#define IFB_MEMORY_STACK_INVALID_OFFSET 0xFFFFFFFF

namespace ifb_memory {

    const IFBMemoryHandleStack
    stack_create(
        const IFBByte* stack_memory,
        const IFBU32   stack_size);

    const IFBU32 stack_push_bytes_relative (const IFBMemoryHandleStack, const IFBU32 size, const IFBU32 alignment = 0);
    const IFBPtr stack_push_bytes_absolute (const IFBMemoryHandleStack, const IFBU32 size, const IFBU32 alignment = 0);
    const IFBB8  stack_pull_bytes          (const IFBMemoryHandleStack, const IFBU32 size, const IFBU32 alignment = 0);
    const IFBPtr stack_get_pointer         (const IFBMemoryHandleStack, const IFBU32 offset);
};

/**********************************************************************************/
/* MEMORY MANAGER                                                                 */
/**********************************************************************************/

struct IFBMemoryManager {
    IFBAddr handle_stack;
    IFBU32  handle_manager;
    IFBByte padding[4];
};

namespace ifb_memory {

    const IFBB8
    manager_create(
              IFBMemoryManager* memory_manager,
        const IFBU64            size_reservation,
        const IFBU32            size_arena);
    
    const IFBB8
    manager_destroy(
        const IFBMemoryManager* memory_manager);
};

/**********************************************************************************/
/* ARENA                                                                          */
/**********************************************************************************/

#define IFB_MEMORY_ARENA_INDEX_INVALID 0xFFFFFFFF

struct IFBMemoryArena {
    IFBAddr handle_stack;
    IFBU32  handle_manager;
    IFBU32  handle_arena;
};

namespace ifb_memory {

    //commit/decommit
    const IFBB8  arena_commit              (IFBMemoryArena* arena);
    const IFBB8  arena_decommit            (IFBMemoryArena* arena);

    //operations
    const IFBB8  arena_reset               (const IFBMemoryArena* arena);
    const IFBU32 arena_push_bytes_relative (const IFBMemoryArena* arena, const IFBU32 size, const IFBU32 alignment = 0);
    const IFBPtr arena_push_bytes_absolute (const IFBMemoryArena* arena, const IFBU32 size, const IFBU32 alignment = 0);
    const IFBB8  arena_pull_bytes          (const IFBMemoryArena* arena, const IFBU32 size, const IFBU32 alignment = 0);
};


struct IFBMemoryBlock {
    IFBAddr start;
    IFBU64  size;
};


#endif //IFB_MEMORY_HPP