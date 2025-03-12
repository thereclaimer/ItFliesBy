#pragma once

#include "ifb-engine-internal-core.hpp"

inline const IFBB8 
ifb_engine::core_threads_create_pool(
          IFBEngineCore* core_ptr,
    const IFBU32         thread_context_size) {

    IFBB8 result = true;

    //sanity check
    ifb_macro_assert(core_ptr);
    ifb_macro_assert(thread_context_size);

    //make sure we got our core information
    //for now, we will enforce at least one CPU core
    const IFBU32 core_count = core_ptr->system_info.cpu.core_count_logical;
    ifb_macro_assert(core_count > 1);

    //the primary core will serve as the core engine thread
    //the thread pool will be created for every other core 
    //on the system
    const IFBU32 thread_count       = core_count - 1;
    const IFBU32 parent_core_number = core_ptr->system_info.cpu.parent_core_number;     

    //calculate allocation sizes
    const IFBU32 size_thread           = sizeof(IFBThread);
    const IFBU32 size_thread_array     = size_thread         * thread_count;
    const IFBU32 size_platform_context = thread_context_size * thread_count;

    //allocate memory
    IFBThread*   thread_array_ptr   = (IFBThread*)ifb_engine::core_memory_commit_bytes_absolute(core_ptr,size_thread_array);
    const IFBPtr thread_context_ptr =             ifb_engine::core_memory_commit_bytes_absolute(core_ptr,size_platform_context); 

    //create the platform threads, 
    //excluding the primary CPU core
    IFBU32        thread_index         = 0;
    const IFBAddr thread_context_start = (IFBAddr)thread_context_ptr;
    for (
        IFBU32 core_id = 0;
               core_id < core_count;
             ++core_id) {

        //skip the primary core
        if (core_id == parent_core_number) continue;

        //calculate the context
        const IFBU32  thread_context_offset = thread_context_size  * thread_index; 
        const IFBAddr thread_context        = thread_context_start + thread_context_offset;

        //get the current thread
        IFBThread* thread_ptr = &thread_array_ptr[thread_index];

        //set the thread properties
        thread_ptr->platform_context_pointer = (IFBPtr)thread_context;
        thread_ptr->platform_context_size    = thread_context_size;
        thread_ptr->logical_core_id_parent   = parent_core_number;
        thread_ptr->logical_core_id_current  = core_id;
        thread_ptr->task_data                = NULL;
        thread_ptr->task_function            = NULL;

        //update the thread index
        ++thread_index;
    }

    //create the threads
    result &= ifb_platform::thread_create(
        thread_array_ptr,
        thread_count);

    //update the thread pool
    IFBEngineCoreThreadPool& thread_pool_ref = core_ptr->thread_pool;
    thread_pool_ref.thread_array          = thread_array_ptr;
    thread_pool_ref.thread_array_count    = thread_count;
    thread_pool_ref.platform_context_size = thread_context_size;

    //we're done
    return(result);
}
