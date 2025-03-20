#ifndef IFB_THREADS_HPP
#define IFB_THREADS_HPP

#include <ifb.hpp>

namespace ifb_thread {

    const IFBU32 memory_size_pool_init        (IFBVoid);
    const IFBU32 memory_size_pool_args        (IFBVoid);
    const IFBU32 memory_size_pool_sizes_cache (IFBVoid);
};

namespace ifb_thread {
    
    const IFBB8 pool_create  (IFBThreadPoolInit*   init);
    const IFBB8 pool_destroy (const IFBThreadPool* thread_pool);
}

#endif //IFB_THREADS_HPP