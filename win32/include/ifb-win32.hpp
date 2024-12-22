#ifndef IFB_WIN32_HPP
#define IFB_WIN32_HPP

#include <Windows.h>
#include <ifb.hpp>
#include <ifb-engine.hpp>

/**********************************************************************************/
/* SYSTEM                                                                         */
/**********************************************************************************/

namespace ifb_win32 {

    ifb_void system_api_initialize(IFBPlatformSystemApi& platform_system_api_ref);

    ifb_internal const ifb_u32  system_page_size              (ifb_void);
    ifb_internal const ifb_u32  system_allocation_granularity (ifb_void);
    ifb_internal const ifb_u64  system_time_ms                (ifb_void);
    ifb_internal       ifb_void system_sleep                  (const ifb_u32 ms);
};

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

namespace ifb_win32 {

    ifb_void memory_api_initialize(IFBPlatformMemoryApi& platform_memory_api_ref);

    ifb_internal const ifb_ptr memory_reserve (const ifb_u32 reservation_size);
    ifb_internal const ifb_b8  memory_release (const ifb_ptr reservation_start, const ifb_u32 reservation_size);
    ifb_internal const ifb_ptr memory_commit  (const ifb_ptr commit_start,      const ifb_u32 commit_size);
};

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

struct IFBWin32Window {
    HWND          window_handle;
    HDC           device_context;
    HGLRC         opengl_context;
    ifb_u32       width;
    ifb_u32       height;
    ifb_u32       position_x;
    ifb_u32       position_y;
    ifb_b8        quit_received;
    ImGuiContext* imgui_context;
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

    ifb_void window_api_initialize(IFBPlatformWindowApi& window_api_ref);

    ifb_internal const ifb_b8 
    window_create(
        const ifb_cstr title,
        const ifb_u32  width,
        const ifb_u32  height,
        const ifb_u32  position_x,
        const ifb_u32  position_y);

    ifb_internal const ifb_b8        window_destroy      (ifb_void);
    ifb_internal const ifb_b8        window_frame_start  (ifb_void);
    ifb_internal const ifb_b8        window_frame_render (ifb_void);
    ifb_internal const ifb_b8        window_show         (ifb_void);
    ifb_internal const ifb_b8        window_opengl_init  (ifb_void);
    ifb_internal       ImGuiContext* window_imgui_init   (ifb_void);

    ifb_internal LRESULT CALLBACK
    window_callback(
        HWND   window_handle,
        UINT   message,
        WPARAM w_param,
        LPARAM l_param);

    const LRESULT window_on_wm_size   (const WPARAM w_param, const LPARAM l_param);
    const LRESULT window_on_wm_move   (const WPARAM w_param, const LPARAM l_param);
    const LRESULT window_on_wm_quit   (const WPARAM w_param, const LPARAM l_param);
    const LRESULT window_on_wm_destroy(const WPARAM w_param, const LPARAM l_param);
};

/**********************************************************************************/
/* MONITOR                                                                        */
/**********************************************************************************/

namespace ifb_win32 {

    ifb_void monitor_api_initialize(IFBPlatformMonitorApi& monitor_api_ref);

    const ifb_u32 monitor_count (ifb_void);
    
    ifb_void
    monitor_info(
        const ifb_u32     monitor_array_count,
              IFBMonitor* monitor_array_ptr);

    ifb_internal BOOL CALLBACK monitor_enum_callback_count (HMONITOR handle,HDC device_context, LPRECT rect_ptr, LPARAM data_ptr);
    ifb_internal BOOL CALLBACK monitor_enum_callback_info  (HMONITOR handle,HDC device_context, LPRECT rect_ptr, LPARAM data_ptr);
};

/**********************************************************************************/
/* FILES                                                                          */
/**********************************************************************************/

#define IFB_WIN32_FILE_MANAGER_MAX_FILES 32

struct IFBWin32FileOverlappedInfo { 
    OVERLAPPED                 overlapped;
    ifb_index                  file_index; 
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

    ifb_internal ifb_void file_api_initialize(IFBPlatformFileApi& platform_file_api_ref);

    ifb_internal const ifb_b8 file_open_read_only  (const ifb_cstr in_file_path, ifb_index& out_file_index_ref);
    ifb_internal const ifb_b8 file_open_read_write (const ifb_cstr in_file_path, ifb_index& out_file_index_ref);

    ifb_internal const ifb_b8   file_close (const ifb_index file_index);
    ifb_internal const ifb_size file_size  (const ifb_index file_index);
    
    ifb_internal const ifb_b8 
    file_read(
        const ifb_index   in_file_index,
        const ifb_size    in_file_read_start,
        const ifb_size    in_file_read_size,
              ifb_memory out_file_read_buffer);

    ifb_internal const ifb_b8 
    file_write(
        const ifb_index   in_file_index,
        const ifb_size    in_file_write_start,
        const ifb_size    in_file_write_size,
              ifb_memory out_file_write_buffer);

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
        IFBPlatformFileDialogApi& platform_api_file_dialog_ref);

    ifb_internal const ifb_b8
    file_dialog_select_file(
        const ifb_cstr  in_file_dialog_starting_directory,
        const ifb_size  in_file_type_count,
        const ifb_cstr* in_file_type_name_cstr_ptr,
        const ifb_cstr* in_file_type_spec_cstr_ptr,
              ifb_cstr out_file_selection_buffer);
};

/**********************************************************************************/
/* WIN32 CONTEXT                                                                  */
/**********************************************************************************/

struct IFBWin32Args {
    HINSTANCE h_instance;
    HINSTANCE h_prev_instance;
    PWSTR     p_cmd_line;
    int       n_cmd_show;
};

struct IFBWin32Context {
    IFBWin32Window  window;
    IFBWin32Args    args;
    IFBPlatformApi  platform_api;
    IFBEngineUpdate engine_update;
};

namespace ifb_win32 {
    

    ifb_global IFBWin32Context _context;

    inline void context_reset(ifb_void) { _context = {0}; }

    inline ifb_void
    context_args_set_values(
              IFBWin32Args& args_ref,
        const HINSTANCE     h_instance,
        const HINSTANCE     h_prev_instance,
        const PWSTR         p_cmd_line,
        const int           n_cmd_show);

    inline ifb_void context_initialize_platform_api(IFBPlatformApi& platform_api_ref);

    inline const HINSTANCE context_args_get_h_instance      (ifb_void) { return(_context.args.h_instance);      }
    inline const HINSTANCE context_args_get_h_prev_instance (ifb_void) { return(_context.args.h_prev_instance); }
    inline const PWSTR     context_args_get_p_cmd_line      (ifb_void) { return(_context.args.p_cmd_line);      }
    inline const int       context_args_get_n_cmd_show      (ifb_void) { return(_context.args.n_cmd_show);      }

    inline IFBWin32Args     context_get_args           (ifb_void) { return(_context.args);          }
    inline IFBWin32Window&  context_get_window         (ifb_void) { return(_context.window);        }
    inline IFBPlatformApi&  context_get_platform_api   (ifb_void) { return(_context.platform_api);  }
    inline IFBEngineUpdate& context_get_engine_update  (ifb_void) { return(_context.engine_update); }
};


#endif //IFB_WIN32_HPP