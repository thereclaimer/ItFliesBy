#ifndef ITFLIESBY_RENDERER_HPP
#define ITFLIESBY_RENDERER_HPP

#include "itfliesby-types.hpp"
#include "math/itfliesby-math.hpp"

typedef void  ItfliesbyRenderer;
typedef void* ItfliesbyRendererHandle;

#define ITFLIESBY_RENDERER_MEMORY_SIZE_BYTES                       ITFLIESBY_MATH_MEGABYTES(64)
#define ITFLIESBY_RENDERER_MEMORY_PARTITION_CORE_SIZE_BYTES        ITFLIESBY_MATH_KILOBYTES(2)
#define ITFLIESBY_RENDERER_MEMORY_ALLOCATOR_CORE_SYSTEM_SIZE_BYTES ITFLIESBY_MATH_KILOBYTES(1)

typedef s8                ItfliesbyRendererShaderIndex;
typedef s8                ItfliesbyRendererSolidQuadId;
typedef s32               ItfliesbyQuadId;
typedef ItfliesbyMathMat3 ItfliesbyRendererModelTransform;

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
// COLOR
//----------------------------------------------------------------

struct ItfliesbyRendererColorHex {
    union {

        struct {
            u8 r;
            u8 g;
            u8 b;
            u8 a;
        };
    
        u32 value;
    };
};

#define ITFLIESBY_RENDERER_QUAD_COLOR_NORMALIZING_FACTOR 0.00392157

struct ItfliesbyRendererColorNormalized {
    f32 r;
    f32 g;
    f32 b;
    f32 a;
};

inline ItfliesbyRendererColorNormalized
itfliesby_renderer_color_normalize(
    ItfliesbyRendererColorHex color_hex) {

    ItfliesbyRendererColorNormalized color_normalized = {0};
    
    color_normalized.r = color_hex.r * ITFLIESBY_RENDERER_QUAD_COLOR_NORMALIZING_FACTOR;  
    color_normalized.g = color_hex.g * ITFLIESBY_RENDERER_QUAD_COLOR_NORMALIZING_FACTOR; 
    color_normalized.b = color_hex.b * ITFLIESBY_RENDERER_QUAD_COLOR_NORMALIZING_FACTOR; 
    color_normalized.a = color_hex.a * ITFLIESBY_RENDERER_QUAD_COLOR_NORMALIZING_FACTOR;

    return(color_normalized);
}

inline ItfliesbyRendererColorHex
itfliesby_renderer_color_hex(
 ItfliesbyRendererColorNormalized color_normal) {

    ItfliesbyRendererColorHex color_hex = {0};
    
    color_hex.r = (u8)(color_normal.r * 255);  
    color_hex.g = (u8)(color_normal.g * 255); 
    color_hex.b = (u8)(color_normal.b * 255); 
    color_hex.a = (u8)(color_normal.a * 255);

    return(color_hex);
}

//----------------------------------------------------------------
// SOLID QUAD
//----------------------------------------------------------------

struct ItfliesbyRendererSolidQuadUpdate {
    f32                       transform[9];
    ItfliesbyRendererColorHex color;
};

#define ITFLIESBY_RENDERER_SOLID_QUAD_COUNT_MAX 128

struct ItfliesbyRendererSolidQuadUpdateBatch {
    ItfliesbyRendererSolidQuadUpdate batch[ITFLIESBY_RENDERER_SOLID_QUAD_COUNT_MAX];
    u8                               count;
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
itfliesby_renderer_render(
    ItfliesbyRendererHandle renderer); 

//----------------------------------------------------------------
// SHADERS
//----------------------------------------------------------------

enum ItfliesbyRendererShaderType {
    ITFLIESBY_RENDERER_SHADER_TYPE_INVALID       = -1,
    ITFLIESBY_RENDERER_SHADER_TYPE_TEXTURED_QUAD =  0,
    ITFLIESBY_RENDERER_SHADER_TYPE_SOLID_QUAD    =  1,
    ITFLIESBY_RENDERER_SHADER_TYPE_TEST          =  2,
    ITFLIESBY_RENDERER_SHADER_TYPE_COUNT         =  3,
};

api ItfliesbyRendererShaderIndex
itfliesby_renderer_shader_compile_and_link(
    ItfliesbyRendererHandle             renderer,
    ItfliesbyRendererShaderType         shader_type,
    ItfliesbyRendererShaderStageBuffer* shader_stage_buffer_vertex,
    ItfliesbyRendererShaderStageBuffer* shader_stage_buffer_fragment);

api void
itfliesby_renderer_shader_destroy(
    ItfliesbyRendererHandle      renderer,
    ItfliesbyRendererShaderIndex shader_index);

api b8
itfliesby_renderer_ready(
    ItfliesbyRenderer* renderer); 

//----------------------------------------------------------------
// QUADS
//----------------------------------------------------------------

api void
itfliesby_renderer_quad_solid_quads_batch_update(
    ItfliesbyRendererHandle                renderer,
    ItfliesbyRendererSolidQuadUpdateBatch* solid_quad_update_batch); 

//----------------------------------------------------------------
// SIMPLE QUAD
//----------------------------------------------------------------

#define ITFLIESBY_RENDERER_TEST_BATCH_COUNT_MAX 32

struct ItfliesbyRendererSimpleQuad {
    ItfliesbyMathMat3                 transform;
    ItfliesbyRendererColorNormalized  color;
};

api u32
itfliesby_renderer_simple_quad_push(
          ItfliesbyRenderer*          renderer,
    const ItfliesbyRendererSimpleQuad simple_quad); 

api void
itfliesby_renderer_simple_quad_push_batch(
          ItfliesbyRendererHandle      renderer,
    const size_t                       simple_quad_count,
    const ItfliesbyRendererSimpleQuad* simple_quad,
          u32*                         simple_quad_indices);

//----------------------------------------------------------------
// TEXTURES
//----------------------------------------------------------------

enum ItfliesbyRendererTextureSpriteCharacterType : s32 {
    ITFLIESBY_RENDERER_TEXTURE_SPRITE_CHARACTER_TYPE_INVALID            = -1,
    ITFLIESBY_RENDERER_TEXTURE_SPRITE_CHARACTER_TYPE_CALIBRATION_CONNOR =  0,
    ITFLIESBY_RENDERER_TEXTURE_SPRITE_CHARACTER_TYPE_CALIBRATION_JIG    =  1,
    ITFLIESBY_RENDERER_TEXTURE_SPRITE_CHARACTER_TYPE_COUNT              =  2
};

api void
itfliesby_renderer_texture_sprite_character_load(
    ItfliesbyRendererHandle                     renderer,
    ItfliesbyRendererTextureSpriteCharacterType sprite_character_type,
    u32                                         sprite_character_data_width_bytes,
    u32                                         sprite_character_data_height_bytes,
    memory                                      sprite_character_data);

#endif //ITFLIESBY_RENDERER_HPP