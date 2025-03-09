#ifndef IFB_PLATFORM_HPP
#define IFB_PLATFORM_HPP

#include "ifb-types.hpp"
#include "ifb-scopes.hpp"

/**********************************************************************************/
/* SYSTEM                                                                         */
/**********************************************************************************/

typedef const IFBB8
(*ifb_platform_funcptr_system_get_info)(
    IFBSystemInfo* system_info);

typedef const IFBTimems
(*ifb_platform_funcptr_system_time_ms)(
    IFBVoid);

typedef IFBVoid
(*ifb_platform_funcptr_system_sleep)(
    const IFBU32 ms);

struct IFBPlatformSystemApi {
    ifb_platform_funcptr_system_get_info get_info;
    ifb_platform_funcptr_system_time_ms  time_ms;
    ifb_platform_funcptr_system_sleep    sleep;
};

namespace ifb_platform {
    extern ifb_platform_funcptr_system_get_info system_get_info;
    extern ifb_platform_funcptr_system_time_ms  system_time_ms;
    extern ifb_platform_funcptr_system_sleep    system_sleep;
};

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

typedef const IFBPtr
(*ifb_platform_funcptr_memory_reserve)(
    const IFBU64 reservation_size);

typedef const IFBB8
(*ifb_platform_funcptr_memory_release)(
    const IFBPtr reservation_start,
    const IFBU64 reservation_size);

typedef const IFBPtr
(*ifb_platform_funcptr_memory_commit)(
    const IFBPtr commit_start,
    const IFBU64 commit_size);

typedef const IFBB8
(*ifb_platform_funcptr_memory_decommit)(
    const IFBPtr commit_start,
    const IFBU64 commit_size);

struct IFBPlatformMemoryApi {
    ifb_platform_funcptr_memory_reserve  reserve;
    ifb_platform_funcptr_memory_release  release;
    ifb_platform_funcptr_memory_commit   commit;
    ifb_platform_funcptr_memory_decommit decommit;
};

namespace ifb_platform {

    extern ifb_platform_funcptr_memory_reserve  memory_reserve;
    extern ifb_platform_funcptr_memory_release  memory_release;
    extern ifb_platform_funcptr_memory_commit   memory_commit;
    extern ifb_platform_funcptr_memory_decommit memory_decommit;
};

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

typedef const IFBB8
(*ifb_platform_funcptr_window_create) (
    const IFBCStr title,
    const IFBU32  width,
    const IFBU32  height,
    const IFBU32  position_x,
    const IFBU32  position_y);

typedef IFBGLContext
(*ifb_platform_funcptr_window_opengl_init) (
    IFBVoid);

typedef ImGuiContext*
(*ifb_platform_funcptr_window_imgui_init) (
    IFBVoid);

typedef const IFBB8
(*ifb_platform_funcptr_window_show)(
    IFBVoid);

typedef const IFBB8
(*ifb_platform_funcptr_window_destroy)(
    IFBVoid);

typedef const IFBB8
(*ifb_platform_funcptr_window_frame_start)(
    IFBVoid);

typedef const IFBB8
(*ifb_platform_funcptr_window_frame_render)(
    IFBVoid);

struct IFBPlatformWindowApi {
    ifb_platform_funcptr_window_create       create;
    ifb_platform_funcptr_window_destroy      destroy;
    ifb_platform_funcptr_window_frame_start  frame_start;
    ifb_platform_funcptr_window_frame_render frame_render;
    ifb_platform_funcptr_window_show         show;
    ifb_platform_funcptr_window_opengl_init  opengl_init;
    ifb_platform_funcptr_window_imgui_init   imgui_init;
};

namespace ifb_platform {

    extern ifb_platform_funcptr_window_create       window_create;
    extern ifb_platform_funcptr_window_destroy      window_destroy;
    extern ifb_platform_funcptr_window_frame_start  window_frame_start;
    extern ifb_platform_funcptr_window_frame_render window_frame_render;
    extern ifb_platform_funcptr_window_show         window_show;
    extern ifb_platform_funcptr_window_opengl_init  window_opengl_init;
    extern ifb_platform_funcptr_window_imgui_init   window_imgui_init;
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

typedef const IFBB8
(*ifb_platform_funcptr_file_open_read_only) (
    const IFBCStr    in_file_path,
          IFBIndex& out_file_index_ref);

typedef const IFBB8
(*ifb_platform_funcptr_file_open_read_write) (
    const IFBCStr    in_file_path,
          IFBIndex& out_file_index_ref);

typedef const IFBB8
(*ifb_platform_funcptr_file_open_read_write) (
    const IFBCStr    in_file_path,
          IFBIndex& out_file_index_ref);

typedef const IFBB8
(*ifb_platform_funcptr_file_close) (
    const IFBIndex file_index);

typedef const IFBSize
(*ifb_platform_funcptr_file_size) (
    const IFBIndex file_index);

typedef const IFBB8
(*ifb_platform_funcptr_file_read)(
    const IFBIndex  in_file_index,
    const IFBSize   in_file_read_start,
    const IFBSize   in_file_read_size,
          IFBByte* out_file_read_buffer);

typedef const IFBB8
(*ifb_platform_funcptr_file_write)(
    const IFBIndex file_index,
    const IFBSize  file_write_start,
    const IFBSize  file_write_size,
          IFBByte* file_write_buffer);

struct IFBPlatformFileApi {
    ifb_platform_funcptr_file_open_read_only  open_read_only;
    ifb_platform_funcptr_file_open_read_write open_read_write;
    ifb_platform_funcptr_file_close           close;
    ifb_platform_funcptr_file_size            size;
    ifb_platform_funcptr_file_read            read;
    ifb_platform_funcptr_file_write           write;
};

namespace ifb_platform {

    extern ifb_platform_funcptr_file_open_read_only  open_read_only;
    extern ifb_platform_funcptr_file_open_read_write open_read_write;
    extern ifb_platform_funcptr_file_close           close;
    extern ifb_platform_funcptr_file_size            size;
    extern ifb_platform_funcptr_file_read            read;
    extern ifb_platform_funcptr_file_write           write;
};

/**********************************************************************************/
/* FILE DIALOG                                                                    */
/**********************************************************************************/

typedef const IFBB8
(*ifb_platform_funcptr_file_dialog_select_file) (
    const IFBCStr  in_file_dialog_starting_directory,
    const IFBSize  in_file_type_count,
    const IFBCStr* in_file_type_name_cstr_ptr,
    const IFBCStr* in_file_type_spec_cstr_ptr,
          IFBCStr out_file_selection_buffer);

struct IFBPlatformFileDialogApi {
    ifb_platform_funcptr_file_dialog_select_file select_file;
};

/**********************************************************************************/
/* PLATFORM API                                                                   */
/**********************************************************************************/

struct IFBPlatformApi {
    IFBPlatformSystemApi  system;
    IFBPlatformMemoryApi  memory;
    IFBPlatformWindowApi  window;
    IFBPlatformMonitorApi monitor;
};

#endif //IFB_ENGINE_PLATFORM_HPP