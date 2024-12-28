#pragma once

#include "ifb-engine-internal-devtools.hpp"

/**********************************************************************************/
/* TAB BARS                                                                       */
/**********************************************************************************/

inline ifb_void
ifb_engine::devtools_tab_bar_render_context(
    IFBEngineDevToolsFlagsContext& flags_ref_context,
    IFBEngineContext*              context_ptr) {

    //sanity check
    ifb_macro_assert(context_ptr);

    //tab bar title and tab count
    const ifb_char* context_tab_bar_title  = IFB_ENGINE_DEVTOOLS_TAB_BAR_NAME_CONTEXT;
    const ifb_u32   context_tab_item_count = 4;

    //tab callbacks
    const devtools_tab_item_render_callback context_tab_item_callbacks[context_tab_item_count] = {
        IFB_ENGINE_DEVTOOLS_TAB_ITEM_RENDER_CALLBACK_CONTEXT_ENGINE_CONTEXT,
        IFB_ENGINE_DEVTOOLS_TAB_ITEM_RENDER_CALLBACK_CONTEXT_SYSTEM_INFO,
        IFB_ENGINE_DEVTOOLS_TAB_ITEM_RENDER_CALLBACK_CONTEXT_USER_INPUT,
        IFB_ENGINE_DEVTOOLS_TAB_ITEM_RENDER_CALLBACK_CONTEXT_CONFIG,
    };


    //tab item names
    const ifb_char* context_tab_item_names[context_tab_item_count] = {
        IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_CONTEXT_ITEM_CONTEXT_STRUCTURE,
        IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_CONTEXT_ITEM_SYSTEM_INFO,
        IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_CONTEXT_ITEM_USER_INPUT,
        IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_CONTEXT_ITEM_CONFIG
    };

    //flag bits
    const IFBEngineDevToolsFlagsContext context_tab_item_flag_bits[context_tab_item_count] = {
        IFBEngineDevToolsFlagsContext_Context,
        IFBEngineDevToolsFlagsContext_SystemInfo,
        IFBEngineDevToolsFlagsContext_UserInput,
        IFBEngineDevToolsFlagsContext_Config,
    };

    //render the tab bar
    ifb_engine::devtools_tab_bar_render(
        flags_ref_context,
        context_ptr,
        context_tab_bar_title,
        context_tab_item_count,
        context_tab_item_names,
        context_tab_item_callbacks,
        context_tab_item_flag_bits);
}

inline ifb_void 
ifb_engine::devtools_tab_bar_render_memory(
    IFBEngineDevToolsFlagsMemory& memory_flags_ref, 
    IFBEngineMemory*              memory_ptr) {

    //sanity check
    ifb_macro_assert(memory_ptr);

    //tab bar title and tab count
    const ifb_char* memory_tab_bar_title  = IFB_ENGINE_DEVTOOLS_TAB_BAR_NAME_MEMORY; 
    const ifb_u32   memory_tab_item_count = 3;

    const ifb_char* memory_tab_bar_names[memory_tab_item_count] = {
        IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_MEMORY_ITEM_GLOBAL_STACK,
        IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_MEMORY_ITEM_SYSTEM_RESERVATION,
        IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_MEMORY_ITEM_SYSTEM_INFO
    };

    //flag bits
    const IFBEngineDevToolsFlagsMemory memory_tab_item_flag_bits[memory_tab_item_count] = {
        IFBEngineDevToolsFlagsMemory_GlobalStack,
        IFBEngineDevToolsFlagsMemory_SystemReservation,
        IFBEngineDevToolsFlagsMemory_SystemInfo
    };

    //tab callbacks
    const devtools_tab_item_render_callback memory_tab_item_callbacks[memory_tab_item_count] = {
        IFB_ENGINE_DEVTOOLS_TAB_ITEM_RENDER_CALLBACK_MEMORY_GLOBAL_STACK,
        IFB_ENGINE_DEVTOOLS_TAB_ITEM_RENDER_CALLBACK_MEMORY_SYSTEM_RESERVATION,
        IFB_ENGINE_DEVTOOLS_TAB_ITEM_RENDER_CALLBACK_MEMORY_SYSTEM_INFO
    };

    //render the tab bar
    ifb_engine::devtools_tab_bar_render(
        memory_flags_ref,
        memory_ptr,
        memory_tab_bar_title,
        memory_tab_item_count,
        memory_tab_bar_names,
        memory_tab_item_callbacks,
        memory_tab_item_flag_bits);
}

