#pragma once

#include "ifb-rendering-gl.hpp"

IFBGLViewport*
ifb_gl::viewport_load_from_arena(
          IFBMemoryArena* ptr_arena,
    const IFBU32          offset) {

    IFBGLViewport* ptr_viewport = (IFBGLViewport*)ifb_memory::arena_get_pointer(ptr_arena,offset);
    ifb_macro_assert(ptr_viewport);
    return(ptr_viewport);
}

IFBGLViewport*
ifb_gl::viewport_commit_to_arena_absolute(
    IFBMemoryArena* ptr_arena) {
    
    const IFBU32   viewport_size = ifb_macro_align_size_struct(IFBGLViewport);
    IFBGLViewport* viewport_ptr  = (IFBGLViewport*)ifb_memory::arena_commit_bytes_absolute(ptr_arena,viewport_size);
    return(viewport_ptr);
}

const IFBU32
ifb_gl::viewport_commit_to_arena_relative(
    IFBMemoryArena* ptr_arena) {

    const IFBU32 viewport_size   = ifb_macro_align_size_struct(IFBGLViewport);
    const IFBU32 viewport_offset = ifb_memory::arena_commit_bytes_relative(ptr_arena,viewport_size);
    
    return(viewport_offset);
}

IFBVoid 
ifb_gl::viewport_initialize(
    IFBGLViewport* viewport) {

    //initialize glew
    ifb_macro_assert(viewport);
    ifb_macro_assert(glewInit() == GLEW_OK); 

    //gl configurations
	glHint     (GL_SAMPLES, 4);
	glEnable   (GL_MULTISAMPLE);
	glEnable   (GL_BLEND);
	glEnable   (GL_LINE_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 
    //set viewport position, dimensions, and clear color
    glViewport(
            viewport->position.x,
            viewport->position.y,
            viewport->dimensions.width,
            viewport->dimensions.height);

    //set the clear color
    glClearColor(
        viewport->clear_color.red,
        viewport->clear_color.green,
        viewport->clear_color.blue,
        viewport->clear_color.alpha);
}

IFBVoid 
ifb_gl::viewport_clear(
    IFBGLViewport* viewport) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


IFBVoid
ifb_gl::viewport_update(
    IFBGLViewport* viewport) {

    //sanity check
    ifb_macro_assert(viewport);

    //cache the flags
    const IFBB8 update_position_and_dimensions = ifb_gl::viewport_update_flags_get_position_and_dimensions (viewport->flags);
    const IFBB8 update_clear_color             = ifb_gl::viewport_update_flags_get_clear_color             (viewport->flags);

    //update the position and dimensions
    if (update_position_and_dimensions) {
        glViewport(
            viewport->position.x,
            viewport->position.y,
            viewport->dimensions.width,
            viewport->dimensions.height);
    }

    //set the clear color
    if (update_clear_color) {
        glClearColor(
            viewport->clear_color.red,
            viewport->clear_color.green,
            viewport->clear_color.blue,
            viewport->clear_color.alpha);
    }

    //clear the flags
    viewport->flags = IFBGLViewportUpdateFlags_None;
}
