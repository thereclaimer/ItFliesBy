#pragma once

#include "ifb-engine-internal-tables.hpp"

inline ifb_void
ifb_engine::table_tag(
    IFBEngineTableTag& tag_table) {

    IFBEngineTableManager* table_manager_ptr = ifb_engine::table_manager_from_context();

    IFBEngineTable& table_ref = table_manager_ptr->tables.tag;

    const ifb_u32 column_handle_start = table_ref.column_handle_start;

    tag_table.column_handle_tag_buffer = table_manager_ptr->columns.column_handles[column_handle_start];
    tag_table.column_handle_hash_value = table_manager_ptr->columns.column_handles[column_handle_start + 1];
}

inline ifb_char*
ifb_engine::table_tag_column_memory_tag_buffer(
    IFBEngineTableTag& tag_table) {

    ifb_char* column_memory_tag_buffer_ptr = (ifb_char*)ifb_engine::memory_pointer_from_handle(tag_table.column_handle_tag_buffer); 

    return(column_memory_tag_buffer_ptr);
}

inline IFBHashValue*
ifb_engine::table_tag_column_memory_hash_value(
    IFBEngineTableTag& tag_table) {

    IFBHashValue* column_memory_hash_value_ptr = (IFBHashValue*)ifb_engine::memory_pointer_from_handle(tag_table.column_handle_hash_value); 

    return(column_memory_hash_value_ptr);
}
