#pragma once

#include "ifb-graphics.hpp"
#include "ifb-graphics-internal.cpp"

using namespace ifb;

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

const u32
graphics::window_memory_size(
    const u32 window_title_length) {

    const u32 size_window   = ifb_macro_align_size_struct(graphics_window_t); 
    const u32 size_title    = window_title_length;
    const u32 size_platform = platform::window_size();
    
    const u32 size_total = 
        size_window + 
        size_title  +
        size_platform;

    return(size_total);
}

graphics_window_t* 
graphics::window_memory_initialize(
    const memory_t& memory) {

    ifb_macro_assert(memory.start);
    ifb_macro_assert(memory.size);

    //zero the memory
    memory::zero_buffer(memory);

    //calculate addresses
    const addr start_window = memory.start;
    const addr start_title  = start_window + ifb_macro_align_size_struct(graphics_window_t);

    //cast pointers
    graphics_window_t* window = (graphics_window_t*)start_window;
    window->title         =          (utf8*)start_title;

    //we're done
    return(window);
}

const b8
graphics::window_create(
    graphics_window_t*            window,
    const graphics_window_args_t& args) {
    
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
    const b8 window_created = platform::window_create(window);
    
    //we're done
    return(window_created);
}

const b8 
graphics::window_show(
    graphics_window_t* window) {
    
    ifb_macro_assert(window);

    //tell the platform to show the window
    //the platform should set the flag
    b8 is_visible = true;
    is_visible &= platform::window_show(window);
    is_visible &= ifb_macro_bit_test(platform_window_flags_e_visible, window->flags);
    
    //we're done
    return(is_visible);
}

const b8 
graphics::window_process_events(
    graphics_window_t* ptr_window) {

    //start the frame
    const b8 result = platform::window_process_events(ptr_window);

    return(result);
}

const b8 
graphics::window_swap_buffers(
    graphics_window_t* ptr_window) {

    //start the frame
    const b8 result = platform::window_swap_buffers(ptr_window);

    return(result);
}

platform_window_flags_t
graphics::window_get_flags(
    graphics_window_t* ptr_window) {

    const platform_window_flags_t flags = ptr_window->flags;

    return(flags);
}