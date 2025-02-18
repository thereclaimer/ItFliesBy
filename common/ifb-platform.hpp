#ifndef IFB_PLATFORM_HPP
#define IFB_PLATFORM_HPP

#include "ifb-types.hpp"
#include "ifb-scopes.hpp"
#include "_ifb-graphics.hpp"

/**********************************************************************************/
/* SYSTEM                                                                         */
/**********************************************************************************/

typedef const IFBU32
(*funcptr_ifb_platform_system_page_size)(
    IFBVoid);

typedef const IFBU32
(*funcptr_ifb_platform_system_allocation_granularity)(
    IFBVoid);

typedef const IFBTimems
(*funcptr_ifb_platform_system_time_ms)(
    IFBVoid);

typedef IFBVoid
(*funcptr_ifb_platform_system_sleep)(
    const IFBU32 ms);

struct IFBPlatformSystemApi {
    funcptr_ifb_platform_system_page_size              page_size;
    funcptr_ifb_platform_system_allocation_granularity allocation_granularity;
    funcptr_ifb_platform_system_time_ms                time_ms;
    funcptr_ifb_platform_system_sleep                  sleep;
};

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

typedef const IFBPtr
(*funcptr_ifb_platform_memory_reserve)(
    const IFBU32 reservation_size);

typedef const IFBB8
(*funcptr_ifb_platform_memory_release)(
    const IFBPtr reservation_start,
    const IFBU32 reservation_size);

typedef const IFBPtr
(*funcptr_ifb_platform_memory_commit)(
    const IFBPtr commit_start,
    const IFBU32 commit_size);

typedef const IFBB8
(*funcptr_ifb_platform_memory_decommit)(
    const IFBPtr commit_start,
    const IFBU32 commit_size);

struct IFBPlatformMemoryApi {
    funcptr_ifb_platform_memory_reserve  reserve;
    funcptr_ifb_platform_memory_release  release;
    funcptr_ifb_platform_memory_commit   commit;
    funcptr_ifb_platform_memory_decommit decommit;
};

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

typedef const IFBB8
(*funcptr_ifb_platform_window_create) (
    const IFBCStr title,
    const IFBU32  width,
    const IFBU32  height,
    const IFBU32  position_x,
    const IFBU32  position_y);

typedef const IFBB8
(*funcptr_ifb_platform_window_opengl_init) (
    IFBVoid);

typedef ImGuiContext*
(*funcptr_ifb_platform_window_imgui_init) (
    IFBVoid);

typedef const IFBB8
(*funcptr_ifb_platform_window_show)(
    IFBVoid);

typedef const IFBB8
(*funcptr_ifb_platform_window_destroy)(
    IFBVoid);

typedef const IFBB8
(*funcptr_ifb_platform_window_frame_start)(
    IFBVoid);

typedef const IFBB8
(*funcptr_ifb_platform_window_frame_render)(
    IFBVoid);

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

typedef const IFBU32
(*funcptr_ifb_platform_monitor_count) (
    IFBVoid);

typedef IFBVoid
(*funcptr_ifb_platform_monitor_info)(
    const IFBU32  monitor_array_count,
          IFBPtr* monitor_array_ptr);

struct IFBPlatformMonitorApi {
    funcptr_ifb_platform_monitor_count count;
    funcptr_ifb_platform_monitor_info  info;
};

/**********************************************************************************/
/* FILES                                                                          */                            
/**********************************************************************************/

typedef const IFBB8
(*funcptr_ifb_platform_file_open_read_only) (
    const IFBCStr    in_file_path,
          IFBIndex& out_file_index_ref);

typedef const IFBB8
(*funcptr_ifb_platform_file_open_read_write) (
    const IFBCStr    in_file_path,
          IFBIndex& out_file_index_ref);

typedef const IFBB8
(*funcptr_ifb_platform_file_open_read_write) (
    const IFBCStr    in_file_path,
          IFBIndex& out_file_index_ref);

typedef const IFBB8
(*funcptr_ifb_platform_file_close) (
    const IFBIndex file_index);

typedef const IFBSize
(*funcptr_ifb_platform_file_size) (
    const IFBIndex file_index);

typedef const IFBB8
(*funcptr_ifb_platform_file_read)(
    const IFBIndex  in_file_index,
    const IFBSize   in_file_read_start,
    const IFBSize   in_file_read_size,
          IFBByte* out_file_read_buffer);

typedef const IFBB8
(*funcptr_ifb_platform_file_write)(
    const IFBIndex file_index,
    const IFBSize  file_write_start,
    const IFBSize  file_write_size,
          IFBByte* file_write_buffer);

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

typedef const IFBB8
(*funcptr_ifb_platform_file_dialog_select_file) (
    const IFBCStr  in_file_dialog_starting_directory,
    const IFBSize  in_file_type_count,
    const IFBCStr* in_file_type_name_cstr_ptr,
    const IFBCStr* in_file_type_spec_cstr_ptr,
          IFBCStr out_file_selection_buffer);

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