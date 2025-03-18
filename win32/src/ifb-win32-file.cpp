#include "ifb-win32.hpp"

#pragma once

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb_win32 {
    
    //validation
    const IFBB8 file_ro_validate_request(const IFBFileReadOnlyRequest* file_ro_request);
    const IFBB8 file_ro_validate_context(const IFBFileReadOnlyContext* file_ro_context);

    //completion routines
    void file_ro_async_callback_read  (DWORD error_code, DWORD bytes_transfered, LPOVERLAPPED overlapped_ptr);
    void file_rw_async_callback_read  (DWORD error_code, DWORD bytes_transfered, LPOVERLAPPED overlapped_ptr);
    void file_rw_async_callback_write (DWORD error_code, DWORD bytes_transfered, LPOVERLAPPED overlapped_ptr);
};

/**********************************************************************************/
/* READ ONLY                                                                      */
/**********************************************************************************/

ifb_internal const IFBU32
ifb_win32::file_ro_context_size(
    IFBVoid) {

    const IFBU32 context_size = ifb_macro_align_size_struct(IFBWin32FileReadOnly);
    return(context_size);
}

ifb_internal const IFBB8
ifb_win32::file_ro_open(
    IFBFileReadOnlyRequest* file_ro_request) {

    //validate the request
    IFBB8 result = ifb_win32::file_ro_validate_request(file_ro_request);
    if (!result) return(false);

    //get the file path information
    const IFBU32            file_count       = file_ro_request->file_count;
    const IFBU32            file_path_stride = file_ro_request->file_path_stride;
    const IFBChar*          file_path_buffer = file_ro_request->pointers.file_path;
    IFBFileReadOnlyContext* file_context     = file_ro_request->pointers.platform_context;

    //loop through the contexts and open the handles
    for (
        IFBU32 file_index = 0;
               file_index < file_count;
             ++file_index) {

        //get the file path
        const IFBU32   win32_file_path_offset = file_index * file_path_stride;
        const IFBChar* win32_file_path_buffer = file_path_buffer[current_file_path_offset];
        
        //get the context
        IFBFileReadOnlyContext& current_context_ref = file_context[file_index];

        //cast the win32 file
        IFBWin32FileReadOnly* win32_file = (IFBWin32FileReadOnly*)current_platform_context_ref.data;

        //open the file handle
        const HANDLE win32_file_handle = CreateFile(
            win32_file_path_buffer,
            win32_file_access,
            win32_file_share_mode,
            win32_file_security_attributes,
            win32_file_creation,
            win32_file_flags,
            win32_file_template);

        //make sure the handle is valid
        result &= (win32_file_handle != INVALID_HANDLE_VALUE); 
    
        //update the file
        win32_file->win32_file_handle = win32_file_handle;
        win32_file->win32_overlapped  = {0};
    }

    //we're done
    return(result);
}

