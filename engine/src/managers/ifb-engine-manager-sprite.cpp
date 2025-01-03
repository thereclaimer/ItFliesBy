#pragma once

#include "ifb-engine-internal-managers.hpp"

inline void
ifb_engine::sprite_manager_reserve_sprites(
          IFBEngineManagerSprite* sprite_manager_ptr,
    const ifb_u32                 sprite_count,
    const IFBIDTag*               sprite_tag_ids,
    const IFBIDTransform*         sprite_transform_ids,
    const IFBColorTableIndex*     sprite_color_table_indexes,
          IFBIDSprite*            sprite_ids) {

    //sanity check
    ifb_macro_assert(sprite_manager_ptr);
    ifb_macro_assert(sprite_count);
    ifb_macro_assert(sprite_tag_ids);
    ifb_macro_assert(sprite_transform_ids);
    ifb_macro_assert(sprite_color_table_indexes);
    ifb_macro_assert(sprite_ids);

    //get the data
    IFBEngineManagerSpriteData sprite_data;
    sprite_data.query = IFBEngineMangerSpriteQuery_All;
    ifb_engine::sprite_manager_data_query(
        sprite_manager_ptr,
        sprite_data);

    //find available flags
    const ifb_u32 flags_count_found = ifb_bitwise::flags_find_bits_clear(
        sprite_manager_ptr->flag_group_count,
        sprite_count,
        sprite_data.flags,
        (ifb_u32*)sprite_ids);

    //sanity check, make sure we got the ids
    ifb_macro_assert(flags_count_found == sprite_count);

    //set the flags
    ifb_bitwise::flags_set(
        sprite_manager_ptr->flag_group_count,
        sprite_count,
        sprite_data.flags,
        (ifb_u32*)sprite_ids);

    //set the other properties
    for(
        ifb_u32 sprite_id_index = 0;
        sprite_id_index < sprite_count;
        ++sprite_id_index) {

        //get the current sprite properties
        const IFBIDSprite        sprite_id                = sprite_ids                 [sprite_id_index];
        const IFBIDTag           sprite_tag_id            = sprite_tag_ids             [sprite_id_index];
        const IFBIDTransform     sprite_transform_id      = sprite_transform_ids       [sprite_id_index];
        const IFBColorTableIndex sprite_color_table_index = sprite_color_table_indexes [sprite_id_index];

        //update the arrays
        sprite_data.transform_id      [sprite_id.index] = sprite_transform_id;
        sprite_data.tag_id            [sprite_id.index] = sprite_tag_id;
        sprite_data.color_table_index [sprite_id.index] = sprite_color_table_index;
    }
}

inline void
ifb_engine::sprite_manager_release_sprites(
          IFBEngineManagerSprite* sprite_manager_ptr,
    const ifb_u32                 sprite_count,
    const IFBIDSprite*            sprite_ids) {

    //sanity check
    ifb_macro_assert(sprite_manager_ptr);
    ifb_macro_assert(sprite_count);
    ifb_macro_assert(sprite_ids);

    //get the flags
    IFBEngineManagerSpriteData sprite_data;
    sprite_data.query = IFBEngineMangerSpriteQuery_Flags;
    ifb_engine::sprite_manager_data_query(
        sprite_manager_ptr,
        sprite_data);

    //clear the flags
    ifb_bitwise::flags_clear(
        sprite_manager_ptr->flag_group_count,
        sprite_count,
        sprite_data.flags,
        (ifb_u32*)sprite_ids);
}

inline void
ifb_engine::sprite_manager_get_sprites(
          IFBEngineManagerSprite* sprite_manager_ptr,
    const ifb_u32                 sprite_count,
    const IFBIDSprite*            sprite_ids,
          IFBSprite*              sprites) {

    //get the arrays
    IFBEngineManagerMemorySprite& sprite_manager_memory_ref = sprite_manager_ptr->memory;

    //get the sprite data
    IFBEngineManagerSpriteData sprite_data;
    sprite_data.query = IFBEngineMangerSpriteQuery_SpriteData;
    ifb_engine::sprite_manager_data_query(
        sprite_manager_ptr,
        sprite_data);

    for(
        ifb_u32 index = 0;
        index < sprite_count;
        ++index) {

        //get the current sprite
        IFBSprite& sprite_ref = sprites[index];
        
        //get the sprite index
        const ifb_u32 sprite_index = sprite_ids[index].index;

        //update the sprite data
        sprite_ref.index             = sprite_index;
        sprite_ref.tag_id            = sprite_data.tag_id            [sprite_index]; 
        sprite_ref.transform_id      = sprite_data.transform_id      [sprite_index]; 
        sprite_ref.color_table_index = sprite_data.color_table_index [sprite_index];         
    }
}
