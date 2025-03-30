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
    ifb::u32 value;
};

namespace ifb_win32 {

    //read only
    const ifb::b8 registry_key_open_read_only_classes_root   (const LPCSTR key_path, HKEY& key_ref);
    const ifb::b8 registry_key_open_read_only_current_user   (const LPCSTR key_path, HKEY& key_ref);
    const ifb::b8 registry_key_open_read_only_local_machine  (const LPCSTR key_path, HKEY& key_ref);
    const ifb::b8 registry_key_open_read_only_users          (const LPCSTR key_path, HKEY& key_ref);
    const ifb::b8 registry_key_open_read_only_current_config (const LPCSTR key_path, HKEY& key_ref);

    //close
    const ifb::b8 registry_key_close(const HKEY key);

    //values
    const ifb::b8 registry_key_read_value_u32           (const HKEY key, const LPCSTR value_name, ifb::u32& value_ref);
    const ifb::b8 registry_key_read_value_cpu_speed_mhz (IFBWin32RegKeyU32& key_u32);
};

#define IFB_WIN32_SYSTEM_REGKEY_PROCESSOR_0     R"(HARDWARE\DESCRIPTION\System\CentralProcessor\0)" 
#define IFB_WIN32_SYSTEM_REGKEY_PROCESSOR_0_MHZ "~MHz"

#define ifb_win32_macro_registry_key_cpu_0(key_ref)                         ifb_win32::registry_key_open_read_only_local_machine(IFB_WIN32_SYSTEM_REGKEY_PROCESSOR_0, key_ref)
#define ifb_win32_macro_registry_key_cpu_0_value_u32_mhz(key,value_u32_ref) ifb_win32::registry_key_read_value_u32(key,IFB_WIN32_SYSTEM_REGKEY_PROCESSOR_0_MHZ,value_u32_ref)

/**********************************************************************************/
/* SYSTEM                                                                         */
/**********************************************************************************/

namespace ifb_win32 {

    const ifb::b8   system_get_info_cpu    (IFBSystemCPUInfo*    cpu_info);
    const ifb::b8   system_get_info_memory (IFBSystemMemoryInfo* memory_info);
    const ifb::u64  system_time_ms         (void);
          void system_sleep           (const ifb::u32 ms);
          void system_debug_print     (const ifb::utf8* debug_string);
};

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

namespace ifb_win32 {

    const ifb::ptr memory_reserve  (const ifb::u64 reservation_size);
    const ifb::b8  memory_release  (const ifb::ptr reservation_start, const ifb::u64 reservation_size);
    const ifb::ptr memory_commit   (const ifb::ptr commit_start,      const ifb::u64 commit_size);
    const ifb::b8  memory_decommit (const ifb::ptr commit_start,      const ifb::u64 commit_size);
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

    const ifb::u32 window_size           (void);
    const ifb::b8  window_create         (IFBWin32Window* window);
    const ifb::b8  window_destroy        (IFBWin32Window* window);
    const ifb::b8  window_process_events (IFBWin32Window* window);
    const ifb::b8  window_swap_buffers   (IFBWin32Window* window);
    const ifb::b8  window_show           (IFBWin32Window* window);
};

/**********************************************************************************/
/* MONITOR                                                                        */
/**********************************************************************************/

namespace ifb_win32 {

    const ifb::u32 monitor_count (void);
    
    const ifb::b8
    monitor_info(
        const ifb::u32      monitor_count,
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
    const ifb::u32 file_ro_context_size     (void);
    const ifb::b8  file_ro_open             (IFBPlatformFileRequest* file_ro_request);
    const ifb::b8  file_ro_read_async       (IFBPlatformFileRequest* file_ro_request);
    const ifb::u32 file_ro_read_immediate   (IFBPlatformFileRequest* file_ro_request);
    const ifb::b8  file_ro_close            (IFBPlatformFileRequest* file_ro_request);
    
    //read write
    const ifb::u32 file_rw_context_size     (void);
    const ifb::b8  file_rw_open             (IFBPlatformFileRequest* file_rw_request);
    const ifb::u32 file_rw_read_immediate   (IFBPlatformFileRequest* file_rw_request);
    const ifb::b8  file_rw_read_async       (IFBPlatformFileRequest* file_rw_request);
    const ifb::u32 file_rw_write_immediate  (IFBPlatformFileRequest* file_rw_request);
    const ifb::b8  file_rw_write_async      (IFBPlatformFileRequest* file_rw_request);
    const ifb::b8  file_rw_close            (IFBPlatformFileRequest* file_rw_request);
};

/**********************************************************************************/
/* USER INPUT                                                                     */
/**********************************************************************************/

namespace ifb_win32 {

    const IFBKeyCode user_input_keycode(const ifb::u32 win32_keycode); 
};

/**********************************************************************************/
/* WIN32 PLATFORM API                                                             */
/**********************************************************************************/

#endif //IFB_WIN32_HPP