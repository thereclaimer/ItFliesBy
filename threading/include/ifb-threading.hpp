#ifndef IFB_THREADING_HPP
#define IFB_THREADING_HPP

#include <ifb.hpp>
#include <ifb-memory.hpp>

/**********************************************************************************/
/* THREAD POOL                                                                    */
/**********************************************************************************/

namespace ifb_thread {

    //memory
    IFBThreadPool*         pool_arena_load_pointer    (IFBMemoryArena* arena, const IFBHNDThreadPool thread_pool_handle);
    IFBThreadPool*         pool_arena_commit_absolute (IFBMemoryArena* arena, const IFBU32 thread_count, const IFBU32 thread_description_stride);
    const IFBHNDThreadPool pool_arena_commit_relative (IFBMemoryArena* arena, const IFBU32 thread_count, const IFBU32 thread_description_stride);

    //reserve/release
    const IFBB8            pool_threads_reserve       (IFBThreadPool* thread_pool, const IFBU32 thread_count, const IFBChar*      thread_descriptions, const IFBThreadTask* thread_tasks IFBHNDThread* thread_handles);
    const IFBB8            pool_threads_release       (IFBThreadPool* thread_pool, const IFBU32 thread_count, const IFBHNDThread* thread_handles);
    
    //control
    const IFBB8            pool_threads_start         (IFBThreadPool* thread_pool, const IFBU32 thread_count, const IFBHNDThread* thread_handles);
    const IFBB8            pool_threads_stop          (IFBThreadPool* thread_pool, const IFBU32 thread_count, const IFBHNDThread* thread_handles);
    const IFBB8            pool_threads_sync          (IFBThreadPool* thread_pool, const IFBU32 thread_count, const IFBHNDThread* thread_handles);
    
    //cores    
    const IFBB8            pool_threads_set_cores     (IFBThreadPool* thread_pool, const IFBU32 thread_count, const IFBHNDThread* thread_handles, const IFBU64* thread_core_masks);
    const IFBB8            pool_threads_get_cores     (IFBThreadPool* thread_pool, const IFBU32 thread_count, const IFBHNDThread* thread_handles,       IFBU64* thread_core_masks);
};


#endif //IFB_THREADING_HPP