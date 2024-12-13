#pragma once

#include "ifb-engine.hpp"

ifb_api const ifb_b8
ifb_engine::context_create(
    IFBPlatformApi& platform_api_ref) {

    //initialize the api
    ifb_engine::platform_initialize(platform_api_ref);

    //global initialization
    ifb_engine::context_reset();
    ifb_engine::context_handles_create_all();

    //get config values
    IFBEngineConfig* config_ptr = ifb_engine::context_get_config();
    ifb_engine::config_get_values(config_ptr);

    //initialize the context
    ifb_engine::context_initialize_managers(config_ptr);
    ifb_engine::context_initialize_memory  (config_ptr);

    //we're done
    return(true);
}

ifb_api const ifb_b8 
ifb_engine::context_destroy(
    ifb_void) {

    //TODO
    ifb_macro_panic();
    return(true);
}
