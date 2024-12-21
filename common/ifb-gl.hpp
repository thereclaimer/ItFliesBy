#ifndef IFB_GL_HPP
#define IFB_GL_HPP

#include "ifb-dependencies.hpp"
#include "ifb-graphics.hpp"
#include "ifb-types.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBGLPosition;
struct IFBGLUvCoordinate;
struct IFBGLVertexArrayObject;
struct IFBGLViewport;

typedef ifb_u32 IFBGLVertexFlags; 

enum IFBGLVertexFlags_ {
    IFBGLVertexFlags_None          = 0,
    IFBGLVertexFlags_Position      = (1 << 0),
    IFBGLVertexFlags_UvCoordinate  = (1 << 1),
};

struct IFBGLPosition {
    ifb_f32 x;
    ifb_f32 y;
};

struct IFBGLUvCoordinate {
    ifb_f32 x;
    ifb_f32 y;
};

struct IFBGLVertexArrayObject {
    GLint            vao;
    IFBGLVertexFlags flags;    
};

/**********************************************************************************/
/* VIEWPORT                                                                       */
/**********************************************************************************/

struct IFBGLViewport {
    IFBPosition          position;
    IFBDimensions        dimensions;
    IFBColor32Normalized clear_color;
};

namespace ifb_gl{

    ifb_void viewport_initialize                  (IFBGLViewport* viewport);
    ifb_void viewport_clear                       (IFBGLViewport* viewport);
    ifb_void viewport_set_clear_color             (IFBGLViewport* viewport);
    ifb_void viewport_set_position_and_dimensions (IFBGLViewport* viewport);
};

inline ifb_void 
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

inline ifb_void 
ifb_gl::viewport_clear(
    IFBGLViewport* viewport) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

inline ifb_void 
ifb_gl::viewport_set_clear_color(
    IFBGLViewport* viewport) {

    //set the clear color
    glClearColor(
        viewport->clear_color.red,
        viewport->clear_color.green,
        viewport->clear_color.blue,
        viewport->clear_color.alpha);
}

inline ifb_void 
ifb_gl::viewport_set_position_and_dimensions(
    IFBGLViewport* viewport) {

    //set viewport position and dimensions
    glViewport(
        viewport->position.x,
        viewport->position.y,
        viewport->dimensions.width,
        viewport->dimensions.height);
}

#endif //IFB_GL_HPP