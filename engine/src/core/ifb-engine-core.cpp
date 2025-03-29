#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-core.hpp"

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