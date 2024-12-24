#pragma once

#include "ifb-engine-internal-devtools.hpp"
#include "ifb-engine-internal-context.hpp"

inline ifb_void
ifb_engine::devtools_memory_render(
    IFBEngineDevToolsMemoryFlags& memory_flags_ref) {

    bool enabled = memory_flags_ref > IFBEngineDevToolsMemoryFlags_None; 

    if (!enabled || !ImGui::Begin("Memory",&enabled)) {
        return;
    }

    //get the memory reference
    IFBEngineMemory* context_memory_ptr = ifb_engine::context_get_memory();
    ifb_macro_assert(context_memory_ptr);

    if (ImGui::BeginTabBar("memory-tab-bar")) {

        //render the controls
        ifb_engine::devtools_memory_render_global_stack      (memory_flags_ref,context_memory_ptr);
        ifb_engine::devtools_memory_render_system_reservation(memory_flags_ref,context_memory_ptr);

        ImGui::EndTabBar();
    }
    //if the window was closed, turn off the flags
    if (!enabled) {
        memory_flags_ref = IFBEngineDevToolsMemoryFlags_None;
    }

    ImGui::End();
}

inline ifb_void
ifb_engine::devtools_memory_render_global_stack(
    IFBEngineDevToolsMemoryFlags& memory_flags_ref,
    IFBEngineMemory*              engine_memory_ptr) {

    //get the flag, if its not enabled we're done
    bool enabled = ifb_engine::devtools_memory_flags_get_global_stack(memory_flags_ref);
    if (!enabled) return;

    //make sure our engine memory is valid
    ifb_macro_assert(engine_memory_ptr);

    if (ImGui::BeginTabItem("Global Stack",&enabled)) {

        ImGui::EndTabItem();
    }

    //update the flag
    ifb_engine::devtools_memory_flags_set_global_stack(memory_flags_ref,enabled);
}

inline ifb_void
ifb_engine::devtools_memory_render_system_reservation(
    IFBEngineDevToolsMemoryFlags& memory_flags_ref,
    IFBEngineMemory*              engine_memory_ptr) {

    //get the flag, if its not enabled we're done
    bool enabled = ifb_engine::devtools_memory_flags_get_system_reservation(memory_flags_ref);
    if (!enabled) return;

    //make sure our engine memory is valid
    ifb_macro_assert(engine_memory_ptr);

    if (ImGui::BeginTabItem("System Reservation",&enabled)) {

        ImGui::EndTabItem();
    }

    //update the flag
    ifb_engine::devtools_memory_flags_set_system_reservation(memory_flags_ref,enabled);
}