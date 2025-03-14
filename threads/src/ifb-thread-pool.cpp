#pragma once

#include "ifb-threads.hpp"

namespace ifb_thread_pool {

    IFBThreadPlatformContext* stack_push_context(IFBThreadPool* thread_pool, const IFBU32 count);
    IFBU64*                   stack_push_id     (IFBThreadPool* thread_pool, const IFBU32 count);
    IFBVoid                   stack_reset       (IFBThreadPool* thread_pool);
};

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

const IFBB8
ifb_thread_pool::validate(
    IFBThreadPool*  thread_pool) {

    if (!thread_pool) return(false);

    IFBB8 result = true; 
    result &= (thread_pool->pointers.array_context      != NULL);
    result &= (thread_pool->pointers.array_id           != NULL);
    result &= (thread_pool->pointers.array_core_mask    != NULL);
    result &= (thread_pool->pointers.description_buffer != NULL);
    result &= (thread_pool->pointers.tmp_stack          != NULL);
    return(result);
}

IFBThreadPool*
ifb_thread_pool::load(
          IFBMemoryArena*  arena,
    const IFBHNDThreadPool thread_pool_handle) {

	ifb_macro_assert(arena);
	IFBThreadPool* thread_pool = (IFBThreadPool*)ifb_memory::arena_get_pointer(arena,thread_pool_handle.offset);    
	return(thread_pool);
}

IFBThreadPool*
ifb_thread_pool::commit_absolute(
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
    const IFBU32 size_stack_struct       = ifb_macro_align_size_struct(IFBStack);
    const IFBU32 size_stack_data         = size_array_context * 2;  //just for kicks, make sure we have enough room
    const IFBU32 size_platform_data      = thread_count * thread_platform_data_size;

    //total commit size    
    const IFBU32 size_total = (
        size_thread_pool        +
        size_array_context      +
        size_array_id           +
        size_array_core_mask    +
        size_description_buffer +
        size_platform_data      +
        size_stack_struct       +
        size_stack_data);

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
    IFBStack*                 ptr_stack_struct       = ifb_utilities_macro_pointer_advance_and_cast(pointer_offset, size_stack_struct,       IFBStack);
    IFBPtr                    ptr_stack_data         = ifb_utilities_macro_pointer_advance_and_cast(pointer_offset, size_stack_data,         IFBPtr);

    //initialize the thread arrays
    for (
	  IFBU32 thread_index = 0;
             thread_index < thread_count;
           ++thread_index) {

	  //set the array values
	  ptr_array_context  [thread_index].platform_data_pointer = NULL;
	  ptr_array_context  [thread_index].platform_data_size    = thread_platform_data_size;
	  ptr_array_context  [thread_index].task_data_pointer     = ifb_utilities::pointer_advance(pointer_offset,thread_platform_data_size);
	  ptr_array_context  [thread_index].task_func_pointer     = 0;
	  ptr_array_id       [thread_index]                       = 0;
	  ptr_array_core_mask[thread_index]                       = 0;
    }

    //initialize the stack
    ptr_stack_struct->data_start = (IFBAddr)ptr_stack_data;
    ptr_stack_struct->data_size  = size_stack_data;
    ptr_stack_struct->position   = 0;

    //update the pool    
    ptr_thread_pool->pointers.array_context      = ptr_array_context;
    ptr_thread_pool->pointers.array_id           = ptr_array_id;
    ptr_thread_pool->pointers.array_core_mask    = ptr_array_core_mask;
    ptr_thread_pool->pointers.description_buffer = ptr_description_buffer;
    ptr_thread_pool->pointers.tmp_stack          = ptr_stack_struct; 
    ptr_thread_pool->thread_count_total          = thread_count;
    ptr_thread_pool->thread_count_running        = 0;
    ptr_thread_pool->description_stride          = thread_description_stride;
    ptr_thread_pool->platform_data_size          = thread_platform_data_size;

    //we're done
    return(ptr_thread_pool);
}

