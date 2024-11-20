#pragma once

#include "ifb-engine-internal-tables.hpp"
#include "ifb-engine-internal-core.hpp"

inline IFBEngineTableManager*
ifb_engine::table_manager_from_handle(
    const ifb_handle_memory_t handle) {

    IFBEngineTableManager* table_manager_ptr = (IFBEngineTableManager*)ifb_engine::memory_pointer_from_handle(handle);

    return(table_manager_ptr);
}

inline IFBEngineTableManager* 
ifb_engine::table_manager_from_context(
    ifb_void) {

    IFBEngineCore* engine_core_ptr           = ifb_engine::core_pointer_from_context();
    IFBEngineTableManager* table_manager_ptr = ifb_engine::table_manager_from_handle(engine_core_ptr->managers.tables);     

    return(table_manager_ptr);
}

inline const ifb_handle_memory_t 
ifb_engine::table_manager_create(
    ifb_void) {

    //calculate sizes
    const ifb_u32 size_table_manager = ifb_macro_align_size_struct(IFBEngineTableManager);

    //commit pages
    const ifb_u32 page_count = ifb_engine::memory_page_count(size_table_manager);
    const ifb_u32 page_start = ifb_engine::memory_page_commit(page_count);

    //if that didn't work, return 0
    if (page_start == 0) {
        return(0);
    }

    //create handles
    const ifb_handle_memory_t handle_table_manager = ifb_engine::memory_handle(page_start, 0);

    //initialize the table manager
    IFBEngineTableManager* table_manager_ptr = ifb_engine::table_manager_from_handle(handle_table_manager);    
    table_manager_ptr->columns.column_count_max  = IFB_ENGINE_TABLE_MANAGER_COLUMN_COUNT_MAX;
    table_manager_ptr->columns.column_count_used = 0;
    
    //create tables
    ifb_b8 result = true;
    result &= ifb_engine::table_manager_create_table_tag             (table_manager_ptr);
    result &= ifb_engine::table_manager_create_table_stack_allocator (table_manager_ptr);
    result &= ifb_engine::table_manager_create_table_arena           (table_manager_ptr);

    //we're done
    return(handle_table_manager);
}

inline IFBEngineTable& 
ifb_engine::table_manager_get_table_ref(
          IFBEngineTableManager* table_manager_ptr,
    const IFBEngineTableId       table_id) {

    return(table_manager_ptr->tables.array[table_id]);
}

inline const ifb_b8 
ifb_engine::table_manager_create_table(
          IFBEngineTableManager* table_manager_ptr,
    const IFBEngineTableId       table_id,
    const ifb_u32                table_column_count,
    const ifb_u32*               table_column_sizes) {

    //cache tables and columns
    IFBEngineTables&       tables_ref  = table_manager_ptr->tables;
    IFBEngineTableColumns& columns_ref = table_manager_ptr->columns;

    //update the table
    IFBEngineTable& table_ref = tables_ref.array[table_id];
    table_ref.column_handle_start = columns_ref.column_count_used;
    table_ref.column_handle_count = table_column_count;

    ifb_b8 result = true;

    for (
        ifb_u32 column_index = 0;
                column_index < table_column_count;
              ++column_index) {

        //commit column page
        const ifb_u32 column_size       = table_column_sizes[column_index];
        const ifb_u32 column_page_count = ifb_engine::memory_page_count(column_size);
        const ifb_u32 column_page_start = ifb_engine::memory_page_commit(column_page_count);    
        
        //get column handle
        const ifb_handle_memory_t column_handle = ifb_engine::memory_handle(column_page_start,0); 

        //sanity check       
        result &= ifb_engine::memory_handle_valid(column_handle);    

        //update the columns
        columns_ref.column_handles[table_ref.column_handle_start + column_index] = column_handle; 
    }

    columns_ref.column_count_used += table_column_count;

    return(result);
}

inline const ifb_b8 
ifb_engine::table_manager_create_table_tag(
    IFBEngineTableManager* table_manager_ptr) {

    const ifb_u32 tag_table_column_count           = 2;
    const ifb_u32 table_tag_column_size_buffer     = IFB_ENGINE_TABLE_TAG_VALUE_LENGTH * IFB_ENGINE_TABLE_TAG_ROW_COUNT;
    const ifb_u32 table_tag_column_size_hash_value = ifb_macro_size_array(IFBHashValue,  IFB_ENGINE_TABLE_TAG_ROW_COUNT);

    const ifb_u32 tag_table_column_sizes[tag_table_column_count] = {
        table_tag_column_size_buffer,
        table_tag_column_size_hash_value
    };

    const ifb_b8 result = ifb_engine::table_manager_create_table(
        table_manager_ptr,
        IFBEngineTableId_Tag,
        tag_table_column_count,
        tag_table_column_sizes);

    return(result);
}

inline const ifb_b8 
ifb_engine::table_manager_create_table_stack_allocator(
    IFBEngineTableManager* table_manager_ptr) {

    //calculate sizes
    const ifb_u32 table_column_count            = 2;
    const ifb_u32 table_row_count               = IFB_ENGINE_TABLE_STACK_ALLOCATOR_ROW_COUNT;
    const ifb_u32 table_column_size_arena_index = ifb_macro_size_array(ifb_u32,table_row_count); 
    const ifb_u32 table_column_size_used        = ifb_macro_size_array(ifb_u32,table_row_count); 

    //size array
    const ifb_u32 table_column_sizes[table_column_count] = {
        table_column_size_arena_index,
        table_column_size_used
    };

    //create the table
    const ifb_b8 result = ifb_engine::table_manager_create_table(
        table_manager_ptr,
        IFBEngineTableId_StackAllocator,
        table_column_count,
        table_column_sizes);

    //we're done
    return(result);
}

inline const ifb_b8 
ifb_engine::table_manager_create_table_block_allocator(
    IFBEngineTableManager* table_manager_ptr) {

    return(false);
}

inline const ifb_b8 
ifb_engine::table_manager_create_table_arena(
    IFBEngineTableManager* table_manager_ptr) {

    //calculate sizes
    const ifb_u32 table_column_count                = 3;
    const ifb_u32 table_row_count                   = IFB_ENGINE_TABLE_ARENA_ROW_COUNT;
    const ifb_u32 table_column_size_page_start      = ifb_macro_size_array(ifb_u32,            table_row_count); 
    const ifb_u32 table_column_size_page_count      = ifb_macro_size_array(ifb_u32,            table_row_count); 
    const ifb_u32 table_column_size_table_index_tag = ifb_macro_size_array(ifb_table_index_tag,table_row_count); 

    //size array
    const ifb_u32 table_column_sizes[table_column_count] = {
        table_column_size_page_start,
        table_column_size_page_count,
        table_column_size_table_index_tag
    };

    //create the table
    const ifb_b8 result = ifb_engine::table_manager_create_table(
        table_manager_ptr,
        IFBEngineTableId_Arena,
        table_column_count,
        table_column_sizes);

    //we're done
    return(result);  
}

inline const ifb_b8 
ifb_engine::table_manager_create_table_shader_program(
    IFBEngineTableManager* table_manager_ptr) {

    return(false);
}