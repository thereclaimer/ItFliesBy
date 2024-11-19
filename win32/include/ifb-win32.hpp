#ifndef IFB_WIN32_HPP
#define IFB_WIN32_HPP

#include <Windows.h>
#include <ifb-engine.hpp>



/**********************************************************************************/
/* SYSTEM                                                                         */
/**********************************************************************************/

namespace ifb_win32 {

    ifb_internal ifb_void system_api_initialize(IFBEnginePlatformSystem& platform_system_api_ref);

    ifb_internal const ifb_size system_page_size              (ifb_void);
    ifb_internal const ifb_size system_allocation_granularity (ifb_void);
};

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

namespace ifb_win32 {

    ifb_internal ifb_void memory_api_initialize(IFBEnginePlatformMemory& platform_memory_api_ref);

    ifb_internal const ifb_memory memory_reserve  (const ifb_size   reservation_size);
    ifb_internal const ifb_b8     memory_release  (const ifb_memory reservation_start, const ifb_size reservation_size);
    ifb_internal const ifb_memory memory_commit   (const ifb_memory commit_start,      const ifb_size commit_size);
    ifb_internal const ifb_b8     memory_decommit (const ifb_memory commit_start,      const ifb_size commit_size);
};

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

struct IFBWin32Window {
    HWND          window_handle;
    HDC           device_context;
    HGLRC         opengl_context;
    ImGuiContext* imgui_context;
    ifb_u32 width;
    ifb_u32 height;
    ifb_u32 pos_x;
    ifb_u32 pos_y;
    ifb_b32 quit_received;
};

extern IMGUI_IMPL_API LRESULT 
ImGui_ImplWin32_WndProcHandler(
    HWND   hWnd,
    UINT   msg,
    WPARAM wParam,
    LPARAM lParam);

typedef const LRESULT
(*ifb_win32_funcptr_on_wm_message_t)(
    const WPARAM w_param,
    const LPARAM l_param);

namespace ifb_win32 {

    ifb_internal const ifb_b8
    window_create(
        const ifb_cstr window_title,
        const ifb_u32  window_width,
        const ifb_u32  window_height,
        const ifb_u32  window_position_x,
        const ifb_u32  window_position_y);

    ifb_internal const ifb_b8 window_destroy      (ifb_void);
    ifb_internal const ifb_b8 window_frame_start  (ifb_void);
    ifb_internal const ifb_b8 window_frame_render (ifb_void);
    ifb_internal const ifb_b8 window_show         (ifb_void);
    ifb_internal const ifb_b8 window_opengl_init  (ifb_void);
    ifb_internal const ifb_b8 window_imgui_init   (ifb_void);

    ifb_internal LRESULT CALLBACK
    window_callback(
        HWND   window_handle,
        UINT   message,
        WPARAM w_param,
        LPARAM l_param);

    ifb_void window_api_initialize(IFBEnginePlatformWindow& window_api_ref);

    const LRESULT window_on_wm_size   (const WPARAM w_param, const LPARAM l_param);
    const LRESULT window_on_wm_move   (const WPARAM w_param, const LPARAM l_param);
    const LRESULT window_on_wm_quit   (const WPARAM w_param, const LPARAM l_param);
    const LRESULT window_on_wm_destroy(const WPARAM w_param, const LPARAM l_param);
};

/**********************************************************************************/
/* MONITOR                                                                        */
/**********************************************************************************/

namespace ifb_win32 {

    ifb_internal ifb_void monitor_size       (IFBEnginePlatformMonitorSize& monitor_size_ref);
    ifb_internal const ifb_u32  monitor_refresh_hz (ifb_void);
    
    ifb_void monitor_api_initialize(IFBEnginePlatformMonitor& monitor_api_ref);

};

/**********************************************************************************/
/* FILES                                                                          */
/**********************************************************************************/

#define IFB_WIN32_FILE_MANAGER_MAX_FILES 32

struct IFBWin32FileOverlappedInfo {
    OVERLAPPED                 overlapped;
    IFBEnginePlatformFileIndex file_index; 
    ifb_size                   bytes_read;
    ifb_size                   bytes_written;
};