const IFBHNDThreadPool
ifb_thread_pool::commit_relative(
	      IFBMemoryArena* arena,
    const IFBU32          thread_count,
    const IFBU32          thread_description_stride,
    const IFBU32          thread_platform_data_size) {

    //thread pool handle
    IFBHNDThreadPool thread_pool_handle;
    thread_pool_handle.offset = 0; 

    //sanity check
	ifb_macro_assert(arena);
    ifb_macro_assert(thread_count);
    ifb_macro_assert(thread_description_stride);

    //property sizes
    const IFBU32 size_thread_pool        = ifb_macro_align_size_struct(IFBThreadPool); 
    const IFBU32 size_array_context      = ifb_macro_array_size(IFBThreadPlatformContext, thread_count); 
    const IFBU32 size_array_id           = ifb_macro_array_size(IFBU64,                   thread_count); 
    const IFBU32 size_array_core_mask    = ifb_macro_array_size(IFBU64,                   thread_count); 
    const IFBU32 size_description_buffer = thread_count * thread_description_stride;
    const IFBU32 size_stack_struct       = ifb_macro_align_size_struct(IFBStack);
    const IFBU32 size_stack_data         = size_array_context * 2;  //just for kicks, make sure we have enough room
    const IFBU32 size_platform_data      = thread_count * thread_platform_data_size;

    //total commit size    
    const IFBU32 size_total = (
        size_thread_pool        +
        size_array_context      +
        size_array_id           +
        size_array_core_mask    +
        size_description_buffer +
        size_platform_data      +
        size_stack_struct       +
        size_stack_data);

    //commit memory
    const IFBU32 arena_offset = ifb_memory::arena_commit_bytes_relative(arena,size_total);
    IFBPtr ptr_commit = ifb_memory::arena_get_pointer(arena,arena_offset); 
    if (!ptr_commit) return(thread_pool_handle);

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
    IFBStack*                 ptr_stack_struct       = ifb_utilities_macro_pointer_advance_and_cast(pointer_offset, size_stack_struct,       IFBStack);
    IFBPtr                    ptr_stack_data         = ifb_utilities_macro_pointer_advance_and_cast(pointer_offset, size_stack_data,         IFBPtr);

    //initialize the thread arrays
    for (
	  IFBU32 thread_index = 0;
             thread_index < thread_count;
           ++thread_index) {

	  //set the array values
	  ptr_array_context  [thread_index].platform_data_pointer = NULL;
	  ptr_array_context  [thread_index].platform_data_size    = thread_platform_data_size;
	  ptr_array_context  [thread_index].task_data_pointer     = ifb_utilities::pointer_advance(pointer_offset,thread_platform_data_size);
	  ptr_array_context  [thread_index].task_func_pointer     = 0;
	  ptr_array_id       [thread_index]                       = 0;
	  ptr_array_core_mask[thread_index]                       = 0;
    }

    //initialize the stack
    ptr_stack_struct->data_start = (IFBAddr)ptr_stack_data;
    ptr_stack_struct->data_size  = size_stack_data;
    ptr_stack_struct->position   = 0;

    //update the pool    
    ptr_thread_pool->pointers.array_context      = ptr_array_context;
    ptr_thread_pool->pointers.array_id           = ptr_array_id;
    ptr_thread_pool->pointers.array_core_mask    = ptr_array_core_mask;
    ptr_thread_pool->pointers.description_buffer = ptr_description_buffer;
    ptr_thread_pool->pointers.tmp_stack          = ptr_stack_struct; 
    ptr_thread_pool->thread_count_total          = thread_count;
    ptr_thread_pool->thread_count_running        = 0;
    ptr_thread_pool->description_stride          = thread_description_stride;
    ptr_thread_pool->platform_data_size          = thread_platform_data_size;

    //we're done
    return(thread_pool_handle);
}

/**********************************************************************************/
/* RESERVE/RELEASE                                                                */
/**********************************************************************************/

