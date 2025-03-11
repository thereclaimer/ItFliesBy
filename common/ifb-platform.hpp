#ifndef IFB_PLATFORM_HPP
#define IFB_PLATFORM_HPP

#include "ifb-types.hpp"
#include "ifb-scopes.hpp"

/**********************************************************************************/
/* SYSTEM                                                                         */
/**********************************************************************************/

typedef const IFBB8     (*ifb_platform_funcptr_system_get_info) (IFBSystemInfo* system_info);
typedef const IFBTimems (*ifb_platform_funcptr_system_time_ms)  (IFBVoid);
typedef IFBVoid         (*ifb_platform_funcptr_system_sleep)    (const IFBU32 ms);

typedef ifb_platform_funcptr_system_get_info IFBPlatformSystemGetInfo;
typedef ifb_platform_funcptr_system_time_ms  IFBPlatformSystemTimeMS;
typedef ifb_platform_funcptr_system_sleep    IFBPlatformSystemSleep;
IFBPlatformSystemGetInfo get_info;
    IFBPlatformSystemTimeMS  time_ms;
    IFBPlatformSystemSleep   sleep;
};

namespace ifb_platform {
    extern IFBPlatformSystemGetInfo system_get_info;
    extern IFBPlatformSystemTimeMS  system_time_ms;
    extern IFBPlatform][[9]p\SystemSleep   system_sleep;
};

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

typedef const IFBPtr (*ifb_platform_funcptr_memory_reserve)  (const IFBU64 reservation_size);
typedef const IFBB8  (*ifb_platform_funcptr_memory_release)  (const IFBPtr reservation_start, const IFBU64 reservation_size);
typedef const IFBPtr (*ifb_platform_funcptr_memory_commit)   (const IFBPtr commit_start,      const IFBU64 commit_size);
typedef const IFBB8  (*ifb_platform_funcptr_memory_decommit) (const IFBPtr commit_start,      const IFBU64 commit_size);

typedef ifb_platform_funcptr_memory_reserve  IFBPlatformMemoryReserve;
typedef ifb_platform_funcptr_memory_release  IFBPlatformMemoryRelease;
typedef ifb_platform_funcptr_memory_commit   IFBPlatformMemoryCommit;
typedef ifb_platform_funcptr_memory_decommit IFBPlatformMemoryDecommit;

struct IFBPlatformMemoryApi {
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

typedef const IFBB8 (*ifb_platform_funcptr_thread_create)  (IFBThread* ptr_thread);
typedef const IFBB8 (*ifb_platform_funcptr_thread_destroy) (IFBThread* ptr_thread);

struct IFBPlatformThreadApi {
    ifb_platform_funcptr_thread_create  create;
    ifb_platform_funcptr_thread_destroy destroy;
};

namespace ifb_platform {

    extern ifb_platform_funcptr_thread_create  thread_create;
    extern ifb_platform_funcptr_thread_destroy thread_destroy;
};

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

typedef const IFBB8
(*ifb_platform_funcptr_window_create) (
    const IFBChar* title,
    const IFBU32   width,
    const IFBU32   height,
    const IFBU32   position_x,
    const IFBU32   position_y);

typedef IFBGLContext  (*ifb_platform_funcptr_window_opengl_init)  (IFBVoid);
typedef ImGuiContext* (*ifb_platform_funcptr_window_imgui_init)   (IFBVoid);
typedef const IFBB8   (*ifb_platform_funcptr_window_show)         (IFBVoid);
typedef const IFBB8   (*ifb_platform_funcptr_window_destroy)      (IFBVoid);
typedef const IFBB8   (*ifb_platform_funcptr_window_frame_start)  (IFBVoid);
typedef const IFBB8   (*ifb_platform_funcptr_window_frame_render) (IFBVoid);

typedef ifb_platform_funcptr_window_create       IFBPlatformWindowCreate;
typedef ifb_platform_funcptr_window_destroy      IFBPlatformWindowDestroy;
typedef ifb_platform_funcptr_window_frame_start  IFBPlatformWindowFrameStart;
typedef ifb_platform_funcptr_window_frame_render IFBPlatformWindowFrameRender;
typedef ifb_platform_funcptr_window_show         IFBPlatformWindowShow;
typedef ifb_platform_funcptr_window_opengl_init  IFBPlatformWindowOpenGLInit;
typedef ifb_platform_funcptr_window_imgui_init   IFBPlatformWindowImGUIInit;

struct IFBPlatformWindowApi {
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
(*ifb_platform_funcptr_monitor_count) (
    IFBVoid);

typedef const IFBB8
(*ifb_platform_funcptr_monitor_info)(
    const IFBU32      monitor_count,
          IFBMonitor* monitor_array);

struct IFBPlatformMonitorApi {
    ifb_platform_funcptr_monitor_count count;
    ifb_platform_funcptr_monitor_info  info;
};

namespace ifb_platform {

