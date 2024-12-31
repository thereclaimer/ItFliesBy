#ifndef IFB_ENGINE_INTERNAL_RENDERING_HPP
#define IFB_ENGINE_INTERNAL_RENDERING_HPP

#include "ifb-engine.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

#define IFB_ENGINE_COLOR_TABLE_COUNT 16

struct IFBEngineRenderer;
struct IFBEngineColorTable;
struct IFBEngineSpriteShaderUniformData;
struct IFBEngineSpriteShader;

struct IFBGHNDEngineRenderer             : IFBGHND;
struct IFBGHNDEngineColorTable           : IFBGHND;
struct IFBGHNDEngineSpriteShader         : IFBGHND;
struct IFBGHNDEngineSpriteShaderUniforms : IFBGHND;

/**********************************************************************************/
/* SPRITE SHADER                                                                  */
/**********************************************************************************/

struct IFBEngineSpriteVertex {
    IFBIDTransform           transform_id;
    IFBEngineColorTableIndex color_table_index;
};

struct IFBEngineSpriteVertexData {
    IFBMat3  transform_matrix;
    IFBColor color;
    IFBVec2  sprite_coordinates;
};

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