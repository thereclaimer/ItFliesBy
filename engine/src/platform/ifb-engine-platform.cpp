#pragma once

#include "ifb-engine-internal-platform.hpp"
#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal.hpp"

inline const ifb_handle 
ifb_engine::platform_initialize(
    IFBPlatformApi& platform_api_ref) {

    //set the api function pointers
    ifb_engine::platform_system_info         = platform_api_ref.system.system_info;
    ifb_engine::platform_window_create       = platform_api_ref.window.create;
    ifb_engine::platform_window_destroy      = platform_api_ref.window.destroy;
    ifb_engine::platform_window_frame_start  = platform_api_ref.window.frame_start;
    ifb_engine::platform_window_frame_render = platform_api_ref.window.frame_render;
    ifb_engine::platform_window_show         = platform_api_ref.window.show;
    ifb_engine::platform_window_opengl_init  = platform_api_ref.window.opengl_init;
    ifb_engine::platform_window_imgui_init   = platform_api_ref.window.imgui_init;
    ifb_engine::platform_monitor_info        = platform_api_ref.monitor.monitor_info;
    ifb_engine::platform_memory_reserve      = platform_api_ref.memory.reserve;
    ifb_engine::platform_memory_release      = platform_api_ref.memory.release;
    ifb_engine::platform_memory_commit       = platform_api_ref.memory.commit;

    //sanity check
    ifb_macro_assert(ifb_engine::platform_system_info);
    ifb_macro_assert(ifb_engine::platform_window_create);
    ifb_macro_assert(ifb_engine::platform_window_destroy);
    ifb_macro_assert(ifb_engine::platform_window_frame_start);
    ifb_macro_assert(ifb_engine::platform_window_frame_render);
    ifb_macro_assert(ifb_engine::platform_window_show);
    ifb_macro_assert(ifb_engine::platform_window_opengl_init);
    ifb_macro_assert(ifb_engine::platform_window_imgui_init);
    ifb_macro_assert(ifb_engine::platform_monitor_info);
    ifb_macro_assert(ifb_engine::platform_memory_reserve);
    ifb_macro_assert(ifb_engine::platform_memory_release);
    ifb_macro_assert(ifb_engine::platform_memory_commit);

    //allocate the platform
    const ifb_handle platform_handle                    = ifb_engine_memory_global_push_struct(IFBEnginePlatform);
    const ifb_handle platform_handle_system_info        = ifb_engine_memory_global_push_struct(IFBEnginePlatformSystemInfo);
    const ifb_handle platform_handle_memory_reservation = ifb_engine_memory_global_push_struct(IFBEnginePlatformMemoryReservation);
    const ifb_handle platform_handle_window             = ifb_engine_memory_global_push_struct(IFBEnginePlatformWindow);
    const ifb_handle platform_handle_monitor_info       = ifb_engine_memory_global_push_struct(IFBEnginePlatformMonitorInfo);

    //get the pointers
    IFBPlatform*                        platform_ptr                    = ifb_engine::platform_global_pointer_system (platform_handle);
    IFBEnginePlatformSystemInfo*        platform_system_info_ptr        = ifb_engine::platform_global_pointer_system (platform_handle_system);
    IFBEnginePlatformMemoryReservation* platform_memory_reservation_ptr = ifb_engine::platform_global_pointer_memory (platform_handle_memory);
    IFBEnginePlatformWindow*            platform_window_ptr             = ifb_engine::platform_global_pointer_window (platform_handle_window);
    IFBEnginePlatformMonitorInfo*       platform_monitor_info_ptr       = ifb_engine::platform_global_pointer_monitor(platform_handle_monitor);

    //get the system info
    ifb_engine::platform_get_system_info(platform_system_info_ptr);


    //reserve platform memory
    platform_memory_ptr->reservation.page_size      = platform_system_ptr->page_size;
    platform_memory_ptr->reservation.size_requested = IFB_ENGINE_MINIMUM_MEMORY_REQUIREMENT_4GB;
    result &= ifb_engine::platform_memory_reserve(platform_memory_ptr);

    return(platform_handle);
}

inline ifb_void 
ifb_engine::platform_get_system_info(
    IFBEnginePlatformSystemInfo* system_info_ptr) {

    //get system info
    system_info_ptr->page_size              = ifb_engine::platform_system_page_size();
    system_info_ptr->allocation_granularity = ifb_engine::platform_system_allocation_granularity();
    
    //sanity check
    ifb_macro_assert(system_info_ptr->page_size              > 0);
    ifb_macro_assert(system_info_ptr->allocation_granularity > 0);
}

inline ifb_void 
ifb_engine::platform_get_monitor_info(
    IFBEnginePlatformMonitorInfo* monitor_info_ptr) {

    //get system info
    system_info_ptr->page_size              = ifb_engine::platform_system_page_size();
    system_info_ptr->allocation_granularity = ifb_engine::platform_system_allocation_granularity();
    
    //sanity check
    ifb_macro_assert(system_info_ptr->page_size              > 0);
    ifb_macro_assert(system_info_ptr->allocation_granularity > 0);
}

