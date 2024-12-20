#pragma once

#include "ifb-win32.hpp"

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