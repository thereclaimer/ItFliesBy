#pragma once

#include "ifb-win32.hpp"

ifb_internal ifb_void 
ifb_win32::system_api_initialize(
    IFBPlatformSystemApi& platform_system_api_ref) {

    platform_system_api_ref.page_size              = ifb_win32::system_page_size;
    platform_system_api_ref.allocation_granularity = ifb_win32::system_allocation_granularity;
    platform_system_api_ref.time_ms                = ifb_win32::system_time_ms;
    platform_system_api_ref.sleep                  = ifb_win32::system_sleep;
}

ifb_internal const ifb_u32
ifb_win32::system_page_size(
    ifb_void) {

    SYSTEM_INFO sys_info;
    GetSystemInfo(&sys_info);

    return(sys_info.dwPageSize);
}

ifb_internal const ifb_u32
ifb_win32::system_allocation_granularity(
    ifb_void) {

    SYSTEM_INFO sys_info;
    GetSystemInfo(&sys_info);

    return(sys_info.dwAllocationGranularity);
}

ifb_internal const ifb_u64
ifb_win32::system_time_ms(
    ifb_void) {

    ifb_macro_panic();
    return(0L);
}

ifb_internal ifb_void 
ifb_win32::system_sleep(
    const ifb_u32 ms) {

    ifb_macro_panic();
}