#pragma once

#include "ifb-platform.hpp"

#include <Windows.h>

/**********************************************************************************/
/* SYSTEM                                                                         */
/**********************************************************************************/

namespace ifb_platform {

    const IFBB8   win32_system_get_info (IFBSystemInfo* system_info);
    const IFBU64  win32_system_time_ms  (IFBVoid);
          IFBVoid win32_system_sleep    (const IFBU32 ms);
};

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

namespace ifb_platform {

    const IFBPtr win32_memory_reserve  (const IFBU64 reservation_size);
    const IFBB8  win32_memory_release  (const IFBPtr reservation_start, const IFBU64 reservation_size);
    const IFBPtr win32_memory_commit   (const IFBPtr commit_start,      const IFBU64 commit_size);
    const IFBB8  win32_memory_decommit (const IFBPtr commit_start,      const IFBU64 commit_size);
};

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

struct IFBWin32Window : IFBPlatformWindow {
    struct {
        HWND window;
        HDC  device;
    } handles;
    struct {
        WPARAM w;
        LPARAM l;       
    } message_params;
};

namespace ifb_platform {

    //api
    const IFBU32 win32_window_context_size (IFBVoid);
    const IFBB8  win32_window_create       (IFBWin32Window* win32_window);
    const IFBB8  win32_window_destroy      (IFBWin32Window* win32_window);
    const IFBB8  win32_window_frame_start  (IFBWin32Window* win32_window);
    const IFBB8  win32_window_frame_render (IFBWin32Window* win32_window);
    const IFBB8  win32_window_show         (IFBWin32Window* win32_window);

    //callback
    LRESULT CALLBACK
    win32_window_callback(
        HWND   window_handle,
        UINT   message,
        WPARAM w_param,
        LPARAM l_param);

    //handlers
    const LRESULT win32_window_on_wm_size    (IFBWin32Window* win32_window);
    const LRESULT win32_window_on_wm_move    (IFBWin32Window* win32_window);
    const LRESULT win32_window_on_wm_close   (IFBWin32Window* win32_window);
    const LRESULT win32_window_on_wm_destroy (IFBWin32Window* win32_window);
};

/**********************************************************************************/
/* MONITOR                                                                        */
/**********************************************************************************/

namespace ifb_win32 {

    const IFBU32 monitor_count (IFBVoid);
    
    const IFBB8
    monitor_info(
        const IFBU32      monitor_count,
              IFBMonitor* monitor_array);

    BOOL CALLBACK monitor_enum_callback_count (HMONITOR handle,HDC device_context, LPRECT rect_ptr, LPARAM data_ptr);
    BOOL CALLBACK monitor_enum_callback_info  (HMONITOR handle,HDC device_context, LPRECT rect_ptr, LPARAM data_ptr);
};

/**********************************************************************************/
/* FILES                                                                          */
/**********************************************************************************/

struct IFBWin32FileReadOnly {
    HANDLE     win32_file_handle;
    OVERLAPPED win32_overlapped;
};

struct IFBWin32FileReadWrite {
    HANDLE     win32_file_handle;
    OVERLAPPED win32_overlapped;
};

namespace ifb_win32 {

    //read only
    const IFBU32 file_ro_context_size     (IFBVoid);
    const IFBB8  file_ro_open             (IFBPlatformFileRequest* file_ro_request);
    const IFBB8  file_ro_read_async       (IFBPlatformFileRequest* file_ro_request);
    const IFBU32 file_ro_read_immediate   (IFBPlatformFileRequest* file_ro_request);
    const IFBB8  file_ro_close            (IFBPlatformFileRequest* file_ro_request);
    
    //read write
    const IFBU32 file_rw_context_size     (IFBVoid);
    const IFBB8  file_rw_open             (IFBPlatformFileRequest* file_rw_request);
    const IFBU32 file_rw_read_immediate   (IFBPlatformFileRequest* file_rw_request);
    const IFBB8  file_rw_read_async       (IFBPlatformFileRequest* file_rw_request);
    const IFBU32 file_rw_write_immediate  (IFBPlatformFileRequest* file_rw_request);
    const IFBB8  file_rw_write_async      (IFBPlatformFileRequest* file_rw_request);
    const IFBB8  file_rw_close            (IFBPlatformFileRequest* file_rw_request);
};