#ifndef IFB_MEMORY_HPP
#define IFB_MEMORY_HPP

#include <ifb.hpp>
#include <ifb-platform.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBMemoryStack;
struct IFBMemoryManagerArgs;
struct IFBMemoryManager;
struct IFBMemoryContext;
struct IFBMemoryContextStack;
struct IFBMemoryArena;
struct IFBMemoryReservation;
struct IFBMemoryBlock;


struct IFBMemoryBlock {
    IFBAddr start;
    IFBU64  size;
};

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

#define IFB_MEMORY_STACK_INVALID_OFFSET 0xFFFFFFFF

namespace ifb_memory {

    IFBMemoryStack* stack_create                (const IFBByte* stack_memory, const IFBU32 stack_size);

    const IFBU32    stack_push_bytes_relative (IFBMemoryStack* stack, const IFBU32 size, const IFBU32 alignment = 0);
    const IFBPtr    stack_push_bytes_absolute (IFBMemoryStack* stack, const IFBU32 size, const IFBU32 alignment = 0);
    const IFBB8     stack_pull_bytes          (IFBMemoryStack* stack, const IFBU32 size, const IFBU32 alignment = 0);
    const IFBPtr    stack_get_pointer         (IFBMemoryStack* stack, const IFBU32 offset);
};

/**********************************************************************************/
/* MEMORY MANAGER                                                                 */
/**********************************************************************************/

struct IFBHNDMemoryArena : IFBHND32 { };

struct IFBMemoryManagerArgs {
    IFBMemoryStack* stack;    
    IFBU64          size_reservation;
    IFBU64          size_arena;
};

namespace ifb_memory {

    IFBMemoryManager* manager_create  (IFBMemoryManagerArgs* args);
    const IFBB8       manager_destroy (IFBMemoryManager* memory_manager);
};

/**********************************************************************************/
/* ARENA                                                                          */
/**********************************************************************************/

struct IFBMemoryArenaRequest {
    struct {
        IFBMemoryManager* manager;
        IFBHNDMemoryArena arena_handle;
        IFBU32            size;
        IFBU32            alignment;
    } in;
    struct {
        IFBU32            offset;
        IFBPtr            pointer;
    } out;
};

namespace ifb_memory {

    const IFBB8 arena_commit     (IFBMemoryArenaRequest* request);
    const IFBB8 arena_decommit   (IFBMemoryArenaRequest* request);
    const IFBB8 arena_reset      (IFBMemoryArenaRequest* request);
    const IFBB8 arena_push_bytes (IFBMemoryArenaRequest* request);
    const IFBB8 arena_pull_bytes (IFBMemoryArenaRequest* request);
};

#endif //IFB_MEMORY_HPP