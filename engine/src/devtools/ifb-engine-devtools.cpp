#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-internal-devtools.hpp"

inline ifb_void 
ifb_engine::devtools_initialize(
    IFBEngineDevTools* devtools_ptr) {

    devtools_ptr->flags = IFBEngineDevToolsFlags_None;
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

    //render the menu
    ifb_engine::devtools_render_menu(devtools_ptr);

    //render the demo
    bool show_demo = ifb_engine::devtools_flags_get_imgui_demo(devtools_ptr->flags);
    if (show_demo) {
        ImGui::ShowDemoWindow(&show_demo);
        ifb_engine::devtools_flags_set_imgui_demo(devtools_ptr->flags, show_demo);
    }
}

inline const ifb_b8 
ifb_engine::devtools_check_active_status(
    IFBEngineDevTools* devtools_ptr,
    IFBInput&          input_ref) {

    //sanity check
    ifb_macro_assert(devtools_ptr);

    //set hotkey flag if it was pressed
    if (ifb_input::keyboard_key_is_down(input_ref.keyboard,IFBKeyCode_F1)) {
        ifb_engine::devtools_flags_set_hotkey_pressed(devtools_ptr->flags, true);
    }

    //if the hotkey flag is high and the key is up, it was toggled
    const ifb_b8 hotkey_toggled = 
        ifb_engine::devtools_flags_get_hotkey_pressed(devtools_ptr->flags) &&
        ifb_input::keyboard_key_is_up(input_ref.keyboard,IFBKeyCode_F1);

    //first, determine if we are turning the tools on or off
    if (hotkey_toggled) {

        const ifb_b8 devtools_active = ifb_engine::devtools_flags_get_active(devtools_ptr->flags);

        ifb_engine::devtools_flags_set_active(devtools_ptr->flags, !devtools_active);

        //now, we can clear the hotkey flag and wait till the next toggle
        ifb_engine::devtools_flags_clear_hotkey_pressed(devtools_ptr->flags);
    } 

    //get the active status
    const ifb_b8 devtools_active = ifb_engine::devtools_flags_get_active(devtools_ptr->flags); 

    //we're done
    return(devtools_active);
}

inline ifb_void 
ifb_engine::devtools_render_menu(
    IFBEngineDevTools* devtools_ptr) {

    //sanity check
    ifb_macro_assert(devtools_ptr);

    ifb_local bool selected = false;

    if (ImGui::BeginMainMenuBar()) {

        if (ImGui::BeginMenu("File")) {

            ImGui::MenuItem("Exit",NULL,&selected);
            ifb_engine::devtools_flags_set_quit_received(devtools_ptr->flags, selected);

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("ImGui")) {

            ImGui::MenuItem("Demo",NULL,&selected);
            ifb_engine::devtools_flags_set_imgui_demo(devtools_ptr->flags, selected);

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}
