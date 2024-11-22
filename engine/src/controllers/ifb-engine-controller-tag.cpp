#pragma once

#include "ifb-engine-internal-controllers.hpp"
#include "ifb-engine-internal-tables.hpp"

inline const IFBHashValue
ifb_engine::controller_tag_hash_value(
          IFBEngineTableTag& tag_table,
    const IFBEngineTagId     tag_id) {

    const IFBHashValue* hash_value_column_ptr = ifb_engine::table_tag_column_hash_value(tag_table);
    const IFBHashValue  hash_value            = hash_value_column_ptr[tag_id.tag_table_index]; 

    return(hash_value);
}

inline const ifb_cstr
ifb_engine::controller_tag_cstr_value(
          IFBEngineTableTag& tag_table,
    const IFBEngineTagId     tag_id) {

    const ifb_char* cstr_value_column_ptr  = ifb_engine::table_tag_column_tag_buffer(tag_table);
    const ifb_u32   cstr_value_char_index  = tag_id.tag_table_index * IFB_ENGINE_TAG_LENGTH;
    const ifb_cstr  cstr_value             = (const ifb_cstr)&cstr_value_column_ptr[cstr_value_char_index]; 

    return(cstr_value);
}

inline const ifb_b8
ifb_engine::controller_tag_collision_check(
          IFBEngineTableTag& tag_table,
    const IFBHashValue       hash_value) {

    const IFBHashValue* hash_value_column_ptr = ifb_engine::table_tag_column_hash_value(tag_table);

    const ifb_b8 collision = ifb_common::hash_collision_check(
            hash_value_column_ptr,
            tag_table.row_count,
            hash_value);

    return(collision);
}

inline const ifb_b8
ifb_engine::controller_tag_table_insert(
          IFBEngineTableTag& in_tag_table,
    const ifb_cstr           in_tag_value, 
          IFBEngineTagId&   out_tag_id) {
    
    ifb_b8 result = true;

    //get the hash values
    const IFBHashValue* hash_value_column_ptr = ifb_engine::table_tag_column_hash_value(in_tag_table);

    //hash the value and check for collisions
    IFBHashValue hash_value;
    result &=  ifb_common::hash_cstr(in_tag_value,IFB_ENGINE_TAG_LENGTH,hash_value) > 0;
    result &= !ifb_common::hash_collision_check (hash_value_column_ptr,in_tag_table.row_count, hash_value);
    result &=  ifb_common::hash_next_clear_value(hash_value_column_ptr,in_tag_table.row_count, out_tag_id.tag_table_index);

    //if that didn't work, we're done
    if (!result) {
        return(false);
    }

    //get the strings
    ifb_char* cstr_value_column_ptr = ifb_engine::table_tag_column_tag_buffer(in_tag_table);

    //copy the tag value
    const ifb_u32 tag_value_length      = IFB_ENGINE_TAG_LENGTH;
    const ifb_u32 tag_value_array_index = IFB_ENGINE_TAG_LENGTH * out_tag_id.tag_table_index;
    for (
        ifb_u32 char_index = 0;
                char_index < tag_value_length;
              ++char_index) {

        cstr_value_column_ptr[tag_value_array_index + char_index] = in_tag_value[char_index]; 
    }

    //we're done
    return(true);
}

inline const ifb_b8
ifb_engine::controller_tag_table_search(
          IFBEngineTableTag& in_tag_table,
    const ifb_cstr           in_tag_value, 
          IFBEngineTagId&   out_tag_id) {

    //get the hash values
    const IFBHashValue* hash_value_column_ptr = ifb_engine::table_tag_column_hash_value(in_tag_table);

    //do the search
    ifb_b8 result;
    IFBHashValue hash_value;
    result &= ifb_common::hash_cstr   (in_tag_value,IFB_ENGINE_TAG_LENGTH,hash_value);        
    result &= ifb_common::hash_search (hash_value_column_ptr,IFB_ENGINE_TAG_COUNT_MAX,hash_value,out_tag_id.tag_table_index);

    //we're done
    return(result);
}

inline const ifb_b8
ifb_engine::controller_tag_table_delete(
          IFBEngineTableTag& tag_table,
    const IFBEngineTagId     tag_id) {

    ifb_char*     tag_values_ptr  = ifb_engine::table_tag_column_tag_buffer(tag_table);
    IFBHashValue* hash_values_ptr = ifb_engine::table_tag_column_hash_value(tag_table);

    
    //clear the hash value
    hash_values_ptr[tag_id.tag_table_index] = {0};

    //clear the tag value
    const ifb_u32 char_index_start = tag_id.tag_table_index * IFB_ENGINE_TAG_LENGTH;
    const ifb_u32 char_index_end   = char_index_start       + IFB_ENGINE_TAG_LENGTH;
    for (
        ifb_u32 char_index = char_index_start;
                char_index < char_index_end;
              ++char_index) {

        tag_values_ptr[char_index] = 0;
    }

    return(true);
}