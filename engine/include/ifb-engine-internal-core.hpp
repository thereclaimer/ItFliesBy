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
struct IFBEngineCoreMemoryReservation;
struct IFBEngineCoreMemory;

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

struct IFBEngineCoreMemoryStack {
    ifb_byte* data;
    ifb_u32   size;
};

struct IFBEngineCoreMemoryReservation {
    ifb_u64                     size;
    IFBMemoryReservationHandle  handle; 
};

struct IFBEngineCoreMemory {
    IFBEngineCoreMemoryStack       stack;
    IFBEngineCoreMemoryReservation reservation; 
};

namespace ifb_engine {

    const ifb_b8                     core_memory_reserve                 (IFBEngineCore* core_ptr, const ifb_u32 size);
    const ifb_b8                     core_memory_release                 (IFBEngineCore* core_ptr, const ifb_u32 size);

    const IFBEngineSingletonHandle   core_memory_singleton_commit        (IFBEngineCore* core_ptr, const ifb_u32 size, const ifb_u32 alignment);
    const ifb_ptr                    core_memory_singleton_load          (IFBEngineCore* core_ptr, const IFBEngineSingletonHandle singleton_handle);

    const IFBMemoryArenaHandle       core_memory_arena_commit_unmanaged  (IFBEngineCore* core_ptr, const ifb_u32 size);
    const IFBMemoryLinearArenaHandle core_memory_arena_commit_linear     (IFBEngineCore* core_ptr, const ifb_u32 size);
    const IFBMemoryBlockArenaHandle  core_memory_arena_commit_block      (IFBEngineCore* core_ptr, const ifb_u32 block_size, const ifb_u32 block_count);
};

/**********************************************************************************/
/* CORE                                                                           */
/**********************************************************************************/

struct IFBEngineCore {
    ifb_u32             stack_offset;
    IFBEngineCoreMemory memory; 
};

namespace ifb_engine {

    IFBEngineCore*
    core_create(
              ifb_byte* core_stack_memory_ptr,
        const ifb_u32   core_stack_memory_size);
    
    const ifb_b8
    core_destroy(
        IFBEngineCore* core_ptr);
};

#endif //IFB_ENGINE_INTERNAL_CORE_HPP