/**********************************************************************************/
/* CONTEXT TAB ITEMS                                                              */
/**********************************************************************************/

inline ifb_void 
ifb_engine::devtools_tab_item_render_callback_context_structure(
    IFBEngineContext* context_ptr) {

    //----------------------------
    // size table
    //----------------------------

    if (ImGui::CollapsingHeader("Sizes")) {

        //sizes
        const ifb_u32 size_context = sizeof(IFBEngineContext);
        const ifb_u32 size_memory  = sizeof(IFBEngineMemory);
        const ifb_u32 size_handles = sizeof(context_ptr->handles);  
        const ifb_u32 size_config  = sizeof(IFBEngineConfig); 

        //size table
        const ifb_char* size_table_name           = "context-sizes-table";
        const ifb_u32   size_table_row_count      = 4;
        const ifb_char* size_table_property_names[size_table_row_count] = {
            "Context Size Total",
            "Memory Size",
            "Handles Size",
            "Config Size"
        };

        //size table properties
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

        //render the size table
        ifb_engine::devtools_render_property_table(
            size_table_name,
            size_table_row_count,
            size_table_property_names,
            size_table_property_values);
    }

    //----------------------------
    // handles table
    //----------------------------

    if (ImGui::CollapsingHeader("Handles")) {

        //handles
        const ifb_u32 handle_managers = context_ptr->handles.managers.offset;
        const ifb_u32 handle_core     = context_ptr->handles.core.offset;
        const ifb_u32 handle_devtools = context_ptr->handles.devtools.offset;

        //handle table
        const ifb_char* handle_table_name           = "context-handle-table";
        const ifb_u32   handle_table_row_count      = 3;
        const ifb_char* handle_table_property_names[handle_table_row_count] = {
            "Managers Handle",
            "Core Handle",
            "DevTools Handle"
        };

        //handle table values
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

        //render the handles table
        ifb_engine::devtools_render_property_table(
            handle_table_name,
            handle_table_row_count,
            handle_table_property_names,
            handle_table_property_values);
    }
}

inline ifb_void 
ifb_engine::devtools_tab_item_render_callback_context_system_info(
    IFBEngineContext* context_ptr) {

    ImGui::TextUnformatted("TODO");
}

inline ifb_void 
ifb_engine::devtools_tab_item_render_callback_context_user_input(
    IFBEngineContext* context_ptr) {

    ImGui::TextUnformatted("TODO");
}

inline ifb_void 
ifb_engine::devtools_tab_item_render_callback_context_config(
    IFBEngineContext* context_ptr) {

    //get the config
    IFBEngineConfig& config_ref = context_ptr->config;

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
        "Minimum Memory Requirement (GB)",
        "Max Memory Commit Count",
        "Global Stack Size (KB)",
        "Arena Minimum Size (KB)",
        "Max Arena Count",
        "Tag Length",
        "Max Tag Count",
        "Use DevTools",
        "Window Title"
    };

    const ifb_char* config_property_table_name = "config-table";
    const ifb_u32   config_property_count      = 9;

    ifb_engine::devtools_render_property_table(
        config_property_table_name,
        config_property_count,
        config_property_names,
        config_property_values);
}

/**********************************************************************************/
/* MEMORY TAB ITEMS                                                               */
/**********************************************************************************/

inline ifb_void
ifb_engine::devtools_tab_item_render_callback_memory_global_stack(
    IFBEngineMemory* memory_ptr) {

    const ifb_char* global_stack_table_name      = "memory-stack-table";
    const ifb_u32   global_stack_table_row_count = 3;

    IFBEngineMemoryGlobalStack& global_stack_ref = memory_ptr->global_stack;
    ifb_f32 stack_percent = (ifb_f32)global_stack_ref.position / (ifb_f32)global_stack_ref.size; 

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
        "Stack Size",
        "Stack Position",
        "Percent Used",
    };

    ifb_engine::devtools_render_property_table(
        global_stack_table_name,
        global_stack_table_row_count,
        global_stack_table_property_names,
        global_stack_table_property_values);

}

