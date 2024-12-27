#pragma once

#include <stdio.h>

#include "ifb-engine-internal-devtools.hpp"

inline ifb_void 
ifb_engine::devtools_context_render_window(
    IFBEngineDevToolsFlagsContext& devtools_context_flags) {

    IFBEngineContext& engine_context = ifb_engine::context();

    ifb_engine::devtools_context_render_tab_bar(
        devtools_context_flags,
        &engine_context);
}

inline ifb_void 
ifb_engine::devtools_context_render_tab_bar(
    IFBEngineDevToolsFlagsContext& devtools_context_flags, 
    IFBEngineContext*              engine_context) {

    //sanity check
    ifb_macro_assert(engine_context);

    //tab bar title and tab count
    const ifb_u32   tab_item_count = 3;
    const ifb_char* tab_bar_title  = "context-tab-bar";

    //tab callbacks
    const funcptr_devtools_render_tab_items_callback tab_item_callbacks[tab_item_count] = {
        (funcptr_devtools_render_tab_items_callback)ifb_engine::devtools_context_render_tab_data_context,
        (funcptr_devtools_render_tab_items_callback)ifb_engine::devtools_context_render_tab_data_system_info,
        (funcptr_devtools_render_tab_items_callback)ifb_engine::devtools_context_render_tab_data_user_input,
    };

    //flag bits
    const IFBEngineDevToolsFlagsContext tab_item_flag_bits[tab_item_count] = {
        IFBEngineDevToolsFlagsContext_Context,
        IFBEngineDevToolsFlagsContext_SystemInfo,
        IFBEngineDevToolsFlagsContext_UserInput
    };

    const ifb_char* tab_item_titles[tab_item_count] = {
        "Context Structure",
        "System Info",
        "User Input"
    };

    //render the tab bar
    ifb_engine::devtools_render_tab_bar(
        devtools_context_flags,
        engine_context,
        tab_bar_title,
        tab_item_count,
        tab_item_titles,
        tab_item_callbacks,
        tab_item_flag_bits);
}


inline ifb_void 
ifb_engine::devtools_context_render_tab_data_context(
    IFBEngineContext* engine_context) {

    //----------------------------
    // size table
    //----------------------------

    if (ImGui::CollapsingHeader("Sizes")) {

        //sizes
        const ifb_u32 size_context = sizeof(IFBEngineContext);
        const ifb_u32 size_memory  = sizeof(IFBEngineMemory);
        const ifb_u32 size_handles = sizeof(engine_context->handles);  
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
        const ifb_u32 handle_managers = engine_context->handles.managers.offset;
        const ifb_u32 handle_core     = engine_context->handles.core.offset;
        const ifb_u32 handle_devtools = engine_context->handles.devtools.offset;

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
ifb_engine::devtools_context_render_tab_data_system_info(
    IFBEngineContext* engine_context) {

}

inline ifb_void 
ifb_engine::devtools_context_render_tab_data_user_input(
    IFBEngineContext* engine_context) {

}

inline ifb_void 
ifb_engine::devtools_context_render_imgui_demo(
    IFBEngineDevToolsFlagsContext& devtools_context_flags) {

    bool show_demo = ifb_engine::devtools_context_flags_get_imgui_demo(devtools_context_flags);
    if (show_demo) {
        ImGui::ShowDemoWindow(&show_demo);
        ifb_engine::devtools_context_flags_set_imgui_demo(devtools_context_flags, show_demo);
    }
}

