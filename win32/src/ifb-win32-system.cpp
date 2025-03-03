#pragma once

#include "ifb-win32.hpp"

ifb_internal const IFBU32
ifb_win32::system_page_size(
    IFBVoid) {

    SYSTEM_INFO sys_info;
    GetSystemInfo(&sys_info);

    return(sys_info.dwPageSize);
}

ifb_internal const IFBU32
ifb_win32::system_allocation_granularity(
    IFBVoid) {

    SYSTEM_INFO sys_info;
    GetSystemInfo(&sys_info);

    return(sys_info.dwAllocationGranularity);
}

ifb_internal const IFBU64
ifb_win32::system_time_ms(
    IFBVoid) {

    ifb_macro_panic();
    return(0L);
}

ifb_internal IFBVoid 
ifb_win32::system_sleep(
    const IFBU32 ms) {

    ifb_macro_panic();
}