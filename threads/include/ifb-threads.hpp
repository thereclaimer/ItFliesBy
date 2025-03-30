#ifndef IFB_THREADS_HPP
#define IFB_THREADS_HPP

#include <ifb.hpp>
#include <ifb-memory.hpp>
#include <ifb-data-structures.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

//handles
struct IFBHNDThread     : IFBHND16 { };
struct IFBHNDThreadPool : IFBHND32 { };

//context
struct IFBThread;
struct IFBThreadStatus;
struct IFBThreadTask;
struct IFBThreadContext;

//thread pool
struct IFBThreadPool;
struct IFBThreadPoolHeader;
struct IFBThreadPoolHandles;
struct IFBThreadPoolArgs;
struct IFBThreadPoolInit;

//callback
typedef void (*IFBThreadTaskCallback) (IFBThread* thread_context);

//request
struct IFBThreadRequest;
struct IFBThreadRequestHeader;
struct IFBThreadRequestHandles;

/**********************************************************************************/
/* THREAD                                                                         */
/**********************************************************************************/

typedef ifb::u64 IFBThreadAffinityMask;

struct IFBThread {
    ifb::addr memory_start;
    ifb::u32  platform_memory_size;
    ifb::u16  pool_index;
    ifb::u16  memory_platform;
    ifb::u16  memory_task;
    ifb::u16  description;
    ifb::u16  task;
    ifb::u16  affinity_mask;
};

/**********************************************************************************/
/* THREAD POOL                                                                    */
/**********************************************************************************/

struct IFBThreadPoolSizesCache {
    struct {
        ifb::u32 max;
        ifb::u32 thread_handle;
        ifb::u32 task_function;
        ifb::u32 affinity_mask;
        ifb::u32 platform_instance;
    } other;
    struct {
        ifb::u16 total;
        ifb::u16 pool_struct_size;
        ifb::u16 platform_total;
        ifb::u16 description_buffer;
        ifb::u16 task_data;
        ifb::u16 thread_functions;
        ifb::u16 array_list_running_threads;
        ifb::u16 array_affinity_mask;  
    } memory;
    IFBArrayListArgs array_list_args;
};

struct IFBThreadPoolArgs {
    IFBMemory thread_pool_memory;
    ifb::u64    thread_count;
    ifb::u32    stride_task_data;
    ifb::u32    stride_thread_description; 
};

struct IFBThreadPoolHeader {
    IFBMemory memory;
    ifb::u32    thread_count;
    ifb::u32    stride_description;
    ifb::u32    stride_memory_platform;
    ifb::u32    stride_memory_task;
};

struct IFBThreadPoolOffsets {
    ifb::u16 description_buffer;
    ifb::u16 memory_platform;
    ifb::u16 memory_task;
    ifb::u16 array_task_functions;
    ifb::u16 array_list_running_threads;
    ifb::u16 array_affinity_mask;
};

struct IFBThreadPool {
    IFBThreadPoolHeader  header;
    IFBThreadPoolOffsets offsets;
    ifb::byte              padding[4];
};

struct IFBThreadPoolInit {
    IFBThreadPoolArgs*       args;
    IFBThreadPoolSizesCache* sizes_cache;
    IFBThreadPool*           pointer;
};

/**********************************************************************************/
/* THREAD REQUEST                                                                 */
/**********************************************************************************/

struct IFBThreadRequest {
    IFBMemory memory;
    ifb::u64    thread_count;
};

/**********************************************************************************/
/* AFFINITY MASK                                                                  */
/**********************************************************************************/

enum IFBThreadAffinityMask_ : ifb::u64 {
    IFBThreadAffinityMask_CPU_Core_00 = IFB_BIT_FLAG_0,
    IFBThreadAffinityMask_CPU_Core_01 = IFB_BIT_FLAG_1,
    IFBThreadAffinityMask_CPU_Core_02 = IFB_BIT_FLAG_2,
    IFBThreadAffinityMask_CPU_Core_03 = IFB_BIT_FLAG_3,
    IFBThreadAffinityMask_CPU_Core_04 = IFB_BIT_FLAG_4,
    IFBThreadAffinityMask_CPU_Core_05 = IFB_BIT_FLAG_5,
    IFBThreadAffinityMask_CPU_Core_06 = IFB_BIT_FLAG_6,
    IFBThreadAffinityMask_CPU_Core_07 = IFB_BIT_FLAG_7,
    IFBThreadAffinityMask_CPU_Core_08 = IFB_BIT_FLAG_8,
    IFBThreadAffinityMask_CPU_Core_09 = IFB_BIT_FLAG_9,
    IFBThreadAffinityMask_CPU_Core_10 = IFB_BIT_FLAG_10,
    IFBThreadAffinityMask_CPU_Core_11 = IFB_BIT_FLAG_11,
    IFBThreadAffinityMask_CPU_Core_12 = IFB_BIT_FLAG_12,
    IFBThreadAffinityMask_CPU_Core_13 = IFB_BIT_FLAG_13,
    IFBThreadAffinityMask_CPU_Core_14 = IFB_BIT_FLAG_14,
    IFBThreadAffinityMask_CPU_Core_15 = IFB_BIT_FLAG_15,
    IFBThreadAffinityMask_CPU_Core_16 = IFB_BIT_FLAG_16,
    IFBThreadAffinityMask_CPU_Core_17 = IFB_BIT_FLAG_17,
    IFBThreadAffinityMask_CPU_Core_18 = IFB_BIT_FLAG_18,
    IFBThreadAffinityMask_CPU_Core_19 = IFB_BIT_FLAG_19,
    IFBThreadAffinityMask_CPU_Core_20 = IFB_BIT_FLAG_20,
    IFBThreadAffinityMask_CPU_Core_21 = IFB_BIT_FLAG_21,
    IFBThreadAffinityMask_CPU_Core_22 = IFB_BIT_FLAG_22,
    IFBThreadAffinityMask_CPU_Core_23 = IFB_BIT_FLAG_23,
    IFBThreadAffinityMask_CPU_Core_24 = IFB_BIT_FLAG_24,
    IFBThreadAffinityMask_CPU_Core_25 = IFB_BIT_FLAG_25,
    IFBThreadAffinityMask_CPU_Core_26 = IFB_BIT_FLAG_26,
    IFBThreadAffinityMask_CPU_Core_27 = IFB_BIT_FLAG_27,
    IFBThreadAffinityMask_CPU_Core_28 = IFB_BIT_FLAG_28,
    IFBThreadAffinityMask_CPU_Core_29 = IFB_BIT_FLAG_29,
    IFBThreadAffinityMask_CPU_Core_30 = IFB_BIT_FLAG_30,
    IFBThreadAffinityMask_CPU_Core_31 = IFB_BIT_FLAG_31
};


namespace ifb_thread {

    const ifb::u32 memory_size_pool_init        (void);
    const ifb::u32 memory_size_pool_args        (void);
    const ifb::u32 memory_size_pool_sizes_cache (void);
};

namespace ifb_thread {
    
    const ifb::b8 pool_create  (IFBThreadPoolInit*   init);
    const ifb::b8 pool_destroy (const IFBThreadPool* thread_pool);
}

#endif //IFB_THREADS_HPP