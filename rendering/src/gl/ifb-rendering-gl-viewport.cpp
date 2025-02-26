#pragma once

#include "ifb-rendering-gl.hpp"

inline IFBVoid 
ifb_gl::viewport_initialize(
    IFBGLViewport* viewport) {

    //initialize glew
    ifb_macro_assert(glewInit() == GLEW_OK); 
 
    //set viewport position, dimensions, and clear color
    ifb_gl::viewport_set_clear_color(viewport);
    ifb_gl::viewport_set_position_and_dimensions(viewport);    

    //other gl configurations
	glHint     (GL_SAMPLES, 4);
	glEnable   (GL_MULTISAMPLE);
	glEnable   (GL_BLEND);
	glEnable   (GL_LINE_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

inline IFBVoid 
ifb_gl::viewport_clear(
    IFBGLViewport* viewport) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

inline IFBVoid 
ifb_gl::viewport_set_clear_color(
    IFBGLViewport* viewport) {

    //set the clear color
    glClearColor(
        viewport->clear_color.red,
        viewport->clear_color.green,
        viewport->clear_color.blue,
        viewport->clear_color.alpha);
}

inline IFBVoid 
ifb_gl::viewport_set_position_and_dimensions(
    IFBGLViewport* viewport) {

    //set viewport position and dimensions
    glViewport(
        viewport->position.x,
        viewport->position.y,
        viewport->dimensions.width,
        viewport->dimensions.height);
}