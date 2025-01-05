#pragma once

#include "ifb-engine-internal-data.hpp"
#include "ifb-engine-internal-context.hpp"
#include "ifb-engine-internal-core.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBEngineTagData {
    ifb_char* char_buffer;
    IFBHash*  hash_array;
};

namespace ifb_engine {

    const ifb_b8 tag_data_query         (IFBEngineTagData& tag_query_ref);
    ifb_void     tag_data_update_value  (IFBEngineTagData& tag_query_ref, const IFBIDTag tag_id, const ifb_char* tag_value);
    ifb_void     tag_data_update_hash   (IFBEngineTagData& tag_query_ref, const IFBIDTag tag_id, const ifb_char* tag_value);

    const ifb_u32 tag_char_buffer_offset (const IFBIDTag tag_id);
};

/**********************************************************************************/
/* TAG                                                                            */
/**********************************************************************************/

inline const IFBHash 
ifb_engine::tag_hash(
    const ifb_char* tag_value) {

    const IFBHash tag_hash = ifb_hash::get_hash((ifb_cstr)tag_value,IFB_TAG_LENGTH);
    return(tag_hash);
}

inline const ifb_b8
ifb_engine::tag_data_query(
    IFBEngineTagData& tag_data_ref) {

    //build the query
    IFBEngineDataQuery data_query = {0};
    ifb_engine::data_query_request_add_tag_char_buffer(data_query.request);
    ifb_engine::data_query_request_add_tag_hash_array (data_query.request);

    //execute the query
    IFBEngineDataStore* data_store_ptr = ifb_engine::context_get_data_store();
    ifb_engine::data_store_execute_query(data_store_ptr,&data_query);

    //get the pointers
    tag_data_ref.char_buffer = (ifb_char*)data_query.result.property_array[0]; 
    tag_data_ref.hash_array  =  (IFBHash*)data_query.result.property_array[1];

    //we're done
    const ifb_b8 result = tag_data_ref.char_buffer && tag_data_ref.hash_array;
    return(result);
}

inline ifb_void
ifb_engine::tag_data_update_value(
          IFBEngineTagData& tag_data_ref,
    const IFBIDTag          tag_id,
    const ifb_char*         tag_value) {

    const ifb_u32 offset = ifb_engine::tag_char_buffer_offset(tag_id);

    //update the char buffer    
    ifb_char* tag_char_buffer = &tag_data_ref.char_buffer[offset]; 
    for (
        ifb_u32 char_index = 0;
        char_index < IFB_TAG_LENGTH;
        ++char_index) {

        tag_char_buffer[char_index] = tag_value[char_index];
    }
}

inline ifb_void
ifb_engine::tag_data_update_hash(
          IFBEngineTagData& tag_query_ref,
    const IFBIDTag          tag_id,
    const ifb_char*         tag_value) {

    const IFBHash tag_hash = ifb_engine::tag_hash(tag_value);

    tag_query_ref.hash_array[tag_id.index] = tag_hash; 
}

inline const ifb_u32 
ifb_engine::tag_char_buffer_offset(
    const IFBIDTag tag_id) {

    const ifb_u32 char_buffer_offset = IFB_TAG_LENGTH * tag_id.index;
    return(char_buffer_offset);
}

inline const ifb_b8
ifb_engine::tag_update_value(
    const IFBIDTag  tag_id,
    const ifb_char* tag_value_array) {

    //get the tag data
    IFBEngineTagData tag_data = {0};
    ifb_engine::tag_data_query(tag_data);

    //update the value and hash
    ifb_engine::tag_data_update_value (tag_data,tag_id,tag_value_array);
    ifb_engine::tag_data_update_hash  (tag_data,tag_id,tag_value_array);
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