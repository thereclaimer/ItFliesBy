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


inline const IFBB8
ifb_engine::context_initialize_config(
    IFBEngineCore*       core_ptr,
    IFBEngineSingletons* singletons_ptr) {

    IFBB8 result = true;

    //sanity check
    ifb_macro_assert(core_ptr);
    ifb_macro_assert(singletons_ptr);

    //load the config
    IFBEngineConfig* ptr_config = ifb_engine::singletons_load_config(singletons_ptr);
    const IFBB8 config_initialized = ifb_engine::config_initialize(ptr_config);

    //we're done
    return(config_initialized);
}

inline const IFBB8
ifb_engine::context_initialize_graphics_and_rendering(
    IFBEngineCore*       core_ptr,
    IFBEngineSingletons* singletons_ptr) {

    IFBB8 result = true;

    //sanity check
    ifb_macro_assert(core_ptr);
    ifb_macro_assert(singletons_ptr);

    //load graphics manager and renderer
    IFBEngineGraphicsManager* graphics_manager_ptr = ifb_engine::singletons_load_graphics_manager (singletons_ptr);
    IFBEngineRenderer*        renderer_ptr         = ifb_engine::singletons_load_renderer         (singletons_ptr);

    //initialize graphics manager
    result &= ifb_engine::graphics_manager_initialize(graphics_manager_ptr,core_ptr);

    //create the clear color
    IFBColorHex clear_color_hex;
    clear_color_hex.red   =  80;
    clear_color_hex.blue  =  80;
    clear_color_hex.green =  80;
    clear_color_hex.alpha = 255;

    //normalize the clear color
    IFBColorNormalized clear_color_normalized;
    ifb_engine::graphics_get_color_normalized(
        &clear_color_hex,
        &clear_color_normalized);

    //the window dimensions will be the renderer viewport dimensions
    IFBDimensions renderer_viewport_dimensions;
    ifb_engine::graphics_window_get_dimensions(graphics_manager_ptr,&renderer_viewport_dimensions);

    //initalize the renderer
    result &= ifb_engine::renderer_initialize(
        renderer_ptr,
        core_ptr,
        &renderer_viewport_dimensions,
        &clear_color_normalized);

    //we're done
    return(result);
}

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

inline IFBEngineContextUpdate*
ifb_engine::context_commit_update(
    IFBEngineCore* core_ptr) {

    const IFBU32 update_size = ifb_macro_align_size_struct(IFBEngineContextUpdate);

    IFBEngineContextUpdate* update_ptr = (IFBEngineContextUpdate*)ifb_engine::core_memory_commit_bytes_absolute(
        core_ptr,
        update_size);
    
    ifb_macro_assert(update_ptr);

    return(update_ptr);
}
