#pragma once

#include <ifb-memory.hpp>

#include "ifb-rendering-gl.hpp"

const IFBU32
ifb_gl::viewport_memory_size(
    IFBVoid) {

    const IFBU32 size = ifb_macro_align_size_struct(IFBGLViewport);
    return(size);
}

IFBGLViewport*
ifb_gl::viewport_memory_initialize(
    const IFBGLViewportArgs& args) {

    //sanity check
    const IFBU32 size = ifb_macro_align_size_struct(IFBGLViewport);
    ifb_macro_assert(size == args.memory.size);

    //zero the buffer
    //this also validates memory
    ifb_memory::zero_buffer(args.memory);
  
    //initialize glew
    ifb_macro_assert(glewInit() == GLEW_OK); 

    //gl configurations
	glHint     (GL_SAMPLES, 4);
	glEnable   (GL_MULTISAMPLE);
	glEnable   (GL_BLEND);
	glEnable   (GL_LINE_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //set the gl viewport dimensions
    glViewport(
            args.position.x,
            args.position.y,
            args.dimensions.width,
            args.dimensions.height);

    //set the gl clear color
    glClearColor(
        args.clear_color.red,
        args.clear_color.green,
        args.clear_color.blue,
        args.clear_color.alpha);

    //cast the pointer
    IFBGLViewport* viewport = (IFBGLViewport*)args.memory.start;

    //set the properties
    viewport->flags       = IFBGLViewportUpdateFlags_None;
    viewport->position    = args.position;
    viewport->dimensions  = args.dimensions;
    viewport->clear_color = args.clear_color;

    //we're done
    return(viewport);
}

IFBVoid 
ifb_gl::viewport_clear(
    IFBGLViewport* viewport) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

IFBVoid
ifb_gl::viewport_update(
    IFBGLViewport* viewport) {

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