#pragma once

#include "ifb-graphics.hpp"
#include "ifb-graphics-internal.cpp"

using namespace ifb;
namespace pfm = ifb::platform;
namespace gfx = ifb::graphics;
namespace mem = ifb::memory;

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

const u32
gfx::window_memory_size(
    const u32 window_title_length) {

    const u32 size_window   = ifb_macro_align_size_struct(pfm::window_t); 
    const u32 size_title    = window_title_length;
    const u32 size_platform = pfm::window_size();
    
    const u32 size_total = 
        size_window + 
        size_title  +
        size_platform;

    return(size_total);
}

pfm::window_t* 
gfx::window_memory_initialize(
    const memory_t& memory) {

    ifb_macro_assert(memory.start);
    ifb_macro_assert(memory.size);

    //zero the memory
    mem::zero_buffer(memory);

    //calculate addresses
    const addr start_window = memory.start;
    const addr start_title  = start_window + ifb_macro_align_size_struct(pfm::window_t);

    //cast pointers
    pfm::window_t* window = (pfm::window_t*)start_window;
    window->title         =          (utf8*)start_title;

    //we're done
    return(window);
}

const b8
graphics::window_create(
    pfm::window_t*       window,
    const window_args_t& args) {
    
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
    const b8 window_created = pfm::window_create(window);
    
    //we're done
    return(window_created);
}

const b8 
graphics::window_show(
    pfm::window_t* window) {
    
    ifb_macro_assert(window);

    //tell the platform to show the window
    //the platform should set the flag
    b8 is_visible = true;
    is_visible &= pfm::window_show(window);
    is_visible &= ifb_macro_bit_test(pfm::window_flags_e_visible, window->flags);
    
    //we're done
    return(is_visible);
}

const b8 
graphics::window_process_events(
    pfm::window_t* ptr_window) {

    //start the frame
    const b8 result = pfm::window_process_events(ptr_window);

    return(result);
}

const b8 
graphics::window_swap_buffers(
    pfm::window_t* ptr_window) {

    //start the frame
    const b8 result = pfm::window_swap_buffers(ptr_window);

    return(result);
}

pfm::window_flags_t
graphics::window_get_flags(
    pfm::window_t* ptr_window) {

    const pfm::window_flags_t flags = ptr_window->flags;

    return(flags);
}