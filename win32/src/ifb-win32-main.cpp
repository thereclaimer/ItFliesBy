#pragma once

#include "ifb-win32.hpp"

r_internal r_s32 
ifb_win32_main(
    RWin32MainArgs& args) {

    //create the context
    if (!r_win32::context_create(
        args,
        16,
        64 * 1024)) {
        return(-1);
    }

    //create the window
    if (!r_win32::window_create(
        "It Flies By",
        0,0,1920,1080,
        RColorFormat_RGBA,
        RWin32RenderingContextType_None,
        RWin32WindowUseImGui_No)) {

        return(S_FALSE);
    }

    //create the opengl context
    if (!r_win32::rendering_create_opengl_context()) {
        return(S_FALSE);
    }

    //set the clear color
    RColor32Bit color_32 = {0};
    color_32.format = RColorFormat_RGBA;
    color_32.hex    = 0x282828FF;
    r_win32::rendering_set_clear_color(color_32);

    //show the window
    r_win32::window_show();

    //main window loop
    r_b8 running = true;
    while(running) {

        //start a new frame
        running &= r_win32::window_frame_start();
        
        //-----------------------------
        // APPLICATION LOGIC HERE!!
        //-----------------------------

        //render the frame
        running &= r_win32::window_frame_render();
    }

    //destroy the context
    if (!r_win32::context_destroy()) {
        return(S_FALSE);
    }

    //done
    return(S_OK);
}