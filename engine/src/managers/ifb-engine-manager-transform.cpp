#pragma once

#include <ifb-math.hpp>

#include "ifb-engine-internal-managers.hpp"

inline void
ifb_engine::transform_manager_initialize(
          IFBEngineTransformManager* transform_manager_ptr,
          IFBEngineMemory*           engine_memory_ptr,
    const ifb_u32                    transform_count_minimum) {

    ifb_macro_assert(transform_manager_ptr);
    ifb_macro_assert(engine_memory_ptr);
    ifb_macro_assert(transform_count_minimum);

    const ifb_u32 transform_count_max = ifb_macro_align_a_to_multiple_of_b(
        transform_count_minimum,
        sizeof(ifb_byte));

    //calculate array sizes
    const ifb_u32 size_array_translation = ifb_macro_size_array(IFBVec2,  transform_count_max);
    const ifb_u32 size_array_scale       = ifb_macro_size_array(IFBVec2,  transform_count_max);
    const ifb_u32 size_array_rotation    = ifb_macro_size_array(ifb_f32,  transform_count_max);
    const ifb_u32 size_array_flags       = ifb_macro_size_array(ifb_byte, transform_count_max);

    //calculate offsets
    const ifb_u32 offset_array_translation = 0;
    const ifb_u32 offset_array_scale       = size_array_translation;
    const ifb_u32 offset_array_rotation    = size_array_scale;
    const ifb_u32 offset_array_flags       = size_array_rotation;

    //calculate commit size
    const ifb_u32 commit_size = (
        size_array_translation +
        size_array_scale       +
        size_array_rotation    +
        size_array_flags);

    //do the commit
    const IFBIDCommit commit_id = ifb_engine::memory_commit(
        engine_memory_ptr,
        commit_size);

    //clear the memory
    ifb_ptr           commit_ptr         = ifb_engine::memory_get_commit_pointer(engine_memory_ptr,commit_id);
    const ifb_address commit_start       = ifb_engine::memory_get_commit_address(engine_memory_ptr,commit_id);
    const ifb_u32     commit_size_actual = ifb_engine::memory_get_commit_size   (engine_memory_ptr,commit_id);
    memset(commit_ptr,0,commit_size_actual);

    //initialize the memory
    IFBEngineTransformManagerMemory& manager_memory_ref = transform_manager_ptr->memory;
    manager_memory_ref.start                         = commit_start;
    manager_memory_ref.offset_array_translation      = offset_array_translation;
    manager_memory_ref.offset_array_scale            = offset_array_scale;
    manager_memory_ref.offset_array_rotation_radians = offset_array_rotation;
    manager_memory_ref.offset_array_flags            = offset_array_flags;
    manager_memory_ref.commit_id                     = commit_id;

    //initialize the rest of the manager properties
    transform_manager_ptr->transform_count_max        = transform_count_max;
    transform_manager_ptr->transform_flag_group_count = transform_count_max / IFB_BIT_FLAG_GROUP_SIZE;
}

inline void
ifb_engine::transform_manager_flags_find_next_available(
    const ifb_byte*                  flag_array,
    const ifb_u32                    flag_group_count,           
    const ifb_u32                    transform_count,
          IFBIDTransform*            transform_ids) {

    //find available flags
    const ifb_u32 flags_count_found = ifb_bitwise::flags_find_bits_clear(
        flag_group_count,
        transform_count,
        flag_array,
        (ifb_u32*)transform_ids);

    //sanity check, we got our transforms
    ifb_macro_assert(flags_count_found == transform_count);
}

inline void
ifb_engine::transform_manager_flags_set(
          ifb_byte*       flag_array,
    const ifb_u32         flag_group_count,           
    const ifb_u32         transform_count,
    const IFBIDTransform* transform_ids) {

    ifb_bitwise::flags_set(
        flag_group_count,
        transform_count,
        flag_array,
        (ifb_u32*)transform_ids);
}

