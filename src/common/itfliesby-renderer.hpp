#ifndef ITFLIESBY_RENDERER_HPP
#define ITFLIESBY_RENDERER_HPP

#include "itfliesby-types.hpp"
#include "math/itfliesby-math.hpp"

typedef void  ItfliesbyRenderer;
typedef void* ItfliesbyRendererHandle;

#define ITFLIESBY_RENDERER_MEMORY_SIZE_BYTES ITFLIESBY_MATH_MEGABYTES(64)

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

struct ItfliesbyRendererShaderStageBuffer {
    memory                       shader_stage_data;
    ItfliesbyRendererShaderError result;
};

//----------------------------------------------------------------
// RENDERER
//----------------------------------------------------------------

api ItfliesbyRendererHandle
itfliesby_renderer_create_and_init(
    ItfliesbyPlatformApi platform,
    memory               renderer_memory,
    u64                  renderer_memory_size_bytes);

api void
itfliesby_renderer_update_and_render(
    ItfliesbyRendererHandle renderer); 

//----------------------------------------------------------------
// SHADERS
//----------------------------------------------------------------

api ItfliesbyRendererShaderIndex
itfliesby_renderer_shader_compile_and_link(
    ItfliesbyRendererHandle             renderer,
    ItfliesbyRendererShaderStageBuffer* shader_stage_buffer_vertex,
    ItfliesbyRendererShaderStageBuffer* shader_stage_buffer_fragment);

api void
itfliesby_renderer_shader_destroy(
    ItfliesbyRendererHandle      renderer,
    ItfliesbyRendererShaderIndex shader_index);


#endif //ITFLIESBY_RENDERER_HPP