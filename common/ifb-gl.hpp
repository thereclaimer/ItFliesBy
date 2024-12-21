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
    IFBPosition   position;
    IFBDimensions dimensions;
};

namespace ifb_gl{

    ifb_void viewport_clear                       (ifb_void);
    ifb_void viewport_set_clear_color             (IFBGLViewport& viewport, const IFBColor32& color_ref);
    ifb_void viewport_set_position_and_dimensions (IFBGLViewport& viewport, const IFBPosition& position, const IFBDimensions& dimensions);
};

#endif //IFB_GL_HPP