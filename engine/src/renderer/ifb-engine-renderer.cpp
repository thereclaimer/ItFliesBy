#pragma once

#include "ifb-engine-internal-renderer.hpp"

const IFBB8
ifb_engine::renderer_initialize(
          IFBEngineRenderer*  ptr_renderer,
          IFBEngineCore*      ptr_core,
    const IFBDimensions*      ptr_viewport_dimensions,
    const IFBColorNormalized* ptr_viewport_color) {

    //sanity check
    ifb_macro_assert(ptr_renderer);
    ifb_macro_assert(ptr_core);
    ifb_macro_assert(ptr_viewport_dimensions);
    ifb_macro_assert(ptr_viewport_color);

    //commit arena
    const IFBHNDArena arena_handle = ifb_engine::core_memory_commit_arena(ptr_core);
    if (!ifb_memory_macro_handle_valid(arena_handle)) return(false);

    //commit viewport to arena
    IFBGLViewport* ptr_viewport = ifb_gl::viewport_commit_to_arena_absolute(arena_handle); 
    if (!ptr_viewport) return(false);
    
    //set the viewport properties
    ptr_viewport->position    = {0,0};
    ptr_viewport->dimensions  = *ptr_viewport_dimensions;
    ptr_viewport->clear_color = *ptr_viewport_color;

    //initialize the viewport
    ifb_gl::viewport_initialize(ptr_viewport);

    //we're done
    return(true);
}

const IFBB8
ifb_engine::renderer_update_viewport(
          IFBEngineRenderer*  ptr_renderer,
    const IFBDimensions*      ptr_viewport_dimensions,
    const IFBColorNormalized* ptr_viewport_color)  {

    //sanity check
    ifb_macro_assert(ptr_renderer);

    //update viewport properties
    IFBGLViewport* ptr_viewport = &ptr_renderer->viewport;

    //viewport dimensions
    if (ptr_viewport_dimensions) {
        ptr_viewport->dimensions = *ptr_viewport_dimensions;
        ifb_gl::viewport_set_position_and_dimensions(ptr_viewport);
    }
    
    //viewport color
    if (ptr_viewport_color) {
        ptr_viewport->clear_color = *ptr_viewport_color;
        ifb_gl::viewport_set_clear_color(ptr_viewport);
    }

    return(true);
}

const IFBB8
ifb_engine::renderer_clear_viewport(
    IFBEngineRenderer* ptr_renderer) {

    //sanity check
    ifb_macro_assert(ptr_renderer);

    ifb_gl::viewport_clear(&ptr_renderer->viewport);

    return(true);
}