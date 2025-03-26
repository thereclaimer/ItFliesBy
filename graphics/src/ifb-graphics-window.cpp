#pragma once

#include "ifb-graphics.hpp"

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

const IFBU32
ifb_graphics::window_memory_size(
    IFBVoid) {

    const IFBU32 size_window = ifb_macro_align_size_struct(IFBWindow); 
    const IFBU32 size_title  = IFB_WINDOW_TITLE_LENGTH_MAX;
    const IFBU32 size_total  = size_window + size_title;

    return(size_total);
}

IFBWindow* 
ifb_graphics::window_memory_initialize(
    const IFBPtr memory) {

    ifb_macro_assert(memory);

    const IFBAddr start_window = (IFBAddr)memory;
    const IFBAddr start_title  = start_window + ifb_macro_align_size_struct(IFBWindow);

    IFBWindow* window = (IFBWindow*)start_window;
    window->title     = (IFBChar*)start_title;

    return(window);
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

const IFBB8
ifb_graphics::window_context_gl_create(
    IFBWindow* ptr_window) {

    //sanity check
    ifb_macro_assert(ptr_window);

    //create the window
    IFBB8 result = ifb_platform::window_create(
        ptr_window->title,
        ptr_window->dimensions.width,
        ptr_window->dimensions.height,
        ptr_window->position.x,
        ptr_window->position.y);


    //create opengl and imgui contexts
    IFBGraphicsContexts& contexts_ref = ptr_window->graphics_contexts; 
    contexts_ref.opengl = ifb_platform::window_opengl_init();
    contexts_ref.imgui  = ifb_platform::window_imgui_init();

    //make sure they are valid
    result &= (contexts_ref.opengl != NULL);
    result &= (contexts_ref.imgui  != NULL);

    //we're done
    return(result);
}