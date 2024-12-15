#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-internal-context.hpp"

ifb_api const ifb_b8
ifb_engine::context_create(
    IFBPlatformApi& platform_api_ref) {

    //initialize the api
    ifb_engine::platform_initialize(platform_api_ref);





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

    const ifb_b8 use_opengl     = true;
    const ifb_b8 use_imgui      = false;
    const ifb_b8 window_visible = true;

    //create the window
    ifb_engine::window_manager_create_window(
        window_manager_ptr,
        config_ptr->window_title_cstr,
        use_opengl,
        use_imgui);

    //show the window
    ifb_engine::window_manager_set_visibility(
        window_manager_ptr,
        window_visible);

    //we're done
    return(true);
}

ifb_api const ifb_b8 
ifb_engine::context_update_and_render(
    ifb_void) {

    //get the pointers
    IFBEngineWindowManager* window_manager_ptr = ifb_engine::context_get_window_manager();

    //start a new frame
    ifb_engine::window_manager_frame_start(window_manager_ptr);

    //render the frame
    ifb_engine::window_manager_frame_render(window_manager_ptr);

    //we're done
    return(true);
}
