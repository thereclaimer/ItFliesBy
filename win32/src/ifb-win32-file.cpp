#include "ifb-win32.hpp"

#pragma once

/**********************************************************************************/
/* INTERNAL                                                                        */
/**********************************************************************************/

namespace ifb_win32 {

    IFBWin32FileInfoReadOnly*  file_ro_win32_info_stack_push  (IFBFileReadOnly* file_read_only);
    IFBWin32FileInfoReadOnly*  file_ro_win32_info_stack_load  (IFBFileReadOnly* file_read_only);
    IFBFileReadOnly*           file_ro_load_from_overlapped   (const LPOVERLAPPED overlapped_ptr);

    IFBWin32FileInfoReadWrite* file_rw_win32_info_stack_push  (IFBFileReadWrite* file_read_write);
    IFBWin32FileInfoReadWrite* file_rw_win32_info_stack_load  (IFBFileReadWrite* file_read_write);
    IFBFileReadWrite*          file_rw_load_from_overlapped   (const LPOVERLAPPED overlapped_ptr);
};

/**********************************************************************************/
/* READ ONLY                                                                      */
/**********************************************************************************/

ifb_internal const IFBB8
ifb_win32::file_ro_open(
          IFBFileReadOnly* file_read_only,
    const IFBChar*         file_path) {

    //sanity check
    IFBB8 result = true;
    result &= (file_read_only != NULL);
    result &= (file_path      != NULL);
    if (!result) return(false);

    //push a new win32 file info structure
    IFBWin32FileInfoReadOnly* ptr_win32_file_info = ifb_win32::file_stack_push_win32_info_read_only(file_read_only);
    ifb_macro_assert(ptr_win32_file_info);
    ptr_win32_file_info->ptr_ifb_file = file_read_only;

    //open the file
    ptr_win32_file_info->win32_file_handle = CreateFile(
        file_path,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
        NULL);

    //sanity check
    result &= (ptr_win32_file_info->win32_file_handle != INVALID_HANDLE_VALUE);

    //get the size
    const IFBU32 file_size = GetFileSize(file_path,MAXINT32);

    //initialize the file struct
    file_read_only->platform_lock = 0;
    file_read_only->size          = file_size;
    file_read_only->bytes_read    = 0;
    
    //we're done
    return(result);
}

ifb_internal const IFBB8
ifb_win32::file_ro_read_async(
          IFBFileReadOnly* file_read_only,
    const IFBU32           read_buffer_size,
          IFBByte*         read_buffer_ptr,
    const IFBU32           file_offset) {

    //sanity check
    IFBB8 result = true;
    result &= (file_read_only   != NULL);
    result &= (read_buffer_size != 0);
    result &= (read_buffer_ptr  != NULL);
    result &= (file_offset      <  file_read_only->size);
    result &= (!file_read_only->platform_lock);
    if (!result) return(false);

    //get the file info
    IFBWin32FileInfoReadOnly* ptr_file_info = ifb_win32::file_read_only_get_win32_info(file_read_only);
    ifb_macro_assert(ptr_file_info);

    //update the file
    file_read_only->platform_lock = true;
    file_read_only->bytes_read    = 0;

    //cache read info
    HANDLE     file_handle     = ptr_file_info->win32_file_handle;
    OVERLAPPED file_overlapped = ptr_file_info->win32_overlapped;

    //set the offset
    file_overlapped.Offset = file_offset;

    //do the read
    result &= ReadFileEx(
        file_handle,
        (LPVOID)read_buffer_ptr,
        read_buffer_size,
        &file_overlapped,
        ifb_win32::file_async_completion_routine_ro_read);

    //we're done
    return(result);   
}

ifb_internal const IFBB8
ifb_win32::file_ro_read_immediate(
          IFBFileReadOnly* file_read_only,
    const IFBU32           read_buffer_size,
          IFBByte*         read_buffer_ptr,
    const IFBU32           file_offset) {

    //sanity check
    IFBB8 result = true;
    result &= (file_read_only   != NULL);
    result &= (read_buffer_size != 0);
    result &= (read_buffer_ptr  != NULL);
    result &= (file_offset      <  file_read_only->size);
    result &= (!file_read_only->platform_lock);
    if (!result) return(false);

    //get the file info
    IFBWin32FileInfoReadOnly* ptr_file_info = ifb_win32::file_read_only_get_win32_info(file_read_only);
    ifb_macro_assert(ptr_file_info);

    //do the read
    result &= ReadFile(
        ptr_file_info->win32_file_handle,  // file handle
        (LPVOID)read_buffer_ptr,           // read buffer pointer
        read_buffer_size,                  // read buffer size
        &file_read_only->bytes_read,       // bytes actually read
        &ptr_file_info->win32_overlapped); // win32 overlapped

    //make sure the bytes read is the bytes requested
    result &= (file_read_only->bytes_read == read_buffer_size);

    //we're done
    return(result);
}

