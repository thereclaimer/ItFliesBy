#ifndef IFB_COMMON_PLATFORM_HPP
#define IFB_COMMON_PLATFORM_HPP

#include "ifb-common-types.hpp"
#include "ifb-common-scopes.hpp"

/**********************************************************************************/
/* SYSTEM                                                                         */
/**********************************************************************************/

struct IFBPlatformSystem {
    ifb_u32 page_size;
    ifb_u32 allocation_granularity;
};

typedef const ifb_size
(*funcptr_ifb_platform_system_info)(
    IFBPlatformSystem& system_info_ref);

struct IFBPlatformSystemApi {
    funcptr_ifb_platform_system_info system_info;
};

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

struct IFBPlatformMemory {
    ifb_memory reservation;
    ifb_u32    page_count_total;
    ifb_u32    page_count_used;
    ifb_u32    page_size;
};

typedef const ifb_b8
(*funcptr_ifb_platform_memory_pages_reserve)(
    IFBPlatformMemory& platform_memory_ref);

typedef const ifb_b8
(*funcptr_ifb_platform_memory_pages_release)(
    IFBPlatformMemory& platform_memory_ref);

typedef const ifb_memory
(*funcptr_ifb_platform_memory_pages_commit)(
          IFBPlatformMemory& platform_memory_ref,
    const ifb_u32            commit_size);


struct IFBPlatformMemoryApi {
    funcptr_ifb_platform_memory_pages_reserve pages_reserve;
    funcptr_ifb_platform_memory_pages_release pages_release;
    funcptr_ifb_platform_memory_pages_commit  pages_commit;
};

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

struct IFBPlatformWindow {
    ifb_cstr title;
    ifb_u32  width;
    ifb_u32  height;
    ifb_u32  position_x;
    ifb_u32  position_y;
};

typedef const ifb_b8
(*funcptr_ifb_platform_window_create) (
    IFBPlatformWindow& platform_window_ref);

typedef const ifb_b8
(*funcptr_ifb_platform_window_opengl_init) (
    ifb_void);

typedef const ifb_b8
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
    IFBPlatformWindow& platform_window_ref);

typedef const ifb_b8
(*funcptr_ifb_platform_window_frame_render)(
    IFBPlatformWindow& platform_window_ref);

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

struct IFBPlatformMonitor {
    ifb_u32 width;
    ifb_u32 height;
    ifb_u32 refresh_hz;
}; 

typedef ifb_void
(*funcptr_ifb_platform_monitor_info)(
    IFBPlatformMonitor& monitor_ref);


struct IFBPlatformMonitorApi {
    funcptr_ifb_platform_monitor_info monitor_info;
};

/**********************************************************************************/
/* FILES                                                                          */
/**********************************************************************************/

typedef ifb_index IFBPlatformFileIndex;

typedef const ifb_b8
(*funcptr_ifb_platform_file_open_read_only) (
    const ifb_cstr                     in_file_path,
          IFBPlatformFileIndex& out_file_index_ref);

typedef const ifb_b8
(*funcptr_ifb_platform_file_open_read_write) (
    const ifb_cstr                     in_file_path,
          IFBPlatformFileIndex& out_file_index_ref);

typedef const ifb_b8
(*funcptr_ifb_platform_file_open_read_write) (
    const ifb_cstr                     in_file_path,
          IFBPlatformFileIndex& out_file_index_ref);

typedef const ifb_b8
(*funcptr_ifb_platform_file_close) (
    const IFBPlatformFileIndex file_index);

typedef const ifb_size
(*funcptr_ifb_platform_file_size) (
    const IFBPlatformFileIndex file_index);

typedef const ifb_b8
(*funcptr_ifb_platform_file_read)(
    const IFBPlatformFileIndex in_file_index,
    const ifb_size                   in_file_read_start,
    const ifb_size                   in_file_read_size,
          ifb_memory                out_file_read_buffer);

typedef const ifb_b8
(*funcptr_ifb_platform_file_write)(
    const IFBPlatformFileIndex in_file_index,
    const ifb_size                   in_file_write_start,
    const ifb_size                   in_file_write_size,
          ifb_memory                 in_file_write_buffer);

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
/* PLATFORM                                                                       */
/**********************************************************************************/

struct IFBPlatform {
    IFBPlatformSystem  system;
    IFBPlatformMemory  memory;
    IFBPlatformWindow  window;
    IFBPlatformMonitor monitor;
};

/**********************************************************************************/
/* PLATFORM API                                                                   */
/**********************************************************************************/