inline void
ifb_engine::transform_manager_flags_clear(
          ifb_byte*     flag_array,
    const ifb_u32         flag_group_count,           
    const ifb_u32         transform_count,
    const IFBIDTransform* transform_ids) {

    ifb_bitwise::flags_clear(
        flag_group_count,
        transform_count,
        flag_array,
        (ifb_u32*)transform_ids);
}

inline void
ifb_engine::transform_manager_reserve_transforms(
          IFBEngineTransformManager* transform_manager_ptr,
    const ifb_u32                    transform_count,
          IFBIDTransform*            transform_ids) {

    //sanity check
    ifb_macro_assert(transform_manager_ptr);
    ifb_macro_assert(transform_count);
    ifb_macro_assert(transform_ids);

    //forward declarations
    const ifb_u32 flag_group_count = transform_manager_ptr->transform_flag_group_count;

    //get the flag array
    ifb_byte* flag_array = ifb_engine::transform_manager_memory_get_array_flags(transform_manager_ptr->memory);

    //get the transform ids
    ifb_engine::transform_manager_flags_find_next_available(
        flag_array,
        flag_group_count,
        transform_count,
        transform_ids);

    //set the flags 
    ifb_engine::transform_manager_flags_set(
        flag_array,
        flag_group_count,
        transform_count,
        transform_ids);
}

inline void
ifb_engine::transform_manager_release_transforms(
          IFBEngineTransformManager* transform_manager_ptr,
    const ifb_u32                    transform_count,
    const IFBIDTransform*            transform_ids) {
 
    //sanity check
    ifb_macro_assert(transform_manager_ptr);
    ifb_macro_assert(transform_count);
    ifb_macro_assert(transform_ids);

    //forward declarations
    const ifb_u32 flag_group_count = transform_manager_ptr->transform_flag_group_count;

    //get the flag array
    ifb_byte* flag_array = ifb_engine::transform_manager_memory_get_array_flags(transform_manager_ptr->memory);

    //set the flags 
    ifb_engine::transform_manager_flags_set(
        flag_array,
        flag_group_count,
        transform_count,
        transform_ids);
}

inline void
ifb_engine::transform_manager_update_translation(
          IFBEngineTransformManager* transform_manager_ptr,
    const ifb_u32                    transform_count,
    const IFBIDTransform*            transform_ids,
    const IFBVec2*                   transform_translations) {

    //sanity check
    ifb_macro_assert(transform_manager_ptr);
    ifb_macro_assert(transform_count);
    ifb_macro_assert(transform_ids);
    ifb_macro_assert(transform_translations);

    //get the translation array
    IFBVec2* translation_array = ifb_engine::transform_manager_memory_get_array_translation(
        transform_manager_ptr->memory);

    for (
        ifb_u32 transform_index = 0;
        transform_index < transform_count;
        ++transform_index) {

        //get the transform and translation
        const IFBIDTransform transform_id = transform_ids     [transform_index];
        const IFBVec2        translation  = translation_array [transform_index]; 

        //update the array
        translation_array[transform_id.index] = translation;
    }
}

inline void
ifb_engine::transform_manager_update_scale(
          IFBEngineTransformManager* transform_manager_ptr,
    const ifb_u32                    transform_count,
    const IFBIDTransform*            transform_ids,
    const IFBVec2*                   transform_scales) {

    //sanity check
    ifb_macro_assert(transform_manager_ptr);
    ifb_macro_assert(transform_count);
    ifb_macro_assert(transform_ids);
    ifb_macro_assert(transform_scales);

    //get the scale array
    IFBVec2* scale_array = ifb_engine::transform_manager_memory_get_array_scale(
        transform_manager_ptr->memory);

    for (
        ifb_u32 transform_index = 0;
        transform_index < transform_count;
        ++transform_index) {

        //get the transform and translation
        const IFBIDTransform transform_id = transform_ids [transform_index];
        const IFBVec2        scale        = scale_array   [transform_index]; 

        //update the array
        scale_array[transform_id.index] = scale;
    }
}

