#pragma once

#include <ifb.hpp>
#include "ifb-engine-internal-context.hpp"

#include "ifb-engine-context-singletons.cpp"
#include "ifb-engine-context-platform.cpp"
#include "ifb-engine-context-config.cpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

ifb_global IFBEngineContext _context;

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
    platform_arena_handle.offset = 0;

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

ifb_engine_api const IFBB8
ifb_engine::context_startup(
    IFBVoid) {

    IFBB8 result = true;

    //get the context structures
    IFBEngineCore*       ptr_core       = ifb_engine::context_get_ptr_core();
    IFBEngineSingletons* ptr_singletons = ifb_engine::context_get_ptr_singletons();
    
    //load the config
    IFBEngineConfig* ptr_config = ifb_engine::singletons_load_config(ptr_singletons);
    result &= ifb_engine::config_initialize(ptr_config);

    //calculate the platform reservation size
    const IFBU64 reservation_gb   = ptr_config->memory_reservation_size_gb;
    const IFBU64 reservation_size = ifb_macro_size_gigabytes(reservation_gb);

    //reserve the platform memory
    result &= ifb_engine::core_memory_reserve_platform_memory(ptr_core,reservation_size);
    if (!result) return(false);

    //initialize engine systems
    IFBEngineGraphicsManager* ptr_graphics_manager = ifb_engine::singletons_load_graphics_manager(ptr_singletons);
    result &= ifb_engine::graphics_manager_initialize(ptr_graphics_manager,ptr_core);

    //we're done
    return(true);
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
    IFBVoid) {

    return(false);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline IFBEngineContext&
ifb_engine::context_ref(
    IFBVoid) {

    return(_context);
}

inline IFBEngineCore*
ifb_engine::context_get_ptr_core(
    IFBVoid) {

    IFBEngineCore* ptr_core = _context.ptr_core;
    ifb_macro_assert(ptr_core);

    return(ptr_core);
}

inline IFBEngineSingletons* 
ifb_engine::context_get_ptr_singletons(
    IFBVoid) {

    IFBEngineSingletons* ptr_singletons = _context.ptr_singletons;
    ifb_macro_assert(ptr_singletons);

    return(ptr_singletons);
}