    extern ifb_platform_funcptr_monitor_count monitor_count;
    extern ifb_platform_funcptr_monitor_info  monitor_info;
};

/**********************************************************************************/
/* FILES                                                                          */                            
/**********************************************************************************/

typedef const IFBB8 (*ifb_platform_func_ptr_file_ro_open)            (IFBFileReadOnly*  file_read_only,  const IFBChar* file_path);
typedef const IFBB8 (*ifb_platform_func_ptr_file_ro_read_immediate)  (IFBFileReadOnly*  file_read_only,  const IFBU32   read_buffer_size,  IFBByte* read_buffer_ptr, const IFBU32 file_offset);
typedef const IFBB8 (*ifb_platform_func_ptr_file_ro_read_async)      (IFBFileReadOnly*  file_read_only,  const IFBU32   read_buffer_size,  IFBByte* read_buffer_ptr, const IFBU32 file_offset);
typedef const IFBB8 (*ifb_platform_func_ptr_file_ro_close)           (IFBFileReadOnly*  file_read_only);

typedef const IFBB8 (*ifb_platform_func_ptr_file_rw_open)            (IFBFileReadWrite* file_read_write, const IFBChar* file_path);
typedef const IFBB8 (*ifb_platform_func_ptr_file_rw_read_immediate)  (IFBFileReadWrite* file_read_write, const IFBU32   read_buffer_size,  IFBByte*       read_buffer_ptr);
typedef const IFBB8 (*ifb_platform_func_ptr_file_rw_read_async)      (IFBFileReadWrite* file_read_write, const IFBU32   read_buffer_size,  IFBByte*       read_buffer_ptr);
typedef const IFBB8 (*ifb_platform_func_ptr_file_rw_write_immediate) (IFBFileReadWrite* file_read_write, const IFBU32   write_buffer_size, const IFBByte* write_buffer_ptr);
typedef const IFBB8 (*ifb_platform_func_ptr_file_rw_write_async)     (IFBFileReadWrite* file_read_write, const IFBU32   write_buffer_size, const IFBByte* write_buffer_ptr);
typedef const IFBB8 (*ifb_platform_func_ptr_file_rw_close)           (IFBFileReadWrite* file_read_write);

typedef ifb_platform_func_ptr_file_ro_open            IFBPlatformFileROOpen;
typedef ifb_platform_func_ptr_file_ro_read_immediate  IFBPlatformFileROReadImmediate;
typedef ifb_platform_func_ptr_file_ro_read_async      IFBPlatformFileROReadAsync;
typedef ifb_platform_func_ptr_file_ro_close           IFBPlatformFileROClose;
typedef ifb_platform_func_ptr_file_rw_open            IFBPlatformFileROOpen;
typedef ifb_platform_func_ptr_file_rw_read_immediate  IFBPlatformFileROReadImmediate;
typedef ifb_platform_func_ptr_file_rw_read_async      IFBPlatformFileROReadAsync;
typedef ifb_platform_func_ptr_file_rw_write_immediate IFBPlatformFileROWriteImmediate;
typedef ifb_platform_func_ptr_file_rw_write_async     IFBPlatformFileROWriteAsync;
typedef ifb_platform_func_ptr_file_rw_close           IFBPlatformFileROClose;

struct IFBPlatformFileApi {
    IFBPlatformFileROOpen           ro_open;
    IFBPlatformFileROReadImmediate  ro_close;
    IFBPlatformFileROReadAsync      ro_read_immediate;
    IFBPlatformFileROClose          ro_read_async;
    IFBPlatformFileROOpen           rw_open;
    IFBPlatformFileROReadImmediate  rw_close;
    IFBPlatformFileROReadAsync      rw_read_immediate;
    IFBPlatformFileROWriteImmediate rw_read_async;
    IFBPlatformFileROWriteAsync     rw_write_immediate;
    IFBPlatformFileROClose          rw_write_async;
};

namespace ifb_platform {

    extern IFBPlatformFileROOpen           file_ro_open;
    extern IFBPlatformFileROReadImmediate  file_ro_close;
    extern IFBPlatformFileROReadAsync      file_ro_read_immediate;
    extern IFBPlatformFileROClose          file_ro_read_async;
    extern IFBPlatformFileROOpen           file_rw_open;
    extern IFBPlatformFileROReadImmediate  file_rw_close;
    extern IFBPlatformFileROReadAsync      file_rw_read_immediate;
    extern IFBPlatformFileROWriteImmediate file_rw_read_async;
    extern IFBPlatformFileROWriteAsync     file_rw_write_immediate;
    extern IFBPlatformFileROClose          file_rw_write_async;
};

/**********************************************************************************/
/* FILE DIALOG                                                                    */
/**********************************************************************************/

typedef const IFBB8
(*ifb_platform_funcptr_file_dialog_select_file) (
    const IFBChar*  in_file_dialog_starting_directory,
    const IFBSize   in_file_type_count,
    const IFBChar** in_file_type_name_cstr_ptr,
    const IFBChar** in_file_type_spec_cstr_ptr,
          IFBChar* out_file_selection_buffer);

struct IFBPlatformFileDialogApi {
    ifb_platform_funcptr_file_dialog_select_file select_file;
};

/**********************************************************************************/
/* PLATFORM API                                                                   */
/**********************************************************************************/

struct IFBPlatformApi {
    IFBPlatformSystemApi  system;
    IFBPlatformMemoryApi  memory;
    IFBPlatformThreadApi  thread;
    IFBPlatformWindowApi  window;
    IFBPlatformFileApi    file;
    IFBPlatformMonitorApi monitor;
};

#endif //IFB_ENGINE_PLATFORM_HPP