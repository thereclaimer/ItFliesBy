#pragma once

#include "ifb-engine-internal-renderer.hpp"

#include "ifb-engine-renderer-viewport.cpp"

const IFBB8
ifb_engine::renderer_initialize(
          IFBEngineRenderer*  ptr_renderer,
          IFBMemoryArena*     ptr_arena,
    const IFBDimensions*      ptr_viewport_dimensions,
    const IFBColorNormalized* ptr_viewport_clear_color) {

    IFBB8 result = true;

    //sanity check
    ifb_macro_assert(ptr_renderer);
    ifb_macro_assert(ptr_arena);
    ifb_macro_assert(ptr_viewport_dimensions);
    ifb_macro_assert(ptr_viewport_clear_color);

    //commit handles
    IFBEngineRendererHandles& handles_ref = ptr_renderer->handles;
    handles_ref.viewport = ifb_gl::viewport_commit_to_arena_relative(ptr_arena);
    
    //load the viewport
    IFBGLViewport* ptr_viewport  = ifb_gl::viewport_load_from_arena(ptr_arena,handles_ref.viewport);
    ifb_macro_assert(ptr_viewport);
    
    //set the viewport properties
    ptr_viewport->position    = {0,0};
    ptr_viewport->dimensions  = *ptr_viewport_dimensions;
    ptr_viewport->clear_color = *ptr_viewport_clear_color;

    //initialize the viewport
    ifb_gl::viewport_initialize(ptr_viewport);

    //set the arena
    ptr_renderer->arena = ptr_arena;

    //we're done
    return(result);
}

inline IFBGLViewport*
ifb_engine::renderer_load_pointer_to_viewport(
    const IFBEngineRenderer* ptr_renderer) {

    ifb_macro_assert(ptr_renderer);
    
    IFBGLViewport* ptr_viewport = ifb_gl::viewport_load_from_arena(
        ptr_renderer->arena,
        ptr_renderer->handles.viewport);
    
    ifb_macro_assert(ptr_renderer);

    return(ptr_viewport);
}