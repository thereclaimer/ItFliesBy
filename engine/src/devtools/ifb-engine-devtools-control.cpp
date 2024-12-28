#pragma once

#include "ifb-engine-internal-devtools.hpp"

inline const ifb_b8 
ifb_engine::devtools_control_check_active_status(
    IFBEngineDevToolsFlagsControl& control_flags_ref,
    IFBKeyboard&                   keyboard_ref) {

    //set hotkey flag if it was pressed
    if (ifb_input::keyboard_key_is_down_f1(keyboard_ref)) {
        ifb_engine::devtools_control_flags_set_hotkey_pressed(control_flags_ref, true);
    }

    //if the hotkey flag is high and the key is up, it was toggled
    const ifb_b8 hotkey_toggled = 
        ifb_engine::devtools_control_flags_get_hotkey_pressed(control_flags_ref) &&
        ifb_input::keyboard_key_is_up_f1(keyboard_ref);

    //first, determine if we are turning the tools on or off
    if (hotkey_toggled) {

        const ifb_b8 devtools_active = ifb_engine::devtools_control_flags_get_active(control_flags_ref);

        ifb_engine::devtools_control_flags_set_active(control_flags_ref, !devtools_active);

        //now, we can clear the hotkey flag and wait till the next toggle
        ifb_engine::devtools_control_flags_set_hotkey_pressed(control_flags_ref,false);
    } 

    //get the active status
    const ifb_b8 devtools_active = ifb_engine::devtools_control_flags_get_active(control_flags_ref); 

    //we're done
    return(devtools_active);


}