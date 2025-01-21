#pragma once

#include "ifb-engine-internal-context.hpp"
#include "ifb-engine-internal-core.hpp"
#include "ifb-engine-internal-data.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBEngineArenaDataMemory {
    IFBIDCommit*  commit_id_array;
    IFBIDTag*     tag_id_array;
    ifb_address*  start_address_array;
    ifb_u32*      size_array;
    ifb_u32       arena_count;
    ifb_u32       arena_size;
};

struct IFBEngineArenaDataTag {
    ifb_char* char_buffer;
    IFBHash*  hash_array;    
    ifb_u32   tag_count;
};

struct IFBEngineArenaDataAll {
    IFBEngineArenaDataMemory memory;
    IFBEngineArenaDataTag    tag;
};  

namespace ifb_engine {

    const ifb_b8 arena_data_query_all    (IFBEngineArenaDataAll&    arena_data_all_ref);
    const ifb_b8 arena_data_query_tag    (IFBEngineArenaDataTag&    arena_data_tag_ref);
    const ifb_b8 arena_data_query_memory (IFBEngineArenaDataMemory& arena_data_memory_ref);
};

/**********************************************************************************/
/* ARENA QUERIES                                                                  */
/**********************************************************************************/

inline const ifb_b8
ifb_engine::arena_data_query_all(
    IFBEngineArenaDataAll& arena_data_all_ref) {

    //build the query
    IFBEngineDataQuery data_query = {0};
    ifb_engine::data_query_request_add_arena_commit_id (data_query.request);
    ifb_engine::data_query_request_add_arena_tag_id    (data_query.request);
    ifb_engine::data_query_request_add_arena_start     (data_query.request);
    ifb_engine::data_query_request_add_arena_size      (data_query.request);
    ifb_engine::data_query_request_add_tag_char_buffer (data_query.request);
    ifb_engine::data_query_request_add_tag_hash_array  (data_query.request);

    //return value
    ifb_b8 result = true;

    //execute the query and get the data store info
    IFBEngineDataStore* data_store_ptr = ifb_engine::context_get_data_store();
    const IFBEngineDataInfo& data_info = ifb_engine::data_store_get_info(data_store_ptr);

    //execute the query    
    result &= ifb_engine::data_store_execute_query(data_store_ptr,&data_query);

    //get the pointers
    result &= (arena_data_all_ref.memory.commit_id_array     = (IFBIDCommit*)data_query.result.property_array[0]) != NULL;
    result &= (arena_data_all_ref.memory.tag_id_array        =    (IFBIDTag*)data_query.result.property_array[1]) != NULL;
    result &= (arena_data_all_ref.memory.start_address_array = (ifb_address*)data_query.result.property_array[2]) != NULL;
    result &= (arena_data_all_ref.memory.size_array          =     (ifb_u32*)data_query.result.property_array[3]) != NULL;
    result &= (arena_data_all_ref.tag.char_buffer            =    (ifb_char*)data_query.result.property_array[4]) != NULL;
    result &= (arena_data_all_ref.tag.hash_array             =     (IFBHash*)data_query.result.property_array[5]) != NULL;
    
    //set the counts/sizes
    result &= (arena_data_all_ref.memory.arena_count = data_info.count_arenas) != 0;    
    result &= (arena_data_all_ref.memory.arena_size  = data_info.arena_size)   != 0;
    result &= (arena_data_all_ref.tag.tag_count      = data_info.count_tags)   != 0;

    //we're done
    return(result);
}

inline const ifb_b8
ifb_engine::arena_data_query_tag(
    IFBEngineArenaDataTag& arena_data_tag_ref) {

    //build the query
    IFBEngineDataQuery data_query = {0};
    ifb_engine::data_query_request_add_tag_char_buffer (data_query.request);
    ifb_engine::data_query_request_add_tag_hash_array  (data_query.request);

    //return value
    ifb_b8 result = true;

    //execute the query and get the data store info
    IFBEngineDataStore* data_store_ptr = ifb_engine::context_get_data_store();
    const IFBEngineDataInfo& data_info = ifb_engine::data_store_get_info(data_store_ptr);

    //execute the query    
    result &= ifb_engine::data_store_execute_query(data_store_ptr,&data_query);

    //get the pointers
    result &= (arena_data_tag_ref.char_buffer = (ifb_char*)data_query.result.property_array[0]) != NULL;
    result &= (arena_data_tag_ref.hash_array  =  (IFBHash*)data_query.result.property_array[1]) != NULL;
    
    //set the counts/sizes
    result &= (arena_data_tag_ref.tag_count   = data_info.count_tags) != 0;
}

