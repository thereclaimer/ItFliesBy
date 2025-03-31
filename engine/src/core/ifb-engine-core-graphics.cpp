#pragma once

#include "ifb-engine-core.hpp"
#include "ifb-engine-memory.hpp"

inline const ifb::b8
engine::core_graphics_initialize(
    engine_core_graphics_t* graphics,
    engine_memory_t*        engine_memory) {

    ifb::b8 result = true;

    //memory for tracking allcoations
    memory_t memory;

    //window memory
    memory.size  = graphics::window_memory_size(IFB_ENGINE_GRAPHICS_WINDOW_TITLE_LENGTH);
    memory.start = engine::memory_arena_push_bytes_absolute_address(
        engine_memory,
        engine_memory_arena_e_core_graphics,
        memory.size);

    graphics->window_handle = graphics::window_memory_initialize(memory);
    result &= (graphics->window_handle != NULL);

    return(result);
}


inline const ifb::b8 
engine::core_graphics_create_and_show_window(
    engine_core_graphics_t* graphics) {

    ifb::b8 result = true;

    //window args
    graphics_window_args_t args;
    args.title        = engine::_globals_core.window_title;
    args.title_length = engine::_globals_core.window_title_length;
    args.dims.width   = engine::_globals_core.window_init_width; 
    args.dims.height  = engine::_globals_core.window_init_height; 
    args.pos.x        = 0;
    args.pos.y        = 0;

    //create the window
    result &= graphics::window_create (graphics->window_handle,args);
    result &= graphics::window_show   (graphics->window_handle);

    //we're done
    return(result);
}

inline const b8
engine::core_graphics_frame_start(
    engine_core_graphics_t* graphics) {

    ifb::b8 result = true;
    
    result &= graphics::window_process_events(graphics->window_handle);

    return(result);
}

inline const b8
engine::core_graphics_frame_render(
    engine_core_graphics_t* graphics) {

    b8 result = true;

    result &= graphics::window_swap_buffers(graphics->window_handle);

    return(result);
}

inline const b8 
engine::core_graphics_window_quit_received(
    engine_core_graphics_t* graphics) {

    platform_window_flags_t flags         = graphics::window_get_flags(graphics->window_handle);
    const b8                quit_received = platform::window_get_flag_closed(flags);

    return(quit_received);
}
