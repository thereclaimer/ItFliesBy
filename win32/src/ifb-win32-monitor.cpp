#pragma once

#include "ifb-win32.hpp"

ifb_internal ifb_void  
ifb_win32::monitor_size(
    IFBEnginePlatformMonitorSize& monitor_size_ref) {

    monitor_size_ref.width  = GetSystemMetrics(SM_CXSCREEN);
    monitor_size_ref.height = GetSystemMetrics(SM_CYSCREEN);

}

ifb_internal const ifb_u32
ifb_win32::monitor_refresh_hz(
    ifb_void) {

    return(0);
}

inline ifb_void 
ifb_win32::monitor_api_initialize(
    IFBEnginePlatformMonitor& monitor_api_ref) {

    monitor_api_ref.size       = ifb_win32::monitor_size;
    monitor_api_ref.refresh_hz = ifb_win32::monitor_refresh_hz;
}
