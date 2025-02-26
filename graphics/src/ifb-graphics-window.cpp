#pragma once

#include "ifb-graphics-internal.hpp"

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

const IFBB8 
ifb_graphics::window_show(
    const IFBHNDWindow window_handle) {

    //get the window
    IFBWindow* ptr_window = ifb_graphics::context_get_window(window_handle);
    
    //if its already visible, we're done
    if (ptr_window->visible) return(true);

    //tell the platform to show the window
    ptr_window->visible = ifb_platform::window_show();

    //we're done
    return(ptr_window->visible);
}

const IFBB8 
ifb_graphics::window_frame_start(
    const IFBHNDWindow window_handle) {
    
    //get the window
    IFBWindow* ptr_window = ifb_graphics::context_get_window(window_handle);

    //start the frame
    const IFBB8 result = ifb_platform::window_frame_start();

    return(result);
}

const IFBB8 
ifb_graphics::window_frame_render(
    const IFBHNDWindow window_handle) {
        
    //get the window
    IFBWindow* ptr_window = ifb_graphics::context_get_window(window_handle);

    //start the frame
    const IFBB8 result = ifb_platform::window_frame_render();

    return(result);
}

const IFBB8
ifb_graphics::window_quit_received(
    const IFBHNDWindow window_handle) {

    //get the window
    IFBWindow* ptr_window = ifb_graphics::context_get_window(window_handle);

    return(ptr_window->quit_received);
}

const IFBB8 
ifb_graphics::window_update(
    const IFBHNDWindow     window_handle,
    const IFBWindowUpdate* ptr_window_update) {
        
    //get the window
    IFBWindow* ptr_window = ifb_graphics::context_get_window(window_handle);
    if (!ptr_window_update) return(false);

    //dimensions
    IFBDimensions& window_dimensions_ref = ptr_window->dimensions;
    window_dimensions_ref.width  = ptr_window_update->dimensions.width;
    window_dimensions_ref.height = ptr_window_update->dimensions.height;

    //position
    IFBPosition& window_position_ref = ptr_window->position;
    window_position_ref.x = ptr_window_update->position.x;
    window_position_ref.y = ptr_window_update->position.y;

    //set quit status
    ptr_window->quit_received = ptr_window_update->quit_received;

    return(true);
}

