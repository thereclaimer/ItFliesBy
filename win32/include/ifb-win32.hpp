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

    const IFBB8   system_get_info_cpu    (IFBSystemCPUInfo*    cpu_info);
    const IFBB8   system_get_info_memory (IFBSystemMemoryInfo* memory_info);
    const IFBU64  system_time_ms         (IFBVoid);
          IFBVoid system_sleep           (const IFBU32 ms);
          IFBVoid system_debug_print     (const IFBChar* debug_string);
};

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

namespace ifb_win32 {

    const IFBPtr memory_reserve  (const IFBU64 reservation_size);
    const IFBB8  memory_release  (const IFBPtr reservation_start, const IFBU64 reservation_size);
    const IFBPtr memory_commit   (const IFBPtr commit_start,      const IFBU64 commit_size);
    const IFBB8  memory_decommit (const IFBPtr commit_start,      const IFBU64 commit_size);
};

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

struct IFBWin32Window : IFBPlatformWindow {
    struct {
        struct {
            HWND window;
            HDC  device;
        } handles;
        struct {
            WPARAM w;
            LPARAM l;
        } message_params;
    } win32;
};
 
namespace ifb_win32 {

    const IFBB8 window_create         (IFBWin32Window* window);
    const IFBB8 window_destroy        (IFBWin32Window* window);
    const IFBB8 window_process_events (IFBWin32Window* window);
    const IFBB8 window_swap_buffers   (IFBWin32Window* window);
    const IFBB8 window_show           (IFBWin32Window* window);
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

/**********************************************************************************/
/* USER INPUT                                                                     */
/**********************************************************************************/

namespace ifb_win32 {

    const IFBKeyCode user_input_keycode(const IFBU32 win32_keycode); 
};

/**********************************************************************************/
/* WIN32 PLATFORM API                                                             */
/**********************************************************************************/

#endif //IFB_WIN32_HPP