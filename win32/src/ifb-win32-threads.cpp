#pragma once

#include "ifb-win32.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb_win32 {

    DWORD WINAPI        thread_function(LPVOID data);
    IFBWin32ThreadInfo* thread_get_win32_info(const IFBThread* ptr_thread);
};


/**********************************************************************************/
/* CREATE/DESTROY                                                                 */
/**********************************************************************************/

ifb_internal const IFBB8
ifb_win32::thread_create(
    IFBThread* ptr_thread) {

    //sanity check
    if (!ptr_thread) return(false);

    //get the processor information
    SYSTEM_INFO win32_system_info;
    GetSystemInfo(&win32_system_info);
    const IFBU32 win32_core_count        = win32_system_info.dwNumberOfProcessors;
    const IFBU32 win32_core_id_current   = GetCurrentProcessorNumber();
    const IFBU32 win32_core_id_requested = ptr_thread->logical_core_id_current;
    const IFBU32 win32_core_id_parent    = ptr_thread->logical_core_id_parent;

    //we can create the thread IF...
    IFBB8 can_create_thread = true;
    can_create_thread &= (win32_core_id_current   == win32_core_id_parent); //...we are on the right parent thread AND
    can_create_thread &= (win32_core_id_requested  < win32_core_count);     //...the requested core id is valid AND
    can_create_thread &= (win32_core_id_parent     < win32_core_count);     //...the parent core id is valid
    if (!can_create_thread) return(false);

    //get win32 info
    IFBWin32ThreadInfo* ptr_win32_thread_info = ifb_win32::thread_get_win32_info(ptr_thread);

    //create the win32 thread
    ptr_win32_thread_info->handle = CreateThread(
        NULL,                         // security attributes
        0,                            // stack size, default size if 0
        ifb_win32::thread_function,   // thread function 
        (LPVOID)ptr_thread,           // thread function data
        ptr_win32_thread_info->flags, // flags
        &ptr_win32_thread_info->id);  // thread id

    //if that failed, we're done
    const IFBB8 thread_created = (ptr_win32_thread_info->handle != NULL); 

    //assign the thread to the requested core
    const IFBB8 thread_assigned = ifb_win32::thread_set_core(
        ptr_win32_thread_info->handle,
        win32_core_id_requested); 

    //last check to see if everything worked
    IFBB8 result = true;
    result &= thread_created;
    result &= thread_assigned;
    
    //if not, we need to close the handle
    if (!result) {
        CloseHandle(ptr_win32_thread_info->handle);
    }

    //we're done
    return(result);
}

ifb_internal const IFBB8
ifb_win32::thread_destroy(
    IFBThread* ptr_thread) {

    if (!ptr_thread) return(false);
    
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
ifb_win32::thread_function(
    LPVOID data) {

    return(0);
}

inline IFBWin32ThreadInfo* 
ifb_win32::thread_get_win32_info(
    const IFBThread* ptr_thread) {

    //sanity check
    ifb_macro_assert(ptr_thread);
    ifb_macro_assert(ptr_thread->platform_context_pointer);
    ifb_macro_assert(ptr_thread->platform_context_size);

    //get thread info
    IFBWin32ThreadInfo* ptr_win32_thread_info = (IFBWin32ThreadInfo*)ptr_thread->platform_context_pointer;   

    //we're done
    return(ptr_win32_thread_info);
}