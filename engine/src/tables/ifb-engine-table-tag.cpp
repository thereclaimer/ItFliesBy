#pragma once

#include "ifb-engine-internal-tables.hpp"

inline const IFBEngineTableHandleTag 
ifb_engine::table_tag_create(
    const IFBEngineTableAllocatorHandle table_allocator_handle) {

    //calculate sizes
    const ifb_u32 table_count_columns  = 2;
    const ifb_u32 table_count_rows     = IFB_ENGINE_TABLE_TAG_ROW_COUNT;
    const ifb_u32 table_size_header    = ifb_macro_align_size_struct(IFBEngineTableTag);
    const ifb_u32 table_size_columns[table_count_columns] = {
        IFB_ENGINE_TABLE_TAG_VALUE_LENGTH, //tag value
        sizeof(IFBHashValue)               //hash
    };

    //allocate table
    const IFBEngineTableMemoryHandle* table_handles = ifb_engine::table_allocator_reserve(
        table_allocator_handle,
        table_count_rows,
        table_count_columns,
        table_size_header,
        table_size_columns);

    //get the table pointer
    IFBEngineTableTag* tag_table_ptr = (IFBEngineTableTag*)ifb_engine::memory_pointer_from_handle(table_handles[0]);

    //initialize the table
    tag_table_ptr->tag_value_size         = IFB_ENGINE_TABLE_TAG_VALUE_LENGTH;
    tag_table_ptr->row_count              = table_count_rows;
    tag_table_ptr->column_ptrs.tag_buffer =     (ifb_char*)ifb_engine::memory_pointer_from_handle(table_handles[1]);
    tag_table_ptr->column_ptrs.hash_value = (IFBHashValue*)ifb_engine::memory_pointer_from_handle(table_handles[2]);

    //we're done
    return(table_handles[0]);
}
    
inline const ifb_cstr
ifb_engine::table_tag_read_value(
    const IFBEngineTableHandleTag tag_table_handle,
    const IFBEngineTableIndexTag  tag_index) {

    //get the table
    IFBEngineTableTag* table_tag_ptr = (IFBEngineTableTag*)ifb_engine::memory_pointer_from_handle(table_handle_tag);

    //sanity check    
    ifb_macro_assert(
        table_tag_ptr &&
        tag_index < table_tag_ptr->row_count);

    //get the tag value
    const ifb_u32  char_index = table_tag_ptr->tag_value_size * tag_index.row;
    const ifb_cstr tag_value  = table_tag_ptr->column_ptrs.tag_buffer[char_index]; 

    return(tag_value);
}

inline const IFBHashValue
ifb_engine::table_tag_read_hash(
    const IFBEngineTableHandleTag tag_table_handle,
    const IFBEngineTableIndexTag  tag_index) {

    //get the table
    IFBEngineTableTag* table_tag_ptr = (IFBEngineTableTag*)ifb_engine::memory_pointer_from_handle(table_handle_tag);

    //sanity check    
    ifb_macro_assert(
        table_tag_ptr &&
        tag_index < table_tag_ptr->row_count);


    //get the hash value
    const IFBHashValue hash_value = table_tag_ptr->column_ptrs.hash_value[tag_index];

    //we're done
    return(hash_value);
}

inline const ifb_b8
ifb_engine::table_tag_delete(
    const IFBEngineTableHandleTag tag_table_handle,
    const IFBEngineTableIndexTag  tag_index) {

    //get the table
    IFBEngineTableTag* table_tag_ptr = (IFBEngineTableTag*)ifb_engine::memory_pointer_from_handle(table_handle_tag);

    //sanity check    
    ifb_macro_assert(
        table_tag_ptr &&
        tag_index < table_tag_ptr->row_count);

    //clear the hash value
    table_tag_ptr->column_ptrs.hash_value[tag_index] = {0};
    
    //clear the char values
    const ifb_u32 char_start = tag_index.row * table_tag_ptr->tag_value_size;
    const ifb_u32 char_end   = char_start    + table_tag_ptr->tag_value_size;  

    for (
        ifb_u32 char_index = char_start;
                char_index < char_end; 
              ++char_index) {

        table_tag_ptr->column_ptrs.tag_buffer[char_index] = '\0';
    }

    return(true);
}

inline const ifb_b8
ifb_engine::table_tag_insert(
    const IFBEngineTableHandleTag  in_tag_table_handle,
    const ifb_cstr                 in_tag_value, 
          IFBEngineTableIndexTag& out_tag_index) {

    //get the table
    IFBEngineTableTag* table_tag_ptr = (IFBEngineTableTag*)ifb_engine::memory_pointer_from_handle(table_handle_tag);

    //sanity check    
    ifb_macro_assert(table_tag_ptr);

    //hash the value
    const IFBHashValue hash_value = ifb_common::hash_cstr(in_tag_value,table_tag_ptr->row_count);

    ifb_b8 result = true;

    //find the next clear value and check collisions
    result &=  ifb_common::hash_next_clear_value (table_tag_ptr->column_ptrs.hash_value, table_tag_ptr->row_count, out_tag_index.row);
    result &= !ifb_common::hash_collision_check  (table_tag_ptr->column_ptrs.hash_value, table_tag_ptr->row_count, hash_value);

    //if that failed, we're done
    if (!result) {
        return(false);
    }

    //add the hash value to the table
    table_tag_ptr->column_ptrs.hash_value[out_tag_index.row] = hash_value;
    const ifb_index char_start = out_tag_index.row * table_tag_ptr->tag_value_size;
    const ifb_index char_end   = char_start        + table_tag_ptr->tag_value_size;
    ifb_index tag_value_index = 0;
    for (
        ifb_index char_index = char_start;
                  char_index < char_end; 
                ++char_index) {
        table_tag_ptr->column_ptrs.tag_buffer[char_index] = in_tag_value[tag_value_index];
        ++tag_value_index;
    }

    //we're done
    return(true);
}

inline const ifb_b8
ifb_engine::table_tag_search(
    const IFBEngineTableHandleTag in_tag_table_handle,
    const ifb_cstr                in_tag_value, 
        IFBEngineTableIndexTag&  out_tag_index) {
    
    //get the table
    IFBEngineTableTag* table_tag_ptr = (IFBEngineTableTag*)ifb_engine::memory_pointer_from_handle(table_handle_tag);

    //sanity check    
    ifb_macro_assert(table_tag_ptr);

    //hash the value
    const IFBHashValue hash_value = ifb_common::hash_cstr(in_tag_value,table_tag_ptr->row_count);

    //search the hash column
    ifb_u32 index;
    const ifb_b8 result = ifb_common::hash_search(
        table_tag_ptr->column_ptrs.hash_value,
        table_tag_ptr->row_count,
        hash_value,
        index);

    //return the result
    return(result);
}

inline IFBEngineTableTag*
ifb_engine::table_tag(
    const IFBEngineTableHandleTag table_handle_tag) {

    IFBEngineTableTag* table_tag_ptr = (IFBEngineTableTag*)ifb_engine::memory_pointer_from_handle(table_handle_tag);

    return(table_tag_ptr);
}