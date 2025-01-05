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
    ifb_u16   tag_count_total;
};

struct IFBEngineTagHashData {
    IFBHash*  hash_array;
    ifb_u16   tag_count_total;
};

namespace ifb_engine {

    const ifb_b8 tag_data_query         (IFBEngineTagData& tag_data_ref);
    const ifb_b8 tag_data_update_value  (IFBEngineTagData& tag_data_ref, const IFBIDTag tag_id, const ifb_char* tag_value);
    const ifb_b8 tag_data_update_hash   (IFBEngineTagData& tag_data_ref, const IFBIDTag tag_id, const ifb_char* tag_value);

    const ifb_b8 tag_hash_data_query    (IFBEngineTagHashData& tag_hash_data_ref);

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

    //get the tag count
    const IFBEngineDataInfo& data_info = ifb_engine::data_store_get_info(data_store_ptr);
    tag_data_ref.tag_count_total = data_info.count_tags;
    
    //sanity check
    ifb_b8 result = true;
    result &= tag_data_ref.char_buffer     != NULL; 
    result &= tag_data_ref.hash_array      != NULL;
    result &= tag_data_ref.tag_count_total != 0; 

    //we're done
    return(result);
}

inline const ifb_b8
ifb_engine::tag_hash_data_query(
    IFBEngineTagHashData& tag_hash_data_ref) {

    ifb_b8 result = true;

    //build the query
    IFBEngineDataQuery data_query = {0};
    ifb_engine::data_query_request_add_tag_hash_array(data_query.request);

    //execute the query and get the data store info
    IFBEngineDataStore* data_store_ptr = ifb_engine::context_get_data_store();
    const IFBEngineDataInfo& data_info = ifb_engine::data_store_get_info(data_store_ptr);
    result &= ifb_engine::data_store_execute_query(data_store_ptr,&data_query);

    //set the properties
    tag_hash_data_ref.hash_array      = (IFBHash*)data_query.result.property_array[0];
    tag_hash_data_ref.tag_count_total = data_info.count_tags;

    //sanity check
    result &= tag_hash_data_ref.hash_array      != NULL;
    result &= tag_hash_data_ref.tag_count_total != 0; 

    //we're done
    return(result);
}


inline const ifb_b8
ifb_engine::tag_data_update_value(
          IFBEngineTagData& tag_data_ref,
    const IFBIDTag          tag_id,
    const ifb_char*         tag_value) {

    const ifb_u32 offset = ifb_engine::tag_char_buffer_offset(tag_id);

    //sanity check
    ifb_b8 valid = true;
    valid &= tag_data_ref.char_buffer     != NULL;
    valid &= tag_data_ref.tag_count_total <= tag_id.index;
    valid &= tag_value                    != NULL;

    if (!valid) return(false);

    //update the char buffer    
    ifb_char* tag_char_buffer = &tag_data_ref.char_buffer[offset]; 
    for (
        ifb_u32 char_index = 0;
        char_index < IFB_TAG_LENGTH;
        ++char_index) {

        tag_char_buffer[char_index] = tag_value[char_index];
    }

    return(true);
}

inline const ifb_b8
ifb_engine::tag_data_update_hash(
          IFBEngineTagData& tag_data_ref,
    const IFBIDTag          tag_id,
    const ifb_char*         tag_value) {

    //sanity check
    ifb_b8 valid = true;
    valid &= tag_data_ref.hash_array      != NULL;
    valid &= tag_data_ref.tag_count_total <= tag_id.index;
    valid &= tag_value                    != NULL;
    if (!valid) return(false);

    //do the hash
    const IFBHash tag_hash = ifb_engine::tag_hash(tag_value);
    
    //make sure we have a value
    if (ifb_hash::hash_is_clear(tag_hash)) return(false);

    //update the hash array
    tag_data_ref.hash_array[tag_id.index] = tag_hash; 

    //we're done
    return(true);
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

    ifb_b8 result = true;

    //get the tag data and update the values
    IFBEngineTagData tag_data = {0};
    result &= ifb_engine::tag_data_query(tag_data);
    result &= ifb_engine::tag_data_update_value (tag_data,tag_id,tag_value_array);
    result &= ifb_engine::tag_data_update_hash  (tag_data,tag_id,tag_value_array);

    //we're done
    return(result);
}

inline const ifb_b8
ifb_engine::tag_reserve(
    const ifb_char* tag_value,
          IFBIDTag& tag_id_ref) {

    ifb_b8 result = true;

    //get the tag data and find the next available index
    IFBEngineTagData tag_data = {0};
    result &= ifb_engine::tag_data_query(tag_data);
    result &= ifb_hash::find_next_clear_value(
        tag_data.hash_array,
        tag_data.tag_count_total,
        tag_id_ref.index);

    //if that didn't work, we're done
    if (!result) return(false);

    //update the values
    result &= ifb_engine::tag_data_update_value (tag_data,tag_id_ref,tag_value);
    result &= ifb_engine::tag_data_update_hash  (tag_data,tag_id_ref,tag_value);

    //we're done
    return(result);

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
