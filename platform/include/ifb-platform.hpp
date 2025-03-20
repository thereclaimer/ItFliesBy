#ifndef IFB_PLATFORM_HPP
#define IFB_PLATFORM_HPP

#include <ifb.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBPlatformAPI;
struct IFBPlatformAPISystem;
struct IFBPlatformAPIMemory;
struct IFBPlatformAPIThread;
struct IFBPlatformAPIWindow;
struct IFBPlatformAPIFile;
struct IFBPlatformAPIMonitor;

/**********************************************************************************/
/* SYSTEM                                                                         */
/**********************************************************************************/


struct IFBSystemMemoryInfo {
    IFBU32 page_size;
    IFBU32 allocation_granularity;
};

struct IFBSystemCPUCacheInfo {
    IFBU32 size_total;
    IFBU32 size_line;
};

struct IFBSystemCPUInfo {
    IFBU32                parent_core_number;
    IFBU32                speed_mhz;
    IFBU32                core_count_physical;
    IFBU32                core_count_logical;
    IFBSystemCPUCacheInfo cache_l1;
    IFBSystemCPUCacheInfo cache_l2;
    IFBSystemCPUCacheInfo cache_l3;
};

struct IFBSystemInfo {
    IFBSystemCPUInfo    cpu;
    IFBSystemMemoryInfo memory;
};

typedef const IFBB8     (*IFBPlatformSystemGetInfo)    (IFBSystemInfo* system_info);
typedef const IFBTimems (*IFBPlatformSystemTimeMS)     (IFBVoid);
typedef IFBVoid         (*IFBPlatformSystemSleep)      (const IFBU32   ms);
typedef IFBVoid         (*IFBPlatformSystemDebugPrint) (const IFBChar* debug_string);

struct IFBPlatformAPISystem {
    IFBPlatformSystemGetInfo    get_info;
    IFBPlatformSystemTimeMS     time_ms;
    IFBPlatformSystemSleep      sleep;
    IFBPlatformSystemDebugPrint debug_print;
};

namespace ifb_platform {
    extern IFBPlatformSystemGetInfo    system_get_info;
    extern IFBPlatformSystemTimeMS     system_time_ms;
    extern IFBPlatformSystemSleep      system_sleep;
    extern IFBPlatformSystemDebugPrint system_debug_print;
};

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

typedef const IFBPtr (*IFBPlatformMemoryReserve)  (const IFBU64 reservation_size);
typedef const IFBB8  (*IFBPlatformMemoryRelease)  (const IFBPtr reservation_start, const IFBU64 reservation_size);
typedef const IFBPtr (*IFBPlatformMemoryCommit)   (const IFBPtr commit_start,      const IFBU64 commit_size);
typedef const IFBB8  (*IFBPlatformMemoryDecommit) (const IFBPtr commit_start,      const IFBU64 commit_size);

struct IFBPlatformAPIMemory {
    IFBPlatformMemoryReserve  reserve;
    IFBPlatformMemoryRelease  release;
    IFBPlatformMemoryCommit   commit;
    IFBPlatformMemoryDecommit decommit;
};

namespace ifb_platform {

    extern IFBPlatformMemoryReserve  memory_reserve;
    extern IFBPlatformMemoryRelease  memory_release;
    extern IFBPlatformMemoryCommit   memory_commit;
    extern IFBPlatformMemoryDecommit memory_decommit;
};

/**********************************************************************************/
/* THREADS                                                                        */
/**********************************************************************************/

struct IFBPlatformThreadContext {
};

struct IFBPlatformThreadRequest {
    IFBPlatformThreadContext* context_array;
    IFBU64                    thread_count;
};

typedef const IFBU32 (*IFBPlatformThreadSize)        (IFBVoid);
typedef const IFBB8  (*IFBPlatformThreadCreate)      (const IFBPlatformThreadRequest* request);
typedef const IFBB8  (*IFBPlatformThreadDestroy)     (const IFBPlatformThreadRequest* request);
typedef const IFBB8  (*IFBPlatformThreadAssignCores) (const IFBPlatformThreadRequest* request);
typedef const IFBB8  (*IFBPlatformThreadWake)        (const IFBPlatformThreadRequest* request);
typedef const IFBB8  (*IFBPlatformThreadSleep)       (const IFBPlatformThreadRequest* request);
typedef const IFBB8  (*IFBPlatformThreadGetStatus)   (const IFBPlatformThreadRequest* request);

struct IFBPlatformAPIThread {
    IFBPlatformThreadSize        size;
    IFBPlatformThreadCreate      create;
    IFBPlatformThreadDestroy     destroy;
    IFBPlatformThreadAssignCores assign_cores;
    IFBPlatformThreadWake        wake;
    IFBPlatformThreadSleep       sleep;
};

namespace ifb_platform {

