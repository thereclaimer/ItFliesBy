#pragma once

#include "ifb-graphics.hpp"

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

IFBWindow*
ifb_graphics::window_commit_to_arena_absolute(
    const IFBHNDArena arena_handle) {

    const IFBU32 window_size = ifb_macro_align_size_struct(IFBWindow); 
    IFBWindow*   window_ptr  = (IFBWindow*)ifb_memory::arena_commit_bytes_absolute(
        arena_handle,
        window_size);

    return(window_ptr);
}

const IFBU32
ifb_graphics::window_commit_to_arena_relative(
    const IFBHNDArena arena_handle) {

    const IFBU32 window_size   = ifb_macro_align_size_struct(IFBWindow); 
    const IFBU32 window_offset = ifb_memory::arena_commit_bytes_relative(
        arena_handle,
        window_size);

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