struct IFBWin32FileTable {
    ifb_size row_count;
    struct {
        HANDLE                     handle    [IFB_WIN32_FILE_MANAGER_MAX_FILES];
        ifb_size                   size      [IFB_WIN32_FILE_MANAGER_MAX_FILES];
        IFBWin32FileOverlappedInfo overlapped[IFB_WIN32_FILE_MANAGER_MAX_FILES];
    } columns;
};

namespace ifb_win32 {

    ifb_internal ifb_void file_api_initialize(IFBEnginePlatformFile& platform_file_api_ref);

    ifb_internal const ifb_b8 file_open_read_only  (const ifb_cstr in_file_path, IFBEnginePlatformFileIndex& out_file_index_ref);
    ifb_internal const ifb_b8 file_open_read_write (const ifb_cstr in_file_path, IFBEnginePlatformFileIndex& out_file_index_ref);

    ifb_internal const ifb_b8   file_close (const IFBEnginePlatformFileIndex file_index);
    ifb_internal const ifb_size file_size  (const IFBEnginePlatformFileIndex file_index);
    
    ifb_internal const ifb_b8 
    file_read(
        const IFBEnginePlatformFileIndex in_file_index,
        const ifb_size                   in_file_read_start,
        const ifb_size                   in_file_read_size,
              ifb_memory                out_file_read_buffer);

    ifb_internal const ifb_b8 
    file_write(
        const IFBEnginePlatformFileIndex in_file_index,
        const ifb_size                   in_file_write_start,
        const ifb_size                   in_file_write_size,
        const ifb_memory                 in_file_write_buffer);

    ifb_internal ifb_void CALLBACK
    file_read_callback(
        DWORD        error_code,
        DWORD        bytes_transferred,
        LPOVERLAPPED overlapped_ptr);

    ifb_internal ifb_void CALLBACK
    file_write_callback(
        DWORD        error_code,
        DWORD        bytes_transferred,
        LPOVERLAPPED overlapped_ptr);
};

/**********************************************************************************/
/* FILE DIALOG                                                                    */
/**********************************************************************************/

#define IFB_WIN32_DIALOG_CSTR_LENGTH_MAX 256
#define IFB_WIN32_DIALOG_WSTR_LENGTH_MAX 128


namespace ifb_win32 {

    ifb_internal ifb_void 
    file_dialog_api_initialize(
        IFBEnginePlatformFileDialog& platform_api_file_dialog_ref);

    ifb_internal const ifb_b8
    file_dialog_select_file(
        const ifb_cstr  in_file_dialog_starting_directory,
        const ifb_size  in_file_type_count,
        const ifb_cstr* in_file_type_name_cstr_ptr,
        const ifb_cstr* in_file_type_spec_cstr_ptr,
              ifb_cstr out_file_selection_buffer);
};

/**********************************************************************************/
/* WIN32 APPLICATION                                                              */
/**********************************************************************************/

ifb_s32 CALLBACK
ifb_win32_main(    
    HINSTANCE h_instance,
    HINSTANCE h_prev_instance,
    PWSTR     p_cmd_line,
    int       n_cmd_show);

struct IFBWin32Args {
    HINSTANCE h_instance;
    HINSTANCE h_prev_instance;
    PWSTR     p_cmd_line;
    int       n_cmd_show;
};

struct IFBWin32Context {
    IFBWin32Args   args;
    IFBWin32Window window;
};

ifb_global IFBWin32Context* _ifb_win32_context_ptr;

namespace ifb_win32 {

    inline const HINSTANCE context_args_h_instance      (ifb_void) { return(_ifb_win32_context_ptr->args.h_instance);      }
    inline const HINSTANCE context_args_h_prev_instance (ifb_void) { return(_ifb_win32_context_ptr->args.h_prev_instance); }
    inline const PWSTR     context_args_p_cmd_line      (ifb_void) { return(_ifb_win32_context_ptr->args.p_cmd_line);      }
    inline const int       context_args_n_cmd_show      (ifb_void) { return(_ifb_win32_context_ptr->args.n_cmd_show);      }


    inline       IFBWin32Window& context_window_ref()       { return(_ifb_win32_context_ptr->window);                       }
    inline const ifb_b8          context_window_has_imgui() { return(_ifb_win32_context_ptr->window.imgui_context != NULL); }
};


#endif //IFB_WIN32_HPP