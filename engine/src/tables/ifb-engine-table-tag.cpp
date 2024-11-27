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
    IFBEngineTableTag* tag_table_ptr = (IFBEngineTableTag*)ifb_engine::memory_pointer_from_handle(table_handles[0].memory);

    //initialize the table
    tag_table_ptr->tag_value_size         = IFB_ENGINE_TABLE_TAG_VALUE_LENGTH;
    tag_table_ptr->row_count              = table_count_rows;
    tag_table_ptr->column_ptrs.tag_buffer =     (ifb_char*)ifb_engine::memory_pointer_from_handle(table_handles[1].memory);
    tag_table_ptr->column_ptrs.hash_value = (IFBHashValue*)ifb_engine::memory_pointer_from_handle(table_handles[2].memory);

    //we're done
    IFBEngineTableHandleTag tag_table;
    tag_table.memory_handle = table_handles[0].memory; 
    return(tag_table);
}

inline const ifb_cstr 
ifb_engine::table_tag_read_value(
          IFBEngineTableTag*     tag_table_ptr,
    const IFBEngineTableIndexTag tag_index) {

    //get the tag value
    const ifb_u32  char_index = tag_table_ptr->tag_value_size * tag_index.index.value;
    const ifb_cstr tag_value  = &tag_table_ptr->column_ptrs.tag_buffer[char_index]; 

    return(tag_value);
}

inline const IFBHashValue
ifb_engine::table_tag_read_hash(
          IFBEngineTableTag*     tag_table_ptr,
    const IFBEngineTableIndexTag tag_index) {

    //get the hash value
    const IFBHashValue hash_value = tag_table_ptr->column_ptrs.hash_value[tag_index.index.value];

    //we're done
    return(hash_value);
}

inline const ifb_b8
ifb_engine::table_tag_delete(
          IFBEngineTableTag*     tag_table_ptr,
    const IFBEngineTableIndexTag tag_index) {

    //clear the hash value
    tag_table_ptr->column_ptrs.hash_value[tag_index.index.value] = {0};
    
    //clear the char values
    const ifb_u32 char_start = tag_table_ptr->tag_value_size * tag_index.index.value;
    const ifb_u32 char_end   = tag_table_ptr->tag_value_size + char_start;  

    for (
        ifb_u32 char_index = char_start;
                char_index < char_end; 
              ++char_index) {

        tag_table_ptr->column_ptrs.tag_buffer[char_index] = '\0';
    }

    return(true);
}

inline const IFBEngineTableIndexTag
ifb_engine::table_tag_insert(
          IFBEngineTableTag* tag_table_ptr,
    const ifb_cstr           tag_value) {

    //hash the value
    const IFBHashValue hash_value = ifb_common::hash_cstr(tag_value,tag_table_ptr->tag_value_size);

    //find the next clear value and check collisions
    IFBEngineTableIndexTag new_tag = {0};
    ifb_b8 can_insert = true;
    can_insert &=  ifb_common::hash_next_clear_value (tag_table_ptr->column_ptrs.hash_value, tag_table_ptr->row_count, new_tag.index.value);
    can_insert &= !ifb_common::hash_collision_check  (tag_table_ptr->column_ptrs.hash_value, tag_table_ptr->row_count, hash_value);
    ifb_macro_assert(can_insert);

    //add the hash value to the table
    tag_table_ptr->column_ptrs.hash_value[new_tag.index.value] = hash_value;
    const ifb_index char_start = new_tag.index.value * tag_table_ptr->tag_value_size;
    const ifb_index char_end   = char_start          + tag_table_ptr->tag_value_size;
    ifb_index tag_value_index = 0;
    for (
        ifb_index char_index = char_start;
                  char_index < char_end; 
                ++char_index) {
        tag_table_ptr->column_ptrs.tag_buffer[char_index] = tag_value[tag_value_index];
        ++tag_value_index;
    }

    //we're done
    return(new_tag);
}

inline const ifb_b8
ifb_engine::table_tag_search(
          IFBEngineTableTag*       in_tag_table_ptr,
    const ifb_cstr                 in_tag_value, 
          IFBEngineTableIndexTag& out_tag_index) {

    //hash the value
    const IFBHashValue hash_value = ifb_common::hash_cstr(in_tag_value,in_tag_table_ptr->row_count);

    //search the hash column
    ifb_u32 index;
    const ifb_b8 search_result = ifb_common::hash_search(
        in_tag_table_ptr->column_ptrs.hash_value,
        in_tag_table_ptr->row_count,
        hash_value,
        out_tag_index.index.value);

    //return the result
    return(search_result);
}

inline IFBEngineTableTag*
ifb_engine::table_tag(
    const IFBEngineTableHandleTag table_handle_tag) {

    IFBEngineTableTag* table_tag_ptr = (IFBEngineTableTag*)ifb_engine::memory_pointer_from_handle(table_handle_tag.memory_handle);

    return(table_tag_ptr);
}