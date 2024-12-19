#pragma once

#include "ifb-win32.hpp"

inline ifb_void 
ifb_win32::monitor_api_initialize(
    IFBPlatformMonitorApi& monitor_api_ref) {

    monitor_api_ref.count        = ifb_win32::monitor_count;
    monitor_api_ref.active_index = ifb_win32::monitor_active_index;
    monitor_api_ref.info         = ifb_win32::monitor_info;
}


ifb_internal const ifb_u32
ifb_win32::monitor_count(
    ifb_void) {

    return(0);

}

ifb_internal const ifb_u32
ifb_win32::monitor_active_index(
    ifb_void) {

    return(0);
}

ifb_internal ifb_void
ifb_win32::monitor_info(
    const ifb_u32     monitor_array_count,
          IFBMonitor* monitor_array_ptr) {

}