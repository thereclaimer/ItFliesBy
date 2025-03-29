#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-core.hpp"

namespace ifb_engine {

    const IFBB8 core_startup_manager_graphics (IFBEngineGraphicsManager* graphics_manager);
    const IFBB8 core_startup_manager_files    (IFBEngineFileManager*     file_manager);
    const IFBB8 core_startup_manager_threads  (IFBEngineThreadManager*   thread_manager);

};

ifb_internal const IFBB8
ifb_engine::core_startup(
    IFBEngineCore* core) {

    IFBB8 result = true;

    result &= ifb_engine::core_startup_manager_graphics (core->graphics);
    result &= ifb_engine::core_startup_manager_files    (core->files);
    result &= ifb_engine::core_startup_manager_threads  (core->threads);

    return(result);
}


inline const IFBB8 
ifb_engine::core_startup_manager_graphics(
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
    result &= ifb_graphics::window_create(graphics_manager->window_handle,args);
    
    return(result);
}

inline const IFBB8 
ifb_engine::core_startup_manager_files(
    IFBEngineFileManager*     file_manager) {

    IFBB8 result = true;


    return(result);
}

inline const IFBB8 
ifb_engine::core_startup_manager_threads(
    IFBEngineThreadManager*   thread_manager) {

    IFBB8 result = true;

    return(result);
}

