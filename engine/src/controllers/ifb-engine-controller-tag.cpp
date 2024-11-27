#pragma once

#include "ifb-engine-internal-controllers.hpp"
#include "ifb-engine-internal-tables.hpp"

inline const IFBHashValue
ifb_engine::controller_tag_hash_value(
          IFBEngineCore* engine_core_ptr,
    const IFBEngineTagId tag_id) {

    IFBEngineTableTag* tag_table = ifb_engine::core_table_tag(engine_core_ptr);

    const IFBHashValue hash_value = tag_table->column_ptrs.hash_value[tag_id.table_index.value];

    return(hash_value);
}

inline const ifb_cstr
ifb_engine::controller_tag_cstr_value(
          IFBEngineCore* engine_core_ptr,
    const IFBEngineTagId tag_id) {

    IFBEngineTableTag* tag_table = ifb_engine::core_table_tag(engine_core_ptr);

    const ifb_char* cstr_value_column_ptr  = tag_table->column_ptrs.tag_buffer;
    const ifb_u32   cstr_value_char_index  = tag_id.table_index.value * IFB_ENGINE_TAG_LENGTH;
    const ifb_cstr  cstr_value             = (const ifb_cstr)&cstr_value_column_ptr[cstr_value_char_index]; 

    return(cstr_value);
}

inline const ifb_b8
ifb_engine::controller_tag_collision_check(
          IFBEngineCore* engine_core_ptr,
    const IFBHashValue   hash_value) {

    IFBEngineTableTag* tag_table = ifb_engine::core_table_tag(engine_core_ptr);

    const ifb_b8 collision = ifb_common::hash_collision_check(
            tag_table->column_ptrs.hash_value,
            tag_table->row_count,
            hash_value);

    return(collision);
}

inline const IFBEngineTagId
ifb_engine::controller_tag_create(
          IFBEngineCore* engine_core_ptr,
    const ifb_cstr       tag_value) {
    
    //get the table
    IFBEngineTableTag* tag_table = ifb_engine::core_table_tag(engine_core_ptr);

    //do the insert
    const IFBEngineTableIndexTag new_tag_index = ifb_engine::table_tag_insert(tag_table,tag_value);

    //we're done
    IFBEngineTagId new_tag;
    new_tag.table_index.value = new_tag_index.index.value;        
    return(new_tag);
}

inline const ifb_b8
ifb_engine::controller_tag_search(
          IFBEngineCore*   in_engine_core_ptr,
    const ifb_cstr         in_tag_value, 
          IFBEngineTagId& out_tag_id) {

    //get the table
    IFBEngineTableTag* tag_table = ifb_engine::core_table_tag(in_engine_core_ptr);

    //do the search
    IFBEngineTableIndexTag tag_table_index;
    const ifb_b8 search_result = ifb_engine::table_tag_search(tag_table,in_tag_value,tag_table_index);

    //update the tag id
    out_tag_id.table_index.value = tag_table_index.index.value;

    //we're done
    return(search_result);
}

inline const ifb_b8
ifb_engine::controller_tag_destroy(
          IFBEngineCore* engine_core_ptr,
    const IFBEngineTagId tag_id) {

    //get the table
    IFBEngineTableTag* tag_table = ifb_engine::core_table_tag(engine_core_ptr);

    //do the delete
    IFBEngineTableIndexTag tag_index;
    tag_index.index.value = tag_id.table_index.value;
    const ifb_b8 result = ifb_engine::table_tag_delete(tag_table,tag_index);

    //we're done
    return(result);
}