const IFBB8
ifb_thread_pool::threads_reserve (
	      IFBThreadPool*  thread_pool,
    const IFBU32          thread_count,
    const IFBChar*        thread_descriptions,
    const IFBThreadTask*  thread_tasks, 
	      IFBHNDThread*   thread_handles) {

    IFBB8 result = true;

    //sanity check, make sure we have valid pointers
    ifb_macro_assert(thread_pool);
    ifb_macro_assert(thread_descriptions);
    ifb_macro_assert(thread_tasks);
    ifb_macro_assert(thread_handles);

    //validate the pool and the thread count
    result &= ifb_thread_pool::validate(thread_pool);
    result &= (thread_count <= thread_pool->thread_count_total);
    ifb_macro_assert(result);

    //push the contexts we need on the stack
    IFBThreadPlatformContext* thread_context_array = ifb_thread_pool::stack_push_context(
        thread_pool,
        thread_count);

    //update the context array
    const IFBU32 thread_count_total = thread_pool->thread_count_total;
    for (
        IFBU32 context_index = 0;
               context_index < thread_count;
             ++context_index) {

        //get the thread index
        const IFBU32 thread_index = thread_handles[context_index].offset;
        ifb_macro_assert(thread_index < thread_count_total);

        //get the current task
        const IFBThreadTask& new_task_ref = thread_tasks[context_index];

        //get the context from the thread pool
        const IFBThreadPlatformContext& current_context_ref = thread_pool->pointers.array_context[thread_index];

        //update the context array we just allocated
        thread_context_array[context_index].platform_data_pointer = current_context_ref.platform_data_pointer;
        thread_context_array[context_index].platform_data_size    = current_context_ref.platform_data_size;
        thread_context_array[context_index].task_data_pointer     = new_task_ref.data;
        thread_context_array[context_index].task_func_pointer     = new_task_ref.func;
    }

    //push thread ids
    IFBU64* thread_id_array = ifb_thread_pool::stack_push_id(thread_pool,thread_count);

    //create the threads
    const IFBU32 thread_description_stride = thread_pool->description_stride;
    result &= ifb_platform::thread_create(
        thread_context_array,
        thread_count,
        thread_descriptions,
        thread_description_stride,
        thread_id_array);

    //if that failed, reset the stack and return
    if (!result) {
        ifb_thread_pool::stack_reset(thread_pool);
        return(false);
    }

    //if that succeeded, copy the thread data back to the pool
    for (
        IFBU32 thread_handle_index = 0; 
               thread_handle_index < thread_count;
             ++thread_handle_index) {

        //get the new values
        const IFBU32                    new_thread_id          = thread_id_array      [thread_handle_index];
        const IFBThreadPlatformContext& new_thread_context_ref = thread_context_array [thread_handle_index];  

        //get the current thread index
        const IFBU32 thread_pool_index = thread_handles[thread_handle_index].offset;

        //update the thread pool at the index
        thread_pool->pointers.array_context[thread_pool_index].platform_data_pointer = new_thread_context_ref.platform_data_pointer; 
        thread_pool->pointers.array_context[thread_pool_index].platform_data_size    = new_thread_context_ref.platform_data_size; 
        thread_pool->pointers.array_context[thread_pool_index].task_data_pointer     = new_thread_context_ref.task_data_pointer; 
        thread_pool->pointers.array_context[thread_pool_index].task_func_pointer     = new_thread_context_ref.task_func_pointer; 
        thread_pool->pointers.array_id     [thread_pool_index]                       = new_thread_id;
    }

    //reset the stack
    ifb_thread_pool::stack_reset(thread_pool);

    return(true);
}

const IFBB8
ifb_thread_pool::threads_release (
	      IFBThreadPool* thread_pool,
    const IFBU32         thread_count,
    const IFBHNDThread*  thread_handles) {

    return(false);
}

/**********************************************************************************/
/* CONTROL                                                                        */
/**********************************************************************************/

const IFBB8
ifb_thread_pool::threads_start(
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
ifb_thread_pool::threads_stop(
	      IFBThreadPool* thread_pool,
    const IFBU32         thread_count,
    const IFBHNDThread*  thread_handles) {
    return(false);

}

const IFBB8
ifb_thread_pool::threads_sync(
	      IFBThreadPool* thread_pool,
    const IFBU32         thread_count,
    const IFBHNDThread*  thread_handles) {
    return(false);

}

/**********************************************************************************/
/* CORES                                                                          */
/**********************************************************************************/

const IFBB8
ifb_thread_pool::threads_set_cores(
	    IFBThreadPool* thread_pool,
    const IFBU32         thread_count,
    const IFBHNDThread*  thread_handles,
    const IFBU64*        thread_core_masks) {
    return(false);

}

const IFBB8
ifb_thread_pool::threads_get_cores(
	    IFBThreadPool* thread_pool,
    const IFBU32         thread_count,
    const IFBHNDThread*  thread_handles,
	    IFBU64*        thread_core_masks) {
    return(false);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline IFBThreadPlatformContext*
ifb_thread_pool::stack_push_context(
          IFBThreadPool* thread_pool,
    const IFBU32         context_count) {

    ifb_macro_assert(thread_pool);
    ifb_macro_assert(context_count);

    //calculate the push size
    const IFBU32 push_size = ifb_macro_array_size(IFBThreadPool, context_count);

    //do the push
    IFBThreadPlatformContext* contexts = (IFBThreadPlatformContext*)ifb_stack::push_absolute(
        thread_pool->pointers.tmp_stack,
        push_size);
    ifb_macro_assert(contexts);

    //we're done
    return(contexts);
}

inline IFBU64*
ifb_thread_pool::stack_push_id(
          IFBThreadPool* thread_pool,
    const IFBU32         count) {

    //sanity check
    ifb_macro_assert(thread_pool);
    ifb_macro_assert(count);

    //calculate the push size
    const IFBU32 push_size = ifb_macro_array_size(IFBU32, count);

    //do the push
    IFBU64* thread_ids = (IFBU64*)ifb_stack::push_absolute(
        thread_pool->pointers.tmp_stack,
        push_size);
    ifb_macro_assert(thread_ids);

    //we're done
    return(thread_ids);
}

inline IFBVoid
ifb_thread_pool::stack_reset(
    IFBThreadPool* thread_pool) {

    ifb_macro_assert(thread_pool);
    const IFBB8 result = ifb_stack::reset(thread_pool->pointers.tmp_stack);
    ifb_macro_assert(result);
}

