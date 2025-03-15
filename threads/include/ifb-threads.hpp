#ifndef IFB_THREADING_HPP
#define IFB_THREADING_HPP

#include <ifb.hpp>
#include <ifb-memory.hpp>

/**********************************************************************************/
/* THREAD POOL                                                                    */
/**********************************************************************************/

namespace ifb_thread_pool {

    const IFBHNDThreadPool
    arena_commit(
              IFBMemoryArena* arena,
        const IFBU32          thread_count,
        const IFBU32          thread_description_stride,
        const IFBU32          thread_platform_data_size);

    //reserve/release
    const IFBB8 threads_reserve   (IFBThreadPoolRequestContext* request_context, const IFBChar* thread_descriptions, const IFBThreadTask* thread_tasks);
    const IFBB8 threads_release   (IFBThreadPoolRequestContext* request_context);
    
    //control
    const IFBB8 threads_start     (IFBThreadPoolRequestContext* request_context);
    const IFBB8 threads_stop      (IFBThreadPoolRequestContext* request_context);
    const IFBB8 threads_sync      (IFBThreadPoolRequestContext* request_context);
    
    //cores    
    const IFBB8 threads_set_cores (IFBThreadPoolRequestContext* request_context, const IFBU64* thread_core_masks);
    const IFBB8 threads_get_cores (IFBThreadPoolRequestContext* request_context,       IFBU64* thread_core_masks);
};


#endif //IFB_THREADING_HPP