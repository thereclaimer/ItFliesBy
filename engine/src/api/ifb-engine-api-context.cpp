#pragma once

#include "ifb-engine-api.hpp"
#include "ifb-engine-internal-context.hpp"

/**********************************************************************************/
/* CREATE/DESTROY                                                                 */
/**********************************************************************************/

ifb_engine_api const IFBHNDArena
ifb_engine::context_create(
    const IFBPlatformApi* ptr_platform_api,
    const IFBByte*        stack_memory_ptr,
    const IFBU32          stack_memory_size,
    const IFBU64          reservation_size) {

    //platform arena
    IFBHNDArena platform_arena_handle;
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

    //get an arena for the platform
    platform_arena_handle = ifb_engine::core_memory_commit_arena(context_ref.ptr_core);

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

    IFBB8 result = true;

    //get the context structures
    IFBEngineCore*       ptr_core       = ifb_engine::context_get_ptr_core();
    IFBEngineSingletons* ptr_singletons = ifb_engine::context_get_ptr_singletons();
    
    //load the config
    IFBEngineConfig* ptr_config = ifb_engine::singletons_load_config(ptr_singletons);
    result &= ifb_engine::config_initialize(ptr_config);

    //initialize engine systems
    IFBEngineGraphicsManager* ptr_graphics_manager = ifb_engine::singletons_load_graphics_manager(ptr_singletons);
    result &= ifb_engine::graphics_manager_initialize(ptr_graphics_manager,ptr_core);

    //allocate an update structure
    const IFBU32 update_size = ifb_macro_align_size_struct(IFBEngineContextUpdate);
    IFBEngineContextUpdate* update_ptr = (IFBEngineContextUpdate*)ifb_engine::core_memory_commit_bytes_absolute(ptr_core,update_size);

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
    IFBEngineSingletons*      ptr_singletons       = ifb_engine::context_get_ptr_singletons();
    IFBEngineGraphicsManager* ptr_graphics_manager = ifb_engine::singletons_load_graphics_manager(ptr_singletons);

    //start a new window frame
    result &= ifb_engine::graphics_window_frame_start(ptr_graphics_manager,&ptr_update->window_update);
    
    //render the window frame
    result &= ifb_engine::graphics_window_frame_render(ptr_graphics_manager);

    //we're done
    return(result);
}