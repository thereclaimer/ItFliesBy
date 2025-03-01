#pragma once

#include "ifb-engine-internal-graphics.hpp"

inline const IFBB8
ifb_engine::graphics_manager_initialize(
    IFBEngineGraphicsManager* ptr_graphics_manager,
    IFBEngineCore*            ptr_core) {

    //sanity check
    ifb_macro_assert(ptr_graphics_manager);
    ifb_macro_assert(ptr_core);

    //commit memory
    ptr_graphics_manager->ptr_memory = ifb_engine::graphics_memory_commit(ptr_core);

    //load the window and monitors
    IFBB8 result = true;
    
    // TODO(SAM): for some reason, calling this causes the renderer to
    // fail initialization, causing premature termination

    result &= ifb_engine::graphics_monitors_update_all (ptr_graphics_manager);
    result &= ifb_engine::graphics_window_initialize   (ptr_graphics_manager);

    //we're done
    return(result);
}

inline const IFBB8
ifb_engine::graphics_manager_frame_start(
    IFBEngineGraphicsManager* ptr_graphics_manager) {

    const IFBB8 result = ifb_engine::graphics_window_frame_start(ptr_graphics_manager);

    return(result);
}

inline const IFBB8
ifb_engine::graphics_manager_frame_render(
    IFBEngineGraphicsManager* ptr_graphics_manager) {

    IFBB8 result = ifb_engine::graphics_window_frame_render(ptr_graphics_manager);
    return(result);
}