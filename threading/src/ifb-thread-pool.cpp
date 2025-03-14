#include "ifb-threading.hpp"

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

IFBThreadPool*
ifb_thread::pool_load_pointer(
          IFBMemoryArena*  arena,
    const IFBHNDThreadPool thread_pool_handle) {

	ifb_macro_assert(arena);
	IFBThreadPool* thread_pool = (IFBThreadPool*)ifb_memory::arena_get_pointer(arena,thread_pool_handle.offset);    
	return(thread_pool);
}

IFBThreadPool*
ifb_thread::pool_commit_absolute(
	      IFBMemoryArena* arena,
	const IFBU32          thread_count,
	const IFBU32          thread_description_stride,
	const IFBU32          thread_platform_data_size) {

    //sanity check
	ifb_macro_assert(arena);
    ifb_macro_assert(thread_count);
    ifb_macro_assert(thread_description_stride);
    ifb_macro_assert(thread_platform_data_size);

    //property sizes
    const IFBU32 size_thread_pool        = ifb_macro_align_size_struct(IFBThreadPool); 
    const IFBU32 size_array_context      = ifb_macro_array_size(IFBThreadPlatformContext, thread_count); 
    const IFBU32 size_array_id           = ifb_macro_array_size(IFBU64,                   thread_count); 
    const IFBU32 size_array_core_mask    = ifb_macro_array_size(IFBU64,                   thread_count); 
    const IFBU32 size_description_buffer = thread_count * thread_description_stride;
    const IFBU32 size_platform_data      = thread_count * thread_platform_data_size;

    //total commit size    
    const IFBU32 size_total = (
        size_thread_pool        +
        size_array_context      +
        size_array_id           +
        size_array_core_mask    +
        size_description_buffer +
        size_platform_data);

    //commit memory    
    IFBPtr ptr_commit = ifb_memory::arena_commit_bytes_absolute(arena,size_total); 
    if (!ptr_commit) return(NULL);

    //pointer offset
    IFBPointerOffset pointer_offset;
    pointer_offset.address = (IFBAddr)ptr_commit;
    pointer_offset.offset  = 0;

    //set pointers
    IFBU32 offset = 0;
    IFBThreadPool*            ptr_thread_pool        = ifb_utilities_macro_pointer_advance_and_cast(pointer_offset, size_thread_pool,        IFBThreadPool);
    IFBThreadPlatformContext* ptr_array_context      = ifb_utilities_macro_pointer_advance_and_cast(pointer_offset, size_array_context,      IFBThreadPlatformContext);
    IFBU64*                   ptr_array_id           = ifb_utilities_macro_pointer_advance_and_cast(pointer_offset, size_array_id,           IFBU64);
    IFBU64*                   ptr_array_core_mask    = ifb_utilities_macro_pointer_advance_and_cast(pointer_offset, size_array_core_mask,    IFBU64);
    IFBChar*                  ptr_description_buffer = ifb_utilities_macro_pointer_advance_and_cast(pointer_offset, size_description_buffer, IFBChar);

    //initialize the thread arrays
    for (
	  IFBU32 thread_index = 0;
             thread_index < thread_count;
           ++thread_index) {

	  //set the array values
	  ptr_array_context  [thread_index].platform_data_pointer = NULL 
	  ptr_array_context  [thread_index].platform_data_size    = thread_platform_data_size;
	  ptr_array_context  [thread_index].task_data_pointer     = ifb_utilities::pointer_advance(pointer_offset,thread_platform_data_size);
	  ptr_array_context  [thread_index].task_func_pointer     = 0
	  ptr_array_id       [thread_index]                       = 0;
	  ptr_array_core_mask[thread_index]                       = 0;
    }

    //update the pool    
    ptr_thread_pool->pointers.array_context      = ptr_array_context;
    ptr_thread_pool->pointers.array_id           = ptr_array_id;
    ptr_thread_pool->pointers.array_core_mask    = ptr_array_core_mask;
    ptr_thread_pool->pointers.description_buffer = ptr_description_buffer;
    ptr_thread_pool->thread_count_total          = thread_count;
    ptr_thread_pool->thread_count_running        = 0;
    ptr_thread_pool->description_stride          = thread_description_stride;

    //we're done
    return(ptr_thread_pool);
}

