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

    //size table
    if (ImGui::CollapsingHeader("Sizes")) {
        ifb_engine::devtools_property_table_render_context_sizes(context_ptr);
    }

    //handles table
    if (ImGui::CollapsingHeader("Handles")) {
        ifb_engine::devtools_property_table_render_context_handles(context_ptr);
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
    ifb_engine::devtools_property_table_render_context_config(context_ptr->config);
}

/**********************************************************************************/
/* MEMORY TAB ITEMS                                                               */
/**********************************************************************************/

inline ifb_void
ifb_engine::devtools_tab_item_render_callback_memory_global_stack(
    IFBEngineMemory* memory_ptr) {
    
    ifb_macro_assert(memory_ptr);
    ifb_engine::devtools_property_table_render_memory_global_stack(memory_ptr->global_stack);
}

inline ifb_void
ifb_engine::devtools_tab_item_render_callback_memory_system_reservation(
    IFBEngineMemory* memory_ptr) {

    ifb_macro_assert(memory_ptr);
    ifb_engine::devtools_property_table_render_memory_system_reservation(memory_ptr->reservation);
}

inline ifb_void
ifb_engine::devtools_tab_item_render_callback_memory_system_info(
    IFBEngineMemory* memory_ptr) {

    ifb_macro_assert(memory_ptr);
    ifb_engine::devtools_property_table_render_memory_system_info(memory_ptr->system_info);
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