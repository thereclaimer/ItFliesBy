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
typedef IFBVoid (*IFBThreadTaskCallback) (IFBThread* thread_context);

//request
struct IFBThreadRequest;
struct IFBThreadRequestHeader;
struct IFBThreadRequestHandles;

/**********************************************************************************/
/* THREAD                                                                         */
/**********************************************************************************/

typedef IFBU64 IFBThreadAffinityMask;

struct IFBThread {
    IFBAddr memory_start;
    IFBU32  platform_memory_size;
    IFBU16  pool_index;
    IFBU16  memory_platform;
    IFBU16  memory_task;
    IFBU16  description;
    IFBU16  task;
    IFBU16  affinity_mask;
};

/**********************************************************************************/
/* THREAD POOL                                                                    */
/**********************************************************************************/

struct IFBThreadPoolSizesCache {
    struct {
        IFBU32 max;
        IFBU32 thread_handle;
        IFBU32 task_function;
        IFBU32 affinity_mask;
        IFBU32 platform_instance;
    } other;
    struct {
        IFBU16 total;
        IFBU16 pool_struct_size;
        IFBU16 platform_total;
        IFBU16 description_buffer;
        IFBU16 task_data;
        IFBU16 thread_functions;
        IFBU16 array_list_running_threads;
        IFBU16 array_affinity_mask;  
    } memory;
    IFBArrayListArgs array_list_args;
};

struct IFBThreadPoolArgs {
    IFBMemory thread_pool_memory;
    IFBU64    thread_count;
    IFBU32    stride_task_data;
    IFBU32    stride_thread_description; 
};

struct IFBThreadPoolHeader {
    IFBMemory memory;
    IFBU32    thread_count;
    IFBU32    stride_description;
    IFBU32    stride_memory_platform;
    IFBU32    stride_memory_task;
};

struct IFBThreadPoolOffsets {
    IFBU16 description_buffer;
    IFBU16 memory_platform;
    IFBU16 memory_task;
    IFBU16 array_task_functions;
    IFBU16 array_list_running_threads;
    IFBU16 array_affinity_mask;
};

struct IFBThreadPool {
    IFBThreadPoolHeader  header;
    IFBThreadPoolOffsets offsets;
    IFBByte              padding[4];
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
    IFBU64    thread_count;
};

/**********************************************************************************/
/* AFFINITY MASK                                                                  */
/**********************************************************************************/

enum IFBThreadAffinityMask_ : IFBU64 {
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

    const IFBU32 memory_size_pool_init        (IFBVoid);
    const IFBU32 memory_size_pool_args        (IFBVoid);
    const IFBU32 memory_size_pool_sizes_cache (IFBVoid);
};

namespace ifb_thread {
    
    const IFBB8 pool_create  (IFBThreadPoolInit*   init);
    const IFBB8 pool_destroy (const IFBThreadPool* thread_pool);
}

#endif //IFB_THREADS_HPP