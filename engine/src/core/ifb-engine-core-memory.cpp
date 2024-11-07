#pragma once

#include "ifb-engine-internal-core.hpp"
#include "ifb-engine-internal.hpp"

/**********************************************************************************/
/* CORE_MEMORY                                                                    */
/**********************************************************************************/

inline const ifb_b8 
ifb_engine::core_memory_reserve(
    IFBEngineCoreMemory& core_memory_ref) {

    ifb_b8 result = true;

    //create the arena pool
    result &= ifb_engine::memory_arena_create_pool(
        IFB_ENGINE_CORE_MEMORY_ARENA_TAG,
        IFB_ENGINE_CORE_MEMORY_ARENA_SIZE_KILOBYTES,
        IFB_ENGINE_CORE_MEMORY_ARENA_COUNT,
        core_memory_ref.arena_pool);

    //create the arenas
    result &= ifb_engine::memory_arena_commit(core_memory_ref.arena_pool, core_memory_ref.arenas.system);
    result &= ifb_engine::memory_arena_commit(core_memory_ref.arena_pool, core_memory_ref.arenas.frame);

    //set the remaining core memory details
    core_memory_ref.w_str_size_max = IFB_ENGINE_CORE_MEMORY_CSTRING_MAX_SIZE;
    core_memory_ref.c_str_size_max = IFB_ENGINE_CORE_MEMORY_WSTRING_MAX_SIZE;
    core_memory_ref.arena_size     = IFB_ENGINE_CORE_MEMORY_ARENA_SIZE_KILOBYTES;
    core_memory_ref.arena_count    = IFB_ENGINE_CORE_MEMORY_ARENA_COUNT;

    //we're done
    return(result);
}

/**********************************************************************************/
/* SYSTEM ARENA                                                                   */
/**********************************************************************************/


/**********************************************************************************/
/* FRAME ARENA                                                                    */
/**********************************************************************************/


inline const ifb_memory ifb_engine::core_memory_frame_arena_push         (const ifb_size size);
inline const ifb_memory ifb_engine::core_memory_frame_arena_push_aligned (const ifb_size size, const ifb_size alignment);

inline const ifb_memory ifb_engine::core_memory_frame_arena_push         (IFBEngineCoreMemory& core_memory_ref, const ifb_size size);
inline const ifb_memory ifb_engine::core_memory_frame_arena_push_aligned (IFBEngineCoreMemory& core_memory_ref, const ifb_size size, const ifb_size alignment);

inline const ifb_cstr   ifb_engine::core_memory_frame_arena_push_cstring (const ifb_cstr string);
