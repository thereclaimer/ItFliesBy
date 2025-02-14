#pragma once

#include "ifb-engine-internal-config.hpp"

inline const ifb_b8 
ifb_engine::config_load(
    ifb_void) {

    //get the config
    IFBEngineContextSingletons& singletons_ref = ifb_engine::context_get_singletons();

    //get the config
    IFBEngineConfig* config_ptr = (IFBEngineConfig*)ifb_engine::context_memory_singleton_load(singletons_ref.config);

    //sanity check
    if (!config_ptr) return(false);

    //set the config values
    config_ptr->memory_stack_size_kb       = IFB_ENGINE_CONFIG_MEMORY_STACK_SIZE_KB;
    config_ptr->memory_reservation_size_gb = IFB_ENGINE_CONFIG_MEMORY_RESERVATION_SIZE_GB;

    //we're done
    return(true);
}