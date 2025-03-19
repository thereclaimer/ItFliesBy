#ifndef IFB_TYPES_THREAD_HPP
#define IFB_TYPES_THREAD_HPP

#include "ifb-types-primitives.hpp"
#include "ifb-types-memory.hpp"
#include "ifb-bit-flags.hpp"

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

struct IFBThreadPoolHeader {
    IFBMemoryBlock memory;
    IFBU32         thread_count;
    IFBU32         stride_description;
    IFBU32         stride_memory_platform;
    IFBU32         stride_memory_task;
};

struct IFBThreadPoolHandles {
    IFBHND16 description_buffer;  
    IFBHND16 memory_platform;
    IFBHND16 memory_task;
    IFBHND16 array_task_functions;
    IFBHND16 array_list_running_threads;
    IFBHND16 array_affinity_mask;
};

struct IFBThreadPool {
    IFBThreadPoolHeader  header;
    IFBThreadPoolHandles handles;
};

/**********************************************************************************/
/* THREAD REQUEST                                                                 */
/**********************************************************************************/

struct IFBThreadRequest {
    IFBMemoryBlock memory;
    IFBU64         thread_count;
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


#endif //IFB_TYPES_THREAD_HPP