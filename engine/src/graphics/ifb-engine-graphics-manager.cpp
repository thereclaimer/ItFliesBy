#pragma once

#include "ifb-engine-internal-graphics.hpp"

inline const IFBB8 
ifb_engine::graphics_manager_initialize(
    IFBEngineGraphicsManager* ptr_graphics_manager,
    IFBEngineCore*            ptr_core) {

    //sanity check
    ifb_macro_assert(ptr_graphics_manager);
    ifb_macro_assert(ptr_core);

    //commit arena
    const IFBHNDArena arena_handle = ifb_engine::core_memory_commit_arena(ptr_core);

    
    //initialize the manager
    ptr_graphics_manager->ptr_core = ptr_core;
    ptr_graphics_manager->arena    = arena_handle;

    //we're done
    return(true);
}