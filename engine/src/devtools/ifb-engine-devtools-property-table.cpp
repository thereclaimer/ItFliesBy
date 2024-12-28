#pragma once

#include "ifb-engine-internal-devtools.hpp"

inline ifb_void 
ifb_engine::devtools_property_table_render_context_sizes(
    IFBEngineContext* context_ptr) {

    //sanity check
    ifb_macro_assert(context_ptr);

    const ifb_char* size_table_name           = IFB_ENGINE_DEVTOOLS_PROPERTY_TABLE_NAME_CONTEXT_SIZES;
    const ifb_u32   size_table_row_count      = 4;
    const ifb_char* size_table_property_names[size_table_row_count] = {
        IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_SIZE_TABLE_CONTEXT,
        IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_SIZE_TABLE_MEMORY,
        IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_SIZE_TABLE_HANDLES,
        IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_SIZE_TABLE_CONFIG
    };

    const ifb_u32 size_context = sizeof(IFBEngineContext);
    const ifb_u32 size_memory  = sizeof(IFBEngineMemory);
    const ifb_u32 size_handles = sizeof(context_ptr->handles);  
    const ifb_u32 size_config  = sizeof(IFBEngineConfig); 

    ifb_char str_size_context[32];
    ifb_char str_size_memory [32];
    ifb_char str_size_handles[32];
    ifb_char str_size_config [32];

    sprintf(str_size_context, "%d", size_context);
    sprintf(str_size_memory,  "%d", size_memory);
    sprintf(str_size_handles, "%d", size_handles);
    sprintf(str_size_config,  "%d", size_config);

    const ifb_char* size_table_property_values[size_table_row_count] = {
        str_size_context,
        str_size_memory,
        str_size_handles,
        str_size_config
    };

    ifb_engine::devtools_property_table_render(
        size_table_name,
        size_table_row_count,
        size_table_property_names,
        size_table_property_values);
}

inline ifb_void 
ifb_engine::devtools_property_table_render_context_handles(
    IFBEngineContext* context_ptr) {

    const ifb_char* handle_table_name           = IFB_ENGINE_DEVTOOLS_PROPERTY_TABLE_NAME_CONTEXT_HANDLES;
    const ifb_u32   handle_table_row_count      = 3;

    const ifb_char* handle_table_property_names[handle_table_row_count] = {
        IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_HANDLES_TABLE_MANAGERS,
        IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_HANDLES_TABLE_CORE,
        IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_HANDLES_TABLE_DEVTOOLS
    };

    const ifb_u32 handle_managers = context_ptr->handles.managers.offset;
    const ifb_u32 handle_core     = context_ptr->handles.core.offset;
    const ifb_u32 handle_devtools = context_ptr->handles.devtools.offset;

    ifb_char str_handle_managers[32];
    ifb_char str_handle_core    [32];
    ifb_char str_handle_devtools[32];
    
    sprintf(str_handle_managers, "%d", handle_managers);
    sprintf(str_handle_core,     "%d", handle_core);
    sprintf(str_handle_devtools, "%d", handle_devtools);

    const ifb_char* handle_table_property_values[handle_table_row_count] = {
        str_handle_managers,
        str_handle_core,
        str_handle_devtools
    };

    ifb_engine::devtools_property_table_render(
        handle_table_name,
        handle_table_row_count,
        handle_table_property_names,
        handle_table_property_values);
}

