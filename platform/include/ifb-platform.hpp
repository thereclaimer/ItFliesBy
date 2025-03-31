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

namespace ifb::platform {

    struct api_t {

        struct {
            api_system_get_info_cpu_f    get_info_cpu;
            api_system_get_info_memory_f get_info_memory;
            api_system_time_ms_f         time_ms;
            api_system_sleep_f           sleep;
            api_system_debug_print_f     debug_print;
        } system;

        struct {
            api_memory_reserve_f        reserve;
            api_memory_release_f        release;
            api_memory_commit_f         commit;
            api_memory_decommit_f       decommit;
        } memory;

        struct {
            api_thread_size_f         size;
            api_thread_create_f       create;
            api_thread_destroy_f      destroy;
            api_thread_assign_cores_f assign_cores;
            api_thread_wake_f         wake;
            api_thread_sleep_f        sleep;
        } thread;

        struct {
            api_window_size_f           size;
            api_window_create_f         create;
            api_window_destroy_f        destroy;
            api_window_process_events_f process_events;
            api_window_swap_buffers_f   swap_buffers;
            api_window_show_f           show;
        } window;

        struct {
            api_monitor_count_f         count;
            api_monitor_info_f          info;
        } monitor;

        struct {
            file_ro_context_size_f    ro_context_size;
            file_ro_open_f            ro_open;
            file_ro_read_immediate_f  ro_close;
            file_ro_read_async_f      ro_read_immediate;
            file_ro_close_f           ro_read_async;
            file_rw_context_size_f    rw_context_size;
            file_rw_open_f            rw_open;
            file_rw_read_immediate_f  rw_close;
            file_rw_read_async_f      rw_read_immediate;
            file_rw_write_immediate_f rw_read_async;
            file_rw_write_async_f     rw_write_immediate;
            file_rw_close_f           rw_write_async;
        } file;
    };

};


namespace ifb::platform {

    const b8 set_api (const api_t* api);

    //------------------
    // system
    //------------------
    extern api_system_get_info_cpu_f    system_get_info_cpu;
    extern api_system_get_info_memory_f system_get_info_memory;
    extern api_system_time_ms_f         system_time_ms;
    extern api_system_sleep_f           system_sleep;
    extern api_system_debug_print_f     system_debug_print;

    //------------------
    // memory
    //------------------
    extern api_memory_reserve_f        memory_reserve;
    extern api_memory_release_f        memory_release;
    extern api_memory_commit_f         memory_commit;
    extern api_memory_decommit_f       memory_decommit;

    //------------------
    // thread
    //------------------
    extern api_thread_size_f           thread_size;
    extern api_thread_create_f         thread_create;
    extern api_thread_destroy_f        thread_destroy;
    extern api_thread_assign_cores_f   thread_assign_cores;
    extern api_thread_wake_f           thread_wake;
    extern api_thread_sleep_f          thread_sleep;

    //------------------
    // window
    //------------------
    extern api_window_size_f           window_size;
    extern api_window_create_f         window_create;
    extern api_window_destroy_f        window_destroy;
    extern api_window_process_events_f window_process_events;
    extern api_window_swap_buffers_f   window_swap_buffers;
    extern api_window_show_f           window_show;

    //------------------
    // monitor
    //------------------
    extern api_monitor_count_f         monitor_count;
    extern api_monitor_info_f          monitor_info;

    //------------------
    // file
    //------------------
    extern file_ro_context_size_f      file_ro_context_size;
    extern file_ro_open_f              file_ro_open;
    extern file_ro_read_immediate_f    file_ro_close;
    extern file_ro_read_async_f        file_ro_read_immediate;
    extern file_ro_close_f             file_ro_read_async;
    extern file_rw_context_size_f      file_rw_context_size;
    extern file_rw_open_f              file_rw_open;
    extern file_rw_read_immediate_f    file_rw_close;
    extern file_rw_read_async_f        file_rw_read_immediate;
    extern file_rw_write_immediate_f   file_rw_read_async;
    extern file_rw_write_async_f       file_rw_write_immediate;
    extern file_rw_close_f             file_rw_write_async;
};

#endif //IFB_ENGINE_PLATFORM_HPP