const IFBHNDThreadPool
ifb_thread::pool_commit_relative(
	      IFBMemoryArena* arena,
    const IFBU32          thread_count,
    const IFBU32          thread_description_stride) {

    //sanity check
	ifb_macro_assert(arena);
    ifb_macro_assert(thread_count);
    ifb_macro_assert(thread_description_stride);
    ifb_macro_assert(thread_platform_data_size);

    //property sizes
    const IFBU32 size_thread_pool        = ifb_macro_align_size_struct(IFBThreadPool); 
    const IFBU32 size_array_context      = ifb_macro_array_size(IFBThreadPlatformContext, thread_count); 
    const IFBU32 size_array_id           = ifb_macro_array_size(IFBU64,                   thread_count); 
    const IFBU32 size_array_core_mask    = ifb_macro_array_size(IFBU64,                   thread_count); 
    const IFBU32 size_description_buffer = thread_count * thread_description_stride;
    const IFBU32 size_platform_data      = thread_count * thread_platform_data_size;

    //total commit size    
    const IFBU32 size_total = (
        size_thread_pool        +
        size_array_context      +
        size_array_id           +
        size_array_core_mask    +
        size_description_buffer +
        size_platform_data);

    //commit memory
    const IFBHNDThreadPool thread_pool_handle = ifb_memory::arena_commit_bytes_relative(arena,size_total);
    IFBPtr ptr_commit = ifb_memory::arena_get_pointer(arena,thread_pool_handle.offset); 
    if (!ptr_commit) return(NULL);

    //pointer offset
    IFBPointerOffset pointer_offset;
    pointer_offset.address = (IFBAddr)ptr_commit;
    pointer_offset.offset  = 0;

    //set pointers
    IFBU32 offset = 0;
    IFBThreadPool*            ptr_thread_pool        = ifb_utilities_macro_pointer_advance_and_cast(pointer_offset, size_thread_pool,        IFBThreadPool);
    IFBThreadPlatformContext* ptr_array_context      = ifb_utilities_macro_pointer_advance_and_cast(pointer_offset, size_array_context,      IFBThreadPlatformContext);
    IFBU64*                   ptr_array_id           = ifb_utilities_macro_pointer_advance_and_cast(pointer_offset, size_array_id,           IFBU64);
    IFBU64*                   ptr_array_core_mask    = ifb_utilities_macro_pointer_advance_and_cast(pointer_offset, size_array_core_mask,    IFBU64);
    IFBChar*                  ptr_description_buffer = ifb_utilities_macro_pointer_advance_and_cast(pointer_offset, size_description_buffer, IFBChar);

    //initialize the thread arrays
    for (
	  IFBU32 thread_index = 0;
             thread_index < thread_count;
           ++thread_index) {

	  //set the array values
	  ptr_array_context  [thread_index].platform_data_pointer = NULL;
	  ptr_array_context  [thread_index].platform_data_size    = thread_platform_data_size;
	  ptr_array_context  [thread_index].task_data_pointer     = ifb_utilities::pointer_advance(pointer_offset,thread_platform_data_size);
	  ptr_array_context  [thread_index].task_func_pointer     = 0
	  ptr_array_id       [thread_index]                       = 0;
	  ptr_array_core_mask[thread_index]                       = 0;
    }

    //update the pool    
    ptr_thread_pool->pointers.array_context      = ptr_array_context;
    ptr_thread_pool->pointers.array_id           = ptr_array_id;
    ptr_thread_pool->pointers.array_core_mask    = ptr_array_core_mask;
    ptr_thread_pool->pointers.description_buffer = ptr_description_buffer;
    ptr_thread_pool->thread_count_total          = thread_count;
    ptr_thread_pool->thread_count_running        = 0;
    ptr_thread_pool->description_stride          = thread_description_stride;

    //we're done
    return(thread_pool_handle);
}

/**********************************************************************************/
/* RESERVE/RELEASE                                                                */
/**********************************************************************************/

const IFBB8
ifb_thread::pool_threads_reserve (
	      IFBThreadPool* thread_pool,
    const IFBU32         thread_count,
    const IFBChar*       thread_descriptions,
    const IFBThreadTask* thread_tasks, 
	      IFBHNDThread*  thread_handles) {

    //sanity check, make sure we have valid pointers
    ifb_macro_assert(thread_pool);
    ifb_macro_assert(thread_descriptions);
    ifb_macro_assert(thread_tasks);
    ifb_macro_assert(thread_handles);

    //sanity check, make sure the count is valid
    return(false);
}

const IFBB8
ifb_thread::pool_threads_release (
	      IFBThreadPool* thread_pool,
    const IFBU32         thread_count,
    const IFBHNDThread*  thread_handles) {

    return(false);
}

/**********************************************************************************/
/* CONTROL                                                                        */
/**********************************************************************************/

const IFBB8
ifb_thread::pool_threads_start(
	      IFBThreadPool* thread_pool,
    const IFBU32         thread_count,
    const IFBHNDThread*  thread_handles) {

    //sanity check
    ifb_macro_assert(thread_pool);
    ifb_macro_assert(thread_count);
    ifb_macro_assert(thread_handles);

    return(false);

}

const IFBB8
ifb_thread::pool_threads_stop(
	      IFBThreadPool* thread_pool,
    const IFBU32         thread_count,
    const IFBHNDThread*  thread_handles) {
    return(false);

}

const IFBB8
ifb_thread::pool_threads_sync(
	      IFBThreadPool* thread_pool,
    const IFBU32         thread_count,
    const IFBHNDThread*  thread_handles) {
    return(false);

}

/**********************************************************************************/
/* CORES                                                                          */
/**********************************************************************************/

const IFBB8
ifb_thread::pool_threads_set_cores(
	    IFBThreadPool* thread_pool,
    const IFBU32         thread_count,
    const IFBHNDThread*  thread_handles,
    const IFBU64*        thread_core_masks) {
    return(false);

}

const IFBB8
ifb_thread::pool_threads_get_cores(
	    IFBThreadPool* thread_pool,
    const IFBU32         thread_count,
    const IFBHNDThread*  thread_handles,
	    IFBU64*        thread_core_masks) {
    return(false);

}