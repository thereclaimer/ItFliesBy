#pragma once

#include <stdio.h>
#include "ifb-win32.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

ifb_global const IFBU32 IFB_WIN32_THREAD_CONTEXT_SIZE     = sizeof(IFBWin32Context); 
ifb_global const IFBU32 IFB_WIN32_THREAD_DEBUG_OUT_LENGTH = 64;

struct IFBWin32ThreadDebugInfo {
    IFBU32   thread_id;
    IFBU32   thread_core_number;
    IFBU32   thread_debug_buffer_length;
    IFBChar* thread_debug_buffer_ptr;
};

namespace ifb_win32 {

    IFBWin32ThreadContext*    thread_get_context_win32    (const IFBThreadPlatformContext* thread_platform_context);
    IFBThreadPlatformContext* thread_get_context_platform (LPVOID data);
    DWORD WINAPI              thread_routine              (LPVOID data);

    IFBVoid
    thread_debug_out(
        const IFBWin32ThreadDebugInfo& thread_debug_info_ref,
        const IFBChar*                 thread_debug_message_ptr);
};

/**********************************************************************************/
/* CREATE/DESTROY                                                                 */
/**********************************************************************************/

ifb_internal const IFBB8
ifb_win32::thread_create(
    const IFBThreadPlatformContext* thread_context,
    const IFBU32                    thread_count,
    const IFBChar*                  thread_description,
    const IFBU32                    thread_description_stride,
          IFBU64*                   thread_id) {

    //sanity check
    IFBB8 result = true;                           // we can create the thread(s) IF...
    result &= (thread_context            != NULL); //...we have a context                   AND
    result &= (thread_count              != 0);    //...we have at least one thread         AND
    result &= (thread_description        != NULL); //...we have a descripiton               AND
    result &= (thread_description_stride != 0);    //...we have a description length/stride AND
    result &= (thread_id                 != 0);    //...we can return a thread id           AND
    if (!result) return(false);                    // if that fails, we're done

    //cached properties
    CONDITION_VARIABLE thread_win32_task_ready;
    CRITICAL_SECTION   thread_win32_data_lock;

    //loop through the contexts and create each thread
    for (
        IFBU32 thread_index = 0;
               thread_index < thread_count;
             ++thread_index) {

        //get the current thread context and description
        const IFBThreadPlatformContext* current_thread_context            = &thread_context[thread_index];
        const IFBU32                    current_thread_description_offset = thread_description_stride * thread_index;
        const IFBChar*                  current_thread_description        = &thread_description[current_thread_description_offset];

        //initialize lock and condition
        InitializeCriticalSection   (&thread_win32_data_lock);
        InitializeConditionVariable (&thread_win32_task_ready);

        //thread win32 properties
        LPSECURITY_ATTRIBUTES  thread_win32_security_attributes = NULL; 
        const DWORD            thread_win32_stack_size          = IFB_WIN32_THREAD_STACK_SIZE;
        LPTHREAD_START_ROUTINE thread_win32_routine             = ifb_win32::thread_routine;
        LPVOID                 thread_win32_data                = (LPVOID)&current_thread_context;
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

        //check that we have a valid thread handle
        result &= (thread_win32_handle != NULL);
        if (!result) break;

        //update the thread win32 context
        IFBWin32ThreadContext* thread_win32_context = ifb_win32::thread_get_context_win32(current_thread_context);
        ifb_macro_assert(thread_win32_context);
        thread_win32_context->handle     = thread_win32_handle;
        thread_win32_context->task_ready = thread_win32_task_ready;
        thread_win32_context->data_lock  = thread_win32_data_lock;
        thread_win32_context->id         = thread_win32_id;
        thread_win32_context->flags      = thread_win32_flags;

        //update the thread id
        thread_id[thread_index] = thread_win32_id;

        //set the thread description
        //TODO: this is a wstring despite being in UTF-8 mode
        // SetThreadDescription(thread_win32_handle,current_thread_description);


    }

    //we're done
    return(result);
}

ifb_internal const IFBB8
ifb_win32::thread_destroy(
    const IFBThreadPlatformContext* thread_context,
    const IFBU32                    thread_count) {

    if (!thread_context) return(false);

    ifb_macro_panic();

    return(false);
}

