#pragma once

#include "ifb-engine-internal-data.hpp"
#include "ifb-engine-internal-context.hpp"
#include "ifb-engine-internal-core.hpp"

inline const ifb_b8
ifb_engine::tag_update_value(
    const IFBIDTag  tag_id,
    const ifb_char* tag_value_array) {

    //build the query
    IFBEngineDataQuery data_query = {0};
    ifb_engine::data_query_request_add_tag_char_buffer(data_query.request);
    ifb_engine::data_query_request_add_tag_hash_array (data_query.request);

    //execute the query
    IFBEngineDataStore* data_store_ptr = ifb_engine::context_get_data_store();
    ifb_engine::data_store_execute_query(data_store_ptr,&data_query);

    //get the pointers
    ifb_char* tag_char_buffer = (ifb_char*)data_query.result.property_array[0]; 
    IFBHash*  tag_hash_array  =  (IFBHash*)data_query.result.property_array[1];

    //sanity check
    if (!tag_char_buffer || !tag_hash_array) {
        return(false);
    }

    //calculate the offset
    const ifb_u32 char_buffer_offset = IFB_TAG_LENGTH * tag_id.index;

    //update the char buffer    
    ifb_char* tag_char_buffer_start = &tag_char_buffer[char_buffer_offset]; 
    for (
        ifb_u32 char_index = 0;
        char_index < IFB_TAG_LENGTH;
        ++char_index) {

        tag_char_buffer_start[char_index] = tag_value_array[char_index];
    }

    //update the hash
    const IFBHash new_hash = ifb_hash::get_hash((const ifb_cstr)tag_char_buffer,IFB_TAG_LENGTH);
    tag_hash_array[tag_id.index] = new_hash;
}

inline const ifb_b8
ifb_engine::tag_reserve(
    const ifb_char* tag_value,
          IFBIDTag& tag_id_ref) {

}

inline const ifb_b8
ifb_engine::tag_find(
    const ifb_char* tag_value,
          IFBIDTag& tag_id_array_ref) {

}

inline const ifb_b8
ifb_engine::tag_get(
    const IFBIDTag tag_id_array,
          IFBTag&  tag_ref) {

}

inline const ifb_b8
ifb_engine::tag_release(
    const IFBIDTag tag_id) {

}

inline const ifb_b8 ifb_engine::tag_update_value (const ifb_u32 tag_count, const IFBIDTag*  tag_id_array,    const ifb_char** tag_value_array);
inline const ifb_b8 ifb_engine::tag_reserve      (const ifb_u32 tag_count, const ifb_char** tag_value_array, IFBIDTag*        tag_id_array);
inline const ifb_b8 ifb_engine::tag_find         (const ifb_u32 tag_count, const ifb_char** tag_value_array, IFBIDTag*        tag_id_array);
inline const ifb_b8 ifb_engine::tag_get          (const ifb_u32 tag_count, const IFBIDTag*  tag_id_array,    IFBTag*          tag_array);
inline const ifb_b8 ifb_engine::tag_release      (const ifb_u32 tag_count, const IFBIDTag*  tag_id_array);