inline const ifb_b8
ifb_engine::arena_data_query_memory(
    IFBEngineArenaDataMemory& arena_data_memory_ref) {

    //build the query
    IFBEngineDataQuery data_query = {0};
    ifb_engine::data_query_request_add_arena_commit_id (data_query.request);
    ifb_engine::data_query_request_add_arena_tag_id    (data_query.request);
    ifb_engine::data_query_request_add_arena_start     (data_query.request);
    ifb_engine::data_query_request_add_arena_size      (data_query.request);

    //return value
    ifb_b8 result = true;

    //execute the query and get the data store info
    IFBEngineDataStore* data_store_ptr = ifb_engine::context_get_data_store();
    const IFBEngineDataInfo& data_info = ifb_engine::data_store_get_info(data_store_ptr);

    //execute the query    
    result &= ifb_engine::data_store_execute_query(data_store_ptr,&data_query);

    //get the pointers
    result &= (arena_data_memory_ref.commit_id_array     = (IFBIDCommit*)data_query.result.property_array[0]) != NULL;
    result &= (arena_data_memory_ref.tag_id_array        =    (IFBIDTag*)data_query.result.property_array[1]) != NULL;
    result &= (arena_data_memory_ref.start_address_array = (ifb_address*)data_query.result.property_array[2]) != NULL;
    result &= (arena_data_memory_ref.size_array          =     (ifb_u32*)data_query.result.property_array[3]) != NULL;
    
    //set the counts/sizes
    result &= (arena_data_memory_ref.arena_count = data_info.count_arenas) != 0;    
    result &= (arena_data_memory_ref.arena_size  = data_info.arena_size)   != 0;

    //we're done
    return(result);
}

/**********************************************************************************/
/* ARENA                                                                          */
/**********************************************************************************/

inline const ifb_b8
ifb_engine::arena_commit(
    const ifb_u32     arena_minimum_size,
    const ifb_char*   arena_tag_value,
          IFBIDArena& arena_id_ref) {

    //sanity check
    if (arena_minimum_size == 0 || arena_tag_value == NULL) {
        return(false);
    }
    
    ifb_b8 result = true;
    
    //get the arena data
    IFBEngineArenaDataAll arena_data;
    result &= ifb_engine::arena_data_query_all(arena_data);

    

}

inline const ifb_b8
ifb_engine::arena_get(
    const IFBIDArena arena_id,
          IFBArena&  arena_ref) {

}

inline const ifb_b8
ifb_engine::arena_get_size(
    const IFBIDArena arena_id,
          ifb_u32&   arena_size_ref) {

}

inline const ifb_b8
ifb_engine::arena_get_tag(
    const IFBIDArena arena_id,
          IFBTag&    arena_tag_ref) {

}

inline const ifb_b8
ifb_engine::arena_get_address_start(
    const IFBIDArena   arena_id,
          ifb_address& address_start_ref) {

}

inline const ifb_b8
ifb_engine::arena_get_pointer_start(
    const IFBIDArena arena_id,
          ifb_ptr&   pointer_start_ref) {

}

inline const ifb_b8
ifb_engine::arena_align_size(
    const IFBIDArena arena_id,
    const ifb_u32    size,
          ifb_u32&   size_aligned) {

}

inline const ifb_b8
ifb_engine::arena_get_address_offset(
    const IFBIDArena   arena_id,
    const ifb_u32      offset,
          ifb_address& address_start_ref) {

}

inline const ifb_b8
ifb_engine::arena_get_pointer_offset(
    const IFBIDArena arena_id,
    const ifb_u32    offset,
          ifb_ptr&   pointer_start_ref) {

}

inline const ifb_b8
ifb_engine::arena_update_tag(
    const IFBIDArena arena_id,
    const ifb_char*  arena_tag_value) {

}