ifb_internal const IFBB8
ifb_win32::thread_assign_cores(
    const IFBThreadPlatformContext* thread_context,
    const IFBU32                    thread_count,
    const IFBU64*                   thread_core_mask) {

    //sanity check
    IFBB8 result = true;                  // we can procceed IF...
    result &= (thread_context   != NULL); //...we have a context           AND
    result &= (thread_count     != 0);    //...we have at least one thread AND
    result &= (thread_core_mask != NULL); //...we have a core mask
    if (!result) return(false);           // if that failed, we're done

    //loop through the contexts and assign the cores 
    for (
        IFBU32 thread_index = 0;
               thread_index < thread_count;
             ++thread_index) {

        //get the current thread context and core mask
        const IFBThreadPlatformContext* current_thread_context   = &thread_context   [thread_index];
        const IFBU64                    current_thread_core_mask =  thread_core_mask [thread_index]; 
    
        //if its zero, there's nothing to do here
        //just go to the next thread
        if (current_thread_core_mask != 0) continue;

        //get the win32 context, it should never be null
        IFBWin32ThreadContext* win32_thread_context = ifb_win32::thread_get_context_win32(current_thread_context);
        ifb_macro_assert(win32_thread_context);

        //set the core mask
        const HANDLE    win32_thread_handle            = win32_thread_context->handle;
        const DWORD_PTR win32_thread_affinity_mask_new = (DWORD_PTR)current_thread_core_mask;
        const DWORD_PTR win32_thread_affinity_mask_old = SetThreadAffinityMask(win32_thread_handle,win32_thread_affinity_mask_new);

        //if that returns a null mask, it failed
        if (!win32_thread_affinity_mask_old) return(false);
    }

    //we're done
    return(true);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

ifb_internal DWORD WINAPI
ifb_win32::thread_routine(
    LPVOID data) {
    
    //debug string
    IFBChar debug_out[IFB_WIN32_THREAD_DEBUG_OUT_LENGTH];

    //get the thread contexts
    //they should never be null
    IFBThreadPlatformContext* thread_context_platform = ifb_win32::thread_get_context_platform (data);
    IFBWin32ThreadContext*    thread_context_win32    = ifb_win32::thread_get_context_win32    (thread_context_platform);
    ifb_macro_assert(thread_context_platform);
    ifb_macro_assert(thread_context_win32);

    //cache thread properties
    const IFBU32 thread_id   = thread_context_win32->id; 
    const IFBU32 thread_core = GetCurrentProcessorNumber(); 

    //intialize debug info
    IFBWin32ThreadDebugInfo debug_info;
    debug_info.thread_id                  = thread_id;
    debug_info.thread_core_number         = thread_core;
    debug_info.thread_debug_buffer_length = IFB_WIN32_THREAD_DEBUG_OUT_LENGTH;
    debug_info.thread_debug_buffer_ptr    = debug_out;

    ifb_win32::thread_debug_out(debug_info,"STARTUP");

    //run the routine
    IFBB8 run_routine = true;
    while(run_routine) {

        ifb_win32::thread_debug_out(debug_info,"ROUTINE START");
        
        //task condition and data lock
        PCONDITION_VARIABLE routiune_task_ready = &thread_context_win32->task_ready;
        LPCRITICAL_SECTION  routiune_data_lock  = &thread_context_win32->data_lock; 

        //lock the task data
        EnterCriticalSection(routiune_data_lock);
        ifb_win32::thread_debug_out(debug_info,"TASK DATA LOCKED");

        //wait unil the task is ready
        SleepConditionVariableCS(
            routiune_task_ready,
            routiune_data_lock,
            INFINITE);
        
        //task function and data
        IFBPtr                routine_task_data     = thread_context_platform->task_data_pointer;
        IFBThreadTaskFunction routine_task_function = thread_context_platform->task_func_pointer;

        //double check that we have data and a function
        run_routine &= (routine_task_data     != NULL);
        run_routine &= (routine_task_function != NULL);

        //execute the task
        ifb_win32::thread_debug_out(debug_info,"TASK START");
        run_routine &= run_routine && routine_task_function(routine_task_data);
        ifb_win32::thread_debug_out(debug_info,"TASK END");

        //unlock the task data
        LeaveCriticalSection(routiune_data_lock);
        ifb_win32::thread_debug_out(debug_info,"TASK DATA UNLOCKED");

        ifb_win32::thread_debug_out(debug_info,"ROUTINE END");
    }

    ifb_win32::thread_debug_out(debug_info,"SHUTDOWN");

    //we're done
    return(S_OK);
}

inline IFBWin32ThreadContext* 
ifb_win32::thread_get_context_win32(
    const IFBThreadPlatformContext* thread_platform_context) {

    //sanity check, these should never fail
    ifb_macro_assert(thread_platform_context);
    ifb_macro_assert(thread_platform_context->platform_data_pointer != NULL);
    ifb_macro_assert(thread_platform_context->platform_data_size    >= IFB_WIN32_THREAD_CONTEXT_SIZE);

    //get thread info
    IFBWin32ThreadContext* ptr_win32_thread_info = (IFBWin32ThreadContext*)thread_platform_context->platform_data_pointer;   

    //we're done
    return(ptr_win32_thread_info);
}

inline IFBThreadPlatformContext*
ifb_win32::thread_get_context_platform(
    LPVOID data) {

    ifb_macro_assert(data);
    IFBThreadPlatformContext* thread_platform_context = (IFBThreadPlatformContext*)data;
    
    return(thread_platform_context);
}


inline IFBVoid
ifb_win32::thread_debug_out(
    const IFBWin32ThreadDebugInfo& thread_debug_info_ref,
    const IFBChar*                 thread_debug_message_ptr) {

    //format the debug string
    (VOID)sprintf_s(
        thread_debug_info_ref.thread_debug_buffer_ptr,
        thread_debug_info_ref.thread_debug_buffer_length,
        "[THREAD-%d-CORE-%d]: %s",
        thread_debug_info_ref.thread_id,
        thread_debug_info_ref.thread_core_number,
        thread_debug_message_ptr);

    //print the message
    ifb_win32::system_debug_out(thread_debug_info_ref.thread_debug_buffer_ptr);
}