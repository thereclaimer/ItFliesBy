#pragma once

#include <ifb-memory.hpp>

#include "ifb-rendering-gl.hpp"

const ifb::u32
ifb::gl::viewport_memory_size(
    void) {

    const ifb::u32 size = ifb_macro_align_size_struct(gl_viewport_t);
    return(size);
}

gl_viewport_t*
ifb::gl::viewport_memory_initialize(
    const gl_viewport_args_t& args) {

    //sanity check
    const ifb::u32 size = ifb_macro_align_size_struct(gl_viewport_t);
    ifb_macro_assert(size == args.memory.size);

    //zero the buffer
    //this also validates memory
    memory::zero_buffer(args.memory);
  
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
    gl_viewport_t* viewport = (gl_viewport_t*)args.memory.start;

    //set the properties
    viewport->flags       = gl_viewport_update_flags_e_none;
    viewport->position    = args.position;
    viewport->dimensions  = args.dimensions;
    viewport->clear_color = args.clear_color;

    //we're done
    return(viewport);
}

void 
ifb::gl::viewport_clear(
    gl_viewport_t* viewport) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void
ifb::gl::viewport_update(
    gl_viewport_t* viewport) {

    //cache the flags
    const ifb::b8 update_position_and_dimensions = ifb::gl::viewport_update_flags_get_position_and_dimensions (viewport->flags);
    const ifb::b8 update_clear_color             = ifb::gl::viewport_update_flags_get_clear_color             (viewport->flags);

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
    viewport->flags = gl_viewport_update_flags_e_none;
}