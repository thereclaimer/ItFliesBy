#pragma once

#include "ifb-win32.hpp"

ifb_internal ifb_void 
ifb_win32::system_api_initialize(
    IFBPlatformSystemApi& platform_system_api_ref) {

    platform_system_api_ref.system_info = ifb_win32::system_info;
}

ifb_internal const ifb_b8 
ifb_win32::system_info(
    IFBPlatformSystemInfo& system_info_ref) {

    SYSTEM_INFO win32_sys_info;
    GetSystemInfo(win32_sys_info);

    system_info_ref.page_size              = win32_sys_info.dwPageSize;
    system_info_ref.allocation_granularity = win32_sys_info.dwAllocationGranularity;

    return(true);
}