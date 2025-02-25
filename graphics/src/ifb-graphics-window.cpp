#pragma once

#include "ifb-graphics-internal.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

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

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/
