#ifndef IFB_COMMON_PLATFORM_HPP
#define IFB_COMMON_PLATFORM_HPP

#include "ifb-common-types.hpp"
#include "ifb-common-scopes.hpp"
#include "ifb-common-arena.hpp"

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

struct IFBPlatformMemoryReservation {
    ifb_u32    page_count_total;
    ifb_u32    page_count_used;
    ifb_u32    page_size;
    ifb_memory start;
};

struct IFBPlatformMemoryCommit {
    ifb_u32    page_start;
    ifb_u32    page_count;
    ifb_memory start;
};

struct IFBPlatformMemory {
    IFBPlatformMemoryReservation reservation;
    IFBPlatformMemoryCommit      current_commit;    
};

typedef const ifb_b8
(*funcptr_ifb_platform_memory_reserve)(
    IFBPlatformMemory& memory_ref);

typedef const ifb_b8
(*funcptr_ifb_platform_memory_release)(
    IFBPlatformMemory& memory_ref);

typedef const ifb_b8
(*funcptr_ifb_platform_memory_commit)(
    IFBPlatformMemory& memory_ref);

struct IFBPlatformMemoryApi {
    funcptr_ifb_platform_memory_reserve reserve;
    funcptr_ifb_platform_memory_release release;
    funcptr_ifb_platform_memory_commit  commit;
};

namespace ifb_platform {

    inline const ifb_size
    memory_reservation_size_total(
        const IFBPlatformMemory& platform_memory_ref) {

        return(platform_memory_ref.reservation.page_size * platform_memory_ref.reservation.page_count_total);
    }

    inline const ifb_size
    memory_reservation_size_used(
        const IFBPlatformMemory& platform_memory_ref) {

        return(platform_memory_ref.reservation.page_size * platform_memory_ref.reservation.page_count_used);
    }

    inline const ifb_size
    memory_commit_size(
        const IFBPlatformMemory& platform_memory_ref) {

        return(platform_memory_ref.reservation.page_size * platform_memory_ref.current_commit.page_count);
    }

    inline const ifb_memory
    memory_commit_start(
        const IFBPlatformMemory& platform_memory_ref) {

        const ifb_size   reservation_size_used = ifb_platform::memory_reservation_size_used(platform_memory_ref);
        const ifb_memory commit_start          = platform_memory_ref.reservation.start + reservation_size_used;

        return(commit_start);
    }
};

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

struct IFBPlatformWindow {
    ifb_cstr   title;
    ifb_u32    width;
    ifb_u32    height;
    ifb_u32    position_x;
    ifb_u32    position_y;
    ifb_b32    quit_received;
    ifb_u32    memory_size;
    ifb_memory memory_start;
};

typedef const ifb_b8
(*funcptr_ifb_platform_window_create) (
    IFBPlatformWindow* platform_window_ptr);

typedef const ifb_b8
(*funcptr_ifb_platform_window_opengl_init) (
    IFBPlatformWindow* platform_window_ptr);

typedef const ifb_b8
(*funcptr_ifb_platform_window_imgui_init) (
    IFBPlatformWindow* platform_window_ptr);

typedef const ifb_b8
(*funcptr_ifb_platform_window_show)(
    IFBPlatformWindow* platform_window_ptr);

typedef const ifb_b8
(*funcptr_ifb_platform_window_destroy)(
    IFBPlatformWindow* platform_window_ptr);

typedef const ifb_b8
(*funcptr_ifb_platform_window_frame_start)(
    IFBPlatformWindow* platform_window_ptr);

typedef const ifb_b8
(*funcptr_ifb_platform_window_frame_render)(
    IFBPlatformWindow* platform_window_ptr);

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
    const ifb_cstr               in_file_path,
          IFBPlatformFileIndex& out_file_index_ref);

typedef const ifb_b8
(*funcptr_ifb_platform_file_open_read_write) (
    const ifb_cstr               in_file_path,
          IFBPlatformFileIndex& out_file_index_ref);

