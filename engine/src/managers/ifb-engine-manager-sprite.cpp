#pragma once

#include "ifb-engine-internal-managers.hpp"

inline void
ifb_engine::sprite_manager_initialize(
          IFBEngineSpriteManager* sprite_manager_ptr,
          IFBEngineMemory*        engine_memory_ptr,
    const ifb_u32                 sprite_count_minimum) {

}

inline void
ifb_engine::sprite_manager_reserve_sprites(
          IFBEngineSpriteManager* sprite_manager_ptr,
    const ifb_u32                 sprite_count,
    const IFBIDTag*               sprite_tag_ids,
    const IFBIDTransform*         sprite_transform_ids,
    const IFBColorTableIndex*     sprite_color_table_index,
          IFBIDSprite*            sprite_ids) {

}

inline void
ifb_engine::sprite_manager_release_sprites(
          IFBEngineSpriteManager* sprite_manager_ptr,
    const ifb_u32                 sprite_count,
    const IFBIDSprite*            sprite_ids) {

}

inline void
ifb_engine::sprite_manager_get_sprites(
          IFBEngineSpriteManager* sprite_manager_ptr,
    const ifb_u32                 sprite_count,
    const IFBIDSprite*            sprite_ids,
          IFBSprite*              sprites) {

    //get the arrays
    IFBEngineSpriteManagerMemory& sprite_manager_memory_ref = sprite_manager_ptr->memory;
    IFBIDTransform*     array_transform_ids       = sprite_manager_memory_get_array_transform_id     (sprite_manager_memory_ref);
    IFBIDTag*           array_tag_ids             = sprite_manager_memory_get_array_tag_id           (sprite_manager_memory_ref);
    IFBColorTableIndex* array_color_table_indexes = sprite_manager_memory_get_array_color_table_index(sprite_manager_memory_ref);

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
        sprite_ref.tag_id            = array_transform_ids      [sprite_index]; 
        sprite_ref.transform_id      = array_tag_ids            [sprite_index]; 
        sprite_ref.color_table_index = array_color_table_indexes[sprite_index];         
    }
}

inline IFBIDTransform*
ifb_engine::sprite_manager_memory_get_array_transform_id(
    IFBEngineSpriteManagerMemory& sprite_manager_memory_ref) {

    IFBIDTransform* array = ifb_macro_pointer_from_offset(
        sprite_manager_memory_ref.start,
        sprite_manager_memory_ref.offset_array_transform_id,
        IFBIDTransform);

    return(array);
}

inline IFBIDTag*
ifb_engine::sprite_manager_memory_get_array_tag_id(
    IFBEngineSpriteManagerMemory& sprite_manager_memory_ref) {

    IFBIDTag* array = ifb_macro_pointer_from_offset(
        sprite_manager_memory_ref.start,
        sprite_manager_memory_ref.offset_array_tag_id,
        IFBIDTag);

    return(array);
}

inline IFBColorTableIndex*
ifb_engine::sprite_manager_memory_get_array_color_table_index(
    IFBEngineSpriteManagerMemory& sprite_manager_memory_ref) {
    
    IFBColorTableIndex* array = ifb_macro_pointer_from_offset(
        sprite_manager_memory_ref.start,
        sprite_manager_memory_ref.offset_array_color_table_index,
        IFBColorTableIndex);

    return(array);
}

inline ifb_byte*
ifb_engine::sprite_manager_memory_get_array_flags(
    IFBEngineSpriteManagerMemory& sprite_manager_memory_ref) {

    ifb_byte* array = ifb_macro_pointer_from_offset(
        sprite_manager_memory_ref.start,
        sprite_manager_memory_ref.offset_array_flags,
        ifb_byte);

    return(array);
}