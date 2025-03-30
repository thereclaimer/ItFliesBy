#ifndef IFB_PLATFORM_HPP
#define IFB_PLATFORM_HPP

#include <ifb.hpp>

#include "ifb-platform-system.hpp"
#include "ifb-platform-memory.hpp"
#include "ifb-platform-thread.hpp"
#include "ifb-platform-window.hpp"
#include "ifb-platform-monitor.hpp"
#include "ifb-platform-file.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBPlatformAPI;

/**********************************************************************************/
/* PLATFORM API                                                                   */
/**********************************************************************************/

struct IFBPlatformAPI {

    struct {
        IFBPlatformSystemGetInfoCPU    get_info_cpu;
        IFBPlatformSystemGetInfoMemory get_info_memory;
        IFBPlatformSystemTimeMS        time_ms;
        IFBPlatformSystemSleep         sleep;
        IFBPlatformSystemDebugPrint    debug_print;
    } system;

    struct {
        IFBPlatformMemoryReserve        reserve;
        IFBPlatformMemoryRelease        release;
        IFBPlatformMemoryCommit         commit;
        IFBPlatformMemoryDecommit       decommit;
    } memory;

    struct {
        IFBPlatformThreadSize           size;
        IFBPlatformThreadCreate         create;
        IFBPlatformThreadDestroy        destroy;
        IFBPlatformThreadAssignCores    assign_cores;
        IFBPlatformThreadWake           wake;
        IFBPlatformThreadSleep          sleep;
    } thread;

    struct {
        IFBPlatformWindowSize          size;
        IFBPlatformWindowCreate        create;
        IFBPlatformWindowDestroy       destroy;
        IFBPlatformWindowProcessEvents process_events;
        IFBPlatformWindowSwapBuffers   swap_buffers;
        IFBPlatformWindowShow          show;
    } window;

    struct {
        IFBPlatformMonitorCount         count;
        IFBPlatformMonitorInfo          info;
    } monitor;

    struct {
        IFBPlatformFileROContextSize    ro_context_size;
        IFBPlatformFileROOpen           ro_open;
        IFBPlatformFileROReadImmediate  ro_close;
        IFBPlatformFileROReadAsync      ro_read_immediate;
        IFBPlatformFileROClose          ro_read_async;
        IFBPlatformFileRWContextSize    rw_context_size;
        IFBPlatformFileRWOpen           rw_open;
        IFBPlatformFileRWReadImmediate  rw_close;
        IFBPlatformFileRWReadAsync      rw_read_immediate;
        IFBPlatformFileRWWriteImmediate rw_read_async;
        IFBPlatformFileRWWriteAsync     rw_write_immediate;
        IFBPlatformFileRWClose          rw_write_async;
    } file;
};

namespace ifb_platform {

    const ifb::b8 set_api (const IFBPlatformAPI* platform_api);

    //------------------
    // system
    //------------------
    extern IFBPlatformSystemGetInfoCPU     system_get_info_cpu;
    extern IFBPlatformSystemGetInfoMemory  system_get_info_memory;
    extern IFBPlatformSystemTimeMS         system_time_ms;
    extern IFBPlatformSystemSleep          system_sleep;
    extern IFBPlatformSystemDebugPrint     system_debug_print;

    //------------------
    // memory
    //------------------
    extern IFBPlatformMemoryReserve        memory_reserve;
    extern IFBPlatformMemoryRelease        memory_release;
    extern IFBPlatformMemoryCommit         memory_commit;
    extern IFBPlatformMemoryDecommit       memory_decommit;

    //------------------
    // thread
    //------------------
    extern IFBPlatformThreadSize           thread_size;
    extern IFBPlatformThreadCreate         thread_create;
    extern IFBPlatformThreadDestroy        thread_destroy;
    extern IFBPlatformThreadAssignCores    thread_assign_cores;
    extern IFBPlatformThreadWake           thread_wake;
    extern IFBPlatformThreadSleep          thread_sleep;

    //------------------
    // window
    //------------------
    extern IFBPlatformWindowSize           window_size;
    extern IFBPlatformWindowCreate         window_create;
    extern IFBPlatformWindowDestroy        window_destroy;
    extern IFBPlatformWindowProcessEvents  window_process_events;
    extern IFBPlatformWindowSwapBuffers    window_swap_buffers;
    extern IFBPlatformWindowShow           window_show;

    //------------------
    // monitor
    //------------------
    extern IFBPlatformMonitorCount         monitor_count;
    extern IFBPlatformMonitorInfo          monitor_info;

    //------------------
    // file
    //------------------
    extern IFBPlatformFileROContextSize    file_ro_context_size;
    extern IFBPlatformFileROOpen           file_ro_open;
    extern IFBPlatformFileROReadImmediate  file_ro_close;
    extern IFBPlatformFileROReadAsync      file_ro_read_immediate;
    extern IFBPlatformFileROClose          file_ro_read_async;
    extern IFBPlatformFileRWContextSize    file_rw_context_size;
    extern IFBPlatformFileRWOpen           file_rw_open;
    extern IFBPlatformFileRWReadImmediate  file_rw_close;
    extern IFBPlatformFileRWReadAsync      file_rw_read_immediate;
    extern IFBPlatformFileRWWriteImmediate file_rw_read_async;
    extern IFBPlatformFileRWWriteAsync     file_rw_write_immediate;
    extern IFBPlatformFileRWClose          file_rw_write_async;
};

#endif //IFB_ENGINE_PLATFORM_HPP