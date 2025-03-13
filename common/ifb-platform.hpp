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

typedef const IFBB8
(*IFBPlatformThreadCreate) (
    const IFBThreadPlatformContext* thread_context,
    const IFBU32                    thread_count,
    const IFBChar*                  thread_description,
    const IFBU32                    thread_description_stride,
          IFBU64*                   thread_id);

typedef const IFBB8 (*IFBPlatformThreadDestroy)     (const IFBThreadPlatformContext* thread_context, const IFBU32 thread_count);
typedef const IFBB8 (*IFBPlatformThreadAssignCores) (const IFBThreadPlatformContext* thread_context, const IFBU32 thread_count, const IFBU64* thread_core_mask);
typedef const IFBB8 (*IFBPlatformThreadWake)        (const IFBThreadPlatformContext* thread_context, const IFBU32 thread_count);
typedef const IFBB8 (*IFBPlatformThreadSleep)       (const IFBThreadPlatformContext* thread_context, const IFBU32 thread_count);
typedef const IFBB8 (*IFBPlatformThreadGetStatus)   (const IFBThreadPlatformContext* thread_context, const IFBU32 thread_count, IFBThreadStatus* thread_status);

struct IFBPlatformAPIThread {
    IFBPlatformThreadCreate      create;
    IFBPlatformThreadDestroy     destroy;
    IFBPlatformThreadAssignCores assign_cores;
    IFBPlatformThreadWake        wake;
    IFBPlatformThreadSleep       sleep;
};

namespace ifb_platform {

    extern IFBPlatformThreadCreate      thread_create;
    extern IFBPlatformThreadDestroy     thread_destroy;
    extern IFBPlatformThreadAssignCores thread_assign_cores;
    extern IFBPlatformThreadWake        thread_wake;
    extern IFBPlatformThreadSleep       thread_sleep;
};

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

typedef const IFBB8 (*IFBPlatformFileROOpen)           (IFBFileReadOnly*  file_read_only,  const IFBChar* file_path);
typedef const IFBB8 (*IFBPlatformFileROReadImmediate)  (IFBFileReadOnly*  file_read_only,  const IFBU32   read_buffer_size,  IFBByte* read_buffer_ptr, const IFBU32 file_offset);
typedef const IFBB8 (*IFBPlatformFileROReadAsync)      (IFBFileReadOnly*  file_read_only,  const IFBU32   read_buffer_size,  IFBByte* read_buffer_ptr, const IFBU32 file_offset);
typedef const IFBB8 (*IFBPlatformFileROClose)          (IFBFileReadOnly*  file_read_only);

typedef const IFBB8 (*IFBPlatformFileRWOpen)           (IFBFileReadWrite* file_read_write, const IFBChar* file_path);
typedef const IFBB8 (*IFBPlatformFileRWReadImmediate)  (IFBFileReadWrite* file_read_write, const IFBU32   read_buffer_size,  IFBByte*       read_buffer_ptr);
typedef const IFBB8 (*IFBPlatformFileRWReadAsync)      (IFBFileReadWrite* file_read_write, const IFBU32   read_buffer_size,  IFBByte*       read_buffer_ptr);
typedef const IFBB8 (*IFBPlatformFileRWWriteImmediate) (IFBFileReadWrite* file_read_write, const IFBU32   write_buffer_size, const IFBByte* write_buffer_ptr);
typedef const IFBB8 (*IFBPlatformFileRWWriteAsync)     (IFBFileReadWrite* file_read_write, const IFBU32   write_buffer_size, const IFBByte* write_buffer_ptr);
typedef const IFBB8 (*IFBPlatformFileRWClose)          (IFBFileReadWrite* file_read_write);

struct IFBPlatformAPIFile {
    IFBPlatformFileROOpen           ro_open;
    IFBPlatformFileROReadImmediate  ro_close;
    IFBPlatformFileROReadAsync      ro_read_immediate;
    IFBPlatformFileROClose          ro_read_async;
    IFBPlatformFileRWOpen           rw_open;
    IFBPlatformFileRWReadImmediate  rw_close;
    IFBPlatformFileRWReadAsync      rw_read_immediate;
    IFBPlatformFileRWWriteImmediate rw_read_async;
    IFBPlatformFileRWWriteAsync     rw_write_immediate;
    IFBPlatformFileRWClose          rw_write_async;
};

namespace ifb_platform {

    extern IFBPlatformFileROOpen           file_ro_open;
    extern IFBPlatformFileROReadImmediate  file_ro_close;
    extern IFBPlatformFileROReadAsync      file_ro_read_immediate;
    extern IFBPlatformFileROClose          file_ro_read_async;
    extern IFBPlatformFileRWOpen           file_rw_open;
    extern IFBPlatformFileRWReadImmediate  file_rw_close;
    extern IFBPlatformFileRWReadAsync      file_rw_read_immediate;
    extern IFBPlatformFileRWWriteImmediate file_rw_read_async;
    extern IFBPlatformFileRWWriteAsync     file_rw_write_immediate;
    extern IFBPlatformFileRWClose          file_rw_write_async;
};

/**********************************************************************************/
/* FILE DIALOG                                                                    */
/**********************************************************************************/

typedef const IFBB8
(*IFBPlatformFileDialogSelectFile) (
    const IFBChar*  in_file_dialog_starting_directory,
    const IFBSize   in_file_type_count,
    const IFBChar** in_file_type_name_cstr_ptr,
    const IFBChar** in_file_type_spec_cstr_ptr,
          IFBChar* out_file_selection_buffer);

struct IFBPlatformFileDialogApi {
    IFBPlatformFileDialogSelectFile select_file;
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

#endif //IFB_ENGINE_PLATFORM_HPP