#pragma once

#include "ifb-threads.hpp"

#define IFB_THREAD_POOL_INIT_MAX_SIZE 0xFFFF

namespace ifb_thread {

    IFBVoid pool_init_step_0_validate_args  (IFBThreadPoolInit* init, IFBB8& result_ref);
    IFBVoid pool_init_step_1_set_size_cache (IFBThreadPoolInit* init, IFBB8& result_ref);
    IFBVoid pool_init_step_2_cast_memory    (IFBThreadPoolInit* init, IFBB8& result_ref);
    IFBVoid pool_init_step_3_set_header     (IFBThreadPoolInit* init, IFBB8& result_ref);
    IFBVoid pool_init_step_4_set_handles    (IFBThreadPoolInit* init, IFBB8& result_ref);
    IFBVoid pool_init_step_5_validate_pool  (IFBThreadPoolInit* init, IFBB8& result_ref);
};

inline IFBVoid 
ifb_thread::pool_init_step_0_validate_args(
    IFBThreadPoolInit* init,
    IFBB8&             result_ref) {

    //check init struct
    result_ref = (init != NULL);
    if (!result_ref) return;

    //check pointers
    result_ref &= (init->args        != NULL);
    result_ref &= (init->sizes_cache != NULL);
    result_ref &= (init->pointer     != NULL);    
    if (!result_ref) return;

    //check remaining args
    const IFBThreadPoolArgs* args = init->args;
    result_ref &= (args->thread_pool_memory.start  != 0);
    result_ref &= (args->thread_pool_memory.size   != 0);
    result_ref &= (args->thread_count              != 0);
    result_ref &= (args->stride_task_data          != 0);
    result_ref &= (args->stride_thread_description != 0);    
}

inline IFBVoid
ifb_thread::pool_init_step_1_set_size_cache(
    IFBThreadPoolInit* init,
    IFBB8&             result_ref) {

    if (!result_ref) return;

    //store arg constants
    IFBThreadPoolArgs* args                           = init->args;
    const IFBU32       arg_thread_count               = args->thread_count;
    const IFBU32       arg_thread_stride_description  = args->stride_thread_description;
    const IFBU32       arg_thread_stride_task_data    = args->stride_task_data;

    //get the cache
    IFBThreadPoolSizesCache* sizes_cache = init->sizes_cache;

    //temporary values
    const IFBU32 tmp_size_max               = IFB_THREAD_POOL_INIT_MAX_SIZE;
    const IFBU32 tmp_size_thread_handle     = sizeof(IFBHNDThread);
    const IFBU32 tmp_size_task_function     = sizeof(IFBThreadTaskCallback);;
    const IFBU32 tmp_size_affinity_mask     = sizeof(IFBThreadAffinityMask);;
    const IFBU32 tmp_size_platform_instance = ifb_platform::thread_size();;

    //thread pool properties
    const IFBU32 pool_size_struct                     = ifb_macro_align_size_struct(IFBThreadPool); 
    const IFBU32 pool_size_platform_total             = arg_thread_count * tmp_size_platform_instance;
    const IFBU32 pool_size_description_buffer         = arg_thread_count * arg_thread_stride_description;
    const IFBU32 pool_size_task_data                  = arg_thread_count * arg_thread_stride_task_data;
    const IFBU32 pool_size_task_functions           = arg_thread_count * tmp_size_task_function;
    const IFBU32 pool_size_array_affinity_mask        = arg_thread_count * tmp_size_affinity_mask;
    const IFBU32 pool_size_array_list_running_threads = ifb_array_list::memory_allocation_size(tmp_size_thread_handle,arg_thread_count);

    //thread pool total size
    const IFBU32 pool_size_total = 
        pool_size_struct              +
        pool_size_platform_total      +
        pool_size_description_buffer  +
        pool_size_task_data           +
        pool_size_task_functions      +
        pool_size_array_affinity_mask +
        pool_size_array_list_running_threads;

    //make sure we fit within max allocation size
    result_ref &= (pool_size_total < tmp_size_max);
    
    //non-essential cache properties
    sizes_cache->other.max                         = tmp_size_max;
    sizes_cache->other.thread_handle               = tmp_size_thread_handle;
    sizes_cache->other.task_function               = tmp_size_task_function;
    sizes_cache->other.affinity_mask               = tmp_size_affinity_mask;
    sizes_cache->other.platform_instance           = tmp_size_platform_instance;

    //memory size properties
    sizes_cache->memory.total                      = *((IFBU16*)&pool_size_total);
    sizes_cache->memory.pool_struct_size           = *((IFBU16*)&pool_size_struct);
    sizes_cache->memory.platform_total             = *((IFBU16*)&pool_size_platform_total);
    sizes_cache->memory.description_buffer         = *((IFBU16*)&pool_size_description_buffer);
    sizes_cache->memory.task_data                  = *((IFBU16*)&pool_size_task_data);
    sizes_cache->memory.thread_functions           = *((IFBU16*)&pool_size_task_functions);
    sizes_cache->memory.array_list_running_threads = *((IFBU16*)&pool_size_array_list_running_threads);
    sizes_cache->memory.array_affinity_mask        = *((IFBU16*)&pool_size_array_affinity_mask);
}

