#pragma once

#include "ifb-engine-internal-managers.hpp"
#include "ifb-engine-internal-context.hpp"

inline const IFBIDTag
ifb_engine::tag_manager_reserve_tag(
    const IFBEngineManagerTag* tag_manager_ptr,
    const ifb_cstr             tag_c_str) {

    //cache constants
    const ifb_u32 tag_c_str_length = tag_manager_ptr->tag_c_str_length;
    const ifb_u32 tag_count        = tag_manager_ptr->tag_count_max;

    //get the pointers
    IFBEngineManagerDataTag tag_data;
    ifb_engine::tag_manager_get_pointer_hash_array (tag_manager_ptr,tag_data);
    ifb_engine::tag_manager_get_pointer_char_buffer(tag_manager_ptr,tag_data);

    //find the next available index
    IFBIDTag tag_id;
    const ifb_b8 can_create_tag = ifb_hash::find_next_clear_value(
        tag_data.hash_array,
        tag_count,
        tag_id.index);

    //santiy check
    ifb_macro_assert(can_create_tag);

    //hash the string and update the table
    tag_data.hash_array[tag_id.index] = ifb_hash::get_hash(
        tag_c_str,
        tag_c_str_length);

    //get the destination address of our new tag
    ifb_char* ptr_tag_c_str_destination = &tag_data.char_buffer[tag_id.index * tag_c_str_length];
 
    //copy the tag value
    for (
        ifb_u32 char_index = 0;
                char_index < tag_c_str_length;
              ++char_index) {

        ptr_tag_c_str_destination[char_index] = tag_c_str[char_index];
    }

    //we're done
    return(tag_id);
}

inline ifb_void
ifb_engine::tag_manager_release_tag(
    const IFBEngineManagerTag* tag_manager_ptr,
    const IFBIDTag&            tag_id) {

    //get the hash array
    IFBEngineManagerDataTag tag_data;
    ifb_engine::tag_manager_get_pointer_hash_array(tag_manager_ptr,tag_data);

    //clear the value
    tag_data.hash_array[tag_id.index] = {0};
}

inline const ifb_cstr
ifb_engine::tag_manager_get_tag_c_str(
    const IFBEngineManagerTag* tag_manager_ptr,
    const IFBIDTag&            tag_id) {

    //get the char buffer
    IFBEngineManagerDataTag tag_data;
    ifb_engine::tag_manager_get_pointer_char_buffer(tag_manager_ptr,tag_data);

    //get the start of the tag
    const ifb_u32  tag_char_index = tag_id.index * tag_manager_ptr->tag_c_str_length;
    const ifb_cstr tag_c_str      = (ifb_cstr)&tag_data.char_buffer[tag_char_index];

    //we're done
    return(tag_c_str);
}

inline const IFBHash
ifb_engine::tag_manager_get_hash(
    const IFBEngineManagerTag* tag_manager_ptr,
    const IFBIDTag&            tag_id) {

    //get the hash array
    IFBEngineManagerDataTag tag_data;
    ifb_engine::tag_manager_get_pointer_hash_array(tag_manager_ptr,tag_data);

    //get the hash
    const IFBHash tag_hash = tag_data.hash_array[tag_id.index];

    //we're done
    return(tag_hash);
}

inline ifb_void
ifb_engine::tag_manager_get_pointer_char_buffer(
    const IFBEngineManagerTag*     tag_manager_ptr,
          IFBEngineManagerDataTag& tag_manager_data_ref) {

    const ifb_address data_start = 
        tag_manager_ptr->memory_start +
        tag_manager_ptr->offset_char_buffer;
    
    tag_manager_data_ref.char_buffer = (ifb_char*)data_start;   
}

inline ifb_void
ifb_engine::tag_manager_get_pointer_hash_array(
    const IFBEngineManagerTag*     tag_manager_ptr,
          IFBEngineManagerDataTag& tag_manager_data_ref) {

    const ifb_address data_start = 
        tag_manager_ptr->memory_start +
        tag_manager_ptr->offset_hash_array;
    
    tag_manager_data_ref.hash_array = (IFBHash*)data_start;
}