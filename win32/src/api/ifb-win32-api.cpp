#pragma once

#include "ifb-win32-api-memory.cpp"
#include "ifb-win32-api-system.cpp"
#include "ifb-win32-api-monitor.cpp"
#include "ifb-win32-api-window.cpp"
#include "ifb-win32-api-user-input.cpp"
#include "ifb-win32-api-registry.cpp"
// #include "ifb-win32-file.cpp"

namespace ifb_win32 {

    ifb_global IFBPlatformAPI _platform_api = {

        //----------------------------------------
        // system
        {
            ifb_win32::system_get_info_cpu,     // IFBPlatformSystemGetInfoCPU
            ifb_win32::system_get_info_memory,  // IFBPlatformSystemGetInfoMemory
            ifb_win32::system_time_ms,          // IFBPlatformSystemTimeMS
            ifb_win32::system_sleep,            // IFBPlatformSystemSleep
            ifb_win32::system_debug_print       // IFBPlatformSystemDebugPrint
        },
        //----------------------------------------
        // memory
        {
            ifb_win32::memory_reserve,          // IFBPlatformMemoryReserve
            ifb_win32::memory_release,          // IFBPlatformMemoryRelease
            ifb_win32::memory_commit,           // IFBPlatformMemoryCommit
            ifb_win32::memory_decommit          // IFBPlatformMemoryDecommit
        },
        //----------------------------------------
        // threads
        {
            NULL,                               // IFBPlatformThreadSize
            NULL,                               // IFBPlatformThreadCreate
            NULL,                               // IFBPlatformThreadDestroy
            NULL,                               // IFBPlatformThreadAssignCores
            NULL,                               // IFBPlatformThreadWake
            NULL                                // IFBPlatformThreadSleep
        },
        //----------------------------------------
        // window
        {
            (IFBPlatformWindowCreate)        ifb_win32::window_create,         // IFBPlatformWindowCreate
            (IFBPlatformWindowDestroy)       ifb_win32::window_destroy,        // IFBPlatformWindowDestroy
            (IFBPlatformWindowProcessEvents) ifb_win32::window_process_events, // IFBPlatformWindowProcessEvents
            (IFBPlatformWindowSwapBuffers)   ifb_win32::window_swap_buffers,   // IFBPlatformWindowSwapBuffers
            (IFBPlatformWindowShow)          ifb_win32::window_show            // IFBPlatformWindowShow
        },
        //----------------------------------------
        // monitor
        {
            ifb_win32::monitor_count,           // IFBPlatformMonitorCount
            ifb_win32::monitor_info             // IFBPlatformMonitorInfo
        }
    };

    inline IFBPlatformAPI* platform_api(IFBVoid) { return(&_platform_api); }
};