#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-internal-devtools.hpp"

inline ifb_void 
ifb_engine::devtools_initialize(
    IFBEngineDevTools* devtools_ptr) {

    devtools_ptr->flags.control  = IFBEngineDevToolsFlagsControl_None;
    devtools_ptr->flags.context  = IFBEngineDevToolsFlagsContext_None;
    devtools_ptr->flags.memory   = IFBEngineDevToolsFlagsMemory_None;
    devtools_ptr->flags.managers = IFBEngineDevToolsFlagsManagers_None;
}

inline ifb_void 
ifb_engine::devtools_update(
    IFBEngineDevTools* devtools_ptr,
    IFBInput&          input_ref) {

    //check if the devtools are active
    const ifb_b8 devtools_active = ifb_engine::devtools_control_check_active_status(
        devtools_ptr->flags.control,
        input_ref.keyboard);

    //if not, we're done
    if (!devtools_active) return;

    //render the controls
    ifb_engine::devtools_menu_render_main_bar(devtools_ptr);
    ifb_engine::devtools_context_render(devtools_ptr->flags.context);
    ifb_engine::devtools_memory_render(devtools_ptr->flags.memory);
}

inline ifb_void 
ifb_engine::devtools_render_menu(
          ifb_u32&   menu_flags_ref,
    const ifb_char*  menu_title,
    const ifb_u32    menu_item_count,
    const ifb_char** menu_item_names,
    const ifb_u32*   menu_item_flag_bits) {

    ifb_macro_assert(menu_title);
    ifb_macro_assert(menu_item_count > 0);
    ifb_macro_assert(menu_item_names);
    ifb_macro_assert(menu_item_flag_bits);

    if (ImGui::BeginMenu(menu_title)) {

        for (
            ifb_u32 menu_item_index = 0;
            menu_item_index < menu_item_count;
            ++menu_item_index) {

            //get the flag and name for the menu item
            const ifb_u32   menu_item_flag = menu_item_flag_bits[menu_item_index];
            const ifb_char* menu_item_name = menu_item_names    [menu_item_index]; 

            //get the current selection status
            bool menu_item_selected = menu_flags_ref & menu_item_flag;

            //render the menu item and get the user selection
            ImGui::MenuItem(menu_item_name,NULL,&menu_item_selected);

            //update the flag value
            ifb_engine_macro_devtools_set_flag_value(menu_flags_ref,menu_item_flag,menu_item_selected);
        }
    
        ImGui::EndMenu();
    }
}

inline ifb_void 
ifb_engine::devtools_render_property_table(
    const ifb_char*  table_name,
    const ifb_u32    table_row_count,
    const ifb_char** table_property_names,
    const ifb_char** table_property_values) {

    //sanity check
    ifb_macro_assert(table_name);
    ifb_macro_assert(table_row_count > 0);
    ifb_macro_assert(table_property_names);
    ifb_macro_assert(table_property_values);

    if (ImGui::BeginTable(table_name,2,ImGuiTableFlags_RowBg)) {

        for (
            ifb_u32 row_index = 0;
            row_index < table_row_count;
            ++row_index) {

            //get the property
            const ifb_char* property_name  = table_property_names [row_index];
            const ifb_char* property_value = table_property_values[row_index];

            //start the next row
            ImGui::TableNextRow();

            //property name
            ImGui::TableSetColumnIndex(0);
            ImGui::TextUnformatted(property_name);
            
            //property value
            ImGui::TableSetColumnIndex(1);
            ImGui::TextUnformatted(property_value);
        }

        ImGui::EndTable();
    }
}

inline ifb_void
ifb_engine::devtools_render_tab_bar(
          ifb_u32&                                    tab_item_flags_ref,
          ifb_void*                                   tab_item_data,
    const ifb_char*                                   tab_bar_title,
    const ifb_u32                                     tab_item_count,
    const ifb_char**                                  tab_item_titles,
    const funcptr_devtools_render_tab_items_callback* tab_item_callbacks,
    const ifb_u32*                                    tab_item_flag_bits) {

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
        const funcptr_devtools_render_tab_items_callback tab_item_callback = tab_item_callbacks[tab_item_index];
        const ifb_char* tab_item_title    = tab_item_titles[tab_item_index];
        const ifb_u32   tab_item_flag_bit = tab_item_flag_bits[tab_item_index];

        //check if the tab is enabled
        tab_item_enabled = tab_item_flags_ref & tab_item_flag_bit;

        //tab begin
        if (!tab_item_enabled || !ImGui::BeginTabItem(tab_item_title,(bool*)&tab_item_enabled)) {
            continue;
        }

        //render the tab specific data
        tab_item_callback(
            tab_item_data,
            tab_item_enabled);

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