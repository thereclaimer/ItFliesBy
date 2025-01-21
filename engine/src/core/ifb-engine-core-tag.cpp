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

    const ifb_b8  tag_data_query         (IFBEngineTagData& tag_data_ref);
    const ifb_b8  tag_hash_data_query    (IFBEngineTagHashData& tag_hash_data_ref);
};

/**********************************************************************************/
/* TAG                                                                            */
/**********************************************************************************/


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
ifb_engine::tag_update_value(
    const IFBIDTag  tag_id,
    const ifb_char* tag_value_new) {

    ifb_b8 result = true;

    //get the tag data and update the values
    IFBEngineTagData tag_data = {0};
    result &= ifb_engine::tag_data_query(tag_data);

    //get the new hash and the pointer to the current value
    const IFBHash tag_hash_new      = ifb_tag::tag_hash(tag_value_new);
    const ifb_u32 offset            = ifb_tag::tag_value_offset(tag_id);
    ifb_char*     tag_value_current = tag_data.char_buffer + offset;

    //copy the tag value
    result &= ifb_tag::tag_copy_value(
        tag_value_new,
        tag_value_current);

    //update the hash
    tag_data.hash_array[tag_id.index] = tag_hash_new;

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

    result = ifb_tag::tag_update_value(
        
    )

    //we're done
    return(result);

}

inline const ifb_b8
ifb_engine::tag_find(
    const ifb_char* tag_value,
          IFBIDTag& tag_id_array_ref) {

    //sanity check
    if (!tag_value) return(false);

    //hash the value
    const IFBHash tag_hash = ifb_engine::tag_hash(tag_value);

    //get the hash data and search for the hashed tag value
    ifb_b8 result = true;
    IFBEngineTagHashData tag_hash_data;
    result &= ifb_engine::tag_hash_data_query(tag_hash_data);
    result &= ifb_hash::search(
        tag_hash_data.hash_array,
        tag_hash_data.tag_count_total,
        tag_hash);

    //we're done
    return(result);
}

inline const ifb_b8
ifb_engine::tag_get(
    const IFBIDTag tag_id,
          IFBTag&  tag_ref) {

    ifb_b8 result = true;
    
    //get the tag data
    IFBEngineTagData tag_data = {0};
    result &= ifb_engine::tag_data_query(tag_data);

    //sanity check
    result &= tag_id.index < tag_data.tag_count_total;
    result &= tag_data.tag_count_total > 0;
    result &= tag_data.char_buffer != NULL;
    result &= tag_data.hash_array  != NULL; 
    if (!result) return(false);
    
    //get the tag_value offset
    const ifb_u32 offset = ifb_engine::tag_char_buffer_offset(tag_id);

    //set the tag properties
    tag_ref.index = tag_id.index;
    tag_ref.hash  = tag_data.hash_array[tag_id.index];

    const ifb_char* tag_value = &tag_data.char_buffer[offset];
    for (
        ifb_u32 char_index = 0;
        char_index < IFB_TAG_LENGTH;
        ++char_index) {
        
        tag_ref.value[char_index] = tag_value[char_index];
    }

    //we're done
    return(true);
}

inline const ifb_b8
ifb_engine::tag_release(
    const IFBIDTag tag_id) {
  
    ifb_b8 result = true;
  
    //get the tag data
    IFBEngineTagData tag_data = {0};
    result &= ifb_engine::tag_data_query(tag_data);

    //sanity check
    result &= tag_id.index < tag_data.tag_count_total;
    result &= tag_data.tag_count_total > 0;
    result &= tag_data.char_buffer != NULL;
    result &= tag_data.hash_array  != NULL; 
    if (!result) return(false);

    //clear the hash value
    tag_data.hash_array[tag_id.index] = {0};

    //we're done
    return(true);
}