ifb_internal const IFBB8
ifb_win32::file_ro_read_async(
    IFBFileReadOnlyRequest* file_ro_request) {

    //validate the request
    IFBB8 result = ifb_win32::file_ro_validate_request(file_ro_request);
    if (!result) return(false);

    const IFBU32            file_count         = file_ro_request->file_count;
    IFBFileReadOnlyContext* file_array_context = file_ro_request->pointers.context;
    IFBFileBuffer*          file_array_buffer  = file_ro_request->pointers.buffer;

    LPOVERLAPPED_COMPLETION_ROUTINE win32_file_completion_routine = ifb_win32::file_ro_async_callback_read; 

    for (
        IFBU32 file_index = 0;
               file_index < file_count;
             ++file_index) {

        //get the current context and buffer
        IFBFileReadOnlyContext& ref_file_context = file_array_context [file_index];
        IFBFileBuffer&          ref_file_buffer  = file_array_buffer  [file_index];

        //get the win32 file
        IFBWin32FileReadOnly* win32_file = ifb_win32::file_ro_validate_context(file_context_ref);
    
        //file read info
        const HANDLE win32_file_handle           = win32_file->win32_file_handle;
        LPVOID       win32_file_read_buffer      = ref_file_buffer.start;
        const DWORD  win32_file_read_buffer_size = ref_file_buffer.size;
        LPOVERLAPPED win32_file_overlapped       = &win32_file->win32_overlapped;

        //update the offset
        win32_file_overlapped->Offset = ref_file_buffer.file_offset;

        //read the file
        result &= ReadFileEx(
            win32_file_handle,
            win32_file_read_buffer,
            win32_file_read_buffer_size,
            win32_file_overlapped,
            win32_file_completion_routine);
    }

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

inline const IFBB8
ifb_win32::file_ro_validate_request(
    const IFBFileReadOnlyRequest* file_ro_request) {
    
    if (!file_ro_request) return(false);

    IFBB8 is_valid = true;
    is_valid &= (file_ro_request->pointers.platform_context != NULL);
    is_valid &= (file_ro_request->pointers.file_table_index != NULL);
    is_valid &= (file_ro_request->file_count != 0);
    return(is_valid);
}

inline IFBWin32FileReadOnly*
ifb_win32::file_ro_validate_context(
    const IFBFileReadOnlyContext& file_ro_context) {

    //cast the context
    IFBWin32FileReadOnly* win32_file = (IFBWin32FileReadOnly*)file_ro_context.data;
    if (!win32_file) return(NULL);

    //validate the parameters
    IFBB8 is_valid = (win32_file->win32_file_handle != INVALID_HANDLE_VALUE);

    //we're done
    return(is_valid);
}


inline IFBWin32FileInfoReadOnly* 
ifb_win32::file_ro_win32_info_stack_push(
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
ifb_win32::file_ro_win32_info_stack_load(
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
ifb_win32::file_ro_load_from_overlapped(
    const LPOVERLAPPED overlapped_ptr) {

    ifb_macro_assert(overlapped_ptr);

    IFBWin32FileInfoReadOnly* ptr_win32_file_info = (IFBWin32FileInfoReadOnly*)overlapped_ptr->Pointer;
    ifb_macro_assert(ptr_win32_file_info);
    
    IFBFileReadOnly* ptr_file = ptr_win32_file_info->ptr_ifb_file;  
    ifb_macro_assert(ptr_file);

    return(ptr_file);
}

inline IFBWin32FileInfoReadWrite* 
ifb_win32::file_rw_win32_info_stack_push(
    IFBFileReadWrite* file_read_write) {

    //sanity check
    ifb_macro_assert(file_read_write);
    ifb_macro_assert(file_read_write->platform_context_stack);

    //push our win32 file info onto the stack
    const IFBU32              win32_file_info_size = ifb_macro_align_size_struct(IFBWin32FileInfoReadOnly);
    IFBWin32FileInfoReadOnly* win32_file_info_ptr  = (IFBWin32FileInfoReadWrite*)ifb_stack::push_absolute(
        file_read_write->platform_context_stack,
        win32_file_info_size);

    //sanity check
    ifb_macro_assert(win32_file_info_ptr);

    //we're done
    return(win32_file_info_ptr);
}

inline IFBWin32FileInfoReadWrite*
ifb_win32::file_rw_win32_info_stack_load(
    IFBFileReadWrite* file_read_write) {

    //sanity check
    ifb_macro_assert(file_read_write);
    ifb_macro_assert(file_read_write->platform_context_stack);

    //get the base of the stack
    IFBWin32FileInfoReadWrite* file_info = ifb_stack::get_pointer(file_read_write->platform_context_stack, 0);
    ifb_macro_assert(file_info);

    //we're done
    return(file_info);
}

inline IFBFileReadWrite*
ifb_win32::file_rw_load_from_overlapped(
    const LPOVERLAPPED overlapped_ptr) {

    ifb_macro_assert(overlapped_ptr);

    IFBWin32FileInfoReadWrite* ptr_win32_file_info = (IFBWin32FileInfoReadWrite*)overlapped_ptr->Pointer;
    ifb_macro_assert(ptr_win32_file_info);
    
    IFBFileReadWrite* ptr_file = ptr_win32_file_info->ptr_ifb_file;  
    ifb_macro_assert(ptr_file);

    return(ptr_file);
}