ifb_internal const IFBB8
ifb_win32::file_ro_close(
    IFBFileReadOnly* file_read_only) {

    IFBB8 result = true;

    //sanity check
    ifb_macro_assert(file_read_only);

    //get the file info
    IFBWin32FileInfoReadOnly* ptr_file_info = ifb_win32::file_read_only_get_win32_info(file_read_only);
    ifb_macro_assert(ptr_file_info);

    //tell win32 to close the file
    result &= CloseHandle(ptr_file_info->win32_file_handle);
    if (!result) return(false);

    //clear the stack
    result &= ifb_stack::reset(file_read_only->platform_context_stack);

    //we're done
    return(result);
}

/**********************************************************************************/
/* READ WRITE                                                                     */
/**********************************************************************************/

ifb_internal const IFBB8
ifb_win32::file_rw_open(
          IFBFileReadWrite* file_read_write,
    const IFBChar*          file_path) {

    //sanity check
    IFBB8 result = true;
    result &= (file_read_write != NULL);
    result &= (file_path       != NULL);
    if (!result) return(false);

    //push a new win32 file info structure
    IFBWin32FileInfoReadWrite* ptr_win32_file_info = ifb_win32::file_rw_win32_info_stack_push(file_read_write);
    ifb_macro_assert(ptr_win32_file_info);
    ptr_win32_file_info->ptr_ifb_file = file_read_write;

    //open the file
    ptr_win32_file_info->win32_file_handle = CreateFile(
        file_path,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
        NULL);

    //sanity check
    result &= (ptr_win32_file_info->win32_file_handle != INVALID_HANDLE_VALUE);

    //get the size
    const IFBU32 file_size = GetFileSize(file_path,MAXINT32);

    //initialize the file struct
    file_read_write->platform_lock = 0;
    file_read_write->size          = file_size;
    file_read_write->bytes_read    = 0;
    file_read_write->bytes_written = 0;

    //we're done
    return(result);
}

ifb_internal const IFBB8
ifb_win32::file_rw_close(
          IFBFileReadWrite* file_read_write,
    const IFBU32            read_buffer_size, 
          IFBByte*          read_buffer_ptr) {

    IFBB8 result = true;

    //sanity check
    ifb_macro_assert(file_read_only);

    //get the file info
    IFBWin32FileInfoReadWrite* ptr_file_info = ifb_win32::file_rw_win32_info_stack_load(file_read_only);
    ifb_macro_assert(ptr_file_info);

    //tell win32 to close the file
    result &= CloseHandle(ptr_file_info->win32_file_handle);
    if (!result) return(false);

    //clear the stack
    result &= ifb_stack::reset(file_read_only->platform_context_stack);

    //we're done
    return(result);

}

ifb_internal const IFBB8
ifb_win32::file_rw_read_immediate(
          IFBFileReadWrite* file_read_write,
    const IFBU32            read_buffer_size,
          IFBByte*          read_buffer_ptr,
    const IFBU32            file_offset) {
    
    //sanity check
    IFBB8 result = true;
    result &= (file_read_write  != NULL);
    result &= (read_buffer_size != 0);
    result &= (read_buffer_ptr  != NULL);
    result &= (file_offset      <  file_read_write->size);
    result &= (!file_read_write->platform_lock);
    if (!result) return(false);

    //get the file info
    IFBWin32FileInfoReadWrite* ptr_file_info = ifb_win32::file_rw_win32_info_stack_load(file_read_write);
    ifb_macro_assert(ptr_file_info);

    //set the offset
    ptr_file_info->win32_overlapped.Offset = file_offset;

    //update the file lock and read size
    file_read_write->bytes_read    = 0;
    file_read_write->platform_lock = true;

    //do the read
    result &= ReadFile(
        ptr_file_info->win32_file_handle,  // file handle
        (LPVOID)read_buffer_ptr,           // read buffer pointer
        read_buffer_size,                  // read buffer size
        &file_read_write->bytes_read,      // bytes actually read
        &ptr_file_info->win32_overlapped); // win32 overlapped

    //make sure the bytes read is the bytes requested
    result &= (file_read_write->bytes_read == read_buffer_size);

    //release the lock
    file_read_write->platform_lock = false;

    //we're done
    return(result);
}

ifb_internal const IFBB8
ifb_win32::file_rw_read_async(
          IFBFileReadWrite* file_read_write,
    const IFBU32            read_buffer_size,
          IFBByte*          read_buffer_ptr,
    const IFBU32            file_offset) {

    //sanity check
    IFBB8 result = true;
    result &= (file_read_write  != NULL);
    result &= (read_buffer_size != 0);
    result &= (read_buffer_ptr  != NULL);
    result &= (file_offset      <  file_read_write->size);
    result &= (!file_read_write->platform_lock);
    if (!result) return(false);

    //get the file info
    IFBWin32FileInfoReadOnly* ptr_file_info = ifb_win32::file_read_only_get_win32_info(file_read_only);
    ifb_macro_assert(ptr_file_info);

    //update the file
    file_read_only->platform_lock = true;
    file_read_only->bytes_read    = 0;

    //set the offset
    file_overlapped.Offset = file_offset;

    //do the read
    result &= ReadFileEx(
        ptr_file_info->win32_file_handle,        // file handle
        (LPVOID)read_buffer_ptr,                 // read buffer pointer
        read_buffer_size,                        // read buffer size
        &ptr_file_info->win32_overlapped,        // win32 overlapped pointer
        ifb_win32::file_rw_async_callback_read); // callback

    //we're done
    return(result);   
}

