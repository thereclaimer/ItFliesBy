#ifndef IFB_ENGINE_INTERNAL_RENDERING_HPP
#define IFB_ENGINE_INTERNAL_RENDERING_HPP

#include "ifb-engine.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBEngineRenderer;
struct IFBEngineColorTable;
struct IFBEngineSpriteShaderUniformData;
struct IFBEngineSpriteShader;

struct IFBGHNDEngineRenderer             : IFBGHND;
struct IFBGHNDEngineColorTable           : IFBGHND;
struct IFBGHNDEngineSpriteShader         : IFBGHND;
struct IFBGHNDEngineSpriteShaderUniforms : IFBGHND;

/**********************************************************************************/
/* VERTICES                                                                       */
/**********************************************************************************/

struct IFBEngineSpriteVertex {
    IFBIDTransform           transform_id;
    IFBEngineColorTableIndex color_table_index;
};

#define IFB_ENGINE_SPRITE_VERTEX_DATA_SIZE (sizeof(IFBMat3) + sizeof(IFBEngineColorTableIndex))

struct IFBEngineSpriteVertexData {
    union {
        struct {
            IFBMat3                  transform_matrix;
            IFBEngineColorTableIndex color_table_index;
        };
        ifb_byte array[IFB_ENGINE_SPRITE_VERTEX_DATA_SIZE]
    };
};

namespace ifb_engine {

    ifb_void
    rendering_vertex_encode_sprite_to_buffer(
        const ifb_u32                    sprite_vertex_count,
        const IFBEngineSpriteVertexData* sprite_vertex_array,
              ifb_memory                 sprite_vertex_buffer);

};

/**********************************************************************************/
/* SPRITE SHADER                                                                  */
/**********************************************************************************/




struct IFBEngineSpriteShaderUniformData {
    IFBEngineColorTable     color_table;
    IFBVec2                 unit_sprite_origin;
    IFBVec2                 unit_sprite_dimensions;
};

struct IFBEngineSpriteShaderUniforms {
    IFBIDUniformColor       color_table;
    IFBIDUniformVec2        unit_sprite_origin;
    IFBIDUniformVec2        unit_sprite_dimensions;
    IFBIDUniformSpriteAtlas sprite_atlas;
};

struct IFBEngineSpriteShader : IFBIDShader {
    IFBGHNDEngineSpriteShaderUniforms  uniform_handle;
    IFBGHNDEngineColorTable            color_table_handle;
};

namespace ifb_engine {

    sprite_shader_initialize();
};

/**********************************************************************************/
/* RENDERER                                                                       */
/**********************************************************************************/

struct IFBEngineRendererHandles {
    IFBGHNDEngineColorTable   color_table;
    IFBGHNDEngineSpriteShader sprite_shader;
};

struct IFBEngineRenderer {
    IFBEngineRendererHandles handles;
};

#endif //IFB_ENGINE_INTERNAL_RENDERING_HPP