#ifndef IFB_ENGINE_PLATFORM_HPP
#define IFB_ENGINE_PLATFORM_HPP

#include <ifb-common.hpp>

/**********************************************************************************/
/* SYSTEM                                                                         */
/**********************************************************************************/

typedef const ifb_size
(*funcptr_ifb_engine_platform_system_page_size)(
    ifb_void);
typedef const ifb_size
(*funcptr_ifb_engine_platform_system_allocation_granularity)(
    ifb_void);

struct IFBEnginePlatformSystem {
    funcptr_ifb_engine_platform_system_page_size              page_size;
    funcptr_ifb_engine_platform_system_allocation_granularity allocation_granularity;
};

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

typedef const ifb_memory
(*funcptr_ifb_engine_platform_memory_pages_commit)(
    const ifb_memory commit_start,
    const ifb_size   commit_size);

typedef const ifb_b8
(*funcptr_ifb_engine_platform_memory_pages_decommit)(
    const ifb_memory commit_start,
    const ifb_size   commit_size);

struct IFBEnginePlatformMemory {
    funcptr_ifb_engine_platform_memory_pages_commit   pages_commit;
    funcptr_ifb_engine_platform_memory_pages_decommit pages_decommit;
};

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

typedef const ifb_b8
(*funcptr_ifb_engine_platform_window_create) (
    const ifb_cstr window_title,
    const ifb_u32  window_width,
    const ifb_u32  window_height,
    const ifb_u32  window_position_x,
    const ifb_u32  window_position_y);

typedef const ifb_b8
(*funcptr_ifb_engine_platform_window_opengl_init) (
    ifb_void);

typedef const ifb_b8
(*funcptr_ifb_engine_platform_window_imgui_init) (
    ifb_void);

typedef const ifb_b8
(*funcptr_ifb_engine_platform_window_show)(
    ifb_void);

typedef const ifb_b8
(*funcptr_ifb_engine_platform_window_destroy)(
    ifb_void);

typedef const ifb_b8
(*funcptr_ifb_engine_platform_window_frame_start)(
    ifb_void);

typedef const ifb_b8
(*funcptr_ifb_engine_platform_window_frame_render)(
    ifb_void);

struct IFBEnginePlatformWindow {
    funcptr_ifb_engine_platform_window_create       create;
    funcptr_ifb_engine_platform_window_destroy      destroy;
    funcptr_ifb_engine_platform_window_frame_start  frame_start;
    funcptr_ifb_engine_platform_window_frame_render frame_render;
    funcptr_ifb_engine_platform_window_show         show;
    funcptr_ifb_engine_platform_window_opengl_init  opengl_init;
    funcptr_ifb_engine_platform_window_imgui_init   imgui_init;
};

namespace ifb_engine {

    ifb_api ifb_void platform_window_update_size     (const ifb_u32 window_width,      const ifb_u32 window_height);
    ifb_api ifb_void platform_window_update_position (const ifb_u32 window_position_x, const ifb_u32 window_position_y);
};

/**********************************************************************************/
/* MONITOR                                                                        */
/**********************************************************************************/

struct IFBEnginePlatformMonitorSize {
    ifb_u32 width;
    ifb_u32 height;
}; 

typedef ifb_void
(*funcptr_ifb_engine_platform_monitor_size)(
    IFBEnginePlatformMonitorSize& monitor_size_ref);

typedef const ifb_u32
(*funcptr_ifb_engine_platform_monitor_refresh_hz)(
    ifb_void);

struct IFBEnginePlatformMonitor {
    funcptr_ifb_engine_platform_monitor_size       size;
    funcptr_ifb_engine_platform_monitor_refresh_hz refresh_hz;
};

/**********************************************************************************/
/* FILES                                                                          */
/**********************************************************************************/

typedef ifb_index IFBEnginePlatformFileIndex;

typedef const ifb_b8
(*funcptr_ifb_engine_platform_file_open_read_only) (
    const ifb_cstr                     in_file_path,
          IFBEnginePlatformFileIndex& out_file_index_ref);

typedef const ifb_b8
(*funcptr_ifb_engine_platform_file_open_read_write) (
    const ifb_cstr                     in_file_path,
          IFBEnginePlatformFileIndex& out_file_index_ref);

typedef const ifb_b8
(*funcptr_ifb_engine_platform_file_open_read_write) (
    const ifb_cstr                     in_file_path,
          IFBEnginePlatformFileIndex& out_file_index_ref);

typedef const ifb_b8
(*funcptr_ifb_engine_platform_file_close) (
    const IFBEnginePlatformFileIndex file_index);

typedef const ifb_size
(*funcptr_ifb_engine_platform_file_size) (
    const IFBEnginePlatformFileIndex file_index);

typedef const ifb_b8
(*funcptr_ifb_engine_platform_file_read)(
    const IFBEnginePlatformFileIndex in_file_index,
    const ifb_size                   in_file_read_start,
    const ifb_size                   in_file_read_size,
          ifb_memory                out_file_read_buffer);

typedef const ifb_b8
(*funcptr_ifb_engine_platform_file_write)(
    const IFBEnginePlatformFileIndex in_file_index,
    const ifb_size                   in_file_write_start,
    const ifb_size                   in_file_write_size,
          ifb_memory                 in_file_write_buffer);

struct IFBEnginePlatformFile {
    funcptr_ifb_engine_platform_file_open_read_only  open_read_only;
    funcptr_ifb_engine_platform_file_open_read_write open_read_write;
    funcptr_ifb_engine_platform_file_close           close;
    funcptr_ifb_engine_platform_file_size            size;
    funcptr_ifb_engine_platform_file_read            read;
    funcptr_ifb_engine_platform_file_write           write;
};

/**********************************************************************************/
/* FILE DIALOG                                                                    */
/**********************************************************************************/

typedef const ifb_b8
(*funcptr_ifb_engine_platform_file_dialog_select_file) (
    const ifb_cstr  in_file_dialog_starting_directory,
    const ifb_size  in_file_type_count,
    const ifb_cstr* in_file_type_name_cstr_ptr,
    const ifb_cstr* in_file_type_spec_cstr_ptr,
          ifb_cstr out_file_selection_buffer);

struct IFBEnginePlatformFileDialog {
    funcptr_ifb_engine_platform_file_dialog_select_file select_file;
};

/**********************************************************************************/
/* PLATFORM API                                                                   */
/**********************************************************************************/

struct IFBEnginePlatformApi {
    IFBEnginePlatformSystem     system;
    IFBEnginePlatformMemory     memory;
    IFBEnginePlatformWindow     window;
    IFBEnginePlatformMonitor    monitor;
    IFBEnginePlatformFile       file;
    IFBEnginePlatformFileDialog file_dialog;
};

/**********************************************************************************/
/* PLATFORM INFO                                                                  */
/**********************************************************************************/

struct IFBEnginePlatformInfo {
    ifb_u32    page_size;
    ifb_size   reservation_size;
    ifb_memory reservation_start;
};


struct IFBEnginePlatform {
    ifb_u32 memory_page_size;
    ifb_u32 memory_page_count_total;
    ifb_u32 memory_page_count_used;
    ifb_u32 window_width;
    ifb_u32 window_height;
    ifb_u32 window_position_x;
    ifb_u32 window_position_y;
};

#endif //IFB_ENGINE_PLATFORM_HPP