#pragma once

#include "ifb-engine-internal-context.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb_platform {

    IFBPlatformSystemGetInfo      system_get_info;
    IFBPlatformSystemTimeMS       system_time_ms;
    IFBPlatformSystemSleep        system_sleep;
    IFBPlatformSystemDebugPrint   system_debug_print;

    IFBPlatformMemoryReserve      memory_reserve;
    IFBPlatformMemoryRelease      memory_release;
    IFBPlatformMemoryCommit       memory_commit;
    IFBPlatformMemoryDecommit     memory_decommit;

    IFBPlatformThreadCreate       thread_create;
    IFBPlatformThreadDestroy      thread_destroy;

    IFBPlatformWindowCreate       window_create;
    IFBPlatformWindowDestroy      window_destroy;
    IFBPlatformWindowFrameStart   window_frame_start;
    IFBPlatformWindowFrameRender  window_frame_render;
    IFBPlatformWindowShow         window_show;
    IFBPlatformWindowOpenGLInit   window_opengl_init;
    IFBPlatformWindowImGUIInit    window_imgui_init;

    IFBPlatformMonitorCount       monitor_count;
    IFBPlatformMonitorInfo        monitor_info;
};

/**********************************************************************************/
/* PLATFORM                                                                       */
/**********************************************************************************/

const IFBB8
ifb_engine::platform_api_initialize(
    const IFBPlatformAPI* ptr_platform_api) {

    if (!ptr_platform_api) return(false);
    
    //cache the api
    const IFBPlatformAPISystem&  ref_api_system  = ptr_platform_api->system;
    const IFBPlatformAPIMemory&  ref_api_memory  = ptr_platform_api->memory;
    const IFBPlatformAPIThread&  ref_api_thread  = ptr_platform_api->thread;
    const IFBPlatformAPIWindow&  ref_api_window  = ptr_platform_api->window;
    const IFBPlatformAPIMonitor& ref_api_monitor = ptr_platform_api->monitor;

    //system
    ifb_platform::system_get_info     = ref_api_system.get_info;
    ifb_platform::system_time_ms      = ref_api_system.time_ms;
    ifb_platform::system_sleep        = ref_api_system.sleep;
    
    //memory
    ifb_platform::memory_reserve      = ref_api_memory.reserve;
    ifb_platform::memory_release      = ref_api_memory.release;
    ifb_platform::memory_commit       = ref_api_memory.commit;
    ifb_platform::memory_decommit     = ref_api_memory.decommit;

    //threads
    ifb_platform::thread_create       = ref_api_thread.create;
    ifb_platform::thread_destroy      = ref_api_thread.destroy;

    //window
    ifb_platform::window_create       = ref_api_window.create;
    ifb_platform::window_destroy      = ref_api_window.destroy;
    ifb_platform::window_frame_start  = ref_api_window.frame_start;
    ifb_platform::window_frame_render = ref_api_window.frame_render;
    ifb_platform::window_show         = ref_api_window.show;
    ifb_platform::window_opengl_init  = ref_api_window.opengl_init;
    ifb_platform::window_imgui_init   = ref_api_window.imgui_init;

    //monitor
    ifb_platform::monitor_count       = ref_api_monitor.count;
    ifb_platform::monitor_info        = ref_api_monitor.info;

    return(true);
}
