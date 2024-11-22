#pragma once

#include "ifb-engine-internal-controllers.hpp"
#include "ifb-engine-internal.hpp"

ifb_api const ifb_b8
ifb_engine::tag_create(
    const ifb_cstr         in_tag_value, 
          IFBEngineTagId& out_tag_id_ref) {

    //sanity check
    if (!in_tag_value) {
        return(false);
    }
    
    //get the table
    IFBEngineTableTag tag_table;
    ifb_engine::table_tag(tag_table);

    //insert the value
    const ifb_b8 result = ifb_engine::controller_tag_table_insert(
        tag_table,
        in_tag_value,
        out_tag_id_ref);

    //we're done
    return(result);
}

ifb_api const ifb_b8
ifb_engine::tag_id(
    const ifb_cstr         in_tag_value, 
          IFBEngineTagId& out_tag_id_ref) {

    //get the table
    IFBEngineTableTag tag_table;
    ifb_engine::table_tag(tag_table);

    //search the table
    const ifb_b8 result = ifb_engine::controller_tag_table_search(
        tag_table,
        in_tag_value,
        out_tag_id_ref);

    //we're done
    return(result);
}

ifb_api const ifb_b8
ifb_engine::tag_destroy(
    const IFBEngineTagId tag_id) {

    //sanity check
    if (tag_id.tag_table_index >= IFB_ENGINE_TAG_COUNT_MAX) {
        return(NULL);
    }

    //get the table
    IFBEngineTableTag tag_table;
    ifb_engine::table_tag(tag_table);

    //do the delete
    const ifb_b8 result = ifb_engine::controller_tag_table_delete(
        tag_table,
        tag_id);

    //we're done
    return(result);
}

ifb_api const ifb_cstr
ifb_engine::tag_value(
    const IFBEngineTagId tag_id) {

    //sanity check
    if (tag_id.tag_table_index >= IFB_ENGINE_TAG_COUNT_MAX) {
        return(NULL);
    }

    //get the table
    IFBEngineTableTag tag_table;
    ifb_engine::table_tag(tag_table);

    //get the value
    const ifb_cstr tag_value = ifb_engine::controller_tag_cstr_value(tag_table,tag_id);

    //we're done
    return(tag_value);
}