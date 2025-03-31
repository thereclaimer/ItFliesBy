#ifndef IFB_THREADS_HPP
#define IFB_THREADS_HPP

#include <ifb.hpp>
#include <ifb-memory.hpp>
#include <ifb-data-structures.hpp>

using namespace ifb;

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb::threads {

    //handles
    struct thread_h      : hnd16 { };
    struct thread_pool_h : hnd32 { };

    //context
    struct thread_t;
    struct thread_status_t;
    struct thread_task_t;
    struct thread_context_t;

    //thread pool
    struct thread_pool_t;
    struct thread_pool_header_t;
    struct thread_pool_handles_t;
    struct thread_pool_args_t;
    struct thread_pool_init_t;

    //callback
    typedef void (*thread_task_callback_f) (thread_t* thread_context);

    //request
    struct thread_request_t;
    struct thread_request_header_t;
    struct thread_request_handles_t;
};

/**********************************************************************************/
/* THREAD                                                                         */
/**********************************************************************************/
namespace ifb::threads {

    typedef u64 thread_affinity_mask_t;

    struct thread_t {
        addr memory_start;
        u32  platform_memory_size; 
        u16  pool_index;
        u16  memory_platform;
        u16  memory_task;
        u16  description;
        u16  task;
        u16  affinity_mask;
    };
};

/**********************************************************************************/
/* THREAD POOL                                                                    */
/**********************************************************************************/

namespace ifb::threads {

    struct thread_pool_sizes_cache_t {
        struct {
            u32 max;
            u32 thread_handle;
            u32 task_function;
            u32 affinity_mask;
            u32 platform_instance;
        } other;
        struct {
            u16 total;
            u16 pool_struct_size;
            u16 platform_total;
            u16 description_buffer;
            u16 task_data;
            u16 thread_functions;
            u16 array_list_running_threads;
            u16 array_affinity_mask;  
        } memory;
        struct {
            u32      element_size;
            u32      element_count;
            memory_t memory;
        } array_list_args;
    };

    struct thread_pool_args_t {
        memory_t thread_pool_memory;
        u64      thread_count;
        u32      stride_task_data;
        u32      stride_thread_description; 
    };

    struct thread_pool_header_t {
        memory_t memory;
        u32      thread_count;
        u32      stride_description;
        u32      stride_memory_platform;
        u32      stride_memory_task;
    };

    struct thread_pool_offsets_t {
        u16 description_buffer;
        u16 memory_platform;
        u16 memory_task;
        u16 array_task_functions;
        u16 array_list_running_threads;
        u16 array_affinity_mask;
    };

    struct thread_pool_t {
        thread_pool_header_t  header;
        thread_pool_offsets_t offsets;
        byte                  padding[4];
    };

    struct thread_pool_init_t {
        thread_pool_args_t*        args;
        thread_pool_sizes_cache_t* sizes_cache;
        thread_pool_t*             pointer;
    };
};

/**********************************************************************************/
/* THREAD REQUEST                                                                 */
/**********************************************************************************/

struct thread_request_t {
    memory_t memory;
    u64      thread_count;
};

/**********************************************************************************/
/* AFFINITY MASK                                                                  */
/**********************************************************************************/

enum thread_affinity_mask_e : u64 {
    thread_affinity_mask_e_cpu_core_00 = IFB_BIT_FLAG_0,
    thread_affinity_mask_e_cpu_core_01 = IFB_BIT_FLAG_1,
    thread_affinity_mask_e_cpu_core_02 = IFB_BIT_FLAG_2,
    thread_affinity_mask_e_cpu_core_03 = IFB_BIT_FLAG_3,
    thread_affinity_mask_e_cpu_core_04 = IFB_BIT_FLAG_4,
    thread_affinity_mask_e_cpu_core_05 = IFB_BIT_FLAG_5,
    thread_affinity_mask_e_cpu_core_06 = IFB_BIT_FLAG_6,
    thread_affinity_mask_e_cpu_core_07 = IFB_BIT_FLAG_7,
    thread_affinity_mask_e_cpu_core_08 = IFB_BIT_FLAG_8,
    thread_affinity_mask_e_cpu_core_09 = IFB_BIT_FLAG_9,
    thread_affinity_mask_e_cpu_core_10 = IFB_BIT_FLAG_10,
    thread_affinity_mask_e_cpu_core_11 = IFB_BIT_FLAG_11,
    thread_affinity_mask_e_cpu_core_12 = IFB_BIT_FLAG_12,
    thread_affinity_mask_e_cpu_core_13 = IFB_BIT_FLAG_13,
    thread_affinity_mask_e_cpu_core_14 = IFB_BIT_FLAG_14,
    thread_affinity_mask_e_cpu_core_15 = IFB_BIT_FLAG_15,
    thread_affinity_mask_e_cpu_core_16 = IFB_BIT_FLAG_16,
    thread_affinity_mask_e_cpu_core_17 = IFB_BIT_FLAG_17,
    thread_affinity_mask_e_cpu_core_18 = IFB_BIT_FLAG_18,
    thread_affinity_mask_e_cpu_core_19 = IFB_BIT_FLAG_19,
    thread_affinity_mask_e_cpu_core_20 = IFB_BIT_FLAG_20,
    thread_affinity_mask_e_cpu_core_21 = IFB_BIT_FLAG_21,
    thread_affinity_mask_e_cpu_core_22 = IFB_BIT_FLAG_22,
    thread_affinity_mask_e_cpu_core_23 = IFB_BIT_FLAG_23,
    thread_affinity_mask_e_cpu_core_24 = IFB_BIT_FLAG_24,
    thread_affinity_mask_e_cpu_core_25 = IFB_BIT_FLAG_25,
    thread_affinity_mask_e_cpu_core_26 = IFB_BIT_FLAG_26,
    thread_affinity_mask_e_cpu_core_27 = IFB_BIT_FLAG_27,
    thread_affinity_mask_e_cpu_core_28 = IFB_BIT_FLAG_28,
    thread_affinity_mask_e_cpu_core_29 = IFB_BIT_FLAG_29,
    thread_affinity_mask_e_cpu_core_30 = IFB_BIT_FLAG_30,
    thread_affinity_mask_e_cpu_core_31 = IFB_BIT_FLAG_31
};

namespace ifb::threads {

    const u32 memory_size_pool_init        (void);
    const u32 memory_size_pool_args        (void);
    const u32 memory_size_pool_sizes_cache (void);
};

namespace ifb::threads {
    
    const b8 pool_create  (thread_pool_init_t*   init);
    const b8 pool_destroy (const thread_pool_t*  thread_pool);
};

#endif //IFB_THREADS_HPP