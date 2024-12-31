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
struct IFBIDShader        : IFBID { };

struct IFBIDBufferVertex  : IFBID { };
struct IFBIDBufferElement : IFBID { };

struct IFBIDUniformU32    : IFBID { }; 
struct IFBIDUniformF32    : IFBID { };
struct IFBIDUniformVec2   : IFBID { };
struct IFBIDUniformVec3   : IFBID { };
struct IFBIDUniformMat3   : IFBID { };
struct IFBIDUniformMat4   : IFBID { };

//--------------------
// structs
//--------------------
struct IFBShader;

struct IFBBufferVertex;
struct IFBBufferElement;

struct IFBUniformU32;
struct IFBUniformF32;
struct IFBUniformVec2;
struct IFBUniformVec3;
struct IFBUniformMat3;
struct IFBUniformMat4;

/**********************************************************************************/
/* SHADERS                                                                        */
/**********************************************************************************/

struct IFBShader {
    IFBIDShader              id;
    IFBIDTag                 tag;
    IFBGLShaderProgram       gl_shader_program;
    IFBGLShaderStageVertex   gl_shader_stage_vertex;
    IFBGLShaderStageFragment gl_shader_stage_fragment;
};

/**********************************************************************************/
/* BUFFERS                                                                        */
/**********************************************************************************/

struct IFBBufferVertex {
    IFBIDBufferVertex id;
    IFBIDTag          tag;
    ifb_u32           size;
    ifb_u32           stride;
    ifb_handle        data_handle;
};

struct IFBBufferElement {
    IFBIDBufferElement id;
    IFBIDTag           tag;
    ifb_u32            count;
    ifb_u32*           data;
};

/**********************************************************************************/
/* UNIFORMS                                                                       */
/**********************************************************************************/

struct IFBUniformU32 {
    IFBIDUniformU32 id;    
    IFBGLUniformU32 gl_uniform_u32;    
    IFBIDShader     shader;
    IFBIDTag        tag;
    ifb_u32         value;
};

struct IFBUniformF32 {
    IFBIDUniformF32 id;
    IFBGLUniformF32 gl_uniform_f32;
    IFBIDShader     shader;
    IFBIDTag        tag;
    ifb_f32         value;
};

struct IFBUniformVec2 {
    IFBIDUniformVec2    id;    
    IFBGLUniformVec2F32 gl_uniform_vec2;    
    IFBIDShader         shader;
    IFBIDTag            tag;
    ifb_f32             value[2];
};

struct IFBUniformVec3 {
    IFBIDUniformVec3    id;
    IFBGLUniformVec3F32 gl_uniform_vec3;
    IFBIDShader         shader;
    IFBIDTag            tag;
    ifb_f32             value[3];

};

struct IFBUniformMat3 {
    IFBIDUniformMat3    id;
    IFBGLUniformMat3F32 gl_uniform_mat3;
    IFBIDShader         shader;
    IFBIDTag            tag;
    ifb_f32             value[9];
};

struct IFBUniformMat4 {
    IFBIDUniformMat4    id;
    IFBGLUniformMat4F32 gl_uniform_mat4;
    IFBIDShader         shader;
    IFBIDTag            tag;
    ifb_f32             value[16];
};

#endif //IFB_RENDERING_HPP