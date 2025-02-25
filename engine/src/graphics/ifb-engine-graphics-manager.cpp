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
    
    //initialize a graphics context
    const IFBB8 context_created = ifb_graphics::context_create(
        arena_handle,
        IFBColorFormat_RGBA);

    // allocate window args
    // we keep them in case we want to reset the window
    const IFBU32   size_title       = ifb_macro_array_size(IFBChar, 255); 
    const IFBU32   size_window_args = ifb_macro_align_size_struct(IFBWindowArgs); 
    const IFBChar* title_str        = "It Flies By (DEBUG)"; 

    IFBWindowArgs* ptr_window_args  = (IFBWindowArgs*)ifb_memory::arena_commit_bytes_absolute(arena_handle,size_window_args);  
    IFBChar*       ptr_window_title =       (IFBChar*)ifb_memory::arena_commit_bytes_absolute(arena_handle,size_title); 

    const IFBB8 window_args_valid = 
        ptr_window_args  != NULL && 
        ptr_window_title != NULL;

    if (!window_args_valid) return(false);

    //copy the window title 
    memcpy_s(
        ptr_window_title, 255,
        title_str,        255);

    ptr_window_args->title = ptr_window_title;

    //set the window dimensions
    ptr_window_args->dimensions.width  = 800;
    ptr_window_args->dimensions.height = 600;
    ptr_window_args->position.x        = 0;
    ptr_window_args->position.y        = 0;

    //commit a window to the graphics manager
    IFBHNDWindow window_handle = ifb_graphics::context_commit_window(ptr_window_args);

    //initialize the manager
    ptr_graphics_manager->ptr_core = ptr_core;
    ptr_graphics_manager->arena    = arena_handle;
    ptr_graphics_manager->window   = window_handle;

    //show the window
    const IFBB8 result = ifb_graphics::window_show(window_handle);

    //we're done
    return(result);
}