    extern IFBPlatformThreadSize        thread_size;
    extern IFBPlatformThreadCreate      thread_create;
    extern IFBPlatformThreadDestroy     thread_destroy;
    extern IFBPlatformThreadAssignCores thread_assign_cores;
    extern IFBPlatformThreadWake        thread_wake;
    extern IFBPlatformThreadSleep       thread_sleep;
};

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

typedef IFBVoid* IFBGLContext;

typedef const IFBB8
(*IFBPlatformWindowCreate) (
    const IFBChar* title,
    const IFBU32   width,
    const IFBU32   height,
    const IFBU32   position_x,
    const IFBU32   position_y);

typedef const IFBB8   (*IFBPlatformWindowDestroy)     (IFBVoid);
typedef const IFBB8   (*IFBPlatformWindowFrameStart)  (IFBVoid);
typedef const IFBB8   (*IFBPlatformWindowFrameRender) (IFBVoid);
typedef const IFBB8   (*IFBPlatformWindowShow)        (IFBVoid);
typedef IFBGLContext  (*IFBPlatformWindowOpenGLInit)  (IFBVoid);
typedef ImGuiContext* (*IFBPlatformWindowImGUIInit)   (IFBVoid);

struct IFBPlatformAPIWindow {
    IFBPlatformWindowCreate      create;
    IFBPlatformWindowDestroy     destroy;
    IFBPlatformWindowFrameStart  frame_start;
    IFBPlatformWindowFrameRender frame_render;
    IFBPlatformWindowShow        show;
    IFBPlatformWindowOpenGLInit  opengl_init;
    IFBPlatformWindowImGUIInit   imgui_init;
};

namespace ifb_platform {

    extern IFBPlatformWindowCreate      window_create;
    extern IFBPlatformWindowDestroy     window_destroy;
    extern IFBPlatformWindowFrameStart  window_frame_start;
    extern IFBPlatformWindowFrameRender window_frame_render;
    extern IFBPlatformWindowShow        window_show;
    extern IFBPlatformWindowOpenGLInit  window_opengl_init;
    extern IFBPlatformWindowImGUIInit   window_imgui_init;
};

/**********************************************************************************/
/* MONITOR                                                                        */
/**********************************************************************************/

struct IFBMonitor;

typedef const IFBU32
(*IFBPlatformMonitorCount) (
    IFBVoid);

typedef const IFBB8
(*IFBPlatformMonitorInfo)(
    const IFBU32      monitor_count,
          IFBMonitor* monitor_array);

struct IFBPlatformAPIMonitor {
    IFBPlatformMonitorCount count;
    IFBPlatformMonitorInfo  info;
};

namespace ifb_platform {

    extern IFBPlatformMonitorCount monitor_count;
    extern IFBPlatformMonitorInfo  monitor_info;
};

/**********************************************************************************/
/* FILES                                                                          */                            
/**********************************************************************************/

struct IFBPlatformFileRequest {
    IFBPtr x; //TEMPORARY
};

typedef const IFBU32 (*IFBPlatformFileROContextSize)    (IFBVoid);
typedef const IFBB8  (*IFBPlatformFileROOpen)           (IFBPlatformFileRequest* file_ro_request);
typedef const IFBB8  (*IFBPlatformFileROReadImmediate)  (IFBPlatformFileRequest* file_ro_request);
typedef const IFBB8  (*IFBPlatformFileROReadAsync)      (IFBPlatformFileRequest* file_ro_request);
typedef const IFBB8  (*IFBPlatformFileROClose)          (IFBPlatformFileRequest* file_ro_request);

typedef const IFBU32 (*IFBPlatformFileRWContextSize)    (IFBVoid);
typedef const IFBB8  (*IFBPlatformFileRWOpen)           (IFBPlatformFileRequest* file_rw_request);
typedef const IFBB8  (*IFBPlatformFileRWReadImmediate)  (IFBPlatformFileRequest* file_rw_request);
typedef const IFBB8  (*IFBPlatformFileRWReadAsync)      (IFBPlatformFileRequest* file_rw_request);
typedef const IFBB8  (*IFBPlatformFileRWWriteImmediate) (IFBPlatformFileRequest* file_rw_request);
typedef const IFBB8  (*IFBPlatformFileRWWriteAsync)     (IFBPlatformFileRequest* file_rw_request);
typedef const IFBB8  (*IFBPlatformFileRWClose)          (IFBPlatformFileRequest* file_rw_request);

struct IFBPlatformAPIFile {
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
};

namespace ifb_platform {

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

/**********************************************************************************/
/* PLATFORM API                                                                   */
/**********************************************************************************/

struct IFBPlatformAPI {
    IFBPlatformAPISystem  system;
    IFBPlatformAPIMemory  memory;
    IFBPlatformAPIThread  thread;
    IFBPlatformAPIWindow  window;
    IFBPlatformAPIFile    file;
    IFBPlatformAPIMonitor monitor;
};

namespace ifb_platform {

    const IFBB8 set_api (const IFBPlatformAPI* platform_api);
};

#endif //IFB_ENGINE_PLATFORM_HPP