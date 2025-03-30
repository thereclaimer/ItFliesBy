#pragma once

#include "ifb-win32.hpp"

ifb_internal const ifb::u32
ifb_win32::monitor_count(
    void) {

    const ifb::u32 monitor_count = GetSystemMetrics(SM_CMONITORS);

    return(monitor_count);
}
    
ifb_internal const ifb::b8
ifb_win32::monitor_info(
    const ifb::u32      monitor_count,
          IFBMonitor* monitor_array) {

    //sanity check
    ifb::b8 result = true;
    result &= (monitor_count != 0);
    result &= (monitor_array != NULL);
    if (!result) return(false);

    // we need to iterate through the display devices
    // as a safety check, we will ensure that we ONLY query
    // 32 times. if the user has more than 32 monitors, 
    // i don't know what to tell them
    const ifb::u32 max_iterations = 32;

    //structures that will hold the win32 monitor info
    DISPLAY_DEVICE win32_display_device;
    DEVMODE        win32_devmode;
    MONITORINFOEX  win32_monitor_info;
    win32_display_device.cb   = sizeof(DISPLAY_DEVICE);
    win32_devmode.dmSize      = sizeof(DEVMODE);
    win32_monitor_info.cbSize = sizeof(MONITORINFOEX);

    //how we will keep track of the physical monitor index
    ifb::u32 monitor_index = 0;

    for (
        ifb::u32 display_device_index = 0;
               display_device_index < max_iterations && monitor_index < monitor_count;
             ++display_device_index) {

        //get the next display device
        const ifb::b8 should_continue = EnumDisplayDevices(
            NULL,                  // device name
            display_device_index,  // device index
            &win32_display_device, // display device structure
            0);                    // flags

        //if there's no more valid display devices, we're done
        if (!should_continue) break;

        //we need to make sure this is a physical monitor
        //we don't want to use virtual displays
        ifb::b8 display_device_is_physical = true;
        display_device_is_physical &=  (win32_display_device.StateFlags & DISPLAY_DEVICE_ACTIVE);
        display_device_is_physical &= !(win32_display_device.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER);
        if (!display_device_is_physical) continue;
    
        //get the next monitor from the array
        IFBMonitor& monitor_ref = monitor_array[monitor_index];

        //get the display settings
        const ifb::b8 display_settings_result = EnumDisplaySettings(
            win32_display_device.DeviceName,
            ENUM_CURRENT_SETTINGS,
            &win32_devmode);

        //update the monitor
        monitor_ref.dimensions.width  = win32_devmode.dmPelsWidth;
        monitor_ref.dimensions.height = win32_devmode.dmPelsHeight;
        monitor_ref.position.x        = win32_devmode.dmPosition.x;
        monitor_ref.position.y        = win32_devmode.dmPosition.y;
        monitor_ref.refresh_hz        = win32_devmode.dmDisplayFrequency;
        monitor_ref.index             = monitor_index; 

        //update the index
        ++monitor_index;
    }

    //we're done
    return(result);
}

ifb_internal BOOL CALLBACK 
ifb_win32::monitor_enum_callback_count(
    HMONITOR handle,
    HDC      device_context,
    LPRECT   rect_ptr,
    LPARAM   data_ptr) {

    //incriment the monitor count
    ifb::u32* count_ptr = (ifb::u32*)data_ptr;
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
    // const ifb::u32    monitor_index     = current_monitor_index;
    // const ifb::u32    monitor_width     = rect_ptr->right - rect_ptr->left;
    // const ifb::u32    monitor_height    = rect_ptr->bottom - rect_ptr->top;
    // const ifb::u32    monitor_origin_x  = rect_ptr->left; 
    // const ifb::u32    monitor_origin_y  = rect_ptr->top; 

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