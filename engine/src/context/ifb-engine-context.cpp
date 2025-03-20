#pragma once

#include <ifb.hpp>
#include "ifb-engine-internal-context.hpp"

#include "ifb-engine-context-singletons.cpp"
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

    //load pointers
    IFBEngineArenas*   ptr_arenas   = ifb_engine::singletons_load_arenas   (singletons_ptr);
    IFBEngineGraphics* ptr_graphics = ifb_engine::singletons_load_graphics (singletons_ptr);
    IFBEngineRenderer* ptr_renderer = ifb_engine::singletons_load_renderer (singletons_ptr);

    //initialize graphics manager
    result &= ifb_engine::graphics_initialize(
        ptr_graphics,
        ptr_arenas->graphics,
        IFBColorFormat_RGBA);

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
    result &= ifb_engine::graphics_window_get_dimensions(ptr_graphics,&renderer_viewport_dimensions);

    //initalize the renderer
    result &= ifb_engine::renderer_initialize(
        ptr_renderer,
        ptr_arenas->rendering,
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
