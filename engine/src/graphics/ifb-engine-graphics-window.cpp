#pragma once

#include "ifb-engine-internal-graphics.hpp"

inline const IFBB8 
ifb_engine::graphics_window_start_new_frame(
    IFBEngineGraphicsManager* ptr_graphics_manager) {

    //get the window handle
    const IFBHNDWindow window_handle = ptr_graphics_manager->window;

    //make sure the window is visible, and start a new frame
    IFBB8 result = true; 
    result &= ifb_graphics::window_show(window_handle);
    result &= ifb_graphics::window_frame_start(window_handle);

    //we're done
    return(result);
}

inline const IFBB8 
ifb_engine::graphics_window_render_frame(
    IFBEngineGraphicsManager* ptr_graphics_manager) {

    //get the window handle
    const IFBHNDWindow window_handle = ptr_graphics_manager->window;

    //make sure the window is visible, and start a new frame
    IFBB8 result = true; 
    result &= ifb_graphics::window_show(window_handle);
    result &= ifb_graphics::window_frame_render(window_handle);

    //we're done
    return(result);
}