inline ifb_void 
ifb_engine::devtools_property_table_render_context_config(
    IFBEngineConfig&  config_ref) {

    const ifb_char* config_property_table_name = IFB_ENGINE_DEVTOOLS_PROPERTY_TABLE_NAME_CONTEXT_CONFIG;
    const ifb_u32   config_property_count      = 9;

    ifb_char str_memory_minimum_gb      [32];
    ifb_char str_memory_commit_count_max[32];
    ifb_char str_global_stack_kb        [32];
    ifb_char str_arena_minimum_kb       [32];
    ifb_char str_arena_count_max        [32];
    ifb_char str_tag_c_str_length       [32];
    ifb_char str_tag_count_max          [32];
    ifb_char str_use_devtools           [32];
    ifb_char str_window_title_cstr      [32];

    sprintf(str_memory_minimum_gb,       "%d", config_ref.memory_minimum_gb);
    sprintf(str_memory_commit_count_max, "%d", config_ref.memory_commit_count_max);
    sprintf(str_global_stack_kb,         "%d", config_ref.global_stack_kb);
    sprintf(str_arena_minimum_kb,        "%d", config_ref.arena_minimum_kb);
    sprintf(str_arena_count_max,         "%d", config_ref.arena_count_max);
    sprintf(str_tag_c_str_length,        "%d", config_ref.tag_c_str_length);
    sprintf(str_tag_count_max,           "%d", config_ref.tag_count_max);
    sprintf(str_use_devtools,            "%d", config_ref.use_devtools);
    sprintf(str_window_title_cstr,       "%s", config_ref.window_title_cstr);

    const ifb_char* config_property_values[] = {
        str_memory_minimum_gb,
        str_memory_commit_count_max,
        str_global_stack_kb,
        str_arena_minimum_kb,
        str_arena_count_max,
        str_tag_c_str_length,
        str_tag_count_max,
        str_use_devtools,
        str_window_title_cstr        
    };

    const ifb_char* config_property_names[] = {
        IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_CONFIG_TABLE_MEMORY_REQUIREMENT,
        IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_CONFIG_TABLE_MEMORY_COMMIT_COUNT,
        IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_CONFIG_TABLE_GLOBAL_STACK_SIZE,
        IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_CONFIG_TABLE_ARENA_SIZE,
        IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_CONFIG_TABLE_MAX_ARENA_COUNT,
        IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_CONFIG_TABLE_TAG_LENGTH,
        IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_CONFIG_TABLE_MAX_TAG_COUNT,
        IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_CONFIG_TABLE_USE_DEVTOOLS,
        IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_CONFIG_TABLE_WINDOW_TITLE
    };

    ifb_engine::devtools_property_table_render(
        config_property_table_name,
        config_property_count,
        config_property_names,
        config_property_values);
}

inline ifb_void 
ifb_engine::devtools_property_table_render_memory_global_stack(
    IFBEngineMemoryGlobalStack& global_stack_ref) {

    const ifb_char* global_stack_table_name      = IFB_ENGINE_DEVTOOLS_PROPERTY_TABLE_NAME_MEMORY_GLOBAL_STACK; 
    const ifb_u32   global_stack_table_row_count = 3;

    const ifb_f32 stack_percent = (ifb_f32)global_stack_ref.position / (ifb_f32)global_stack_ref.size; 

    ifb_char str_global_stack_size     [32];
    ifb_char str_global_stack_position [32];
    ifb_char str_global_stack_percent  [32];

    sprintf(str_global_stack_size,     "%d",     global_stack_ref.size);
    sprintf(str_global_stack_position, "%d",     global_stack_ref.position);
    sprintf(str_global_stack_percent,  "%.2f%%", stack_percent);

    const ifb_char* global_stack_table_property_values[global_stack_table_row_count] = {
        str_global_stack_size,
        str_global_stack_position,
        str_global_stack_percent
    };

    const ifb_char* global_stack_table_property_names[global_stack_table_row_count] = {
        IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_MEMORY_GLOBAL_STACK_TABLE_STACK_SIZE,
        IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_MEMORY_GLOBAL_STACK_TABLE_STACK_POSITION,
        IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_MEMORY_GLOBAL_STACK_TABLE_PERCENT_USED
    };

    ifb_engine::devtools_property_table_render(
        global_stack_table_name,
        global_stack_table_row_count,
        global_stack_table_property_names,
        global_stack_table_property_values);
}

