#ifndef IFB_ENGINE_INTERNAL_CORE_HPP
#define IFB_ENGINE_INTERNAL_CORE_HPP

#include <ifb-memory.hpp>

#include "ifb-engine.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

//core
struct IFBEngineCore;

struct IFBEngineCoreMemoryStack;
struct IFBEngineCoreMemorySubStack;
struct IFBEngineCoreMemoryReservation;
struct IFBEngineCoreMemory;

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

#define IFB_ENGINE_CORE_MEMORY_ARENA_SIZE ifb_macro_size_kilobytes(64) 

struct IFBEngineCoreMemoryStack {
    IFBByte* data;
    IFBU32   size;
};

struct IFBEngineCoreMemoryReservation {
    IFBMemoryReservation* ptr_reservation; 
    IFBU32                size_arena;
};

struct IFBEngineCoreMemory {
    IFBMemoryContext*              ptr_memory_context;
    IFBEngineCoreMemoryStack       stack;
    IFBEngineCoreMemoryReservation reservation; 
};

namespace ifb_engine {

    //reservation
    const IFBB8       core_memory_reserve_platform_memory (IFBEngineCore* core_ptr, const IFBU64 size);
    const IFBB8       core_memory_release_platform_memory (IFBEngineCore* core_ptr);

    //stack
    const IFBPtr      core_memory_commit_bytes_absolute   (IFBEngineCore* core_ptr, const IFBU32 size, const IFBU32 alignment = 0);
    const IFBU32      core_memory_commit_bytes_relative   (IFBEngineCore* core_ptr, const IFBU32 size, const IFBU32 alignment = 0);

    //arenas
    IFBMemoryArena*   core_memory_commit_arena            (IFBEngineCore* core_ptr);           
};

/**********************************************************************************/
/* CORE                                                                           */
/**********************************************************************************/

struct IFBEngineCore {
    IFBSystemInfo       system_info;
    IFBEngineCoreMemory memory; 
};

namespace ifb_engine {

    IFBEngineCore*
    core_create(
        const IFBByte* core_stack_memory_ptr,
        const IFBU32   core_stack_memory_size,
        const IFBU64   core_reserved_memory_size);
    
    const IFBB8
    core_destroy(
        IFBEngineCore* core_ptr);
};

/**********************************************************************************/
/* MACROS                                                                         */
/**********************************************************************************/


#endif //IFB_ENGINE_INTERNAL_CORE_HPP