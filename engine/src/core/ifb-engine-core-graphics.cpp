#pragma once

#include "ifb-engine-core.hpp"
#include "ifb-engine-memory.hpp"

inline const ifb::b8
ifb_engine::graphics_manager_initialize(
    IFBEngineGraphicsManager* graphics_manager,
    IFBEngineMemory*          engine_memory) {

    ifb::b8 result = true;

    //memory for tracking allcoations
    IFBMemory memory;

    //window memory
    memory.size  = ifb_graphics::window_memory_size(IFB_ENGINE_GRAPHICS_WINDOW_TITLE_LENGTH);
    memory.start = ifb_engine::memory_arena_push_bytes_absolute_address(
        engine_memory,
        IFBEngineArena_Core_ManagerGraphics,
        memory.size);

    graphics_manager->window_handle = ifb_graphics::window_memory_initialize(memory);
    result &= (graphics_manager->window_handle != NULL);

    return(result);
}


inline const ifb::b8 
ifb_engine::graphics_manager_create_and_show_window(
    IFBEngineGraphicsManager* graphics_manager) {

    ifb::b8 result = true;

    //window args
    IFBGraphicsWindowArgs args;
    args.title        = ifb_engine::_global_core.window_title;
    args.title_length = ifb_engine::_global_core.window_title_length;
    args.dims.width   = ifb_engine::_global_core.window_init_width; 
    args.dims.height  = ifb_engine::_global_core.window_init_height; 
    args.pos.x        = 0;
    args.pos.y        = 0;

    //create the window
    result &= ifb_graphics::window_create (graphics_manager->window_handle,args);
    result &= ifb_graphics::window_show   (graphics_manager->window_handle);

    //we're done
    return(result);
}

inline const ifb::b8
ifb_engine::graphics_manager_frame_start(
    IFBEngineGraphicsManager* graphics_manager) {

    ifb::b8 result = true;
    
    result &= ifb_graphics::window_process_events(graphics_manager->window_handle);

    return(result);
}

inline const ifb::b8
ifb_engine::graphics_manager_frame_render(
    IFBEngineGraphicsManager* graphics_manager) {

    ifb::b8 result = true;

    result &= ifb_graphics::window_swap_buffers(graphics_manager->window_handle);

    return(result);
}

inline const ifb::b8 
ifb_engine::graphics_manager_window_quit_received(
    IFBEngineGraphicsManager* graphics_manager) {

    IFBPlatformWindowFlags flags         = ifb_graphics::window_get_flags(graphics_manager->window_handle);
    const ifb::b8            quit_received = ifb_platform::window_get_flag_closed(flags);

    return(quit_received);
}
