#pragma once

#include <stdio.h>

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

        IFBEngineMemoryGlobalStack& global_stack_ref = engine_memory_ptr->global_stack;

        if (ImGui::BeginTable("global-stack-table",2,ImGuiTableFlags_RowBg)) {

            ifb_char stack_size_str      [32];
            ifb_char stack_position_str  [32];
            ifb_char stack_percentage_str[32];

            const ifb_f32 stack_percent_used = 
                (ifb_f32)global_stack_ref.position /
                (ifb_f32)global_stack_ref.size;

            sprintf(stack_size_str,      "%d",     global_stack_ref.size);
            sprintf(stack_position_str,  "%d",     global_stack_ref.position);
            sprintf(stack_percentage_str,"%.2f%%", stack_percent_used);

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::TextUnformatted("Stack Size");
            ImGui::TableSetColumnIndex(1);
            ImGui::TextUnformatted(stack_size_str);

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::TextUnformatted("Stack Position");
            ImGui::TableSetColumnIndex(1);
            ImGui::TextUnformatted(stack_position_str);

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::TextUnformatted("Percentage Used");
            ImGui::TableSetColumnIndex(1);
            ImGui::TextUnformatted(stack_percentage_str);

            ImGui::EndTable();
        }

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