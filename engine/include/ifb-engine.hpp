#ifndef IFB_ENGINE_HPP
#define IFB_ENGINE_HPP

#include <ifb.hpp>

/**********************************************************************************/
/* CONFIG                                                                         */
/**********************************************************************************/

#define IFB_ENGINE_CONFIG_MEMORY_MINIMUM_GB       2
#define IFB_ENGINE_CONFIG_MEMORY_COMMIT_COUNT_MAX 128
#define IFB_ENGINE_CONFIG_GLOBAL_STACK_KB         64
#define IFB_ENGINE_CONFIG_ARENA_MINIMUM_KB        4
#define IFB_ENGINE_CONFIG_ARENA_COUNT_MAX         64
#define IFB_ENGINE_CONFIG_TAG_C_STR_LENGTH        32
#define IFB_ENGINE_CONFIG_TAG_COUNT_MAX           1024

struct IFBEngineConfig {
    ifb_u16 memory_minimum_gb;
    ifb_u16 memory_commit_count_max;
    ifb_u16 global_stack_kb;
    ifb_u16 arena_minimum_kb;
    ifb_u16 arena_count_max;
    ifb_u16 tag_c_str_length;
    ifb_u16 tag_count_max; 
};

namespace ifb_engine {

    inline ifb_void 
    config_get_values(IFBEngineConfig* ptr_engine_config) {

        ptr_engine_config->memory_minimum_gb       = IFB_ENGINE_CONFIG_MEMORY_MINIMUM_GB;
        ptr_engine_config->memory_commit_count_max = IFB_ENGINE_CONFIG_MEMORY_COMMIT_COUNT_MAX;
        ptr_engine_config->global_stack_kb         = IFB_ENGINE_CONFIG_GLOBAL_STACK_KB;
        ptr_engine_config->arena_minimum_kb        = IFB_ENGINE_CONFIG_ARENA_MINIMUM_KB;
        ptr_engine_config->arena_count_max         = IFB_ENGINE_CONFIG_ARENA_COUNT_MAX;
        ptr_engine_config->tag_c_str_length        = IFB_ENGINE_CONFIG_TAG_C_STR_LENGTH;
        ptr_engine_config->tag_count_max           = IFB_ENGINE_CONFIG_TAG_COUNT_MAX;
    }
};

/**********************************************************************************/
/* ENGINE                                                                            */
/**********************************************************************************/

enum IFBEngineState_ {
    IFBEngineState_NotRunning   = 0,
    IFBEngineState_Fatal        = 1,
    IFBEngineState_Startup      = 2,
    IFBEngineState_Shutdown     = 3,
    IFBEngineState_Idle         = 4,
    IFBEngineState_FrameExecute = 5,
};

typedef ifb_u32 IFBEngineState;
namespace ifb_engine {

    ifb_api const ifb_b8 context_create(IFBPlatformApi& platform_api_ref);
};

/**********************************************************************************/
/* TAG                                                                            */
/**********************************************************************************/

namespace ifb_engine {

    ifb_api const ifb_b8   tag_reserve  (const ifb_cstr  tag_cstr, IFBIDTag& tag_id_ref); 
    ifb_api const ifb_b8   tag_release  (const IFBIDTag& tag_id_ref);
    ifb_api const ifb_cstr tag_get_cstr (const IFBIDTag& tag_id_ref);
    ifb_api const IFBHash  tag_get_hash (const IFBIDTag& tag_id_ref);
};

/**********************************************************************************/
/* ARENA                                                                            */
/**********************************************************************************/

namespace ifb_engine {

    ifb_api const ifb_u32    arena_get_page_start     (const IFBIDArena& arena_id_ref);
    ifb_api const ifb_u32    arena_get_page_count     (const IFBIDArena& arena_id_ref);
    ifb_api const ifb_cstr   arena_get_tag_cstr       (const IFBIDArena& arena_id_ref);
    ifb_api const ifb_memory arena_get_pointer_start  (const IFBIDArena& arena_id_ref);
    ifb_api const ifb_memory arena_get_pointer_offset (const IFBIDArena& arena_id_ref, const ifb_u32 offset);
};

/**********************************************************************************/
/* LINEAR ALLOCATOR                                                               */
/**********************************************************************************/

namespace ifb_engine {

    const IFBHNDLinearAllocator  
    linear_allocator_commit(
        const ifb_cstr linear_allocator_tag_cstr,
        const ifb_u32  linear_allocator_size_minimum);
    
    const ifb_u32 linear_allocator_reserve             (const IFBHNDLinearAllocator linear_allocator_handle, const ifb_u32 size);
    const ifb_u32 linear_allocator_release             (const IFBHNDLinearAllocator linear_allocator_handle, const ifb_u32 size);
    const ifb_ptr linear_allocator_get_pointer         (const IFBHNDLinearAllocator linear_allocator_handle);
    const ifb_b8  linear_allocator_save_point_set      (const IFBHNDLinearAllocator linear_allocator_handle);
    const ifb_b8  linear_allocator_save_point_clear    (const IFBHNDLinearAllocator linear_allocator_handle);
    const ifb_b8  linear_allocator_reset               (const IFBHNDLinearAllocator linear_allocator_handle);
    const ifb_b8  linear_allocator_reset_to_save_point (const IFBHNDLinearAllocator linear_allocator_handle);
};

/**********************************************************************************/
/* BLOCK ALLOCATOR                                                                */
/**********************************************************************************/

namespace ifb_engine {

    const IFBHNDBlockAllocator 
    block_allocator_commit(
        const ifb_cstr block_allocator_tag_cstr,
        const ifb_u32  block_size,
        const ifb_u32  block_count);

    const ifb_b8  block_allocator_reserve     (const IFBHNDBlockAllocator block_allocator_handle, ifb_index& ref_block_index);
    const ifb_b8  block_allocator_release     (const IFBHNDBlockAllocator block_allocator_handle, const ifb_index block_index);
    const ifb_ptr block_allocator_get_pointer (const IFBHNDBlockAllocator block_allocator_handle, const ifb_index block_index);
    const ifb_b8  block_allocator_reset       (const IFBHNDBlockAllocator block_allocator_handle);
};

#endif //IFB_ENGINE_HPP