ifb_internal const IFBB8
ifb_win32::file_rw_write_immediate (IFBFileReadWrite* file_read_write, const IFBU32   write_buffer_size, const IFBByte* write_buffer_ptr);
ifb_internal const IFBB8
ifb_win32::file_rw_write_async     (IFBFileReadWrite* file_read_write);


/**********************************************************************************/
/* COMPLETION ROUTINES                                                            */
/**********************************************************************************/

ifb_internal void
ifb_win32::file_async_completion_routine_ro_read(
    DWORD        error_code,
    DWORD        bytes_transfered,
    LPOVERLAPPED overlapped_ptr) {

    //get the file pointer
    IFBFileReadOnly* ptr_file = ifb_win32::file_read_only_from_overlapped(overlapped_ptr);
    ifb_macro_assert(ptr_file);

    //make sure there was an operation in progress
    ifb_macro_assert(ptr_file->platform_lock);

    //update the file
    ptr_file->platform_lock = false;
    ptr_file->bytes_read    = bytes_transfered; 
}

ifb_internal void
ifb_win32::file_async_completion_routine_rw_read(
    DWORD        error_code,
    DWORD        bytes_transfered,
    LPOVERLAPPED overlapped_ptr) {

    //get the file pointer
    IFBFileReadOnly* ptr_file = ifb_win32::file_read_only_from_overlapped(overlapped_ptr);
    ifb_macro_assert(ptr_file);

    //make sure there was an operation in progress
    ifb_macro_assert(ptr_file->platform_lock);

    //update the file
    ptr_file->platform_lock = false;
    ptr_file->bytes_read    = bytes_transfered; 
}

ifb_internal void
ifb_win32::file_async_completion_routine_rw_write(
    DWORD        error_code,
    DWORD        bytes_transfered,
    LPOVERLAPPED overlapped_ptr) {

    //get the file pointer
    IFBFileReadOnly* ptr_file = ifb_win32::file_read_only_from_overlapped(overlapped_ptr);
    ifb_macro_assert(ptr_file);

    //make sure there was an operation in progress
    ifb_macro_assert(ptr_file->platform_lock);

    //update the file
    ptr_file->platform_lock = false;
    ptr_file->bytes_read    = bytes_transfered; 
}

/**********************************************************************************/
/* INTERNAL                                                                        */
/**********************************************************************************/


inline IFBWin32FileInfoReadOnly* 
ifb_win32::file_read_only_push_win32_info(
    IFBFileReadOnly* file_read_only) {

    //sanity check
    ifb_macro_assert(file_read_only);
    ifb_macro_assert(file_read_only->platform_context_stack);

    //push our win32 file info onto the stack
    const IFBU32              win32_file_info_size = ifb_macro_align_size_struct(IFBWin32FileInfoReadOnly);
    IFBWin32FileInfoReadOnly* win32_file_info_ptr  = (IFBWin32FileInfoReadOnly*)ifb_stack::push_absolute(
        file_read_only->platform_context_stack,
        win32_file_info_size);

    //sanity check
    ifb_macro_assert(win32_file_info_ptr);

    //we're done
    return(win32_file_info_ptr);
}

inline IFBWin32FileInfoReadOnly*
ifb_win32::file_read_only_get_win32_info(
    IFBFileReadOnly* file_read_only) {

    //sanity check
    ifb_macro_assert(file_read_only);
    ifb_macro_assert(file_read_only->platform_context_stack);

    //get the base of the stack
    IFBWin32FileInfoReadOnly* file_info = ifb_stack::get_pointer(file_read_only->platform_context_stack, 0);
    ifb_macro_assert(file_info);

    //we're done
    return(file_info);
}

inline IFBFileReadOnly*
ifb_win32::file_from_overlapped_read_only(
    const LPOVERLAPPED overlapped_ptr) {

    ifb_macro_assert(overlapped_ptr);

    IFBWin32FileInfoReadOnly* ptr_win32_file_info = (IFBWin32FileInfoReadOnly*)overlapped_ptr->Pointer;
    ifb_macro_assert(ptr_win32_file_info);
    
    IFBFileReadOnly* ptr_file = ptr_win32_file_info->ptr_ifb_file;  
    ifb_macro_assert(ptr_file);

    return(ptr_file);
}

inline IFBFileReadWrite*
ifb_win32::file_from_overlapped_read_write(
    const LPOVERLAPPED overlapped_ptr) {

    ifb_macro_assert(overlapped_ptr);

    IFBWin32FileInfoReadWrite* ptr_win32_file_info = (IFBWin32FileInfoReadWrite*)overlapped_ptr->Pointer;
    ifb_macro_assert(ptr_win32_file_info);
    
    IFBFileReadWrite* ptr_file = ptr_win32_file_info->ptr_ifb_file;  
    ifb_macro_assert(ptr_file);

    return(ptr_file);
}
