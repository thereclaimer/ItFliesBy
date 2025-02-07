#ifndef IFB_ENGINE_INTERNAL_CONFIG_HPP
#define IFB_ENGINE_INTERNAL_CONFIG_HPP

#ifndef IFB_ENGINE_CONFIG_MEMORY_STACK_SIZE_KB
    #define IFB_ENGINE_CONFIG_MEMORY_STACK_SIZE_KB 64
#endif //IFB_ENGINE_CONFIG_MEMORY_STACK_SIZE_KB

#ifndef IFB_ENGINE_CONFIG_MEMORY_RESERVATION_SIZE_GB
    #define IFB_ENGINE_CONFIG_MEMORY_RESERVATION_SIZE_GB 4
#endif //IFB_ENGINE_CONFIG_MEMORY_RESERVATION_SIZE_GB

struct IFBEngineConfig {
    ifb_u32 memory_stack_size_kb;
    ifb_u32 memory_reservation_size_gb;
};

namespace ifb_engine {

    inline ifb_void
    config_get_values(IFBEngineConfig& config_ref) {

        config_ref.memory_stack_size_kb       = IFB_ENGINE_CONFIG_MEMORY_STACK_SIZE_KB;
        config_ref.memory_reservation_size_gb = IFB_ENGINE_CONFIG_MEMORY_RESERVATION_SIZE_GB;
    }
};


#endif //IFB_ENGINE_INTERNAL_CONFIG_HPP