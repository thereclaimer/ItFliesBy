#pragma once

#include "ifb-engine-internal-renderer.hpp"

inline const IFBB8
ifb_engine::renderer_viewport_clear(
    const IFBEngineRenderer* ptr_renderer) {

    //sanity check
    ifb_macro_assert(ptr_renderer);

    //load the viewport
    IFBGLViewport* ptr_viewport = ifb_engine::renderer_load_pointer_to_viewport(ptr_renderer);

    //clear the viewport
    ifb_gl::viewport_clear(ptr_viewport);

    //we're done
    return(true);
}

inline const IFBB8
ifb_engine::renderer_viewport_update_dimensions(
    const IFBEngineRenderer* ptr_renderer,
    const IFBDimensions*     ptr_viewport_dimensions) {

    //sanity check
    ifb_macro_assert(ptr_renderer);
    if (!ptr_viewport_dimensions) return(false);

    //load the viewport
    IFBGLViewport* ptr_viewport = ifb_engine::renderer_load_pointer_to_viewport(ptr_renderer);
    
    //update the dimensions
    ptr_viewport->dimensions.width  = ptr_viewport_dimensions->width;
    ptr_viewport->dimensions.height = ptr_viewport_dimensions->height;

    //set the update flag
    ifb_gl::viewport_update_flags_set_position_and_dimensions(ptr_viewport->flags);

    //we're done
    return(true);
}

inline const IFBB8
ifb_engine::renderer_viewport_update_clear_color(
    const IFBEngineRenderer*  ptr_renderer,
    const IFBColorNormalized* ptr_viewport_clear_color) {

    //sanity check
    ifb_macro_assert(ptr_renderer);
    if (!ptr_viewport_clear_color) return(false);

    //load the viewport
    IFBGLViewport* ptr_viewport = ifb_engine::renderer_load_pointer_to_viewport(ptr_renderer);
    
    //update the color
    ptr_viewport->clear_color = *ptr_viewport_clear_color;

    //set the update flag
    ifb_gl::viewport_update_flags_set_clear_color(ptr_viewport->flags);

    //we're done
    return(true);
}
