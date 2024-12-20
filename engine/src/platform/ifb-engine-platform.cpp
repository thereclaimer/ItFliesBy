#pragma once

#include "ifb-engine-internal-platform.hpp"
#include "ifb-engine-internal-memory.hpp"

inline ifb_void 
ifb_engine::platform_initialize(
    IFBPlatformApi& platform_api_ref) {

    //set the api function pointers
    ifb_engine::platform_system_page_size              = platform_api_ref.system.page_size;
    ifb_engine::platform_system_allocation_granularity = platform_api_ref.system.allocation_granularity;
    ifb_engine::platform_system_time_ms                = platform_api_ref.system.time_ms;
    ifb_engine::platform_system_sleep                  = platform_api_ref.system.sleep;
    ifb_engine::platform_window_create                 = platform_api_ref.window.create;
    ifb_engine::platform_window_destroy                = platform_api_ref.window.destroy;
    ifb_engine::platform_window_frame_start            = platform_api_ref.window.frame_start;
    ifb_engine::platform_window_frame_render           = platform_api_ref.window.frame_render;
    ifb_engine::platform_window_show                   = platform_api_ref.window.show;
    ifb_engine::platform_window_opengl_init            = platform_api_ref.window.opengl_init;
    ifb_engine::platform_window_imgui_init             = platform_api_ref.window.imgui_init;
    ifb_engine::platform_monitor_count                 = platform_api_ref.monitor.count;
    ifb_engine::platform_monitor_info                  = platform_api_ref.monitor.info;
    ifb_engine::platform_memory_reserve                = platform_api_ref.memory.reserve;
    ifb_engine::platform_memory_release                = platform_api_ref.memory.release;
    ifb_engine::platform_memory_commit                 = platform_api_ref.memory.commit;

    //sanity check
    ifb_macro_assert(ifb_engine::platform_system_page_size);
    ifb_macro_assert(ifb_engine::platform_system_allocation_granularity);
    ifb_macro_assert(ifb_engine::platform_system_time_ms);
    ifb_macro_assert(ifb_engine::platform_system_sleep);
    ifb_macro_assert(ifb_engine::platform_window_create);
    ifb_macro_assert(ifb_engine::platform_window_destroy);
    ifb_macro_assert(ifb_engine::platform_window_frame_start);
    ifb_macro_assert(ifb_engine::platform_window_frame_render);
    ifb_macro_assert(ifb_engine::platform_window_show);
    ifb_macro_assert(ifb_engine::platform_window_opengl_init);
    ifb_macro_assert(ifb_engine::platform_window_imgui_init);
    ifb_macro_assert(ifb_engine::platform_monitor_count);
    ifb_macro_assert(ifb_engine::platform_monitor_info);
    ifb_macro_assert(ifb_engine::platform_memory_release);
    ifb_macro_assert(ifb_engine::platform_memory_commit);
}