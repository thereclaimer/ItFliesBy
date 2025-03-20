#pragma once

#include <ifb-data-structures.hpp>

#include "ifb-threads.hpp"


const IFBU32 
ifb_thread::memory_size_pool_args(
    IFBVoid) {

    const IFBU32 size = ifb_macro_align_size_struct(IFBThreadPoolArgs);

    return(size);
}

const IFBU32 
ifb_thread::memory_size_platform_thread(
    const IFBU32 thread_count) {

    const IFBU32 size_thread = ifb_platform::thread_size();
    const IFBU32 size_total  = size_thread * thread_count; 

    return(size_total);
}

const IFBU32 
ifb_thread::memory_size_pool(
    const IFBU32 thread_count,
    const IFBU32 stride_thread_data,
    const IFBU32 stride_thread_description) {

    //max allocation size
    //because our handles are U16
    const IFBU32 size_max = 0xFFFF;

    //temp stuff
    const IFBU32 size_thread_handle     = sizeof(IFBHNDThread); 
    const IFBU32 size_task_function     = sizeof(IFBThreadTaskCallback);
    const IFBU32 size_affinity_mask     = sizeof(IFBThreadAffinityMask);
    const IFBU32 size_platform_instance = ifb_platform::thread_size();
    
    //actual properties
    const IFBU32 pool_size_struct                     = ifb_macro_align_size_struct(IFBThreadPool); 
    const IFBU32 pool_size_platform_total             = thread_count * size_platform_instance;
    const IFBU32 pool_size_description_buffer         = thread_count * stride_thread_description;
    const IFBU32 pool_size_task_data                  = thread_count * stride_thread_data;
    const IFBU32 pool_size_thread_functions           = thread_count * size_task_function;
    const IFBU32 pool_size_array_list_running_threads = ifb_array_list::memory_allocation_size(size_thread_handle,thread_count);
    const IFBU32 pool_size_array_affinity_mask        = thread_count * size_affinity_mask;

    //total size
    const IFBU32 pool_size_total =
        pool_size_struct                     +
        pool_size_platform_total             +
        pool_size_description_buffer         +
        pool_size_task_data                  +
        pool_size_thread_functions           +
        pool_size_array_list_running_threads +
        pool_size_array_affinity_mask;

    //make sure we are within our expected size
    ifb_macro_assert(pool_size_total <= size_max);

    //we're done
    return(pool_size_total);
}