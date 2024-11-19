#pragma once

#include "ifb-engine-internal-platform.hpp"
#include "ifb-engine-internal.hpp"

ifb_api ifb_void 
ifb_engine::platform_window_update_size(
    const ifb_u32 window_width,
    const ifb_u32 window_height) {

    _engine_context->platform.window_width  = window_width;
    _engine_context->platform.window_height = window_height;
}

ifb_api ifb_void 
ifb_engine::platform_window_update_position(
    const ifb_u32 window_position_x,
    const ifb_u32 window_position_y) {

    _engine_context->platform.window_position_x = window_position_x;
    _engine_context->platform.window_position_y = window_position_y;
}