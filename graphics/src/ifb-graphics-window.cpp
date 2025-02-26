#pragma once

#include "ifb-graphics.hpp"

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

IFBWindow*
ifb_graphics::window_commit_to_arena_absolute(
    const IFBHNDArena arena_handle) {

    IFBWindow* ptr_window = (IFBWindow*)ifb_memory::arena_commit_bytes_absolute(
        arena_handle,
        sizeof(IFBWindow),
        alignof(IFBWindow));

    return(ptr_window);
}

const IFBU32
ifb_graphics::window_commit_to_arena_relative(
    const IFBHNDArena arena_handle) {

    const IFBU32 window_offset = ifb_memory::arena_commit_bytes_relative(
        arena_handle,
        sizeof(IFBWindow),
        alignof(IFBWindow));

    return(window_offset);
}

const IFBB8 
ifb_graphics::window_show(
    IFBWindow* ptr_window) {
    
    //if its already visible, we're done
    if (ptr_window->visible) return(true);

    //tell the platform to show the window
    ptr_window->visible = ifb_platform::window_show();

    //we're done
    return(ptr_window->visible);
}

const IFBB8 
ifb_graphics::window_frame_start(
    IFBWindow* ptr_window) {

    //start the frame
    const IFBB8 result = ifb_platform::window_frame_start();

    return(result);
}

const IFBB8 
ifb_graphics::window_frame_render(
    IFBWindow* ptr_window) {

    //start the frame
    const IFBB8 result = ifb_platform::window_frame_render();

    return(result);
}