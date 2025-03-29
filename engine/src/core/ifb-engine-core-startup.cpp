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

    result &= ifb_engine::graphics_manager_create_and_show_window(graphics_manager);
    
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

