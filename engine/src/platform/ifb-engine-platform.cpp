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
    ifb_engine::platform_monitor_dimensions  = platform_api_ref.monitor.dimensions;
    ifb_engine::platform_monitor_refresh_hz  = platform_api_ref.monitor.refresh_hz;
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
    ifb_macro_assert(ifb_engine::platform_monitor_dimensions);
    ifb_macro_assert(ifb_engine::platform_monitor_refresh_hz);
    ifb_macro_assert(ifb_engine::platform_memory_reserve);
    ifb_macro_assert(ifb_engine::platform_memory_release);
    ifb_macro_assert(ifb_engine::platform_memory_commit);

    //allocate the platform
    const ifb_handle platform_handle         = ifb_engine_memory_global_push_struct(IFBEnginePlatform);
    const ifb_handle platform_handle_system  = ifb_engine_memory_global_push_struct(IFBEnginePlatformSystemInfo);
    const ifb_handle platform_handle_memory  = ifb_engine_memory_global_push_struct(IFBEnginePlatformMemory);
    const ifb_handle platform_handle_window  = ifb_engine_memory_global_push_struct(IFBEnginePlatformWindow);
    const ifb_handle platform_handle_monitor = ifb_engine_memory_global_push_struct(IFBEnginePlatformMonitorInfo);

    //get the pointers
    IFBPlatform*                  ptr_platform         = ifb_engine::platform_global_pointer_system (platform_handle);
    IFBEnginePlatformSystemInfo*  ptr_platform_system  = ifb_engine::platform_global_pointer_system (platform_handle_system);
    IFBEnginePlatformMemory*      ptr_platform_memory  = ifb_engine::platform_global_pointer_memory (platform_handle_memory);
    IFBEnginePlatformWindow*      ptr_platform_window  = ifb_engine::platform_global_pointer_window (platform_handle_window);
    IFBEnginePlatformMonitorInfo* ptr_platform_monitor = ifb_engine::platform_global_pointer_monitor(platform_handle_monitor);

    //----------------
    // system info
    //----------------
    
    ptr_platform_system->page_size              = ifb_engine::platform_system_page_size();
    ptr_platform_system->allocation_granularity = ifb_engine::platform_system_allocation_granularity();
    
    ifb_macro_assert(ptr_platform_system->page_size              > 0);
    ifb_macro_assert(ptr_platform_system->allocation_granularity > 0);

    //----------------
    // monitor info
    //----------------
    
    ifb_engine::platform_monitor_dimensions(ptr_platform_monitor->dimensions);
    ptr_platform_monitor->refresh_hz = ifb_engine::platform_monitor_refresh_hz();

    //sanity check
    ifb_macro_assert(ptr_platform_monitor->dimensions.width  > 0);
    ifb_macro_assert(ptr_platform_monitor->dimensions.height > 0);
    ifb_macro_assert(ptr_platform_monitor->refresh_hz        > 0);

    //----------------
    // memory
    //----------------
    
    ptr_platform_memory->reservation_size  = IFB_ENGINE_MINIMUM_MEMORY_REQUIREMENT_4GB;
    ptr_platform_memory->reservation_start = (ifb_address)ifb_engine::platform_memory_reserve(ptr_platform_memory->reservation_size);

    ifb_macro_assert(ptr_platform_memory->reservation_start != 0);

    return(platform_handle);
}