#ifndef IFB_THREADS_HPP
#define IFB_THREADS_HPP

#include <ifb.hpp>

namespace ifb_thread {

    const IFBU32 memory_size_pool_args (IFBVoid);
    const IFBU32 memory_size_platform  (const IFBU32 thread_count);
    const IFBU32 memory_size_pool      (const IFBU32 thread_count, const IFBU32 thread_data_stride);

};

struct IFBThreadPoolArgs {
    IFBMemoryBlock         thread_pool_memory;
    IFBU32                 thread_count;
    IFBU32                 thread_task_data_stride;    
};

namespace ifb_thread {
    
    const IFBHNDThreadPool pool_create  (const IFBThreadPoolArgs* args);
    const IFBB8            pool_destroy (const IFBThreadPool*     thread_pool);
}

#endif //IFB_THREADS_HPP