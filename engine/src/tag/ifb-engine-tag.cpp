#pragma once

#include "ifb-engine-internal-tag.hpp"
#include "ifb-engine-internal-tables.hpp"
#include "ifb-engine-internal.hpp"

ifb_api const ifb_b8
ifb_engine::tag_create(
    const ifb_cstr  in_tag_value, 
          ifb_u32& out_tag_index_ref) {

    //sanity check
    if (!in_tag_value) {
        return(false);
    }
    
    ifb_b8 result = true;

    //hash the value
    IFBHashValue tag_hash;
    const ifb_u32 tag_length = ifb_common::hash_cstr(in_tag_value,IFB_ENGINE_TAG_LENGTH,tag_hash);
    if (tag_length == 0) {
        return(false);
    }

    //get the table
    IFBEngineTableTag tag_table;
    ifb_engine::table_tag(tag_table);

    //get the hash memory
    IFBHashValue* tag_hash_array_ptr = ifb_engine::table_tag_column_memory_hash_value(tag_table);

    //collision check
    if(
        ifb_common::hash_collision_check(
            tag_hash,
            tag_hash_array_ptr,
            IFB_ENGINE_TAG_COUNT_MAX)) {

        //if we have a collision, we're done
        return(false);
    }

    //find the next available index
    ifb_u32 tag_index;
    if (
        !ifb_common::hash_next_clear_value(
            tag_hash_array_ptr,
            IFB_ENGINE_TAG_COUNT_MAX,
            tag_index)) {

        //if we don't have an available index, we're done
        return(false);
    }

    //get the value memory
    ifb_char* tag_value_array_ptr = ifb_engine::table_tag_column_memory_tag_buffer(tag_table);

    //copy the tag value
    const ifb_u32 tag_value_array_index = tag_index * IFB_ENGINE_TAG_LENGTH;
    for (
        ifb_u32 char_index = 0;
                char_index < tag_length;
              ++char_index) {

        tag_value_array_ptr[tag_value_array_index + char_index] = in_tag_value[char_index]; 
    }

    //we're done
    return(true);
}

ifb_api const ifb_b8
ifb_engine::tag_index(
    const ifb_cstr  in_tag_value, 
          ifb_u32& out_tag_index_ref) {

    //get the table
    IFBEngineTableTag tag_table;
    ifb_engine::table_tag(tag_table);

    //get the hash values
    const IFBHashValue* tag_hash_value_ptr = ifb_engine::table_tag_column_memory_hash_value(tag_table);

    //hash the input value
    IFBHashValue hash_value;
    const ifb_u32 hash_value_length = ifb_common::hash_cstr(
        in_tag_value,
        IFB_ENGINE_TAG_LENGTH,
        hash_value);

    //if that didn't work, we're done
    if (hash_value_length == 0) {
        return(false);
    }

    //search for the index
    ifb_b8 result = ifb_common::hash_search(
        hash_value,
        tag_hash_value_ptr,
        IFB_ENGINE_TAG_COUNT_MAX,
        out_tag_index_ref);

    //we're done
    return(result);
}

ifb_api const ifb_b8
ifb_engine::tag_destroy(
    const ifb_u32 tag_index) {

    //sanity check
    if (tag_index >= IFB_ENGINE_TAG_COUNT_MAX) {
        return(NULL);
    }

    //get the table
    IFBEngineTableTag tag_table;
    ifb_engine::table_tag(tag_table);

    //get the table memory
    ifb_char*     tag_values_ptr  = ifb_engine::table_tag_column_memory_tag_buffer(tag_table);
    IFBHashValue* hash_values_ptr = ifb_engine::table_tag_column_memory_hash_value(tag_table);

    //clear the hash value
    hash_values_ptr[tag_index].h1 = 0;
    hash_values_ptr[tag_index].h2 = 0;
    hash_values_ptr[tag_index].h3 = 0;
    hash_values_ptr[tag_index].h4 = 0;

    //clear the tag value
    const ifb_u32 char_index_start = tag_index        * IFB_ENGINE_TAG_LENGTH;
    const ifb_u32 char_index_end   = char_index_start + IFB_ENGINE_TAG_LENGTH;
    for (
        ifb_u32 char_index = char_index_start;
                char_index < char_index_end;
              ++char_index) {

        tag_values_ptr[char_index] = 0;
    }

    //we're done
    return(true);
}

ifb_api const ifb_cstr
ifb_engine::tag_value(
    const ifb_u32 tag_index) {

    //sanity check
    if (tag_index >= IFB_ENGINE_TAG_COUNT_MAX) {
        return(NULL);
    }

    //get the table
    IFBEngineTableTag tag_table;
    ifb_engine::table_tag(tag_table);

    //get the values
    ifb_char*     tag_values_ptr  = ifb_engine::table_tag_column_memory_tag_buffer(tag_table);

    //calculate the starting index for this tag
    const ifb_u32 tag_char_index = tag_index * IFB_ENGINE_TAG_LENGTH;

    //get the pointer to this tag value
    const ifb_cstr tag_value = (const ifb_cstr)&tag_values_ptr[tag_char_index]; 

    //we're done
    return(tag_value);
}