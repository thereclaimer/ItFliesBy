#ifndef IFB_WIN32_HPP
#define IFB_WIN32_HPP

#include <r-libs.hpp>
#include <ifb-engine.hpp>

#define IFB_WIN32_FILE_MANAGER_MAX_FILES 32

struct IFBWin32FileOverlappedInfo {
    OVERLAPPED                 overlapped;
    IFBEnginePlatformFileIndex file_index;    
};

struct IFBWin32FileTable {
    ifb_size row_count;
    struct {
        HANDLE                     handle           [IFB_WIN32_FILE_MANAGER_MAX_FILES];
        ifb_size                   size             [IFB_WIN32_FILE_MANAGER_MAX_FILES];
        ifb_size                   bytes_transferred[IFB_WIN32_FILE_MANAGER_MAX_FILES];
        IFBWin32FileOverlappedInfo overlapped       [IFB_WIN32_FILE_MANAGER_MAX_FILES];
    } columns;
};

namespace ifb_win32 {

    ifb_internal const ifb_b8 file_open_read_only  (const ifb_cstr file_path, IFBEnginePlatformFileIndex& out_file_index_ref);
    ifb_internal const ifb_b8 file_open_read_write (const ifb_cstr file_path, IFBEnginePlatformFileIndex& out_file_index_ref);
    ifb_internal const ifb_b8 file_create_new      (const ifb_cstr file_path, IFBEnginePlatformFileIndex& out_file_index_ref);

    ifb_internal const ifb_b8   file_close (const IFBEnginePlatformFileIndex);
    ifb_internal const ifb_size file_size  (const IFBEnginePlatformFileIndex);
    
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
              ifb_memory                 in_file_write_buffer);

    ifb_internal r_void CALLBACK
    file_io_completion_routine(
        DWORD        error_code,
        DWORD        bytes_transferred,
        LPOVERLAPPED overlapped_ptr);
};

struct IFBWin32 {
    RMemoryReservationHandle memory_reservation;
    RMemoryRegionHandle      win32_region;
    IFBWin32FileTable        file_table;
};

ifb_global IFBWin32 _ifb_win32;

namespace ifb_win32 {

    inline IFBWin32FileTable& file_table_ref() { return(_ifb_win32.file_table); }
};

#define ifb_win32_main r_win32_main

#endif //IFB_WIN32_HPP