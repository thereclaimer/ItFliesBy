#ifndef IFB_WIN32_HPP
#define IFB_WIN32_HPP

#include <Windows.h>
#include <ifb.hpp>
#include <ifb-engine.hpp>

/**********************************************************************************/
/* REGISTRY                                                                       */
/**********************************************************************************/

struct IFBWin32RegKeyU32 {
    HKEY   key;
    IFBU32 value;
};

namespace ifb_win32 {

    //read only
    const IFBB8 registry_key_open_read_only_classes_root   (const LPCSTR key_path, HKEY& key_ref);
    const IFBB8 registry_key_open_read_only_current_user   (const LPCSTR key_path, HKEY& key_ref);
    const IFBB8 registry_key_open_read_only_local_machine  (const LPCSTR key_path, HKEY& key_ref);
    const IFBB8 registry_key_open_read_only_users          (const LPCSTR key_path, HKEY& key_ref);
    const IFBB8 registry_key_open_read_only_current_config (const LPCSTR key_path, HKEY& key_ref);

    //close
    const IFBB8 registry_key_close(const HKEY key);

    //values
    const IFBB8 registry_key_read_value_u32           (const HKEY key, const LPCSTR value_name, IFBU32& value_ref);
    const IFBB8 registry_key_read_value_cpu_speed_mhz (IFBWin32RegKeyU32& key_u32);
};

#define IFB_WIN32_SYSTEM_REGKEY_PROCESSOR_0     R"(HARDWARE\DESCRIPTION\System\CentralProcessor\0)" 
#define IFB_WIN32_SYSTEM_REGKEY_PROCESSOR_0_MHZ "~MHz"


#define ifb_win32_macro_registry_key_cpu_0(key_ref)                         ifb_win32::registry_key_open_read_only_local_machine(IFB_WIN32_SYSTEM_REGKEY_PROCESSOR_0, key_ref)
#define ifb_win32_macro_registry_key_cpu_0_value_u32_mhz(key,value_u32_ref) ifb_win32::registry_key_read_value_u32(key,IFB_WIN32_SYSTEM_REGKEY_PROCESSOR_0_MHZ,value_u32_ref)

/**********************************************************************************/
/* SYSTEM                                                                         */
/**********************************************************************************/

namespace ifb_win32 {

    ifb_internal const IFBB8   system_get_info_cpu    (IFBSystemCPUInfo*    cpu_info);
    ifb_internal const IFBB8   system_get_info_memory (IFBSystemMemoryInfo* memory_info);
    ifb_internal const IFBU64  system_time_ms         (IFBVoid);
    ifb_internal       IFBVoid system_sleep           (const IFBU32 ms);
    ifb_internal       IFBVoid system_debug_print     (const IFBChar* debug_string);
};

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

namespace ifb_win32 {

    ifb_internal const IFBPtr memory_reserve (const IFBU64 reservation_size);
    ifb_internal const IFBB8  memory_release (const IFBPtr reservation_start, const IFBU64 reservation_size);
    ifb_internal const IFBPtr memory_commit  (const IFBPtr commit_start,      const IFBU64 commit_size);
};

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

struct IFBWin32Window {
    HWND          window_handle;
    HDC           device_context;
    HGLRC         opengl_context;
    IFBU32        width;
    IFBU32        height;
    IFBU32        position_x;
    IFBU32        position_y;
    IFBB8         quit_received;
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

    ifb_internal const IFBB8 
    window_create(
        const IFBChar* title,
        const IFBU32  width,
        const IFBU32  height,
        const IFBU32  position_x,
        const IFBU32  position_y);

    ifb_internal const IFBB8   window_destroy      (IFBVoid);
    ifb_internal const IFBB8   window_frame_start  (IFBVoid);
    ifb_internal const IFBB8   window_frame_render (IFBVoid);
    ifb_internal const IFBB8   window_show         (IFBVoid);
    ifb_internal IFBGLContext  window_opengl_init  (IFBVoid);
    ifb_internal ImGuiContext* window_imgui_init   (IFBVoid);

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

    const IFBU32 monitor_count (IFBVoid);
    
    const IFBB8
    monitor_info(
        const IFBU32      monitor_count,
              IFBMonitor* monitor_array);

    ifb_internal BOOL CALLBACK monitor_enum_callback_count (HMONITOR handle,HDC device_context, LPRECT rect_ptr, LPARAM data_ptr);
    ifb_internal BOOL CALLBACK monitor_enum_callback_info  (HMONITOR handle,HDC device_context, LPRECT rect_ptr, LPARAM data_ptr);
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
    ifb_internal const IFBU32 file_ro_context_size     (IFBVoid);
    ifb_internal const IFBB8  file_ro_open             (IFBPlatformFileRequest* file_ro_request);
    ifb_internal const IFBB8  file_ro_read_async       (IFBPlatformFileRequest* file_ro_request);
    ifb_internal const IFBU32 file_ro_read_immediate   (IFBPlatformFileRequest* file_ro_request);
    ifb_internal const IFBB8  file_ro_close            (IFBPlatformFileRequest* file_ro_request);
    
    //read write
    ifb_internal const IFBU32 file_rw_context_size     (IFBVoid);
    ifb_internal const IFBB8  file_rw_open             (IFBPlatformFileRequest* file_rw_request);
    ifb_internal const IFBU32 file_rw_read_immediate   (IFBPlatformFileRequest* file_rw_request);
    ifb_internal const IFBB8  file_rw_read_async       (IFBPlatformFileRequest* file_rw_request);
    ifb_internal const IFBU32 file_rw_write_immediate  (IFBPlatformFileRequest* file_rw_request);
    ifb_internal const IFBB8  file_rw_write_async      (IFBPlatformFileRequest* file_rw_request);
    ifb_internal const IFBB8  file_rw_close            (IFBPlatformFileRequest* file_rw_request);
};

/**********************************************************************************/
/* FILE DIALOG                                                                    */
/**********************************************************************************/

#define IFB_WIN32_DIALOG_CSTR_LENGTH_MAX 256
#define IFB_WIN32_DIALOG_WSTR_LENGTH_MAX 128

namespace ifb_win32 {

    ifb_internal const IFBB8
    file_dialog_select_file(
        const IFBChar*  in_file_dialog_starting_directory,
        const IFBSize   in_file_type_count,
        const IFBChar** in_file_type_name_cstr_ptr,
        const IFBChar** in_file_type_spec_cstr_ptr,
              IFBChar* out_file_selection_buffer);
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
    IFBMemoryContext*       ptr_memory_context;
    IFBWin32Args*           ptr_win32_args;
    IFBWin32Window*         ptr_win32_window;
    IFBEngineContextUpdate* ptr_engine_update;
};

struct IFBWin32ContextInit {
    IFBB64            result;
    IFBWin32Context*  context_win32;
    IFBMemoryContext* context_memory;
    IFBPlatformAPI    platform_api;
};

namespace ifb_win32 {


    const IFBB8 context_create    (const IFBWin32Args* win32_args);
    const IFBB8 context_main_loop (IFBVoid);
    const IFBB8 context_destroy   (IFBVoid);

    IFBEngineContextUpdate* context_get_engine_update (IFBVoid);
    IFBWin32Args*           context_get_args          (IFBVoid);
    IFBWin32Window*         context_get_window        (IFBVoid);
};


#endif //IFB_WIN32_HPP