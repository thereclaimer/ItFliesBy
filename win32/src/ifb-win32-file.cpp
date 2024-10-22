#include "ifb-win32.hpp"

#pragma once

ifb_internal const r_b8 
ifb_win32::file_open_read_only(
    const ifb_cstr                     in_file_path,
          IFBEnginePlatformFileIndex& out_file_index_ref) {

    //get the file table
    IFBWin32FileTable& file_table_ref = ifb_win32::file_table_ref();

    //find the first free file
    ifb_b8 file_available = false;
    IFBEnginePlatformFileIndex file_index;
    
    for (
        out_file_index_ref = 0;
        out_file_index_ref < IFB_WIN32_FILE_MANAGER_MAX_FILES;
        ++out_file_index_ref) {

        //if the handle is null, its available
        if (!file_table_ref.columns.handle[out_file_index_ref]) {
            file_available = true;
            break;
        }
    }

    //if we didn't find an available file, we're done
    if (!file_available) {
        return(false);
    }

    //open the file
    const HANDLE file_handle = 
        CreateFile(
            in_file_path,
            GENERIC_READ,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
            NULL);

    //if we couldn't open the file, we're done
    if (!file_handle) {
        return(false);
    }

    //get the file size
    const ifb_size file_size = GetFileSize(file_handle,NULL);

    //initialize this row in the table
    file_table_ref.columns.handle    [out_file_index_ref] = file_handle;
    file_table_ref.columns.size      [out_file_index_ref] = file_size;
    file_table_ref.columns.overlapped[out_file_index_ref] = {0};

    //we're done
    return(true);
}

ifb_internal const r_b8 
ifb_win32::file_open_read_write(
    const ifb_cstr                     in_file_path,
          IFBEnginePlatformFileIndex& out_file_index_ref) {

    //get the file table
    IFBWin32FileTable& file_table_ref = ifb_win32::file_table_ref();

    //find the first free file
    ifb_b8 file_available = false;
    
    for (
        out_file_index_ref = 0;
        out_file_index_ref < IFB_WIN32_FILE_MANAGER_MAX_FILES;
        ++out_file_index_ref) {

        //if the handle is null, its available
        if (!file_table_ref.columns.handle[out_file_index_ref]) {
            file_available = true;
            break;
        }
    }

    //if we didn't find an available file, we're done
    if (!file_available) {
        return(false);
    }

    //open the file
    const HANDLE file_handle = 
        CreateFile(
            in_file_path,
            GENERIC_READ    | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
            NULL);

    //if we couldn't open the file, we're done
    if (!file_handle) {
        return(false);
    }

    //get the file size
    const ifb_size file_size = GetFileSize(file_handle,NULL);

    //initialize this row in the table
    file_table_ref.columns.handle    [out_file_index_ref] = file_handle;
    file_table_ref.columns.size      [out_file_index_ref] = file_size;
    file_table_ref.columns.overlapped[out_file_index_ref] = {0};

    //we're done
    return(true);
}

ifb_internal const ifb_b8
ifb_win32::file_close(
    const IFBEnginePlatformFileIndex file_index) {

    //get the file table
    IFBWin32FileTable& file_table_ref = ifb_win32::file_table_ref();

    //sanity check
    if (file_index > IFB_WIN32_FILE_MANAGER_MAX_FILES) {
        return(false);
    }

    //close the handle
    ifb_b8 result = (ifb_b8)CloseHandle(file_table_ref.columns.handle[file_index]);    
    
    //update the table
    file_table_ref.columns.handle           [file_index] = NULL;
    file_table_ref.columns.size             [file_index] = 0;
    file_table_ref.columns.bytes_transferred[file_index] = 0;
    file_table_ref.columns.overlapped       [file_index] = {0};

    //we're done
    return(result);
}

ifb_internal const ifb_size
ifb_win32::file_size(
    const IFBEnginePlatformFileIndex file_index) {

    //get the file table
    IFBWin32FileTable& file_table_ref = ifb_win32::file_table_ref();

    //sanity check
    if (file_index > IFB_WIN32_FILE_MANAGER_MAX_FILES &&     // valid index
        file_table_ref.columns.handle[file_index] != NULL) { // open file
        return(0);
    }

    //get the file size
    const ifb_size file_size = file_table_ref.columns.size[file_index]; 

    //we're done
    return(file_size);
}

ifb_internal const ifb_b8 
ifb_win32::file_read(
    const IFBEnginePlatformFileIndex in_file_index,
    const ifb_size                   in_file_read_start,
    const ifb_size                   in_file_read_size,
          ifb_memory                out_file_read_buffer) {

    //get the file table
    IFBWin32FileTable& file_table_ref = ifb_win32::file_table_ref();

    //sanity check
    if (in_file_index > IFB_WIN32_FILE_MANAGER_MAX_FILES     && // valid index
        file_table_ref.columns.handle[in_file_index] != NULL && // open file
        out_file_read_buffer                         != NULL) { // valid read buffer

        return(false);
    }

    //get the file handle and pointer to the overlapped structure
    HANDLE                      file_handle    = file_table_ref.columns.handle[in_file_index];
    IFBWin32FileOverlappedInfo* overlapped_ptr = &file_table_ref.columns.overlapped[in_file_index]; 

    //set the start for the read
    overlapped_ptr->overlapped.Offset = in_file_read_start;

    //dp the read
    const r_b8 result = 
        ReadFileEx(
            file_handle,
            out_file_read_buffer,
            in_file_read_size,
            (LPOVERLAPPED)overlapped_ptr,
            ifb_win32::file_io_completion_routine);

    //return the result
    return(result);
}

ifb_internal const ifb_b8 
ifb_win32::file_write(
    const IFBEnginePlatformFileIndex in_file_index,
    const ifb_size                   in_file_write_start,
    const ifb_size                   in_file_write_size,
          ifb_memory                 in_file_write_buffer) {

    //TODO
    return(true);

}

ifb_internal ifb_void CALLBACK
ifb_win32::file_io_completion_routine(
    DWORD        error_code,
    DWORD        bytes_transferred,
    LPOVERLAPPED overlapped_ptr) {

    //get the file table
    IFBWin32FileTable& file_table_ref = ifb_win32::file_table_ref();

    //cast the win32 overlapped to our overlapped structure 
    IFBWin32FileOverlappedInfo* ifb_overlapped_ptr = (IFBWin32FileOverlappedInfo*)overlapped_ptr;

    //sanity check, 
    if (!ifb_overlapped_ptr &&                                               // valid overlapped structure
        ifb_overlapped_ptr->file_index < IFB_WIN32_FILE_MANAGER_MAX_FILES) { // valid index 
        return;
    }
    
    //update the table
    file_table_ref.columns.bytes_transferred[ifb_overlapped_ptr->file_index] = bytes_transferred;
}