#pragma once

#include "ifb-engine-api.hpp"
#include "ifb-engine-internal-context.hpp"

/**********************************************************************************/
/* CREATE/DESTROY                                                                 */
/**********************************************************************************/

ifb_engine_api const IFBHNDEngineArena
ifb_engine::context_create(
    const IFBPlatformApi* ptr_platform_api,
    const IFBByte*        stack_memory_ptr,
    const IFBU32          stack_memory_size,
    const IFBU64          reservation_size) {

    //platform arena
    IFBHNDEngineArena platform_arena_handle;
    platform_arena_handle.pointer = NULL;

    //get the context
    IFBEngineContext& context_ref = ifb_engine::context_ref();

    //sanity check
    ifb_macro_assert(ptr_platform_api);
    ifb_macro_assert(stack_memory_ptr);
    ifb_macro_assert(stack_memory_size);
    ifb_macro_assert(reservation_size);

    //set the api
    (IFBVoid)ifb_engine::platform_api_initialize(ptr_platform_api);
        
    //create the core
    context_ref.ptr_core = ifb_engine::core_create(
        stack_memory_ptr,
        stack_memory_size,
        reservation_size);
    if (!context_ref.ptr_core) return(platform_arena_handle);
    
    //commit the singletons
    context_ref.ptr_singletons = ifb_engine::singletons_create(context_ref.ptr_core);
    if (!context_ref.ptr_singletons) return(platform_arena_handle);

    //commit the arenas
    IFBEngineArenas* ptr_arenas = ifb_engine::singletons_load_arenas(context_ref.ptr_singletons);
    ptr_arenas->platform  = ifb_engine::core_memory_commit_arena(context_ref.ptr_core);
    ptr_arenas->graphics  = ifb_engine::core_memory_commit_arena(context_ref.ptr_core);
    ptr_arenas->rendering = ifb_engine::core_memory_commit_arena(context_ref.ptr_core);

    //set the platform arena
    platform_arena_handle.pointer = (IFBPtr)ptr_arenas->platform; 

    //we're done
    return(platform_arena_handle);
}

ifb_engine_api const IFBB8
ifb_engine::context_destroy(
    IFBVoid) {

    IFBB8 result = true;

    IFBEngineContext& context_ref = ifb_engine::context_ref();

    result &= ifb_engine::core_destroy(context_ref.ptr_core);

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