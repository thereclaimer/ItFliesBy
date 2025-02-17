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

    //reservation
    const ifb_b8                     core_memory_reserve                 (IFBEngineCore* core_ptr, const ifb_u32 size);
    const ifb_b8                     core_memory_release                 (IFBEngineCore* core_ptr);

    //stack
    const ifb_ptr                    core_memory_stack_commit_absolute   (IFBEngineCore* core_ptr, const ifb_u32 size, const ifb_u32 alignment = 0);
    const ifb_u32                    core_memory_stack_commit_relative   (IFBEngineCore* core_ptr, const ifb_u32 size, const ifb_u32 alignment = 0);

    //arenas
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
        const IFBPlatformApi* platform_api_ptr,
        const ifb_byte*       core_stack_memory_ptr,
        const ifb_u32         core_stack_memory_size);
    
    const ifb_b8
    core_destroy(
        IFBEngineCore* core_ptr);
};

/**********************************************************************************/
/* MACROS                                                                         */
/**********************************************************************************/

#define ifb_engine_macro_core_memory_commit_struct(ptr_core,struct) (struct*)ifb_engine::core_memory_stack_commit_absolute(ptr_core,sizeof(struct),alignof(struct))

#endif //IFB_ENGINE_INTERNAL_CORE_HPP