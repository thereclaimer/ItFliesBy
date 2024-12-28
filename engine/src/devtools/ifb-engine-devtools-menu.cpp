#pragma once

#include "ifb-engine-internal-devtools.hpp"

inline ifb_void 
ifb_engine::devtools_menu_bar_render(
    IFBEngineDevTools* devtools_ptr) {

    //sanity check
    ifb_macro_assert(devtools_ptr);

    if (ImGui::BeginMainMenuBar()) {

        ifb_engine::devtools_menu_render_context (devtools_ptr->flags.context);
        ifb_engine::devtools_menu_render_memory  (devtools_ptr->flags.memory);
        ifb_engine::devtools_menu_render_managers(devtools_ptr->flags.managers);
        ifb_engine::devtools_menu_render_tools   (devtools_ptr->flags.tools);

        ImGui::EndMainMenuBar();
    }
}

inline ifb_void 
ifb_engine::devtools_menu_render_context(
    IFBEngineDevToolsFlagsContext& context_flags_ref) {

    const ifb_char* context_menu_name       = IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_CONTEXT;
    const ifb_u32   context_menu_item_count = 5;
    
    const ifb_char* context_menu_items[context_menu_item_count] = {
        IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_CONTEXT_ITEM_CONTEXT_STRUCTURE,
        IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_CONTEXT_ITEM_SYSTEM_INFO,
        IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_CONTEXT_ITEM_USER_INPUT,
        IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_CONTEXT_ITEM_CONFIG,
        IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_CONTEXT_ITEM_EXIT
    };

    const ifb_u32 context_menu_item_flags[context_menu_item_count] = {
        IFBEngineDevToolsFlagsContext_Context,
        IFBEngineDevToolsFlagsContext_SystemInfo,
        IFBEngineDevToolsFlagsContext_UserInput,
        IFBEngineDevToolsFlagsContext_Config,
        IFBEngineDevToolsFlagsContext_Exit        
    };

    ifb_engine::devtools_menu_render(
        context_flags_ref,
        context_menu_name,
        context_menu_item_count,
        context_menu_items,
        context_menu_item_flags);
}

inline ifb_void 
ifb_engine::devtools_menu_render_memory(
    IFBEngineDevToolsFlagsMemory& memory_flags_ref) {

    const ifb_char* memory_menu_name       = IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_MEMORY;
    const ifb_u32   memory_menu_item_count = 3;
    
    const ifb_char* memory_menu_items[memory_menu_item_count] = {
        IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_MEMORY_ITEM_GLOBAL_STACK,
        IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_MEMORY_ITEM_SYSTEM_RESERVATION,
        IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_MEMORY_ITEM_SYSTEM_INFO
    };

    const ifb_u32 memory_menu_item_flags[memory_menu_item_count] = {
        IFBEngineDevToolsFlagsMemory_GlobalStack,
        IFBEngineDevToolsFlagsMemory_SystemReservation,
        IFBEngineDevToolsFlagsMemory_SystemInfo        
    };

    ifb_engine::devtools_menu_render(
        memory_flags_ref,
        memory_menu_name,
        memory_menu_item_count,
        memory_menu_items,
        memory_menu_item_flags);
}

inline ifb_void 
ifb_engine::devtools_menu_render_managers(
    IFBEngineDevToolsFlagsManagers& managers_flags_ref) {

    const ifb_char* managers_menu_name       = IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_MANAGERS;
    const ifb_u32   managers_menu_item_count = 3;
    
    const ifb_char* managers_menu_items[managers_menu_item_count] = {
        IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_MANAGERS_ITEM_TAG_MANAGER,
        IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_MANAGERS_ITEM_ARENA_MANAGER,
        IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_MANAGERS_ITEM_GRAPHICS_MANAGER
    };

    const ifb_u32 managers_menu_item_flags[managers_menu_item_count] = {
        IFBEngineDevToolsFlagsManagers_Tag,
        IFBEngineDevToolsFlagsManagers_Arena,
        IFBEngineDevToolsFlagsManagers_Graphics        
    };

    ifb_engine::devtools_menu_render(
        managers_flags_ref,
        managers_menu_name,
        managers_menu_item_count,
        managers_menu_items,
        managers_menu_item_flags);
}

inline ifb_void 
ifb_engine::devtools_menu_render_tools(
    IFBEngineDevToolsFlagsTools& tools_flags_ref) {

    const ifb_char* tools_menu_name       = IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_TOOLS;
    const ifb_u32   tools_menu_item_count = 1;
    
    const ifb_char* tools_menu_items[tools_menu_item_count] = {
        IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_TOOLS_ITEM_IMGUI_DEMO
    };

    const ifb_u32 tools_menu_item_flags[tools_menu_item_count] = {
        IFBEngineDevToolsFlagsTools_ImGuiDemo,
    };

    ifb_engine::devtools_menu_render(
        tools_flags_ref,
        tools_menu_name,
        tools_menu_item_count,
        tools_menu_items,
        tools_menu_item_flags);
}


inline ifb_void 
ifb_engine::devtools_menu_render(
          ifb_u32&   menu_flags_ref,
    const ifb_char*  menu_title,
    const ifb_u32    menu_item_count,
    const ifb_char** menu_item_names,
    const ifb_u32*   menu_item_flag_bits) {

    ifb_macro_assert(menu_title);
    ifb_macro_assert(menu_item_count > 0);
    ifb_macro_assert(menu_item_names);
    ifb_macro_assert(menu_item_flag_bits);

    //menu start
    if (!ImGui::BeginMenu(menu_title)) {
        return;
    }

    //render menu items
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

    //menu end
    ImGui::EndMenu();
}