#pragma once

#include "ifb-graphics-internal.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

/**********************************************************************************/
/* RESERVE/RELEASE                                                                */
/**********************************************************************************/


const IFBGraphicsWindowHandle
ifb_graphics::window_reserve(
    ifb_void) {

    //first, search for a free window 
    IFBGraphicsWindowHandle window_handle;

    //get the stack
    IFBStack* ptr_stack = ifb_graphics::context_get_stack();

    //calculate the window size
    const ifb_u32 window_size = ifb_macro_align_size_struct(IFBGraphicsWindow);

    //push a window on the stack
    window_handle.offset = ifb_stack::push_relative(ptr_stack,window_size);

    //we're done
}

const ifb_b8
ifb_graphics::window_release(
    const IFBGraphicsWindowHandle) {

}



/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

// const IFBGraphicsWindowHandle
// ifb_graphics::window_create(
//     ) {

// }

const ifb_b8 
ifb_graphics::window_show(
    const IFBGraphicsWindowHandle window_handle) {

}

const ifb_b8 
ifb_graphics::window_frame_start(
    const IFBGraphicsWindowHandle window_handle) {

}

const ifb_b8 
ifb_graphics::window_frame_render(
    const IFBGraphicsWindowHandle window_handle) {

}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/
