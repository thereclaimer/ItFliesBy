#ifndef IFB_RENDERING_HPP
#define IFB_RENDERING_HPP

#include "ifb-types.hpp"
#include "ifb-gl.hpp"
#include "ifb-memory.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

//--------------------
// ids
//--------------------

struct IFBIDShader;
struct IFBIDBufferVertex;
struct IFBIDBufferElement;
struct IFBIDUniform;
struct IFBIDUniformU32;
struct IFBIDUniformF32;
struct IFBIDUniformVec2;
struct IFBIDUniformVec3;
struct IFBIDUniformMat3;
struct IFBIDUniformColor;
struct IFBIDUniformSpriteAtlas;
struct IFBIDTransform;

//--------------------
// structs
//--------------------

struct IFBShader;
struct IFBBufferVertex;
struct IFBBufferElement;
struct IFBUniformHeader;
struct IFBUniformU32;
struct IFBUniformF32;
struct IFBUniformVec2;
struct IFBUniformVec3;
struct IFBUniformMat3;
struct IFBUniformColor;
struct IFBTransform;

/**********************************************************************************/
/* SHADERS                                                                        */
/**********************************************************************************/

struct IFBIDShader : IFBID {
    struct {
        IFBIDTag                 tag;
        IFBGLIDShaderProgram     gl_shader_program;
        IFBGLIDVertex            gl_vertex;
    } foreign_ids;
};

struct IFBShader : IFBIDShader {
    ifb_u32 uniform_count;
};

/**********************************************************************************/
/* BUFFERS                                                                        */
/**********************************************************************************/

struct IFBIDBufferVertex  : IFBID { 
    struct {
        IFBIDTag            tag;
        IFBGLIDBufferVertex gl_vertex_buffer;
    } foreign_ids;
};

struct IFBBufferVertex : IFBIDBufferVertex {
    ifb_u32 size;
    ifb_u32 stride;
    IFBHND  data_handle;
};

struct IFBIDBufferElement : IFBID {
    struct {
        IFBIDTag             tag;
        IFBGLIDBufferElement gl_element_buffer; 
    } foreign_ids;
};

struct IFBBufferElement : IFBIDBufferElement {
    ifb_u32  count;
    ifb_u32* data;
};

/**********************************************************************************/
/* UNIFORMS                                                                       */
/**********************************************************************************/

struct IFBIDUniform : IFBID {
    struct {
        IFBIDShader    shader;
        IFBIDTag       tag;
        IFBGLIDUniform gl_uniform;
    } foreign_ids;
};

struct IFBIDUniformU32         : IFBIDUniform { };
struct IFBIDUniformF32         : IFBIDUniform { };
struct IFBIDUniformVec2        : IFBIDUniform { };
struct IFBIDUniformVec3        : IFBIDUniform { };
struct IFBIDUniformMat3        : IFBIDUniform { };
struct IFBIDUniformColor       : IFBIDUniform { };
struct IFBIDUniformSpriteAtlas : IFBIDUniform { };

/**********************************************************************************/
/* TRANSFORMS                                                                     */
/**********************************************************************************/

struct IFBIDTransform : IFBID { };

struct IFBTransform : IFBIDTransform {
    IFBVec2 translation;
    IFBVec2 scale;
    ifb_f32 rotation_radians;
};

#endif //IFB_RENDERING_HPP