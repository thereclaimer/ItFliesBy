#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-core.hpp"
#include "ifb-engine-memory.hpp"

ifb_internal const b8
engine::core_initialize(
    engine_core_t* core) {

    b8 result = true;
    
    result &= engine::core_graphics_initialize(core->graphics, core->memory);

    return(result);
}

inline const b8
engine::core_frame_start(
    engine_core_t* core) {

    b8 result = true;

    result &= engine::core_graphics_frame_start(core->graphics);

    return(result);
}

inline const b8
engine::core_frame_render(
    engine_core_t* core) {

    b8 result = true;

    result &= engine::core_graphics_frame_render(core->graphics);

    return(result);
}

inline const b8 
engine::core_should_quit(
    engine_core_t* core) {

    b8 result = true;

    result &= engine::core_graphics_window_quit_received(core->graphics);

    return(result);
}
