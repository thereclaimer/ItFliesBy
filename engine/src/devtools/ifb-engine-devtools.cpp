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
    const ifb_b8 devtools_active = ifb_engine::devtools_check_active_status(
        devtools_ptr,
        input_ref);

    //if not, we're done
    if (!devtools_active) return;

    //render the controls
    ifb_engine::devtools_render_menu(devtools_ptr);
    ifb_engine::devtools_render_imgui_demo(devtools_ptr);
    ifb_engine::devtools_memory_render(devtools_ptr->flags.memory);
}

inline const ifb_b8 
ifb_engine::devtools_check_active_status(
    IFBEngineDevTools* devtools_ptr,
    IFBInput&          input_ref) {

    //sanity check
    ifb_macro_assert(devtools_ptr);

    //set hotkey flag if it was pressed
    if (ifb_input::keyboard_key_is_down(input_ref.keyboard,IFBKeyCode_F1)) {
        ifb_engine::devtools_control_flags_set_hotkey_pressed(devtools_ptr->flags.control, true);
    }

    //if the hotkey flag is high and the key is up, it was toggled
    const ifb_b8 hotkey_toggled = 
        ifb_engine::devtools_control_flags_get_hotkey_pressed(devtools_ptr->flags.control) &&
        ifb_input::keyboard_key_is_up(input_ref.keyboard,IFBKeyCode_F1);

    //first, determine if we are turning the tools on or off
    if (hotkey_toggled) {

        const ifb_b8 devtools_active = ifb_engine::devtools_control_flags_get_active(devtools_ptr->flags.control);

        ifb_engine::devtools_control_flags_set_active(devtools_ptr->flags.control, !devtools_active);

        //now, we can clear the hotkey flag and wait till the next toggle
        ifb_engine::devtools_control_flags_set_hotkey_pressed(devtools_ptr->flags.control,false);
    } 

    //get the active status
    const ifb_b8 devtools_active = ifb_engine::devtools_control_flags_get_active(devtools_ptr->flags.control); 

    //we're done
    return(devtools_active);
}

inline ifb_void 
ifb_engine::devtools_render_menu(
    IFBEngineDevTools* devtools_ptr) {

    //sanity check
    ifb_macro_assert(devtools_ptr);

    if (ImGui::BeginMainMenuBar()) {

        if (ImGui::BeginMenu("Engine")) {

            ifb_engine::devtools_render_menu_items(
                devtools_ptr->flags.context,
                IFB_ENGINE_DEVTOOLS_CONTEXT_MENU_ITEM_COUNT,
                IFB_ENGINE_DEVTOOLS_CONTEXT_MENU_ITEM_NAMES,
                IFB_ENGINE_DEVTOOLS_CONTEXT_MENU_ITEM_FLAGS);

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Memory")) {

            ifb_engine::devtools_render_menu_items(
                devtools_ptr->flags.memory,
                IFB_ENGINE_DEVTOOLS_MEMORY_MENU_ITEM_COUNT,
                IFB_ENGINE_DEVTOOLS_MEMORY_MENU_ITEM_NAMES,
                IFB_ENGINE_DEVTOOLS_MEMORY_MENU_ITEM_FLAGS);
                
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Managers")) {

            ifb_engine::devtools_render_menu_items(
                devtools_ptr->flags.managers,
                IFB_ENGINE_DEVTOOLS_MANAGER_MENU_ITEM_COUNT,
                IFB_ENGINE_DEVTOOLS_MANAGER_MENU_ITEM_NAMES,
                IFB_ENGINE_DEVTOOLS_MANAGER_MENU_ITEM_FLAGS);
                
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
}

inline ifb_void 
ifb_engine::devtools_render_menu_items(
          ifb_u32&   menu_item_flags_ref,
    const ifb_u32    menu_item_count,
    const ifb_char** menu_item_names,
    const ifb_u32*   menu_item_flags) {

    ifb_macro_assert(menu_item_count > 0);
    ifb_macro_assert(menu_item_names);
    ifb_macro_assert(menu_item_flags);

    for (
        ifb_u32 menu_item_index = 0;
        menu_item_index < menu_item_count;
        ++menu_item_index) {

        //get the flag and name for the menu item
        const ifb_u32   menu_item_flag = menu_item_flags[menu_item_index];
        const ifb_char* menu_item_name = menu_item_names[menu_item_index]; 

        //get the current selection status
        bool menu_item_selected = menu_item_flags_ref & menu_item_flag;

        //render the menu item and get the user selection
        ImGui::MenuItem(menu_item_name,NULL,&menu_item_selected);

        //update the flag value
        ifb_engine_macro_devtools_set_flag_value(menu_item_flags_ref,menu_item_flag,menu_item_selected);
    }
}

inline ifb_void 
ifb_engine::devtools_render_imgui_demo(
    IFBEngineDevTools* devtools_ptr) {

    bool show_demo = ifb_engine::devtools_context_flags_get_imgui_demo(devtools_ptr->flags.context);
    if (show_demo) {
        ImGui::ShowDemoWindow(&show_demo);
        ifb_engine::devtools_context_flags_set_imgui_demo(devtools_ptr->flags.context, show_demo);
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