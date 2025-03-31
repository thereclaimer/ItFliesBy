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
    api_system_get_info_cpu_f    system_get_info_cpu;
    api_system_get_info_memory_f system_get_info_memory;
    api_system_time_ms_f         system_time_ms;
    api_system_sleep_f           system_sleep;
    api_system_debug_print_f     system_debug_print;

    //------------------
    // memory
    //------------------
    api_memory_reserve_f        memory_reserve;
    api_memory_release_f        memory_release;
    api_memory_commit_f         memory_commit;
    api_memory_decommit_f       memory_decommit;

    //------------------
    // thread
    //------------------
    api_thread_size_f           thread_size;
    api_thread_create_f         thread_create;
    api_thread_destroy_f        thread_destroy;
    api_thread_assign_cores_f   thread_assign_cores;
    api_thread_wake_f           thread_wake;
    api_thread_sleep_f          thread_sleep;

    //------------------
    // window
    //------------------
    api_window_size_f           window_size;
    api_window_create_f         window_create;
    api_window_destroy_f        window_destroy;
    api_window_process_events_f window_process_events;
    api_window_swap_buffers_f   window_swap_buffers;
    api_window_show_f           window_show;

    //------------------
    // monitor
    //------------------
    api_monitor_count_f         monitor_count;
    api_monitor_info_f          monitor_info;
};

/**********************************************************************************/
/* PLATFORM                                                                       */
/**********************************************************************************/

const b8
platform::set_api(
    const api_t* api) {

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