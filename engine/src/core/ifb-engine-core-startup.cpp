#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-core.hpp"

namespace ifb::engine {

    const b8 core_startup_graphics (engine_core_graphics_t* graphics_manager);
    const b8 core_startup_files    (engine_core_files_t*     file_manager);
    const b8 core_startup_threads  (engine_core_threads_t*   thread_manager);
};

ifb_internal const b8
engine::core_startup(
    engine_core_t* core) {

    b8 result = true;

    result &= engine::core_startup_graphics (core->graphics);
    result &= engine::core_startup_files    (core->files);
    result &= engine::core_startup_threads  (core->threads);

    return(result);
}


inline const b8 
engine::core_startup_graphics(
    engine_core_graphics_t* graphics_manager) {

    b8 result = true;

    result &= engine::core_graphics_create_and_show_window(graphics_manager);
    
    return(result);
}

inline const b8 
engine::core_startup_files(
    engine_core_files_t*     file_manager) {

    b8 result = true;


    return(result);
}

inline const b8 
engine::core_startup_threads(
    engine_core_threads_t*   thread_manager) {

    b8 result = true;

    return(result);
}

