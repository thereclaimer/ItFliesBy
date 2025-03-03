#pragma once

#include "ifb-engine-internal-context.hpp"

inline const IFBB8 
ifb_engine::config_initialize(
    IFBEngineConfig* ptr_config) {

    if (!ptr_config);

    ptr_config->memory_stack_size_kb       = IFB_ENGINE_CONFIG_MEMORY_STACK_SIZE_KB;
    ptr_config->memory_reservation_size_gb = IFB_ENGINE_CONFIG_MEMORY_RESERVATION_SIZE_GB;

    //we're done
    return(true);
}