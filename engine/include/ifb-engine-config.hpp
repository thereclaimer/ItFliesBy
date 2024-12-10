#ifndef IFB_ENGINE_CONFIG_HPP
#define IFB_ENGINE_CONFIG_HPP

#include <ifb-common.hpp>

#define IFB_ENGINE_CONFIG_MEMORY_MINIMUM_GB       2
#define IFB_ENGINE_CONFIG_MEMORY_COMMIT_COUNT_MAX 128
#define IFB_ENGINE_CONFIG_GLOBAL_STACK_KB         64
#define IFB_ENGINE_CONFIG_ARENA_MINIMUM_KB        4
#define IFB_ENGINE_CONFIG_ARENA_COUNT_MAX         64
#define IFB_ENGINE_CONFIG_TAG_C_STR_LENGTH        32
#define IFB_ENGINE_CONFIG_TAG_COUNT_MAX           1024



struct IFBEngineConfig {
    ifb_u32 memory_minimum_gb;
    ifb_u32 memory_commit_count_max;
    ifb_u32 global_stack_kb;
    ifb_u32 arena_minimum_kb;
    ifb_u32 arena_count_max;
    ifb_u32 tag_c_str_length;
    ifb_u32 tag_count_max; 
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

#endif //IFB_ENGINE_CONFIG_HPP