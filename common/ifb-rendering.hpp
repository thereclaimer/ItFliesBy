#ifndef IFB_RENDERING_HPP
#define IFB_RENDERING_HPP

#include "ifb-types.hpp"
#include "ifb-gl.hpp"

struct IFBIDShader : IFBID { };

struct IFBShader {
    IFBIDShader              id;
    IFBGLShaderProgram       gl_shader_program;
    IFBGLShaderStageVertex   gl_shader_stage_vertex;
    IFBGLShaderStageFragment gl_shader_stage_fragment;
};

struct IFBIDBuffer;

struct IFBBuffer {
    IFBIDBuffer id;
    ifb_u32     size;
    ifb_handle  data_handle;
};

#endif //IFB_RENDERING_HPP