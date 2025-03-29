#pragma once

#include "ifb-platform.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb_platform {

    IFBPlatformSystemGetInfoCPU    system_get_info_cpu;
    IFBPlatformSystemGetInfoMemory system_get_info_memory;
    IFBPlatformSystemTimeMS        system_time_ms;
    IFBPlatformSystemSleep         system_sleep;
    IFBPlatformSystemDebugPrint    system_debug_print;

    IFBPlatformMemoryReserve       memory_reserve;
    IFBPlatformMemoryRelease       memory_release;
    IFBPlatformMemoryCommit        memory_commit;
    IFBPlatformMemoryDecommit      memory_decommit;

    IFBPlatformWindowSize          window_size;
    IFBPlatformWindowCreate        window_create;
    IFBPlatformWindowDestroy       window_destroy;
    IFBPlatformWindowProcessEvents window_process_events;
    IFBPlatformWindowSwapBuffers   window_swap_buffers;
    IFBPlatformWindowShow          window_show;

    IFBPlatformMonitorCount        monitor_count;
    IFBPlatformMonitorInfo         monitor_info;
};

/**********************************************************************************/
/* PLATFORM                                                                       */
/**********************************************************************************/

const IFBB8
ifb_platform::set_api(
    const IFBPlatformAPI* platform_api) {

    if (!platform_api) return(false);

    //system
    ifb_platform::system_get_info_cpu    = platform_api->system.get_info_cpu;
    ifb_platform::system_get_info_memory = platform_api->system.get_info_memory;
    ifb_platform::system_time_ms         = platform_api->system.time_ms;
    ifb_platform::system_sleep           = platform_api->system.sleep;
    
    //memory
    ifb_platform::memory_reserve         = platform_api->memory.reserve;
    ifb_platform::memory_release         = platform_api->memory.release;
    ifb_platform::memory_commit          = platform_api->memory.commit;
    ifb_platform::memory_decommit        = platform_api->memory.decommit;

    //window
    ifb_platform::window_size            = platform_api->window.size;
    ifb_platform::window_create          = platform_api->window.create;
    ifb_platform::window_destroy         = platform_api->window.destroy;
    ifb_platform::window_process_events  = platform_api->window.process_events;
    ifb_platform::window_swap_buffers    = platform_api->window.swap_buffers;
    ifb_platform::window_show            = platform_api->window.show;

    //monitor
    ifb_platform::monitor_count          = platform_api->monitor.count;
    ifb_platform::monitor_info           = platform_api->monitor.info;

    return(true);
}