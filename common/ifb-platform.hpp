#ifndef IFB_PLATFORM_HPP
#define IFB_PLATFORM_HPP

#include "ifb-types.hpp"
#include "ifb-scopes.hpp"

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

// typedef const IFBB8
// (*IFBPlatformThreadCreate) (
//     const IFBThreadPlatformContext* thread_context,
//     const IFBU32                    thread_count,
//     const IFBChar*                  thread_description,
//     const IFBU32                    thread_description_stride,
//           IFBU64*                   thread_id);

// typedef const IFBB8 (*IFBPlatformThreadDestroy)     (const IFBThreadPlatformContext* thread_context, const IFBU32 thread_count);
// typedef const IFBB8 (*IFBPlatformThreadAssignCores) (const IFBThreadPlatformContext* thread_context, const IFBU32 thread_count, const IFBU64* thread_core_mask);
// typedef const IFBB8 (*IFBPlatformThreadWake)        (const IFBThreadPlatformContext* thread_context, const IFBU32 thread_count);
// typedef const IFBB8 (*IFBPlatformThreadSleep)       (const IFBThreadPlatformContext* thread_context, const IFBU32 thread_count);
// typedef const IFBB8 (*IFBPlatformThreadGetStatus)   (const IFBThreadPlatformContext* thread_context, const IFBU32 thread_count, IFBThreadStatus* thread_status);

// struct IFBPlatformAPIThread {
//     IFBPlatformThreadCreate      create;
//     IFBPlatformThreadDestroy     destroy;
//     IFBPlatformThreadAssignCores assign_cores;
//     IFBPlatformThreadWake        wake;
//     IFBPlatformThreadSleep       sleep;
// };

// namespace ifb_platform {

//     extern IFBPlatformThreadCreate      thread_create;
//     extern IFBPlatformThreadDestroy     thread_destroy;
//     extern IFBPlatformThreadAssignCores thread_assign_cores;
//     extern IFBPlatformThreadWake        thread_wake;
//     extern IFBPlatformThreadSleep       thread_sleep;
// };

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

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

typedef const IFBU32 (*IFBPlatformFileROContextSize)    (IFBVoid);
typedef const IFBB8  (*IFBPlatformFileROOpen)           (IFBFileRequest* file_ro_request);
typedef const IFBB8  (*IFBPlatformFileROReadImmediate)  (IFBFileRequest* file_ro_request);
typedef const IFBB8  (*IFBPlatformFileROReadAsync)      (IFBFileRequest* file_ro_request);
typedef const IFBB8  (*IFBPlatformFileROClose)          (IFBFileRequest* file_ro_request);

typedef const IFBU32 (*IFBPlatformFileRWContextSize)    (IFBVoid);
typedef const IFBB8  (*IFBPlatformFileRWOpen)           (IFBFileRequest* file_rw_request);
typedef const IFBB8  (*IFBPlatformFileRWReadImmediate)  (IFBFileRequest* file_rw_request);
typedef const IFBB8  (*IFBPlatformFileRWReadAsync)      (IFBFileRequest* file_rw_request);
typedef const IFBB8  (*IFBPlatformFileRWWriteImmediate) (IFBFileRequest* file_rw_request);
typedef const IFBB8  (*IFBPlatformFileRWWriteAsync)     (IFBFileRequest* file_rw_request);
typedef const IFBB8  (*IFBPlatformFileRWClose)          (IFBFileRequest* file_rw_request);

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
    // IFBPlatformAPIThread  thread;
    IFBPlatformAPIWindow  window;
    IFBPlatformAPIFile    file;
    IFBPlatformAPIMonitor monitor;
};

#endif //IFB_ENGINE_PLATFORM_HPP