#pragma once

#include "ifb-graphics.hpp"
#include "ifb-graphics-internal.cpp"

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

const ifb::u32
ifb_graphics::window_memory_size(
    const ifb::u32 window_title_length) {

    const ifb::u32 size_window   = ifb_macro_align_size_struct(IFBGraphicsWindow); 
    const ifb::u32 size_title    = window_title_length;
    const ifb::u32 size_platform = ifb_platform::window_size();
    
    const ifb::u32 size_total = 
        size_window + 
        size_title  +
        size_platform;

    return(size_total);
}

IFBGraphicsWindow* 
ifb_graphics::window_memory_initialize(
    const IFBMemory& memory) {

    ifb_macro_assert(memory.start);
    ifb_macro_assert(memory.size);

    //zero the memory
    ifb_memory::zero_buffer(memory);

    //calculate addresses
    const ifb::addr start_window = memory.start;
    const ifb::addr start_title  = start_window + ifb_macro_align_size_struct(IFBGraphicsWindow);

    //cast pointers
    IFBGraphicsWindow* window = (IFBGraphicsWindow*)start_window;
    window->title             =           (ifb::utf8*)start_title;

    //we're done
    return(window);
}

const ifb::b8
ifb_graphics::window_create(
          IFBGraphicsWindow*     window,
    const IFBGraphicsWindowArgs& args) {
    
    ifb_macro_assert(window);
    ifb_macro_assert(args.title);
    ifb_macro_assert(args.title_length);

    //copy the window title
    strcpy_s(
        window->title,
        args.title_length,
        args.title);

    //set the properties
    window->dims = args.dims;
    window->pos  = args.pos;

    //tell the platform to create the window
    const ifb::b8 window_created = ifb_platform::window_create(window);
    
    //we're done
    return(window_created);
}

const ifb::b8 
ifb_graphics::window_show(
    IFBGraphicsWindow* ptr_window) {
    
    ifb_macro_assert(ptr_window);

    //tell the platform to show the window
    //the platform should set the flag
    ifb::b8 is_visible = true;
    is_visible &= ifb_platform::window_show(ptr_window);
    is_visible &= ifb_macro_bit_test(IFBPlatformWindowFlags_Visible, ptr_window->flags);
    
    //we're done
    return(is_visible);
}

const ifb::b8 
ifb_graphics::window_process_events(
    IFBGraphicsWindow* ptr_window) {

    //start the frame
    const ifb::b8 result = ifb_platform::window_process_events(ptr_window);

    return(result);
}

const ifb::b8 
ifb_graphics::window_swap_buffers(
    IFBGraphicsWindow* ptr_window) {

    //start the frame
    const ifb::b8 result = ifb_platform::window_swap_buffers(ptr_window);

    return(result);
}

IFBPlatformWindowFlags
ifb_graphics::window_get_flags(
    IFBGraphicsWindow* ptr_window) {

    const IFBPlatformWindowFlags flags = ptr_window->flags;

    return(flags);
}