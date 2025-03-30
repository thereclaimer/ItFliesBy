#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-core.hpp"
#include "ifb-engine-memory.hpp"

ifb_internal const IFBB8
ifb_engine::core_initialize(
    IFBEngineCore* core) {

    IFBB8 result = true;
    
    result &= ifb_engine::graphics_manager_initialize(core->graphics, core->memory);

    return(result);
}

inline const IFBB8
ifb_engine::core_frame_start(
    IFBEngineCore* core) {

    IFBB8 result = true;

    result &= ifb_engine::graphics_manager_frame_start(core->graphics);

    return(result);
}

inline const IFBB8
ifb_engine::core_frame_render(
    IFBEngineCore* core) {

    IFBB8 result = true;

    result &= ifb_engine::graphics_manager_frame_render(core->graphics);

    return(result);
}

inline const IFBB8 
ifb_engine::core_should_quit(
    IFBEngineCore* core) {

    IFBB8 result = true;

    result &= ifb_engine::graphics_manager_window_quit_received(core->graphics);

    return(result);
}
