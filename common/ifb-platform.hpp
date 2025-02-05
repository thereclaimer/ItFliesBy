#ifndef IFB_PLATFORM_HPP
#define IFB_PLATFORM_HPP

#include "ifb-types.hpp"
#include "ifb-scopes.hpp"
#include "ifb-graphics.hpp"

/**********************************************************************************/
/* SYSTEM                                                                         */
/**********************************************************************************/

typedef const ifb_u32
(*funcptr_ifb_platform_system_page_size)(
    ifb_void);

typedef const ifb_u32
(*funcptr_ifb_platform_system_allocation_granularity)(
    ifb_void);

typedef const ifb_timems
(*funcptr_ifb_platform_system_time_ms)(
    ifb_void);

typedef ifb_void
(*funcptr_ifb_platform_system_sleep)(
    const ifb_u32 ms);

struct IFBPlatformSystemApi {
    funcptr_ifb_platform_system_page_size              page_size;
    funcptr_ifb_platform_system_allocation_granularity allocation_granularity;
    funcptr_ifb_platform_system_time_ms                time_ms;
    funcptr_ifb_platform_system_sleep                  sleep;
};

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

typedef const ifb_ptr
(*funcptr_ifb_platform_memory_reserve)(
    const ifb_u32 reservation_size);

typedef const ifb_b8
(*funcptr_ifb_platform_memory_release)(
    const ifb_ptr reservation_start,
    const ifb_u32 reservation_size);

typedef const ifb_ptr
(*funcptr_ifb_platform_memory_commit)(
    const ifb_ptr commit_start,
    const ifb_u32 commit_size);

struct IFBPlatformMemoryApi {
    funcptr_ifb_platform_memory_reserve reserve;
    funcptr_ifb_platform_memory_release release;
    funcptr_ifb_platform_memory_commit  commit;
};

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

typedef const ifb_b8
(*funcptr_ifb_platform_window_create) (
    const ifb_cstr title,
    const ifb_u32  width,
    const ifb_u32  height,
    const ifb_u32  position_x,
    const ifb_u32  position_y);

typedef const ifb_b8
(*funcptr_ifb_platform_window_opengl_init) (
    ifb_void);

typedef ImGuiContext*
(*funcptr_ifb_platform_window_imgui_init) (
    ifb_void);

typedef const ifb_b8
(*funcptr_ifb_platform_window_show)(
    ifb_void);

typedef const ifb_b8
(*funcptr_ifb_platform_window_destroy)(
    ifb_void);

typedef const ifb_b8
(*funcptr_ifb_platform_window_frame_start)(
    ifb_void);

typedef const ifb_b8
(*funcptr_ifb_platform_window_frame_render)(
    ifb_void);

struct IFBPlatformWindowApi {
    funcptr_ifb_platform_window_create       create;
    funcptr_ifb_platform_window_destroy      destroy;
    funcptr_ifb_platform_window_frame_start  frame_start;
    funcptr_ifb_platform_window_frame_render frame_render;
    funcptr_ifb_platform_window_show         show;
    funcptr_ifb_platform_window_opengl_init  opengl_init;
    funcptr_ifb_platform_window_imgui_init   imgui_init;
};

/**********************************************************************************/
/* MONITOR                                                                        */
/**********************************************************************************/

typedef const ifb_u32
(*funcptr_ifb_platform_monitor_count) (
    ifb_void);

typedef ifb_void
(*funcptr_ifb_platform_monitor_info)(
    const ifb_u32     monitor_array_count,
          IFBMonitor* monitor_array_ptr);

struct IFBPlatformMonitorApi {
    funcptr_ifb_platform_monitor_count count;
    funcptr_ifb_platform_monitor_info  info;
};

/**********************************************************************************/
/* FILES                                                                          */                            
/**********************************************************************************/

typedef const ifb_b8
(*funcptr_ifb_platform_file_open_read_only) (
    const ifb_cstr    in_file_path,
          ifb_index& out_file_index_ref);

typedef const ifb_b8
(*funcptr_ifb_platform_file_open_read_write) (
    const ifb_cstr    in_file_path,
          ifb_index& out_file_index_ref);

typedef const ifb_b8
(*funcptr_ifb_platform_file_open_read_write) (
    const ifb_cstr    in_file_path,
          ifb_index& out_file_index_ref);

typedef const ifb_b8
(*funcptr_ifb_platform_file_close) (
    const ifb_index file_index);

typedef const ifb_size
(*funcptr_ifb_platform_file_size) (
    const ifb_index file_index);

typedef const ifb_b8
(*funcptr_ifb_platform_file_read)(
    const ifb_index  in_file_index,
    const ifb_size   in_file_read_start,
    const ifb_size   in_file_read_size,
          ifb_byte* out_file_read_buffer);

typedef const ifb_b8
(*funcptr_ifb_platform_file_write)(
    const ifb_index file_index,
    const ifb_size  file_write_start,
    const ifb_size  file_write_size,
          ifb_byte* file_write_buffer);

struct IFBPlatformFileApi {
    funcptr_ifb_platform_file_open_read_only  open_read_only;
    funcptr_ifb_platform_file_open_read_write open_read_write;
    funcptr_ifb_platform_file_close           close;
    funcptr_ifb_platform_file_size            size;
    funcptr_ifb_platform_file_read            read;
    funcptr_ifb_platform_file_write           write;
};

/**********************************************************************************/
/* FILE DIALOG                                                                    */
/**********************************************************************************/

typedef const ifb_b8
(*funcptr_ifb_platform_file_dialog_select_file) (
    const ifb_cstr  in_file_dialog_starting_directory,
    const ifb_size  in_file_type_count,
    const ifb_cstr* in_file_type_name_cstr_ptr,
    const ifb_cstr* in_file_type_spec_cstr_ptr,
          ifb_cstr out_file_selection_buffer);

struct IFBPlatformFileDialogApi {
    funcptr_ifb_platform_file_dialog_select_file select_file;
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