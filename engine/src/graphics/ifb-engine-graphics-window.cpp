#pragma once

#include "ifb-engine-internal-graphics.hpp"

inline const IFBB8 
ifb_engine::graphics_window_frame_start(
    IFBEngineGraphicsManager* ptr_graphics_manager,
    IFBWindowUpdate*          ptr_window_update) {

    //get the window handle
    const IFBHNDWindow window_handle = ptr_graphics_manager->window;

    //new frame start is successful IF
    IFBB8 result = true; 
    result &= ifb_graphics::window_update      (window_handle,ptr_window_update); // we can update the window AND
    result &= ifb_graphics::window_show        (window_handle);                   // the window is visible AND
    result &= ifb_graphics::window_frame_start (window_handle);                   // the window has started a new frame

    //we're done
    return(result);
}

inline const IFBB8 
ifb_engine::graphics_window_frame_render(
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