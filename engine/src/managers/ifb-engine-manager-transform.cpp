#pragma once

#include <ifb-math.hpp>

#include "ifb-engine-internal-managers.hpp"

inline void
ifb_engine::transform_manager_reserve_transforms(
    const IFBEngineManagerTransform* transform_manager_ptr,
    const ifb_u32                    transform_count,
          IFBIDTransform*            transform_ids) {

    //sanity check
    ifb_macro_assert(transform_manager_ptr);
    ifb_macro_assert(transform_count);
    ifb_macro_assert(transform_ids);

    //forward declarations
    const ifb_u32 flag_group_count = transform_manager_ptr->transform_flag_group_count;

    //get the flag array
    IFBEngineManagerDataTransform transform_data;
    transform_data.query = IFBEngineManagerTransformQuery_Flags;
    ifb_engine::transform_manager_data_query(transform_data);

    //find available flags
    const ifb_u32 flags_count_found = ifb_bitwise::flags_find_bits_clear(
        flag_group_count,
        transform_count,
        transform_data.flags,
        (ifb_u32*)transform_ids);

    //sanity check, we got our transforms
    ifb_macro_assert(flags_count_found == transform_count);

    //set the flags 
    ifb_bitwise::flags_set(
        flag_group_count,
        transform_count,
        flag_array,
        (ifb_u32*)transform_ids);
}

inline void
ifb_engine::transform_manager_release_transforms(
    const IFBEngineManagerTransform* transform_manager_ptr,
    const ifb_u32                    transform_count,
    const IFBIDTransform*            transform_ids) {
 
    //sanity check
    ifb_macro_assert(transform_manager_ptr);
    ifb_macro_assert(transform_count);
    ifb_macro_assert(transform_ids);

    //forward declarations
    const ifb_u32 flag_group_count = transform_manager_ptr->transform_flag_group_count;

    //get the flag array
    IFBEngineManagerDataTransform transform_data;
    transform_data.query = IFBEngineManagerTransformQuery_Flags;
    ifb_engine::transform_manager_data_query(transform_manager_ptr, transform_data);

    //clear the flags
    ifb_bitwise::flags_clear(
        flag_group_count,
        transform_count,
        transform_data.flags,
        (ifb_u32*)transform_ids);
}

inline void
ifb_engine::transform_manager_update_translation(
    const IFBEngineManagerTransform* transform_manager_ptr,
    const ifb_u32                    transform_count,
    const IFBIDTransform*            transform_ids,
    const IFBVec2*                   transform_translations) {

    //sanity check
    ifb_macro_assert(transform_manager_ptr);
    ifb_macro_assert(transform_count);
    ifb_macro_assert(transform_ids);
    ifb_macro_assert(transform_translations);

    //get the translation array
    IFBEngineManagerDataTransform transform_data;
    transform_data.query = IFBEngineManagerTransformQuery_Translation;
    ifb_engine::transform_manager_data_query(transform_manager_ptr, transform_data);

    for (
        ifb_u32 transform_index = 0;
        transform_index < transform_count;
        ++transform_index) {

        //get the transform and translation
        const IFBIDTransform transform_id = transform_ids          [transform_index];
        const IFBVec2        translation  = transform_translations [transform_index]; 

        //update the array
        transform_data.translation[transform_id.index] = translation;
    }
}

inline void
ifb_engine::transform_manager_update_scale(
    const IFBEngineManagerTransform* transform_manager_ptr,
    const ifb_u32                    transform_count,
    const IFBIDTransform*            transform_ids,
    const IFBVec2*                   transform_scales) {

    //sanity check
    ifb_macro_assert(transform_manager_ptr);
    ifb_macro_assert(transform_count);
    ifb_macro_assert(transform_ids);
    ifb_macro_assert(transform_scales);

    //get the scale array
    IFBEngineManagerDataTransform transform_data;
    transform_data.query = IFBEngineManagerTransformQuery_Scale;
    ifb_engine::transform_manager_data_query(transform_manager_ptr, transform_data);

    for (
        ifb_u32 transform_index = 0;
        transform_index < transform_count;
        ++transform_index) {

        //get the transform and translation
        const IFBIDTransform transform_id = transform_ids    [transform_index];
        const IFBVec2        scale        = transform_scales [transform_index]; 

        //update the array
        transform_data.scale[transform_id.index] = scale;
    }
}

