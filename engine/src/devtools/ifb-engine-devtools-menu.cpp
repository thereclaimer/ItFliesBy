#pragma once

#include "ifb-engine-internal-devtools.hpp"

inline ifb_void 
ifb_engine::devtools_menu_render_main_bar(
    IFBEngineDevTools* devtools_ptr) {

    //sanity check
    ifb_macro_assert(devtools_ptr);

    if (ImGui::BeginMainMenuBar()) {

        ifb_engine::devtools_menu_render_context (devtools_ptr->flags.context);
        ifb_engine::devtools_menu_render_memory  (devtools_ptr->flags.memory);
        ifb_engine::devtools_menu_render_managers(devtools_ptr->flags.managers);

        ImGui::EndMainMenuBar();
    }     
}

inline ifb_void 
ifb_engine::devtools_menu_render_context(
    IFBEngineDevToolsFlagsContext& context_flags_ref) {

    ifb_engine::devtools_render_menu(
        context_flags_ref,
        IFB_ENGINE_DEVTOOLS_MENU_TITLE_ENGINE,
        IFB_ENGINE_DEVTOOLS_MENU_ITEM_COUNT_CONTEXT,
        IFB_ENGINE_DEVTOOLS_MENU_ITEM_NAMES_CONTEXT,
        IFB_ENGINE_DEVTOOLS_MENU_ITEM_FLAGS_CONTEXT);
}

inline ifb_void 
ifb_engine::devtools_menu_render_memory(
    IFBEngineDevToolsFlagsMemory& memory_flags_ref) {

    ifb_engine::devtools_render_menu(
        memory_flags_ref,
        IFB_ENGINE_DEVTOOLS_MENU_TITLE_MEMORY,
        IFB_ENGINE_DEVTOOLS_MENU_ITEM_COUNT_MEMORY,
        IFB_ENGINE_DEVTOOLS_MENU_ITEM_NAMES_MEMORY,
        IFB_ENGINE_DEVTOOLS_MENU_ITEM_FLAGS_MEMORY);
}

inline ifb_void 
ifb_engine::devtools_menu_render_managers(
    IFBEngineDevToolsFlagsManagers& managers_flags_ref) {

    ifb_engine::devtools_render_menu(
        managers_flags_ref,
        IFB_ENGINE_DEVTOOLS_MENU_TITLE_MANAGERS,
        IFB_ENGINE_DEVTOOLS_MENU_ITEM_COUNT_MANAGERS,
        IFB_ENGINE_DEVTOOLS_MENU_ITEM_NAMES_MANAGERS,
        IFB_ENGINE_DEVTOOLS_MENU_ITEM_FLAGS_MANAGERS);
}