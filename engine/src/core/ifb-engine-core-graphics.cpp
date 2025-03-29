#pragma once

#include "ifb-engine-core.hpp"

inline const IFBB8 
ifb_engine::graphics_manager_create_and_show_window(
    IFBEngineGraphicsManager* graphics_manager) {

    IFBB8 result = true;

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

