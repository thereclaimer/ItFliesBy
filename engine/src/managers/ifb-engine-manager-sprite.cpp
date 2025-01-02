#pragma once

#include "ifb-engine-internal-managers.hpp"

inline void
ifb_engine::sprite_manager_initialize(
          IFBEngineManagerSprite* sprite_manager_ptr,
          IFBEngineMemory*        engine_memory_ptr,
    const ifb_u32                 sprite_count_minimum) {

    //sanity check
    ifb_macro_assert(sprite_manager_ptr);
    ifb_macro_assert(engine_memory_ptr);
    ifb_macro_assert(sprite_count_minimum);        

    const ifb_u32 sprite_count_max = ifb_macro_align_a_to_multiple_of_b(
        sprite_count_minimum,
        sizeof(ifb_byte));

    //calculate array sizes
    const ifb_u32 size_array_tag_id            = ifb_macro_size_array(IFBIDTag,           sprite_count_max);
    const ifb_u32 size_array_transform_id      = ifb_macro_size_array(IFBIDTransform,     sprite_count_max);
    const ifb_u32 size_array_color_table_index = ifb_macro_size_array(IFBColorTableIndex, sprite_count_max);
    const ifb_u32 size_array_flags             = ifb_macro_size_array(ifb_byte,           sprite_count_max);

    //calculate offsets
    const ifb_u32 offset_array_tag_id            = 0;
    const ifb_u32 offset_array_transform_id      = size_array_tag_id;
    const ifb_u32 offset_array_color_table_index = size_array_transform_id;
    const ifb_u32 offset_array_flags             = size_array_color_table_index;    

    //calculate commit size
    const ifb_u32 commit_size = (
        size_array_tag_id            +
        size_array_transform_id      +
        size_array_color_table_index +
        size_array_flags);
    
    //do the commit
    const IFBIDCommit commit_id = ifb_engine::memory_commit(
        engine_memory_ptr,
        commit_size);

    //get the commit start
    const ifb_address commit_start = ifb_engine::memory_get_commit_address(engine_memory_ptr,commit_id);

    //initialize the memory
    IFBEngineManagerMemorySprite& sprite_manager_memory_ref = sprite_manager_ptr->memory;
    sprite_manager_memory_ref.start                          = commit_start;
    sprite_manager_memory_ref.offset_array_tag_id            = offset_array_tag_id;
    sprite_manager_memory_ref.offset_array_transform_id      = offset_array_transform_id;
    sprite_manager_memory_ref.offset_array_color_table_index = offset_array_color_table_index;
    sprite_manager_memory_ref.offset_array_flags             = offset_array_flags;
    sprite_manager_memory_ref.commit_id                      = commit_id;

    //clear the flags
    const ifb_u32 flag_group_count = sprite_count_max / IFB_BIT_FLAG_GROUP_SIZE;
    ifb_byte*     flag_group_array = ifb_engine::sprite_manager_memory_get_array_flags(sprite_manager_ptr->memory);
    for (
        ifb_u32 flag_group_index = 0;
        flag_group_index < flag_group_count;
        ++flag_group_index) {

        flag_group_array[flag_group_index] = 0;
    }

    //initialize the rest of the manager
    sprite_manager_ptr->sprite_count_max = sprite_count_max;
    sprite_manager_ptr->flag_group_count = flag_group_count; 
}

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

    //get the arrays
    IFBIDTransform*      array_transform_id      = ifb_engine::sprite_manager_memory_get_array_transform_id      (sprite_manager_ptr->memory);
    IFBIDTag*            array_tag_id            = ifb_engine::sprite_manager_memory_get_array_tag_id            (sprite_manager_ptr->memory);
    IFBColorTableIndex*  array_color_table_index = ifb_engine::sprite_manager_memory_get_array_color_table_index (sprite_manager_ptr->memory);
    ifb_byte*            array_flags             = ifb_engine::sprite_manager_memory_get_array_flags             (sprite_manager_ptr->memory);

    //find available flags
    const ifb_u32 flags_count_found = ifb_bitwise::flags_find_bits_clear(
        sprite_manager_ptr->flag_group_count,
        sprite_count,
        array_flags,
        (ifb_u32*)sprite_ids);

    //sanity check, make sure we got the ids
    ifb_macro_assert(flags_count_found == sprite_count);

    //set the flags
    ifb_bitwise::flags_set(
        sprite_manager_ptr->flag_group_count,
        sprite_count,
        array_flags,
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
        array_transform_id      [sprite_id.index] = sprite_transform_id;
        array_tag_id            [sprite_id.index] = sprite_tag_id;
        array_color_table_index [sprite_id.index] = sprite_color_table_index;
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

    //get the flags array
    ifb_byte* flags_array = ifb_engine::sprite_manager_memory_get_array_flags(sprite_manager_ptr->memory);

    //clear the flags
    ifb_bitwise::flags_clear(
        sprite_manager_ptr->flag_group_count,
        sprite_count,
        flags_array,
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
        sprite_ref.tag_id            = array_tag_ids             [sprite_index]; 
        sprite_ref.transform_id      = array_transform_ids       [sprite_index]; 
        sprite_ref.color_table_index = array_color_table_indexes [sprite_index];         
    }
}

inline IFBIDTransform*
ifb_engine::sprite_manager_memory_get_array_transform_id(
    const IFBEngineManagerMemorySprite& sprite_manager_memory_ref) {

    IFBIDTransform* array = ifb_macro_pointer_from_offset(
        sprite_manager_memory_ref.start,
        sprite_manager_memory_ref.offset_array_transform_id,
        IFBIDTransform);

    return(array);
}

inline IFBIDTag*
ifb_engine::sprite_manager_memory_get_array_tag_id(
    const IFBEngineManagerMemorySprite& sprite_manager_memory_ref) {

    IFBIDTag* array = ifb_macro_pointer_from_offset(
        sprite_manager_memory_ref.start,
        sprite_manager_memory_ref.offset_array_tag_id,
        IFBIDTag);

    return(array);
}

inline IFBColorTableIndex*
ifb_engine::sprite_manager_memory_get_array_color_table_index(
    const IFBEngineManagerMemorySprite& sprite_manager_memory_ref) {
    
    IFBColorTableIndex* array = ifb_macro_pointer_from_offset(
        sprite_manager_memory_ref.start,
        sprite_manager_memory_ref.offset_array_color_table_index,
        IFBColorTableIndex);

    return(array);
}

inline ifb_byte*
ifb_engine::sprite_manager_memory_get_array_flags(
    const IFBEngineManagerMemorySprite& sprite_manager_memory_ref) {

    ifb_byte* array = ifb_macro_pointer_from_offset(
        sprite_manager_memory_ref.start,
        sprite_manager_memory_ref.offset_array_flags,
        ifb_byte);

    return(array);
}