typedef const ifb_b8
(*funcptr_ifb_platform_file_open_read_write) (
    const ifb_cstr               in_file_path,
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
    const ifb_size             in_file_read_start,
    const ifb_size             in_file_read_size,
          ifb_memory          out_file_read_buffer);

typedef const ifb_b8
(*funcptr_ifb_platform_file_write)(
    const IFBPlatformFileIndex file_index,
    const ifb_size             file_write_start,
    const ifb_size             file_write_size,
          ifb_memory           file_write_buffer);

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
    IFBPlatformSystemApi  system;
    IFBPlatformMemoryApi  memory;
    IFBPlatformWindowApi  window;
    IFBPlatformMonitorApi monitor;
};

namespace ifb_platform {

    //system


    //file
    // ifb_global funcptr_ifb_platform_file_open_read_only     file_open_read_only;
    // ifb_global funcptr_ifb_platform_file_open_read_write    file_open_read_write;
    // ifb_global funcptr_ifb_platform_file_close              file_close;
    // ifb_global funcptr_ifb_platform_file_size               file_size;
    // ifb_global funcptr_ifb_platform_file_read               file_read;
    // ifb_global funcptr_ifb_platform_file_write              file_write;

    // //file dialog
    // ifb_global funcptr_ifb_platform_file_dialog_select_file file_dialog_select_file;

    inline const ifb_b8
    platform_api_validate(
        IFBPlatformApi& platform_api_ref) {

        //set the function pointers
        ifb_platform::window_create           = platform_api_ref.window.create;
        ifb_platform::window_destroy          = platform_api_ref.window.destroy;
        ifb_platform::window_frame_start      = platform_api_ref.window.frame_start;
        ifb_platform::window_frame_render     = platform_api_ref.window.frame_render;
        ifb_platform::window_show             = platform_api_ref.window.show;
        ifb_platform::window_opengl_init      = platform_api_ref.window.opengl_init;
        ifb_platform::window_imgui_init       = platform_api_ref.window.imgui_init;
        ifb_platform::monitor_info            = platform_api_ref.monitor.monitor_info;
        ifb_platform::memory_reserve          = platform_api_ref.memory.reserve;
        ifb_platform::memory_release          = platform_api_ref.memory.release;
        ifb_platform::memory_commit           = platform_api_ref.memory.commit;
        // ifb_platform::file_open_read_only     = platform_api_ref.file.open_read_only;
        // ifb_platform::file_open_read_write    = platform_api_ref.file.open_read_write;
        // ifb_platform::file_close              = platform_api_ref.file.close;
        // ifb_platform::file_size               = platform_api_ref.file.size;
        // ifb_platform::file_read               = platform_api_ref.file.read;
        // ifb_platform::file_write              = platform_api_ref.file.write;
        // ifb_platform::file_dialog_select_file = platform_api_ref.file_dialog.select_file;

        //sanity check
        ifb_b8 result = true;
        result &= ifb_platform::memory_pages_commit;
        result &= ifb_platform::memory_pages_decommit;
        result &= ifb_platform::window_create;
        result &= ifb_platform::window_destroy;
        result &= ifb_platform::window_frame_start;
        result &= ifb_platform::window_frame_render;
        result &= ifb_platform::window_show;
        result &= ifb_platform::window_opengl_init;
        result &= ifb_platform::window_imgui_init;
        result &= ifb_platform::monitor_info;
        // result &= ifb_platform::file_open_read_only;
        // result &= ifb_platform::file_open_read_write;
        // result &= ifb_platform::file_close;
        // result &= ifb_platform::file_size;
        // result &= ifb_platform::file_read;
        // result &= ifb_platform::file_write;
        // result &= ifb_platform::file_dialog_select_file;

        //we're done
        return(result);
    }
};

#endif //IFB_ENGINE_PLATFORM_HPP