#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-internal-context.hpp"

ifb_api const ifb_b8
ifb_engine::context_create(
    IFBPlatformApi& platform_api_ref) {

    //initialize the api
    ifb_engine::platform_initialize(platform_api_ref);

    //reset the context
    ifb_engine::context_reset();

    //get config values
    IFBEngineConfig* config_ptr = ifb_engine::context_get_config();
    ifb_engine::config_get_values(config_ptr);

    //initialize the context
    ifb_engine::context_initialize_stack   (config_ptr);
    ifb_engine::context_handles_create_all();
    ifb_engine::context_initialize_memory  (config_ptr);
    ifb_engine::context_initialize_managers(config_ptr);

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

ifb_api const ifb_b8 
ifb_engine::context_startup(
    ifb_void) {
        
    //get the pointers
    IFBEngineWindowManager* window_manager_ptr = ifb_engine::context_get_window_manager();
    IFBEngineConfig*        config_ptr         = ifb_engine::context_get_config();

    const ifb_b8 use_opengl = true;
    const ifb_b8 use_imgui  = true;

    //create the window
    ifb_engine::window_manager_create_window(
        window_manager_ptr,
        config_ptr->window_title_cstr,
        use_opengl,
        use_imgui);

    //we're done
    return(true);
}
