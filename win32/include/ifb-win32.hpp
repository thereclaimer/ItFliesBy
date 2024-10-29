#ifndef IFB_WIN32_HPP
#define IFB_WIN32_HPP

#include <r-libs.hpp>
#include <ifb-engine.hpp>

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

namespace ifb_win32 {

    ifb_internal const ifb_memory
    

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

    ifb_internal r_void CALLBACK
    file_read_callback(
        DWORD        error_code,
        DWORD        bytes_transferred,
        LPOVERLAPPED overlapped_ptr);

    ifb_internal r_void CALLBACK
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
    RWin32MonitorInfo            monitor_info;
    RMemoryReservationHandle     memory_reservation;
    RMemoryRegionHandle          win32_region;
    RWin32WindowHandle           window_handle;
    RWin32RenderingContextHandle rendering_context_handle;
    RWin32FileDialogHandle       file_dialog_handle;
    ImGuiContext*                imgui_context;
    IFBWin32FileTable            file_table;
    IFBEnginePlatformApi         platform_api;
    IFBEngineHandle              engine_handle;
};

ifb_global IFBWin32 _ifb_win32;

namespace ifb_win32 {

    inline IFBWin32FileTable&        file_table_ref          (ifb_void) { return(_ifb_win32.file_table);          }
};

#define ifb_win32_main r_win32_main

#endif //IFB_WIN32_HPP