#pragma once

#include "ifb-win32.hpp"



ifb_internal const IFBU32
ifb_win32::monitor_count(
    IFBVoid) {

    IFBU32 monitor_count = 0;

    const IFBB8 result = EnumDisplayMonitors(
        NULL,
        NULL,
        ifb_win32::monitor_enum_callback_count,
        (LPARAM)&monitor_count);

    return(result ? monitor_count : 0);
}

ifb_global IFBU32 current_monitor_index;

// ifb_internal IFBVoid
// ifb_win32::monitor_info(
//     const IFBU32     monitor_array_count,
//           IFBMonitor* monitor_array_ptr) {

//     current_monitor_index = 0;

//     const IFBB8 result = EnumDisplayMonitors(
//         NULL,
//         NULL,
//         ifb_win32::monitor_enum_callback_info,
//         (LPARAM)monitor_array_ptr);

//     current_monitor_index = 0;
// }

ifb_internal BOOL CALLBACK 
ifb_win32::monitor_enum_callback_count(
    HMONITOR handle,
    HDC      device_context,
    LPRECT   rect_ptr,
    LPARAM   data_ptr) {

    //incriment the monitor count
    IFBU32* count_ptr = (IFBU32*)data_ptr;
    ++(*count_ptr);

    return(true);
}

ifb_internal BOOL CALLBACK 
ifb_win32::monitor_enum_callback_info(
    HMONITOR handle,
    HDC      device_context,
    LPRECT   rect_ptr,
    LPARAM   data_ptr) {

    // //cast the data pointer and get the current monitor info reference
    // IFBMonitor* monitor_ptr         = (IFBMonitor*)data_ptr;
    // IFBMonitor& current_monitor_ref = monitor_ptr[current_monitor_index];

    // //get the information available to us
    // const IFBHandle monitor_handle    = (IFBHandle)handle;
    // const IFBU32    monitor_index     = current_monitor_index;
    // const IFBU32    monitor_width     = rect_ptr->right - rect_ptr->left;
    // const IFBU32    monitor_height    = rect_ptr->bottom - rect_ptr->top;
    // const IFBU32    monitor_origin_x  = rect_ptr->left; 
    // const IFBU32    monitor_origin_y  = rect_ptr->top; 

    // //calculate the aspect ratio
    // const IFBAspectRatioType monitor_aspect_ratio_type = ifb_graphics::aspect_ratio_lookup(
    //     monitor_width,
    //     monitor_height);

    // //set the properties
    // current_monitor_ref.id.index          = monitor_index; 
    // current_monitor_ref.platform_handle   = monitor_handle; 
    // current_monitor_ref.dimensions.width  = monitor_width; 
    // current_monitor_ref.dimensions.height = monitor_height; 
    // current_monitor_ref.desktop_origin.x  = monitor_origin_x; 
    // current_monitor_ref.desktop_origin.y  = monitor_origin_y; 
    // current_monitor_ref.aspect_ratio      = monitor_aspect_ratio_type;

    // //update the global monitor index
    // ++current_monitor_index;

    //we're done
    return(true);
}