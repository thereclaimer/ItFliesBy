#ifndef IFB_PLATFORM_HPP
#define IFB_PLATFORM_HPP

#include <ifb.hpp>

#include "ifb-platform-system.hpp"
#include "ifb-platform-memory.hpp"
#include "ifb-platform-thread.hpp"
#include "ifb-platform-window.hpp"
#include "ifb-platform-monitor.hpp"
#include "ifb-platform-file.hpp"

using namespace ifb;

/**********************************************************************************/
/* PLATFORM API                                                                   */
/**********************************************************************************/

namespace ifb {

    struct platform_api_t {

        struct {
            platform_api_system_get_info_cpu_f    get_info_cpu;
            platform_api_system_get_info_memory_f get_info_memory;
            platform_api_system_time_ms_f         time_ms;
            platform_api_system_sleep_f           sleep;
            platform_api_system_debug_print_f     debug_print;
        } system;

        struct {
            platform_api_memory_reserve_f        reserve;
            platform_api_memory_release_f        release;
            platform_api_memory_commit_f         commit;
            platform_api_memory_decommit_f       decommit;
        } memory;

        struct {
            platform_api_thread_size_f         size;
            platform_api_thread_create_f       create;
            platform_api_thread_destroy_f      destroy;
            platform_api_thread_assign_cores_f assign_cores;
            platform_api_thread_wake_f         wake;
            platform_api_thread_sleep_f        sleep;
        } thread;

        struct {
            platform_api_window_size_f           size;
            platform_api_window_create_f         create;
            platform_api_window_destroy_f        destroy;
            platform_api_window_process_events_f process_events;
            platform_api_window_swap_buffers_f   swap_buffers;
            platform_api_window_show_f           show;
        } window;

        struct {
            platform_api_monitor_count_f         count;
            platform_api_monitor_info_f          info;
        } monitor;

        struct {
            platform_api_file_ro_context_size_f    ro_context_size;
            platform_api_file_ro_open_f            ro_open;
            platform_api_file_ro_read_immediate_f  ro_close;
            platform_api_file_ro_read_async_f      ro_read_immediate;
            platform_api_file_ro_close_f           ro_read_async;
            platform_api_file_rw_context_size_f    rw_context_size;
            platform_api_file_rw_open_f            rw_open;
            platform_api_file_rw_read_immediate_f  rw_close;
            platform_api_file_rw_read_async_f      rw_read_immediate;
            platform_api_file_rw_write_immediate_f rw_read_async;
            platform_api_file_rw_write_async_f     rw_write_immediate;
            platform_api_file_rw_close_f           rw_write_async;
        } file;
    };
};


namespace ifb::platform {

    const b8 set_api (const platform_api_t* api);

    //------------------
    // system
    //------------------
    extern platform_api_system_get_info_cpu_f    system_get_info_cpu;
    extern platform_api_system_get_info_memory_f system_get_info_memory;
    extern platform_api_system_time_ms_f         system_time_ms;
    extern platform_api_system_sleep_f           system_sleep;
    extern platform_api_system_debug_print_f     system_debug_print;

    //------------------
    // memory
    //------------------
    extern platform_api_memory_reserve_f        memory_reserve;
    extern platform_api_memory_release_f        memory_release;
    extern platform_api_memory_commit_f         memory_commit;
    extern platform_api_memory_decommit_f       memory_decommit;

    //------------------
    // thread
    //------------------
    extern platform_api_thread_size_f           thread_size;
    extern platform_api_thread_create_f         thread_create;
    extern platform_api_thread_destroy_f        thread_destroy;
    extern platform_api_thread_assign_cores_f   thread_assign_cores;
    extern platform_api_thread_wake_f           thread_wake;
    extern platform_api_thread_sleep_f          thread_sleep;

    //------------------
    // window
    //------------------
    extern platform_api_window_size_f           window_size;
    extern platform_api_window_create_f         window_create;
    extern platform_api_window_destroy_f        window_destroy;
    extern platform_api_window_process_events_f window_process_events;
    extern platform_api_window_swap_buffers_f   window_swap_buffers;
    extern platform_api_window_show_f           window_show;

    //------------------
    // monitor
    //------------------
    extern platform_api_monitor_count_f         monitor_count;
    extern platform_api_monitor_info_f          monitor_info;

    //------------------
    // file
    //------------------
    extern platform_api_file_ro_context_size_f      file_ro_context_size;
    extern platform_api_file_ro_open_f              file_ro_open;
    extern platform_api_file_ro_read_immediate_f    file_ro_close;
    extern platform_api_file_ro_read_async_f        file_ro_read_immediate;
    extern platform_api_file_ro_close_f             file_ro_read_async;
    extern platform_api_file_rw_context_size_f      file_rw_context_size;
    extern platform_api_file_rw_open_f              file_rw_open;
    extern platform_api_file_rw_read_immediate_f    file_rw_close;
    extern platform_api_file_rw_read_async_f        file_rw_read_immediate;
    extern platform_api_file_rw_write_immediate_f   file_rw_read_async;
    extern platform_api_file_rw_write_async_f       file_rw_write_immediate;
    extern platform_api_file_rw_close_f             file_rw_write_async;
};

#endif //IFB_ENGINE_PLATFORM_HPP