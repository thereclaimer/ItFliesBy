#pragma once

#include "ifb-engine-internal-managers.hpp"

inline ifb_void
ifb_engine::manager_data_query_tag(
    const IFBEngineManagerDataQueryTag data_query_tag,
    const IFBEngineManagerTag*         manager_tag,
          IFBEngineManagerDataTag&     data_tag) {


}

inline ifb_void
ifb_engine::manager_data_query_arena(
    const IFBEngineManagerDataQueryArena data_query_arena,
    const IFBEngineManagerArena*         manager_arena,
          IFBEngineManagerDataArena&     data_arena) {


}

inline ifb_void
ifb_engine::manager_data_query_graphics(
    const IFBEngineManagerDataQueryGraphics data_query_graphics,
    const IFBEngineManagerGraphics*         manager_graphics,
          IFBEngineManagerDataGraphics&     data_graphics) {

    //get the addresses of our requested data
    const ifb_address address_start    = manager_tag->memory_start;
    const ifb_address address_window   = (data_query & IFBEngineMangerGraphicsQuery_Window)   ? (address_start + manager_graphics.offset_window)        : 0;
    const ifb_address address_viewport = (data_query & IFBEngineMangerGraphicsQuery_Monitors) ? (address_start + manager_graphics.offset_viewport)      : 0;
    const ifb_address address_monitors = (data_query & IFBEngineMangerGraphicsQuery_Viewport) ? (address_start + manager_graphics.offset_monitor_array) : 0;

    //cast the pointers
    data_graphics.window   =     (IFBWindow*)address_window;
    data_graphics.viewport = (IFBGLViewport*)address_viewport;
    data_graphics.monitors =    (IFBMonitor*)address_monitors;
}

inline ifb_void
ifb_engine::manager_data_query_shader(
    const IFBEngineManagerDataQueryShader data_query_shader,
    const IFBEngineManagerShader*         manager_shader,
          IFBEngineManagerDataShader&     data_shader) {

    const ifb_address data_start = manager_shader->memory_start;
}

inline ifb_void
ifb_engine::manager_data_query_transform(
    const IFBEngineManagerDataQueryTransform data_query_transform,
    const IFBEngineManagerTransform*         manager_transform,
          IFBEngineManagerDataTransform&     data_transform) {

    //get the starting addresses of our requested data
    const ifb_address address_start       = manager_transform->memory_start;
    const ifb_address address_translation = (data_query & IFBEngineManagerTransformQuery_Translation) ? (address_start + manager_transform->offset_array_translation)      : 0;
    const ifb_address address_scale       = (data_query & IFBEngineManagerTransformQuery_Scale)       ? (address_start + manager_transform->offset_array_scale)            : 0;
    const ifb_address address_rotation    = (data_query & IFBEngineManagerTransformQuery_Rotation)    ? (address_start + manager_transform->offset_array_rotation_radians) : 0;
    const ifb_address address_flags       = (data_query & IFBEngineManagerTransformQuery_Flags)       ? (address_start + manager_transform->offset_array_flags)            : 0;

    //cast the pointers
    data_transform.translation =  (IFBVec2*)address_translation;
    data_transform.scale       =  (IFBVec2*)address_scale;
    data_transform.rotation    =  (ifb_f32*)address_rotation;
    data_transform.flags       = (ifb_byte*)address_flags;
}

inline ifb_void
ifb_engine::manager_data_query_sprite(
    const IFBEngineManagerDataQuerySprite data_query_sprite,
    const IFBEngineManagerSprite*         manager_sprite,
          IFBEngineManagerDataSprite&     data_sprite) {

    //get the addresses of our requested data
    const ifb_address address_start             = manager_sprite->memory_start;
    const ifb_address address_tag_id            = (data_query & IFBEngineMangerSpriteQuery_TagId)           ? (address_start + manager_sprite->offset_array_tag_id)            : 0;
    const ifb_address address_transform_id      = (data_query & IFBEngineMangerSpriteQuery_TransformId)     ? (address_start + manager_sprite->offset_array_transform_id)      : 0;
    const ifb_address address_color_table_index = (data_query & IFBEngineMangerSpriteQuery_ColorTableIndex) ? (address_start + manager_sprite->offset_array_color_table_index) : 0;
    const ifb_address address_flags             = (data_query & IFBEngineMangerSpriteQuery_Flags)           ? (address_start + manager_sprite->offset_array_flags)             : 0;

    //cast the pointers
    sprite_manager_data_ref.tag_id            =           (IFBIDTag*)address_tag_id;
    sprite_manager_data_ref.transform_id      =     (IFBIDTransform*)address_transform_id;
    sprite_manager_data_ref.color_table_index = (IFBColorTableIndex*)address_color_table_index;
    sprite_manager_data_ref.flags             =           (ifb_byte*)address_flags;
}
