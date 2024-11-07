#pragma once

#include "ifb-engine-internal-tools.hpp"

inline const ifb_b8 
ifb_engine_tools::memory_reserve(
    IFBEngineCoreMemory&         in_memory_core_ref,
    IFBEngineToolsMemory&       out_memory_tools_ref) {

    ifb_b8 result = true;

    result &= ifb_engine::memory_arena_create_pool(
        IFB_ENGINE_TOOLS_MEMORY_ARENA_POOL_NAME,
        IFB_ENGINE_TOOLS_MEMORY_ARENA_SIZE,
        IFB_ENGINE_TOOLS_MEMORY_ARENA_COUNT,
        out_memory_tools_ref.tools_arena_pool_handle);

    //we're done
    return(result);    
}