inline void
ifb_engine::transform_manager_update_rotation(
    const IFBEngineManagerTransform* transform_manager_ptr,
    const ifb_u32                    transform_count,
    const IFBIDTransform*            transform_ids,
    const ifb_f32*                   transform_radians) {

    //sanity check
    ifb_macro_assert(transform_manager_ptr);
    ifb_macro_assert(transform_count);
    ifb_macro_assert(transform_ids);
    ifb_macro_assert(transform_radians);

    //get the rotation array
    IFBEngineManagerDataTransform transform_data;
    transform_data.query = IFBEngineManagerTransformQuery_Rotation;
    ifb_engine::transform_manager_data_query(transform_manager_ptr, transform_data);

    for (
        ifb_u32 transform_index = 0;
        transform_index < transform_count;
        ++transform_index) {

        //get the transform and translation
        const IFBIDTransform transform_id = transform_ids     [transform_index];
        const ifb_f32        radians      = transform_radians [transform_index]; 

        //update the array
        transform_data.rotation[transform_id.index] = radians;
    }
}

inline void
ifb_engine::transform_manager_get_transforms(
    const IFBEngineManagerTransform* transform_manager_ptr,
    const ifb_u32                    transform_count,
    const IFBIDTransform*            transform_ids,      
          IFBTransform*              transforms) {

    //sanity check
    ifb_macro_assert(transform_manager_ptr);
    ifb_macro_assert(transform_count);
    ifb_macro_assert(transform_ids);
    ifb_macro_assert(transforms);

    //get the arrays
    IFBEngineManagerDataTransform transform_data;
    transform_data.query = (
        IFBEngineManagerTransformQuery_Translation |
        IFBEngineManagerTransformQuery_Scale       |
        IFBEngineManagerTransformQuery_Rotation);
    ifb_engine::transform_manager_data_query(transform_manager_ptr, transform_data);
    
    for (
        ifb_u32 transform_index = 0;
        transform_index < transform_count;
        ++transform_index) {

        //get the current transform
        const IFBIDTransform transform_id  = transform_ids [transform_index];
        IFBTransform&        transform_ref = transforms    [transform_index];

        //get the transform data 
        transform_ref.index            = transform_id.index;
        transform_ref.translation      = transform_data.translation [transform_id.index]; 
        transform_ref.scale            = transform_data.scale       [transform_id.index]; 
        transform_ref.rotation_radians = transform_data.rotation    [transform_id.index]; 
    }
}

inline ifb_void
ifb_engine::transform_manager_data_query(
    const IFBEngineManagerTransform*     transform_manager_ptr,
          IFBEngineManagerDataTransform& transform_manager_data) {

    //get the query and start of the manager data
    const IFBEngineManagerTransformQuery data_query = transform_manager_data.query;
    const ifb_address                    data_start = transform_manager_ptr->memory_start;

    //get the starting addresses of our requested data
    const ifb_address address_translation = (data_query & IFBEngineManagerTransformQuery_Translation) ? (data_start + transform_manager_ptr->offset_array_translation)      : 0;
    const ifb_address address_scale       = (data_query & IFBEngineManagerTransformQuery_Scale)       ? (data_start + transform_manager_ptr->offset_array_scale)            : 0;
    const ifb_address address_rotation    = (data_query & IFBEngineManagerTransformQuery_Rotation)    ? (data_start + transform_manager_ptr->offset_array_rotation_radians) : 0;
    const ifb_address address_flags       = (data_query & IFBEngineManagerTransformQuery_Flags)       ? (data_start + transform_manager_ptr->offset_array_flags)            : 0;

    //cast the pointers
    transform_manager_data.translation =  (IFBVec2*)address_translation;
    transform_manager_data.scale       =  (IFBVec2*)address_scale;
    transform_manager_data.rotation    =  (ifb_f32*)address_rotation;
    transform_manager_data.flags       = (ifb_byte*)address_flags;
}