inline ifb_void
ifb_engine::devtools_tab_item_render_callback_memory_system_reservation(
    IFBEngineMemory* memory_ptr) {

  const ifb_char* reservation_table_name      = "memory-reservation-table";
    const ifb_u32   reservation_table_row_count = 5;

    ifb_char str_reservation_start               [32];
    ifb_char str_reservation_page_count_total    [32];
    ifb_char str_reservation_page_count_committed[32];
    ifb_char str_reservation_commit_count_max    [32];
    ifb_char str_reservation_commit_count_current[32];

    IFBEngineMemoryReservation& reservation_ref = memory_ptr->reservation;
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
        "Starting Address",
        "Pages Total",
        "Pages Committed",
        "Commit Count Max",
        "Commit Count Current"
    };

    ifb_engine::devtools_render_property_table(
        reservation_table_name,
        reservation_table_row_count,
        reservation_table_property_names,
        reservation_table_property_values);
}

inline ifb_void
ifb_engine::devtools_tab_item_render_callback_memory_system_info(
    IFBEngineMemory* memory_ptr) {

    IFBEngineMemorySystemInfo& sys_info_ref = memory_ptr->system_info;

    const ifb_char* sys_info_table_name      = "memory-sysinfo-table";
    const ifb_u32   sys_info_table_row_count = 2;
    
    const ifb_char* sys_info_table_property_names[sys_info_table_row_count] = {
        "Page Size",
        "Allocation Granularity"
    };

    ifb_char str_page_size              [32];
    ifb_char str_allocation_granularity [32];

    sprintf(str_page_size,              "%d", sys_info_ref.page_size);
    sprintf(str_allocation_granularity, "%d", sys_info_ref.allocation_granularity);

    const ifb_char* sys_info_table_property_values[sys_info_table_row_count] = {
        str_page_size,
        str_allocation_granularity
    };

    ifb_engine::devtools_render_property_table(
        sys_info_table_name,
        sys_info_table_row_count,
        sys_info_table_property_names,
        sys_info_table_property_values);
}

/**********************************************************************************/
/* TAB CONTROL                                                                    */
/**********************************************************************************/

inline ifb_void
ifb_engine::devtools_tab_bar_render(
          ifb_u32&                           tab_item_flags_ref,
          ifb_void*                          tab_item_data,
    const ifb_char*                          tab_bar_title,
    const ifb_u32                            tab_item_count,
    const ifb_char**                         tab_item_titles,
    const devtools_tab_item_render_callback* tab_item_callbacks,
    const ifb_u32*                           tab_item_flag_bits) {

    //tab bar begin
    if (tab_item_flags_ref == 0 || !ImGui::BeginTabBar(tab_bar_title)) {
        return;
    }

    ifb_b8 tab_item_enabled = false;
    for (
        ifb_u32 tab_item_index = 0;
        tab_item_index < tab_item_count;
        ++tab_item_index) {

        //get the data for this tab
        const ifb_char* tab_item_title    = tab_item_titles[tab_item_index];
        const ifb_u32   tab_item_flag_bit = tab_item_flag_bits[tab_item_index];

        //check if the tab is enabled
        tab_item_enabled = tab_item_flags_ref & tab_item_flag_bit;

        //tab begin
        if (!tab_item_enabled || !ImGui::BeginTabItem(tab_item_title,(bool*)&tab_item_enabled)) {
            continue;
        }

        //render the tab specific data
        tab_item_callbacks[tab_item_index](tab_item_data);

        //update the flag value
        ifb_engine_macro_devtools_set_flag_value(
            tab_item_flags_ref,
            tab_item_flag_bit,
            tab_item_enabled);

        //tab end
        ImGui::EndTabItem();
    }

    //tab bar end
    ImGui::EndTabBar();
}