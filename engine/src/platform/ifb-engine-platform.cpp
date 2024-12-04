#pragma once

#include "ifb-engine-internal-platform.hpp"
#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal.hpp"

inline const ifb_handle 
ifb_engine::platform_initialize(
    IFBPlatformApi& platform_api_ref) {

    //allocate the platform
    const ifb_handle platform_handle         = ifb_engine_memory_global_push_struct(IFBEnginePlatform);
    const ifb_handle platform_handle_system  = ifb_engine_memory_global_push_struct(IFBPlatformSystem);
    const ifb_handle platform_handle_memory  = ifb_engine_memory_global_push_struct(IFBPlatformMemory);
    const ifb_handle platform_handle_window  = ifb_engine_memory_global_push_struct(IFBPlatformWindow);
    const ifb_handle platform_handle_monitor = ifb_engine_memory_global_push_struct(IFBPlatformMonitor);

    //get the pointers
    IFBPlatform*        platform_ptr         = ifb_engine::platform_global_pointer_system (platform_handle);
    IFBPlatformSystem*  platform_system_ptr  = ifb_engine::platform_global_pointer_system (platform_handle_system);
    IFBPlatformMemory*  platform_memory_ptr  = ifb_engine::platform_global_pointer_memory (platform_handle_memory);
    IFBPlatformWindow*  platform_window_ptr  = ifb_engine::platform_global_pointer_window (platform_handle_window);
    IFBPlatformMonitor* platform_monitor_ptr = ifb_engine::platform_global_pointer_monitor(platform_handle_monitor);

    return(platform_handle);
}

inline ifb_void 
ifb_engine::platform_window_update_size(
    const ifb_u32 window_width,
    const ifb_u32 window_height) {

    _engine_context->platform.window_width  = window_width;
    _engine_context->platform.window_height = window_height;
}

inline ifb_void 
ifb_engine::platform_window_update_position(
    const ifb_u32 window_position_x,
    const ifb_u32 window_position_y) {

    _engine_context->platform.window_position_x = window_position_x;
    _engine_context->platform.window_position_y = window_position_y;
}

inline ifb_void 
ifb_engine::platform_window_default_dimensions(
    IFBDimensions& window_dimensions_ref) {y
    
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
