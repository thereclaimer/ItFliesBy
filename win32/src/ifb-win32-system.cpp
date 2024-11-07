#pragma once

#include "ifb-win32.hpp"

ifb_internal ifb_void 
ifb_win32::system_api_initialize(
    IFBEnginePlatformSystem& platform_system_api_ref) {

    platform_system_api_ref.page_size              = ifb_win32::system_page_size;
    platform_system_api_ref.allocation_granularity = ifb_win32::system_allocation_granularity;
}

ifb_internal const ifb_size 
ifb_win32::system_page_size(
    ifb_void) {

    return(r_win32::system_page_size());
}

ifb_internal const ifb_size 
ifb_win32::system_allocation_granularity(
    ifb_void) {

    return(r_win32::system_allocation_granularity());
}