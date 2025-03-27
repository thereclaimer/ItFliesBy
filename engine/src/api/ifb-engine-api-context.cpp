#pragma once

#include "ifb-engine-api.hpp"
#include "ifb-engine-internal-context.hpp"

#include "ifb-engine-context-init.cpp"

/**********************************************************************************/
/* CREATE/DESTROY                                                                 */
/**********************************************************************************/

ifb_engine_api const IFBB8
ifb_engine::context_create(
    IFBEngineArgs* args) {

    //set up the init struct
    IFBEngineInit init;
    init.result  = true;
    init.args    = args;
    init.context = ifb_engine::context(); 

    //initialize the context
    ifb_engine::context_init_step_0_validate_args     (init);
    ifb_engine::context_init_step_1_set_platform_api  (init);
    ifb_engine::context_init_step_2_create_core       (init);
    ifb_engine::context_init_step_3_create_singletons (init);    
    ifb_engine::context_init_step_4_commit_arenas     (init);

    //check the result
    const IFBB8 result = init.result ? true : false;

    //we're done
    return(result);
}

ifb_engine_api const IFBB8
ifb_engine::context_destroy(
    IFBVoid) {

    IFBB8 result = true;

    IFBEngineContext* context = ifb_engine::context();

    result &= ifb_engine::core_destroy(context->ptr_core);

    return(result);
}

/**********************************************************************************/
/* STARTUP/SHUTDOWN                                                               */
/**********************************************************************************/

ifb_engine_api IFBEngineContextUpdate*
ifb_engine::context_startup(
    IFBVoid) {

    //get the context structures
    IFBEngineCore*       ptr_core       = ifb_engine::context_get_ptr_core();
    IFBEngineSingletons* ptr_singletons = ifb_engine::context_get_ptr_singletons();
    
    //initialize engine systems
    IFBB8 startup_result = true;
    startup_result &= ifb_engine::context_initialize_config                 (ptr_core, ptr_singletons);
    startup_result &= ifb_engine::context_initialize_graphics_and_rendering (ptr_core, ptr_singletons);

    // allocate an update structure if startup was successful
    // this part should ALWAYS work, so an assertion is built in
    // if we did not succeed, we will return NULL to the platform
    // to let them know shit's fucked up
    IFBEngineContextUpdate* update_ptr = startup_result
        ? ifb_engine::context_commit_update(ptr_core)
        : NULL;

    //we're done
    return(update_ptr);
}

ifb_engine_api const IFBB8
ifb_engine::context_shutdown(
    IFBVoid) {

    return(false);
}

/**********************************************************************************/
/* RENDERING                                                                      */
/**********************************************************************************/

ifb_engine_api const IFBB8
ifb_engine::context_render_frame(
    IFBEngineContextUpdate* ptr_update) {

    //result
    IFBB8 result = true;
    ifb_macro_assert(ptr_update);

    //get the singletons
    IFBEngineSingletons* ptr_singletons = ifb_engine::context_get_ptr_singletons();
    IFBEngineGraphics*   ptr_graphics   = ifb_engine::singletons_load_graphics (ptr_singletons);
    IFBEngineRenderer*   ptr_renderer   = ifb_engine::singletons_load_renderer (ptr_singletons);

    //cache window flags
    const IFBB8 update_window_dimensions = ifb_engine::update_flags_get_window_dimensions(ptr_update->flags);
    const IFBB8 update_window_position   = ifb_engine::update_flags_get_window_position  (ptr_update->flags);

    //handle window and viewport updates
    if (update_window_dimensions) {
        result &= ifb_engine::graphics_window_update_dimensions   (ptr_graphics, &ptr_update->window.dimensions);
        result &= ifb_engine::renderer_viewport_update_dimensions (ptr_renderer, &ptr_update->window.dimensions);
    }
    if (update_window_position) {
        result &= ifb_engine::graphics_window_update_position(ptr_graphics, &ptr_update->window.position);
    }   
    
    //start a new window frame
    result &= ifb_engine::graphics_window_frame_start (ptr_graphics);
    result &= ifb_engine::renderer_viewport_clear     (ptr_renderer);

    //render the window frame
    result &=  ifb_engine::graphics_window_frame_render (ptr_graphics);
    result &= !ifb_engine::update_flags_get_quit        (ptr_update->flags);

    //clear the flags
    ptr_update->flags = IFBEngineContextUpdateFlags_None;

    //we're done
    return(result);
}