#pragma once

#include <stdio.h>
#include "ifb-win32.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb_win32 {

    IFBWin32ThreadContext* thread_get_context (const IFBThread* ptr_thread);
    DWORD WINAPI           thread_routine           (LPVOID data);
    IFBThread*             thread_validate_data     (LPVOID data);
};


/**********************************************************************************/
/* CREATE/DESTROY                                                                 */
/**********************************************************************************/

ifb_internal const IFBB8
ifb_win32::thread_create(
          IFBThread* thread_ptr,
    const IFBU32     thread_count) {

    IFBB8 result = true;

    //sanity check
    if (!thread_ptr) return(false);

    //get the processor information
    SYSTEM_INFO win32_system_info;
    GetSystemInfo(&win32_system_info);
    const IFBU32 win32_core_count        = win32_system_info.dwNumberOfProcessors;
    const IFBU32 win32_core_id_current   = GetCurrentProcessorNumber();

    // iterate through each thread and intialize the context
    // based on the information at each index
    //
    // this loop is all or nothing, we successfully create
    // all threads or we fail
    for ( 
        IFBU32 thread_index = 0;
               thread_index < thread_count;
             ++thread_index) {

        //get the current thread
        IFBThread* thread_current_ptr = &thread_ptr[thread_index];

        //get the requested and parent core ids 
        const IFBU32 thread_core_id_requested = thread_current_ptr->logical_core_id_current;
        const IFBU32 thread_core_id_parent    = thread_current_ptr->logical_core_id_parent;

        //get win32 info
        IFBWin32ThreadContext* thread_win32_context_ptr = ifb_win32::thread_get_context(thread_current_ptr);
        
        //make sure the core ids and thread info are valid
        result &= (thread_core_id_requested <  win32_core_count); 
        result &= (thread_core_id_parent    <  win32_core_count);
        result &= (thread_win32_context_ptr != NULL); 
        if (!result) break;

        //thread win32 properties
        LPSECURITY_ATTRIBUTES  thread_win32_security_attributes = NULL; 
        const DWORD            thread_win32_stack_size          = IFB_WIN32_THREAD_STACK_SIZE;
        LPTHREAD_START_ROUTINE thread_win32_routine             = ifb_win32::thread_routine;
        LPVOID                 thread_win32_data                = (LPVOID)thread_current_ptr;
        const DWORD            thread_win32_flags               = IFB_WIN32_THREAD_FLAGS; 
        DWORD                  thread_win32_id                  = 0;
        
        //create the win32 thread handle
        const HANDLE thread_win32_handle = CreateThread(
            thread_win32_security_attributes, // security attributes
            thread_win32_stack_size,          // stack size, default size if 0
            thread_win32_routine,             // thread function 
            thread_win32_data,                // thread function data
            thread_win32_flags,               // flags
           &thread_win32_id);                 // thread id
    
        //assign the thread to the requested core
        result &= (thread_win32_handle > 0);
        result &= ifb_win32::thread_set_core(thread_win32_handle, thread_core_id_requested); 

        //if creating the thread or assigning it to a core failed, 
        //make sure the handle is closed
        if (!result) {

            //we don't care about the result, windows can
            //deal with invalid handles and the function
            //has failed anyway
            (VOID)CloseHandle(thread_win32_handle);
            break;
        }

        //update the thread win32 context
        thread_win32_context_ptr->handle = thread_win32_handle;
        thread_win32_context_ptr->id     = thread_win32_id;
        thread_win32_context_ptr->flags  = thread_win32_flags;
    }

    //we're done
    return(result);
}

ifb_internal const IFBB8
ifb_win32::thread_destroy(
          IFBThread* thread_ptr,
    const IFBU32     thread_count) {

    if (!thread_ptr) return(false);
    
    return(false);
}

ifb_internal const IFBB8 
ifb_win32::thread_set_core(
    const HANDLE win32_thread_handle,
    const IFBU32 core_number) {

    //calculate the affinity mask.
    //where the core number is the bit
    const DWORD_PTR core_affinity_mask  = (DWORD_PTR)(1ULL << core_number);
    
    //set the mask, returns the prior affinity mask
    const DWORD_PTR prior_affinity_mask = SetThreadAffinityMask(
        win32_thread_handle,
        core_affinity_mask);
        
    //if thats not null, it succeeded
    const IFBB8 thread_assigned = (prior_affinity_mask != NULL);

    //we're done
    return(thread_assigned);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

ifb_internal DWORD WINAPI
ifb_win32::thread_routine(
    LPVOID data) {

    //get the thread context
    IFBThread*             ptr_thread         = ifb_win32::thread_validate_data (data);
    IFBWin32ThreadContext* ptr_thread_context = ifb_win32::thread_get_context   (ptr_thread);

    //debug string
    const IFBU32 debug_out_size = 128;
    IFBChar debug_out[debug_out_size];
    (IFBVoid)sprintf_s(debug_out,debug_out_size,"HELLO FROM THREAD [%d]",ptr_thread->logical_core_id_current);
    ifb_win32::system_debug_out(debug_out);

    //we're done
    return(S_OK);
}

inline IFBWin32ThreadContext* 
ifb_win32::thread_get_context(
    const IFBThread* ptr_thread) {

    //get the context size
    const IFBU32 context_size = ifb_macro_align_size_struct(IFBWin32ThreadContext);

    //sanity check
    IFBB8 result = true;
    result &= (ptr_thread != NULL);
    result &= (result && ptr_thread->platform_context_pointer != NULL);
    result &= (result && ptr_thread->platform_context_size    >= context_size);
    if (!result) return(NULL);

    //get thread info
    IFBWin32ThreadContext* ptr_win32_thread_info = (IFBWin32ThreadContext*)ptr_thread->platform_context_pointer;   

    //we're done
    return(ptr_win32_thread_info);
}

inline IFBThread*
ifb_win32::thread_validate_data(
    LPVOID data) {

    //make sure the pointer is valid
    if (!data) return(NULL);

    //cast the pointer
    IFBThread* ptr_thread = (IFBThread*)data;

    //make sure the thread is operating on the assigned core
    const IFBU32 core_id_current  = GetCurrentProcessorNumber();
    const IFBU32 core_id_assigned = ptr_thread->logical_core_id_current;
    if (core_id_current != core_id_assigned) return(NULL);

    //we're done
    return(ptr_thread);
}
