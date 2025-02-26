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
    ifb_macro_assert(ptr_graphics_manager->ptr_memory);

    // allocate window args
    // we keep them in case we want to reset the window


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

inline const IFBB8 
ifb_engine::graphics_manager_frame_start(
    IFBEngineGraphicsManager* ptr_graphics_manager,
    IFBWindowUpdate*          ptr_window_update) {

    //get the window handle
    const IFBHNDWindow window_handle = ptr_graphics_manager->window;

    //new frame start is successful IF
    IFBB8 result = true; 
    result &= ifb_graphics::window_update      (window_handle,ptr_window_update); // we can update the window AND
    result &= ifb_graphics::window_show        (window_handle);                   // the window is visible AND
    result &= ifb_graphics::window_frame_start (window_handle);                   // the window has started a new frame

    //check for quit event
    ptr_graphics_manager->quit_received = ifb_graphics::window_quit_received(window_handle);
        
    //we're done
    return(result);
}

inline const IFBB8 
ifb_engine::graphics_manager_frame_render(
    IFBEngineGraphicsManager* ptr_graphics_manager) {

    //get the window handle
    const IFBHNDWindow window_handle = ptr_graphics_manager->window;

    //frame render is successful if
    IFBB8 result = true; 
    result &= ifb_graphics::window_show         (window_handle); // the window is visible AND
    result &= ifb_graphics::window_frame_render (window_handle); // the window frame is rendered

    //we're done
    return(result);
}