inline IFBVoid
ifb_thread::pool_init_step_2_cast_memory(
    IFBThreadPoolInit* init,
    IFBB8&             result_ref) {

    if (!result_ref) return;

    //get the memory args
    IFBThreadPoolArgs* args = init->args;
    const IFBAddr args_mem_start = args->thread_pool_memory.start;
    const IFBU64  args_mem_size  = args->thread_pool_memory.size;

    //make sure its what we expect
    result_ref &= args_mem_start != NULL;
    result_ref &= args_mem_size  >= init->sizes_cache->memory.total;
    if (!result_ref) return;

    //cast the memory
    init->pointer = (IFBThreadPool*)args_mem_start;
}

inline IFBVoid
ifb_thread::pool_init_step_3_set_header(
    IFBThreadPoolInit* init,
    IFBB8&             result_ref) {

    if (!result_ref) return;

    //get the pointers
    IFBThreadPoolArgs*       args  = init->args;
    IFBThreadPool*           pool  = init->pointer;
    IFBThreadPoolSizesCache* sizes = init->sizes_cache;

    //initialize the header
    IFBThreadPoolHeader& header_ref   = pool->header;
    header_ref.memory.start           = args->thread_pool_memory.start;
    header_ref.memory.size            = args->thread_pool_memory.size;
    header_ref.thread_count           = args->thread_count;
    header_ref.stride_description     = args->stride_thread_description;
    header_ref.stride_memory_platform = sizes->other.platform_instance;
    header_ref.stride_memory_task     = args->stride_task_data;
}

inline IFBVoid 
ifb_thread::pool_init_step_4_set_handles(
    IFBThreadPoolInit* init,
    IFBB8&             result_ref) {
        
    if (!result_ref) return;

    //get the pointers
    IFBThreadPoolArgs*       args  = init->args;
    IFBThreadPoolSizesCache* sizes = init->sizes_cache;
    IFBThreadPool*           pool  = init->pointer;

    //calculate offsets
    const IFBU16 offset_description_buffer         = sizes->memory.pool_struct_size;
    const IFBU16 offset_memory_platform            = sizes->memory.platform_total             + offset_description_buffer;
    const IFBU16 offset_memory_task                = sizes->memory.description_buffer         + offset_memory_platform;
    const IFBU16 offset_array_task_functions       = sizes->memory.task_data                  + offset_memory_task;
    const IFBU16 offset_array_list_running_threads = sizes->memory.thread_functions           + offset_array_task_functions;
    const IFBU16 offset_array_affinity_mask        = sizes->memory.array_list_running_threads + offset_array_list_running_threads;

    //set handles
    IFBThreadPoolHandles& handles = pool->handles;
    handles.description_buffer.offset         = offset_description_buffer;
    handles.memory_platform.offset            = offset_memory_platform;
    handles.memory_task.offset                = offset_memory_task;
    handles.array_task_functions.offset       = offset_array_task_functions;
    handles.array_list_running_threads.offset = offset_array_list_running_threads;
    handles.array_affinity_mask.offset        = offset_array_affinity_mask;
}

inline IFBVoid 
ifb_thread::pool_init_step_5_validate_pool(
    IFBThreadPoolInit* init,
    IFBB8&             result_ref) {

    if (!result_ref) return;

    //get the pointers
    IFBThreadPoolArgs*       args  = init->args;
    IFBThreadPoolSizesCache* sizes = init->sizes_cache;
    IFBThreadPool*           pool  = init->pointer;

    //validate header
    result_ref &= (pool->header.memory.start           == args->thread_pool_memory.start);
    result_ref &= (pool->header.memory.size            == sizes->memory.total);
    result_ref &= (pool->header.thread_count           == args->thread_count);
    result_ref &= (pool->header.stride_description     == args->stride_thread_description);
    result_ref &= (pool->header.stride_memory_platform == sizes->other.platform_instance);
    result_ref &= (pool->header.stride_memory_task     == sizes->other.task_function); 

    //validate handles
    result_ref &= (pool->handles.description_buffer.offset         != 0);
    result_ref &= (pool->handles.memory_platform.offset            != 0);
    result_ref &= (pool->handles.memory_task.offset                != 0);
    result_ref &= (pool->handles.array_task_functions.offset       != 0);
    result_ref &= (pool->handles.array_list_running_threads.offset != 0);
    result_ref &= (pool->handles.array_affinity_mask.offset        != 0);
}
