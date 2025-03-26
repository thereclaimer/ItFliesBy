#include "ifb-platform.hpp"

#include "ifb-platform-win32-internal.cpp"
#include "ifb-platform-win32-system.cpp"
#include "ifb-platform-win32-window.cpp"
#include "ifb-platform-win32-memory.cpp"

namespace ifb_platform {

    IFBPlatformSystemGetInfo      system_get_info;
    IFBPlatformSystemTimeMS       system_time_ms;
    IFBPlatformSystemSleep        system_sleep;
    IFBPlatformSystemDebugPrint   system_debug_print;

    IFBPlatformMemoryReserve      memory_reserve;
    IFBPlatformMemoryRelease      memory_release;
    IFBPlatformMemoryCommit       memory_commit;
    IFBPlatformMemoryDecommit     memory_decommit;

    IFBPlatformWindowCreate       window_create = ifb_platform::win32_window_create;
    IFBPlatformWindowDestroy      window_destroy;
    IFBPlatformWindowFrameStart   window_frame_start;
    IFBPlatformWindowFrameRender  window_frame_render;
    IFBPlatformWindowShow         window_show;

    IFBPlatformMonitorCount       monitor_count;
    IFBPlatformMonitorInfo        monitor_info;


};