inline ifb_void 
ifb_engine::devtools_property_table_render_memory_system_reservation(
    IFBEngineMemoryReservation& reservation_ref) {

    const ifb_char* reservation_table_name      = IFB_ENGINE_DEVTOOLS_PROPERTY_TABLE_NAME_MEMORY_SYSTEM_RESERVATION;
    const ifb_u32   reservation_table_row_count = 5;

    ifb_char str_reservation_start               [32];
    ifb_char str_reservation_page_count_total    [32];
    ifb_char str_reservation_page_count_committed[32];
    ifb_char str_reservation_commit_count_max    [32];
    ifb_char str_reservation_commit_count_current[32];

    sprintf(str_reservation_start,                "%p", (void*)reservation_ref.start);
    sprintf(str_reservation_page_count_total,     "%d", reservation_ref.page_count_total);
    sprintf(str_reservation_page_count_committed, "%d", reservation_ref.page_count_committed);
    sprintf(str_reservation_commit_count_max,     "%d", reservation_ref.commit_count_max);
    sprintf(str_reservation_commit_count_current, "%d", reservation_ref.commit_count_current);

    const ifb_char* reservation_table_property_values[reservation_table_row_count] = {
        str_reservation_start,
        str_reservation_page_count_total,
        str_reservation_page_count_committed,
        str_reservation_commit_count_max,
        str_reservation_commit_count_current  
    };

    const ifb_char* reservation_table_property_names[reservation_table_row_count] = {
        IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_MEMORY_RESERVATION_TABLE_STARTING_ADDRESS,
        IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_MEMORY_RESERVATION_TABLE_PAGES_TOTAL,
        IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_MEMORY_RESERVATION_TABLE_PAGES_COMMITTED,
        IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_MEMORY_RESERVATION_TABLE_COMMIT_COUNT_MAX,
        IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_MEMORY_RESERVATION_TABLE_COMMIT_COUNT_CURRENT
    };

    ifb_engine::devtools_property_table_render(
        reservation_table_name,
        reservation_table_row_count,
        reservation_table_property_names,
        reservation_table_property_values);

}

inline ifb_void 
ifb_engine::devtools_property_table_render_memory_system_info(
    IFBEngineMemorySystemInfo& system_info) {

    const ifb_char* sys_info_table_name      = IFB_ENGINE_DEVTOOLS_PROPERTY_TABLE_NAME_MEMORY_SYSTEM_INFO;
    const ifb_u32   sys_info_table_row_count = 2;
    
    const ifb_char* sys_info_table_property_names[sys_info_table_row_count] = {
        IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_MEMORY_SYSTEM_INFO_TABLE_PAGE_SIZE,
        IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_MEMORY_SYSTEM_INFO_TABLE_ALLOCATION_GRANULARITY
    };

    ifb_char str_page_size              [32];
    ifb_char str_allocation_granularity [32];

    sprintf(str_page_size,              "%d", system_info.page_size);
    sprintf(str_allocation_granularity, "%d", system_info.allocation_granularity);

    const ifb_char* sys_info_table_property_values[sys_info_table_row_count] = {
        str_page_size,
        str_allocation_granularity
    };

    ifb_engine::devtools_property_table_render(
        sys_info_table_name,
        sys_info_table_row_count,
        sys_info_table_property_names,
        sys_info_table_property_values);
}

inline ifb_void
ifb_engine::devtools_property_table_render(
    const ifb_char*  property_table_name,
    const ifb_u32    property_table_row_count,
    const ifb_char** property_table_property_names,
    const ifb_char** property_table_property_values) {

    //sanity check
    ifb_macro_assert(property_table_name);
    ifb_macro_assert(property_table_row_count > 0);
    ifb_macro_assert(property_table_property_names);
    ifb_macro_assert(property_table_property_values);

    //table start
    if (!ImGui::BeginTable(property_table_name,2,ImGuiTableFlags_RowBg)) {
        return;
    }

    //table rows
    for (
        ifb_u32 row_index = 0;
        row_index < property_table_row_count;
        ++row_index) {

        //get the property
        const ifb_char* property_name  = property_table_property_names [row_index];
        const ifb_char* property_value = property_table_property_values[row_index];

        //start the next row
        ImGui::TableNextRow();

        //property name
        ImGui::TableSetColumnIndex(0);
        ImGui::TextUnformatted(property_name);
        
        //property value
        ImGui::TableSetColumnIndex(1);
        ImGui::TextUnformatted(property_value);
    }

    //table end
    ImGui::EndTable();
}