inline void
ifb_engine::transform_manager_update_rotation(
          IFBEngineTransformManager* transform_manager_ptr,
    const ifb_u32                    transform_count,
    const IFBIDTransform*            transform_ids,
    const ifb_f32*                   transform_radians) {

    //sanity check
    ifb_macro_assert(transform_manager_ptr);
    ifb_macro_assert(transform_count);
    ifb_macro_assert(transform_ids);
    ifb_macro_assert(transform_radians);

    //get the scale array
    ifb_f32* radians_array = ifb_engine::transform_manager_memory_get_array_rotation_radians(
        transform_manager_ptr->memory);

    for (
        ifb_u32 transform_index = 0;
        transform_index < transform_count;
        ++transform_index) {

        //get the transform and translation
        const IFBIDTransform transform_id = transform_ids     [transform_index];
        const ifb_f32        radians      = transform_radians [transform_index]; 

        //update the array
        radians_array[transform_id.index] = radians;
    }
}

inline void
ifb_engine::transform_manager_get_transforms(
          IFBEngineTransformManager* transform_manager_ptr,
    const ifb_u32                    transform_count,
    const IFBIDTransform*            transform_ids,      
          IFBTransform*              transforms) {

    //sanity check
    ifb_macro_assert(transform_manager_ptr);
    ifb_macro_assert(transform_count);
    ifb_macro_assert(transform_ids);
    ifb_macro_assert(transforms);

    //get the arrays
    const IFBVec2* array_translation = ifb_engine::transform_manager_memory_get_array_translation      (transform_manager_ptr->memory);
    const IFBVec2* array_scale       = ifb_engine::transform_manager_memory_get_array_scale            (transform_manager_ptr->memory);
    const ifb_f32* array_radians     = ifb_engine::transform_manager_memory_get_array_rotation_radians (transform_manager_ptr->memory);

    for (
        ifb_u32 transform_index = 0;
        transform_index < transform_count;
        ++transform_index) {

        //get the current transform id and matrix
        const IFBIDTransform transform_id  = transform_ids [transform_index];
        IFBTransform&        transform_ref = transforms    [transform_index];

        //get the transform data 
        transform_ref.index            = transform_id.index;
        transform_ref.translation      = array_translation [transform_id.index]; 
        transform_ref.scale            = array_scale       [transform_id.index]; 
        transform_ref.rotation_radians = array_radians     [transform_id.index]; 
    }
}

inline IFBVec2*
ifb_engine::transform_manager_memory_get_array_translation(
    const IFBEngineTransformManagerMemory& transform_manager_memory_ref) {

    IFBVec2* array_ptr = ifb_macro_pointer_from_offset(
        transform_manager_memory_ref.start,
        transform_manager_memory_ref.offset_array_translation,
        IFBVec2);

    return(array_ptr);    
}

inline IFBVec2*
ifb_engine::transform_manager_memory_get_array_scale(
    const IFBEngineTransformManagerMemory& transform_manager_memory_ref) {

    IFBVec2* array_ptr = ifb_macro_pointer_from_offset(
        transform_manager_memory_ref.start,
        transform_manager_memory_ref.offset_array_scale,
        IFBVec2);

    return(array_ptr);   

}

inline ifb_f32*
ifb_engine::transform_manager_memory_get_array_rotation_radians(
    const IFBEngineTransformManagerMemory& transform_manager_memory_ref) {

    ifb_f32* array_ptr = ifb_macro_pointer_from_offset(
        transform_manager_memory_ref.start,
        transform_manager_memory_ref.offset_array_rotation_radians,
        ifb_f32);

    return(array_ptr);   
}

inline ifb_byte*
ifb_engine::transform_manager_memory_get_array_flags(
    const IFBEngineTransformManagerMemory& transform_manager_memory_ref) {

    ifb_byte* array_ptr = ifb_macro_pointer_from_offset(
        transform_manager_memory_ref.start,
        transform_manager_memory_ref.offset_array_flags,
        ifb_byte);

    return(array_ptr);  
}

