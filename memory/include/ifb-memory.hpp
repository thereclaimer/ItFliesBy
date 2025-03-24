#ifndef IFB_MEMORY_HPP
#define IFB_MEMORY_HPP

#include <ifb.hpp>
#include <ifb-platform.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

typedef IFBAddr  IFBMEM64;
typedef IFBU32   IFBMEM32;

typedef IFBMEM64 IFBMEM64Stack;
typedef IFBMEM32 IFBMEM32Manager;
typedef IFBMEM32 IFBMEM32Arena;

#define IFB_MEMORY_INVALID_VALUE 0xFFFFFFFF

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

namespace ifb_memory {

    const IFBMEM64Stack
    stack_create(
        const IFBByte* stack_memory,
        const IFBU32   stack_size);

    const IFBU32 stack_push_bytes_relative (const IFBMEM64Stack stack_id, const IFBU32 size, const IFBU32 alignment = 0);
    const IFBPtr stack_push_bytes_absolute (const IFBMEM64Stack stack_id, const IFBU32 size, const IFBU32 alignment = 0);
    const IFBB8  stack_pull_bytes          (const IFBMEM64Stack stack_id, const IFBU32 size, const IFBU32 alignment = 0);
    const IFBPtr stack_get_pointer         (const IFBMEM64Stack stack_id, const IFBU32 offset);
};

/**********************************************************************************/
/* MEMORY MANAGER                                                                 */
/**********************************************************************************/

namespace ifb_memory {

    const IFBMEM32Manager
    manager_create(
        const IFBMEM64Stack memory_stack,
        const IFBU64        memory_size_reservation,
        const IFBU32        memory_size_arena);
    
    const IFBB8
    manager_destroy(
        const IFBMEM64Stack   memory_stack,
        const IFBMEM32Manager memory_manager);
};

/**********************************************************************************/
/* ARENA                                                                          */
/**********************************************************************************/

struct IFBMemoryArenaContext {
    struct {
        IFBMEM64Stack   stack;
        IFBMEM32Manager manager;
        IFBMEM32Arena   arena;
    } ids;
    
    union {
        IFBPtr absolute_pointer;
        IFBU32 relative_offset;
    } memory;
    
    union {
        IFBU32 size;
        IFBU32 offset;
    } input;
};

namespace ifb_memory {

    //commit/decommit
    const IFBB8 arena_commit               (IFBMemoryArenaContext* arena_context);
    const IFBB8 arena_decommit             (IFBMemoryArenaContext* arena_context);

    //operations
    const IFBB8  arena_reset               (IFBMemoryArenaContext* arena_context);
    const IFBU32 arena_push_bytes_relative (IFBMemoryArenaContext* arena_context);
    const IFBPtr arena_push_bytes_absolute (IFBMemoryArenaContext* arena_context);
    const IFBB8  arena_pull_bytes          (IFBMemoryArenaContext* arena_context);
    const IFBPtr arena_get_pointer         (IFBMemoryArenaContext* arena_context);
};

/**********************************************************************************/
/* UTILITIES                                                                      */
/**********************************************************************************/

namespace ifb_memory {

    const IFBPtr get_pointer(const IFBAddr start, const IFBU32 offset);
};

inline const IFBPtr
ifb_memory::get_pointer(
    const IFBAddr start,
    const IFBU32  offset) {

    const IFBAddr address = start + offset;
    const IFBPtr  pointer = (IFBPtr)address;

    return(pointer);
}

#endif //IFB_MEMORY_HPP