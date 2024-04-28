#ifndef ITFLIESBY_RENDERER_SHADER_HPP
#define ITFLIESBY_RENDERER_SHADER_HPP

#include <common/itfliesby-types.hpp>
#include <common/itfliesby-platform-api.hpp>
#include <common/itfliesby-memory.hpp>
#include "itfliesby-renderer-opengl.hpp"

struct ItfliesbyRendererShader {
    GLuint gl_program_id;
    GLuint gl_stage_id_vertex;
    GLuint gl_stage_id_fragment;
};


typedef s8 ItfliesbyRendererShaderIndex;

enum ItfliesbyRendererShaderError {
    ITFLIESBY_RENDERER_SHADER_ERROR_OKAY                             = 0x01,
    ITFLIESBY_RENDERER_SHADER_ERROR                                  = 0x80,
    ITFLIESBY_RENDERER_SHADER_ERROR_FAILED_TO_COMPILE                = 0x81,
    ITFLIESBY_RENDERER_SHADER_ERROR_FAILED_TO_COMPILE_STAGE_VERTEX   = 0x82,
    ITFLIESBY_RENDERER_SHADER_ERROR_FAILED_TO_COMPILE_STAGE_FRAGMENT = 0x83,
    ITFLIESBY_RENDERER_SHADER_ERROR_FAILED_TO_LINK                   = 0x84,
    ITFLIESBY_RENDERER_SHADER_ERROR_MAX_SHADERS                      = 0x85
};

enum ItfliesbyRendererShaderType : s32 {
    ITFLIESBY_RENDERER_SHADER_TYPE_INVALID       = -1,
    ITFLIESBY_RENDERER_SHADER_TYPE_TEXTURED_QUAD =  0,
    ITFLIESBY_RENDERER_SHADER_TYPE_SOLID_QUAD    =  1,
    ITFLIESBY_RENDERER_SHADER_TYPE_COUNT         =  2,
};


struct ItfliesbyRendererShaderStageBuffer {
    memory                       shader_stage_data;
    ItfliesbyRendererShaderError result;
};


#define ITFLIESBY_RENDERER_SHADER_UNIFORM_SOLID_QUAD_UPDATE "solid_quad_update"

struct ItfliesbyRendererShaderUniformsSolidQuad {
    GLuint gl_block_index_solid_quad_update;
    GLuint gl_solid_quad_update_ubo;
};

struct ItfliesbyRendererShaderUniforms {
    ItfliesbyRendererShaderUniformsSolidQuad solid_quad_uniforms;
};

struct ItfliesbyRendererShaderStore {

    union {
        struct {
            ItfliesbyRendererShader textured_quad;
            ItfliesbyRendererShader solid_quad;
        } types;

        ItfliesbyRendererShader shaders[ITFLIESBY_RENDERER_SHADER_TYPE_COUNT];
    };

    ItfliesbyRendererShaderUniforms uniforms;
};




#endif //ITFLIESBY_RENDERER_SHADER_HPP