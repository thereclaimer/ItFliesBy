#ifndef IFB_WIN32_HPP
#define IFB_WIN32_HPP

#include <Windows.h>
#include <ifb-engine.hpp>

#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_opengl3.h>

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
};

namespace ifb_engine {
    
    ifb_internal const ifb_b8
    window_create(
        const ifb_cstr window_title,
        const ifb_u32  window_width,
        const ifb_u32  window_height,
        const ifb_u32  window_position_x,
        const ifb_u32  window_position_y);

    ifb_internal const ifb_b8 window_destroy     (ifb_void);
    ifb_internal const ifb_b8 window_update      (ifb_void);
    ifb_internal const ifb_b8 window_show        (ifb_void);
    ifb_internal const ifb_b8 window_opengl_init (ifb_void);
    ifb_internal const ifb_b8 window_imgui_init  (ifb_void);
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

struct IFBWin32 {
};


ifb_global IFBWin32* _ifb_win32_ptr;

namespace ifb_win32 {

};


#endif //IFB_WIN32_HPP