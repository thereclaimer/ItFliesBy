#pragma once

#include "ifb-win32.hpp"

ifb_internal ifb_void  
ifb_win32::monitor_dimensions(
    IFBDimensions& dimensions_ref) {

    dimensions_ref.width  = GetSystemMetrics(SM_CXSCREEN);
    dimensions_ref.height = GetSystemMetrics(SM_CYSCREEN);
}

ifb_internal const ifb_u32
ifb_win32::monitor_refresh_hz(
    ifb_void) {

    ifb_macro_panic();

    return(0);
}

inline ifb_void 
ifb_win32::monitor_api_initialize(
    IFBPlatformMonitorApi& monitor_api_ref) {

    monitor_api_ref.dimensions = ifb_win32::monitor_dimensions;
    monitor_api_ref.refresh_hz = ifb_win32::monitor_refresh_hz;
}
