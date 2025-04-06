#pragma once

#include "ifb-platform.hpp"

using namespace ifb;

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb::platform {

    //------------------
    // system
    //------------------
    platform_api_system_get_info_cpu_f    system_get_info_cpu;
    platform_api_system_get_info_memory_f system_get_info_memory;
    platform_api_system_time_ms_f         system_time_ms;
    platform_api_system_sleep_f           system_sleep;
    platform_api_system_debug_print_f     system_debug_print;

    //------------------
    // memory
    //------------------
    platform_api_memory_reserve_f        memory_reserve;
    platform_api_memory_release_f        memory_release;
    platform_api_memory_commit_f         memory_commit;
    platform_api_memory_decommit_f       memory_decommit;

    //------------------
    // thread
    //------------------
    platform_api_thread_size_f           thread_size;
    platform_api_thread_create_f         thread_create;
    platform_api_thread_destroy_f        thread_destroy;
    platform_api_thread_assign_cores_f   thread_assign_cores;
    platform_api_thread_wake_f           thread_wake;
    platform_api_thread_sleep_f          thread_sleep;

    //------------------
    // window
    //------------------
    platform_api_window_size_f           window_size;
    platform_api_window_create_f         window_create;
    platform_api_window_destroy_f        window_destroy;
    platform_api_window_process_events_f window_process_events;
    platform_api_window_swap_buffers_f   window_swap_buffers;
    platform_api_window_show_f           window_show;

    //------------------
    // monitor
    //------------------
    platform_api_monitor_count_f         monitor_count;
    platform_api_monitor_info_f          monitor_info;
};

/**********************************************************************************/
/* PLATFORM                                                                       */
/**********************************************************************************/

const b8
platform::set_api(
    const platform_api_t* api) {

    if (!api) return(false);

    //system
    platform::system_get_info_cpu    = api->system.get_info_cpu;
    platform::system_get_info_memory = api->system.get_info_memory;
    platform::system_time_ms         = api->system.time_ms;
    platform::system_sleep           = api->system.sleep;
    
    //memory
    platform::memory_reserve         = api->memory.reserve;
    platform::memory_release         = api->memory.release;
    platform::memory_commit          = api->memory.commit;
    platform::memory_decommit        = api->memory.decommit;

    //window
    platform::window_size            = api->window.size;
    platform::window_create          = api->window.create;
    platform::window_destroy         = api->window.destroy;
    platform::window_process_events  = api->window.process_events;
    platform::window_swap_buffers    = api->window.swap_buffers;
    platform::window_show            = api->window.show;

    //monitor
    platform::monitor_count          = api->monitor.count;
    platform::monitor_info           = api->monitor.info;

    return(true);
}