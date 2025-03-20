#pragma once

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

    const IFBU32 size_platform_instance  = ifb_platform::thread_size();
    const IFBU32 size_platform_total     = thread_count * size_platform_instance;
    const IFBU32 size_description_buffer = thread_count * stride_thread_description;
    const IFBU32 size_thread_data        = thread_count * stride_thread_data;

}