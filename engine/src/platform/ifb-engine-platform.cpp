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

inline ifb_void 
ifb_engine::platform_window_default_dimensions(
    IFBDimensions& window_dimensions_ref) {
    
    //get monitor size
    IFBEnginePlatformMonitorSize monitor_size;
    ifb_engine::platform_monitor_size(monitor_size);

    //get monitor aspect ratio
    const IFBAspectRatioType aspect_ratio = ifb_common::aspect_ratio_lookup(
        monitor_size.width,
        monitor_size.height);

    //get the monitor resolution
    const IFBResolutionType resolution_type = ifb_common::resolution_default_type_from_aspect_ratio(aspect_ratio);
    IFBResolution resolution;
    ifb_common::resolution_dimensions(
        resolution_type,
        resolution);

    //put together window arguments
    window_dimensions_ref.width      = resolution.width;
    window_dimensions_ref.height     = resolution.height;
    window_dimensions_ref.position_x = (monitor_size.width  - resolution.width)  / 2;
    window_dimensions_ref.position_y = (monitor_size.height - resolution.height) / 2;
}
