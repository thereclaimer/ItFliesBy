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
    IFBEngineContextManagers* managers_ptr         = ifb_engine::context_get_managers();
    IFBEngineGraphicsManager* graphics_manager_ptr = ifb_engine::context_managers_get_graphics_manager(managers_ptr);
    IFBEngineConfig*          config_ptr           = ifb_engine::context_get_config();

    //set the window flags
    const IFBWindowFlags window_flags = 
        IFBWindowFlags_Visible | 
        IFBWindowFlags_ImGui   | 
        IFBWindowFlags_OpenGL;

    //create the window
    ifb_engine::graphics_manager_create_window(
        graphics_manager_ptr,
        config_ptr->window_title_cstr,
        window_flags);

    //we're done
    return(true);
}

ifb_api const ifb_b8 
ifb_engine::context_update_and_render(
    ifb_void) {

    //get the pointers
    IFBEngineContextManagers* managers_ptr         = ifb_engine::context_get_managers();
    IFBEngineGraphicsManager* graphics_manager_ptr = ifb_engine::context_managers_get_graphics_manager(managers_ptr);

    //start a new frame
    ifb_engine::graphics_manager_frame_start(graphics_manager_ptr);

    //render the frame
    ifb_engine::graphics_manager_frame_render(graphics_manager_ptr);

    //we're done
    return(true);
}
