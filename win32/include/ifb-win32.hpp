#ifndef IFB_WIN32_HPP
#define IFB_WIN32_HPP

#include <Windows.h>
#include <ifb.hpp>
#include <ifb-engine.hpp>

/**********************************************************************************/
/* SYSTEM                                                                         */
/**********************************************************************************/

namespace ifb_win32 {

    IFBVoid system_api_initialize(IFBPlatformSystemApi& platform_system_api_ref);

    ifb_internal const IFBU32  system_page_size              (IFBVoid);
    ifb_internal const IFBU32  system_allocation_granularity (IFBVoid);
    ifb_internal const IFBU64  system_time_ms                (IFBVoid);
    ifb_internal       IFBVoid system_sleep                  (const IFBU32 ms);
};

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

namespace ifb_win32 {

    IFBVoid memory_api_initialize(IFBPlatformMemoryApi& platform_memory_api_ref);

    ifb_internal const IFBPtr memory_reserve (const IFBU32 reservation_size);
    ifb_internal const IFBB8  memory_release (const IFBPtr reservation_start, const IFBU32 reservation_size);
    ifb_internal const IFBPtr memory_commit  (const IFBPtr commit_start,      const IFBU32 commit_size);
};

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

struct IFBWin32Window {
    HWND          window_handle;
    HDC           device_context;
    HGLRC         opengl_context;
    IFBU32       width;
    IFBU32       height;
    IFBU32       position_x;
    IFBU32       position_y;
    IFBB8        quit_received;
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

    IFBVoid window_api_initialize(IFBPlatformWindowApi& window_api_ref);

    ifb_internal const IFBB8 
    window_create(
        const IFBCStr title,
        const IFBU32  width,
        const IFBU32  height,
        const IFBU32  position_x,
        const IFBU32  position_y);

    ifb_internal const IFBB8        window_destroy      (IFBVoid);
    ifb_internal const IFBB8        window_frame_start  (IFBVoid);
    ifb_internal const IFBB8        window_frame_render (IFBVoid);
    ifb_internal const IFBB8        window_show         (IFBVoid);
    ifb_internal const IFBB8        window_opengl_init  (IFBVoid);
    ifb_internal       ImGuiContext* window_imgui_init   (IFBVoid);

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

    IFBVoid monitor_api_initialize(IFBPlatformMonitorApi& monitor_api_ref);

    const IFBU32 monitor_count (IFBVoid);
    
    IFBVoid
    monitor_info(
        const IFBU32     monitor_array_count,
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
    IFBIndex                  file_index; 
    IFBSize                   bytes_read;
    IFBSize                   bytes_written;
};

struct IFBWin32FileTable {
    IFBSize row_count;
    struct {
        HANDLE                     handle    [IFB_WIN32_FILE_MANAGER_MAX_FILES];
        IFBSize                   size      [IFB_WIN32_FILE_MANAGER_MAX_FILES];
        IFBWin32FileOverlappedInfo overlapped[IFB_WIN32_FILE_MANAGER_MAX_FILES];
    } columns;
};

namespace ifb_win32 {

    ifb_internal IFBVoid file_api_initialize(IFBPlatformFileApi& platform_file_api_ref);

    ifb_internal const IFBB8 file_open_read_only  (const IFBCStr in_file_path, IFBIndex& out_file_index_ref);
    ifb_internal const IFBB8 file_open_read_write (const IFBCStr in_file_path, IFBIndex& out_file_index_ref);

    ifb_internal const IFBB8   file_close (const IFBIndex file_index);
    ifb_internal const IFBSize file_size  (const IFBIndex file_index);
    
    ifb_internal const IFBB8 
    file_read(
        const IFBIndex   in_file_index,
        const IFBSize    in_file_read_start,
        const IFBSize    in_file_read_size,
              IFBByte*  out_file_read_buffer);

    ifb_internal const IFBB8 
    file_write(
        const IFBIndex   in_file_index,
        const IFBSize    in_file_write_start,
        const IFBSize    in_file_write_size,
              IFBByte*  out_file_write_buffer);

    ifb_internal IFBVoid CALLBACK
    file_read_callback(
        DWORD        error_code,
        DWORD        bytes_transferred,
        LPOVERLAPPED overlapped_ptr);

    ifb_internal IFBVoid CALLBACK
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

    ifb_internal IFBVoid 
    file_dialog_api_initialize(
        IFBPlatformFileDialogApi& platform_api_file_dialog_ref);

    ifb_internal const IFBB8
    file_dialog_select_file(
        const IFBCStr  in_file_dialog_starting_directory,
        const IFBSize  in_file_type_count,
        const IFBCStr* in_file_type_name_cstr_ptr,
        const IFBCStr* in_file_type_spec_cstr_ptr,
              IFBCStr out_file_selection_buffer);
};

/**********************************************************************************/
/* USER INPUT                                                                     */
/**********************************************************************************/

namespace ifb_win32 {

    const IFBKeyCode user_input_keycode(const IFBU32 win32_keycode); 
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
    // IFBEngineUpdate engine_update;
};

namespace ifb_win32 {
    

    ifb_global IFBWin32Context _context;

    inline void context_reset(IFBVoid) { _context = {0}; }

    inline IFBVoid
    context_args_set_values(
              IFBWin32Args& args_ref,
        const HINSTANCE     h_instance,
        const HINSTANCE     h_prev_instance,
        const PWSTR         p_cmd_line,
        const int           n_cmd_show);

    inline IFBVoid context_initialize_platform_api(IFBPlatformApi& platform_api_ref);

    inline const HINSTANCE context_args_get_h_instance      (IFBVoid) { return(_context.args.h_instance);      }
    inline const HINSTANCE context_args_get_h_prev_instance (IFBVoid) { return(_context.args.h_prev_instance); }
    inline const PWSTR     context_args_get_p_cmd_line      (IFBVoid) { return(_context.args.p_cmd_line);      }
    inline const int       context_args_get_n_cmd_show      (IFBVoid) { return(_context.args.n_cmd_show);      }

    inline IFBWin32Args     context_get_args           (IFBVoid) { return(_context.args);          }
    inline IFBWin32Window&  context_get_window         (IFBVoid) { return(_context.window);        }
    inline IFBPlatformApi&  context_get_platform_api   (IFBVoid) { return(_context.platform_api);  }
    // inline IFBEngineUpdate& context_get_engine_update  (IFBVoid) { return(_context.engine_update); }
};


#endif //IFB_WIN32_HPP