struct IFBPlatformApi {
    IFBPlatformSystemApi     system;
    IFBPlatformMemoryApi     memory;
    IFBPlatformWindowApi     window;
    IFBPlatformMonitorApi    monitor;
    IFBPlatformFileApi       file;
    IFBPlatformFileDialogApi file_dialog;
};

namespace ifb_platform {

    //system

    //window
    ifb_global funcptr_ifb_platform_window_create           window_create;
    ifb_global funcptr_ifb_platform_window_destroy          window_destroy;
    ifb_global funcptr_ifb_platform_window_frame_start      window_frame_start;
    ifb_global funcptr_ifb_platform_window_frame_render     window_frame_render;
    ifb_global funcptr_ifb_platform_window_show             window_show;
    ifb_global funcptr_ifb_platform_window_opengl_init      window_opengl_init;
    ifb_global funcptr_ifb_platform_window_imgui_init       window_imgui_init;

    //monitor
    ifb_global funcptr_ifb_platform_monitor_info            monitor_info;

    //memory
    ifb_global funcptr_ifb_platform_memory_pages_reserve     memory_pages_reserve;
    ifb_global funcptr_ifb_platform_memory_pages_release     memory_pages_release;
    ifb_global funcptr_ifb_platform_memory_pages_commit      memory_pages_commit;

    //file
    ifb_global funcptr_ifb_platform_file_open_read_only     file_open_read_only;
    ifb_global funcptr_ifb_platform_file_open_read_write    file_open_read_write;
    ifb_global funcptr_ifb_platform_file_close              file_close;
    ifb_global funcptr_ifb_platform_file_size               file_size;
    ifb_global funcptr_ifb_platform_file_read               file_read;
    ifb_global funcptr_ifb_platform_file_write              file_write;

    //file dialog
    ifb_global funcptr_ifb_platform_file_dialog_select_file file_dialog_select_file;

    inline const ifb_b8 
    platform_api_validate(
        IFBPlatformApi& platform_api_ref) {

        ifb_b8 result = true;

        //set the function pointers
        ifb_platform::memory_pages_commit     = platform_api_ref.memory.pages_commit; 
        ifb_platform::memory_pages_decommit   = platform_api_ref.memory.pages_decommit;         
        ifb_platform::window_create           = platform_api_ref.window.create;
        ifb_platform::window_destroy          = platform_api_ref.window.destroy;
        ifb_platform::window_frame_start      = platform_api_ref.window.frame_start; 
        ifb_platform::window_frame_render     = platform_api_ref.window.frame_render;
        ifb_platform::window_show             = platform_api_ref.window.show;
        ifb_platform::window_opengl_init      = platform_api_ref.window.opengl_init;
        ifb_platform::window_imgui_init       = platform_api_ref.window.imgui_init;
        ifb_platform::monitor_size            = platform_api_ref.monitor.size;
        ifb_platform::monitor_refresh_hz      = platform_api_ref.monitor.refresh_hz;
        ifb_platform::file_open_read_only     = platform_api_ref.file.open_read_only;
        ifb_platform::file_open_read_write    = platform_api_ref.file.open_read_write;
        ifb_platform::file_close              = platform_api_ref.file.close;
        ifb_platform::file_size               = platform_api_ref.file.size;
        ifb_platform::file_read               = platform_api_ref.file.read;
        ifb_platform::file_write              = platform_api_ref.file.write;
        ifb_platform::file_dialog_select_file = platform_api_ref.file_dialog.select_file;        

        //sanity check
        result &= (
            ifb_engine::platform_memory_pages_commit   && 
            ifb_engine::platform_memory_pages_decommit && 
            ifb_engine::platform_window_create         &&
            ifb_engine::platform_window_destroy        &&
            ifb_engine::platform_window_frame_start    &&
            ifb_engine::platform_window_frame_render   &&
            ifb_engine::platform_window_show           &&
            ifb_engine::platform_window_opengl_init    &&
            ifb_engine::platform_window_imgui_init     &&
            ifb_engine::platform_monitor_size          &&
            ifb_engine::platform_monitor_refresh_hz

            // ifb_engine::platform_file_open_read_only           &&
            // ifb_engine::platform_file_open_read_write          &&
            // ifb_engine::platform_file_close                    &&
            // ifb_engine::platform_file_size                     &&
            // ifb_engine::platform_file_read                     &&
            // ifb_engine::platform_file_write                    &&
            // ifb_engine::platform_file_dialog_select_file
            );

        //we're done
        return(result);
    }
};

#endif //IFB_ENGINE_PLATFORM_HPP