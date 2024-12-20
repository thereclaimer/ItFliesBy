#ifndef IFB_ENGINE_INTERNAL_PLATFORM_HPP
#define IFB_ENGINE_INTERNAL_PLATFORM_HPP

#include "ifb-engine.hpp"

//api
namespace ifb_engine {

    //system
    ifb_global funcptr_ifb_platform_system_page_size              platform_system_page_size;
    ifb_global funcptr_ifb_platform_system_allocation_granularity platform_system_allocation_granularity;
    ifb_global funcptr_ifb_platform_system_time_ms                platform_system_time_ms;
    ifb_global funcptr_ifb_platform_system_sleep                  platform_system_sleep;
    
    //window
    ifb_global funcptr_ifb_platform_window_create                 platform_window_create;
    ifb_global funcptr_ifb_platform_window_destroy                platform_window_destroy;
    ifb_global funcptr_ifb_platform_window_frame_start            platform_window_frame_start;
    ifb_global funcptr_ifb_platform_window_frame_render           platform_window_frame_render;
    ifb_global funcptr_ifb_platform_window_show                   platform_window_show;
    ifb_global funcptr_ifb_platform_window_opengl_init            platform_window_opengl_init;
    ifb_global funcptr_ifb_platform_window_imgui_init             platform_window_imgui_init;

    //monitor
    ifb_global funcptr_ifb_platform_monitor_count                 platform_monitor_count;
    ifb_global funcptr_ifb_platform_monitor_info                  platform_monitor_info;

    //memory
    ifb_global funcptr_ifb_platform_memory_reserve                platform_memory_reserve;
    ifb_global funcptr_ifb_platform_memory_release                platform_memory_release;
    ifb_global funcptr_ifb_platform_memory_commit                 platform_memory_commit;
};


namespace ifb_engine {

    ifb_void platform_initialize(IFBPlatformApi& platform_api_ref);
};

#endif //IFB_ENGINE_INTERNAL_PLATFORM_HPP