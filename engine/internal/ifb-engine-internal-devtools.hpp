#ifndef IFB_ENGINE_INTERNAL_DEVTOOLS_HPP
#define IFB_ENGINE_INTERNAL_DEVTOOLS_HPP

#include "ifb-engine.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBEngineDevTools;

typedef ifb_u32 IFBEngineDevToolsFlags;
typedef ifb_u32 IFBEngineDevToolsManagerFlags;
typedef ifb_u32 IFBEngineDevToolsMemoryFlags;
typedef ifb_u32 IFBEngineDevToolsEngineContextFlags;

#define ifb_engine_macro_devtools_set_flag_value(flags_u32, flag_bit, value_b8) flags_u32 = value_b8 ? (flags_u32 | flag_bit) : (flags_u32 & ~(flag_bit))

#define IFB_ENGINE_DEVTOOLS_PROPERTY_STRING_LENGTH 32

/**********************************************************************************/
/* FLAGS                                                                          */
/**********************************************************************************/

enum IFBEngineDevToolsFlags_ {
    IFBEngineDevToolsFlags_None          = 0,
    IFBEngineDevToolsFlags_HotKeyPressed = (1 << 0),
    IFBEngineDevToolsFlags_Active        = (1 << 1),
    IFBEngineDevToolsFlags_QuitReceived  = (1 << 2),
    IFBEngineDevToolsFlags_ImGuiDemo     = (1 << 3),
};

ifb_global const ifb_char* IFB_ENGINE_DEVTOOLS_ENGINE_MENU_ITEM_NAMES[] = {
    "ImGui Demo",
    "Exit"
};

ifb_global const IFBEngineDevToolsFlags IFB_ENGINE_DEVTOOLS_ENGINE_MENU_ITEM_FLAGS[] = {
    IFBEngineDevToolsFlags_ImGuiDemo,
    IFBEngineDevToolsFlags_QuitReceived
};

ifb_global const ifb_u32 IFB_ENGINE_DEVTOOLS_ENGINE_MENU_ITEM_COUNT = 
    sizeof(IFB_ENGINE_DEVTOOLS_ENGINE_MENU_ITEM_FLAGS) / sizeof(IFBEngineDevToolsFlags);

namespace ifb_engine {

    //set flags
    inline ifb_void devtools_flags_set_hotkey_pressed     (IFBEngineDevToolsFlags& devtools_flags, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(devtools_flags,IFBEngineDevToolsFlags_HotKeyPressed, value); } 
    inline ifb_void devtools_flags_set_active             (IFBEngineDevToolsFlags& devtools_flags, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(devtools_flags,IFBEngineDevToolsFlags_Active,        value); } 
    inline ifb_void devtools_flags_set_quit_received      (IFBEngineDevToolsFlags& devtools_flags, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(devtools_flags,IFBEngineDevToolsFlags_QuitReceived,  value); } 
    inline ifb_void devtools_flags_set_imgui_demo         (IFBEngineDevToolsFlags& devtools_flags, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(devtools_flags,IFBEngineDevToolsFlags_ImGuiDemo,     value); } 

    //get flags
    inline const ifb_b8 devtools_flags_get_hotkey_pressed (const IFBEngineDevToolsFlags devtools_flags) { return(devtools_flags & IFBEngineDevToolsFlags_HotKeyPressed); }
    inline const ifb_b8 devtools_flags_get_active         (const IFBEngineDevToolsFlags devtools_flags) { return(devtools_flags & IFBEngineDevToolsFlags_Active);        }
    inline const ifb_b8 devtools_flags_get_quit_received  (const IFBEngineDevToolsFlags devtools_flags) { return(devtools_flags & IFBEngineDevToolsFlags_QuitReceived);  }
    inline const ifb_b8 devtools_flags_get_imgui_demo     (const IFBEngineDevToolsFlags devtools_flags) { return(devtools_flags & IFBEngineDevToolsFlags_ImGuiDemo);     }
};


/**********************************************************************************/
/* CONTEXT TOOLS                                                                  */
/**********************************************************************************/

enum IFBEngineDevToolsEngineContextFlags_ {
    IFBEngineDevToolsEngineContextFlags_None       = 0,
    IFBEngineDevToolsEngineContextFlags_Context    = (1 << 0),
    IFBEngineDevToolsEngineContextFlags_SystemInfo = (1 << 1),
    IFBEngineDevToolsEngineContextFlags_UserInput  = (1 << 2)
};

namespace ifb_engine {

    ifb_void devtools_engine_context_render(IFBEngineDevToolsEngineContextFlags& devtools_context_flags);

    inline ifb_void devtools_engine_context_flags_set_context (IFBEngineDevToolsEngineContextFlags& devtools_context_flags, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(devtools_context_flags, IFBEngineDevToolsEngineContextFlags_Context, value); }

    const ifb_b8 devtools_engine_context_flags_get_context    (IFBEngineDevToolsEngineContextFlags& devtools_context_flags) { return(devtools_context_flags & IFBEngineDevToolsEngineContextFlags_Context); }
};


/**********************************************************************************/
/* MANAGER TOOLS                                                                  */
/**********************************************************************************/

enum IFBEngineDevToolsManagerFlags_ {
    IFBEngineDevToolsManagerFlags_None     = 0,
    IFBEngineDevToolsManagerFlags_Tag      = (1 << 0),
    IFBEngineDevToolsManagerFlags_Arena    = (1 << 1),
    IFBEngineDevToolsManagerFlags_Graphics = (1 << 2)
};

ifb_global const ifb_char* IFB_ENGINE_DEVTOOLS_MANAGER_MENU_ITEM_NAMES[] = {
    "Tag Manager",
    "Arena Manager",
    "Graphics Manager"
};

ifb_global const IFBEngineDevToolsManagerFlags IFB_ENGINE_DEVTOOLS_MANAGER_MENU_ITEM_FLAGS[] = {
    IFBEngineDevToolsManagerFlags_Tag,
    IFBEngineDevToolsManagerFlags_Arena,
    IFBEngineDevToolsManagerFlags_Graphics
};

ifb_global const ifb_u32 IFB_ENGINE_DEVTOOLS_MANAGER_MENU_ITEM_COUNT = 
    sizeof(IFB_ENGINE_DEVTOOLS_MANAGER_MENU_ITEM_FLAGS) / sizeof(IFBEngineDevToolsManagerFlags);

namespace ifb_engine {

    inline ifb_void devtools_manager_flags_set_tag      (IFBEngineDevToolsManagerFlags& devtools_manager_flags, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(devtools_manager_flags, IFBEngineDevToolsManagerFlags_Tag,      value); }
    inline ifb_void devtools_manager_flags_set_arena    (IFBEngineDevToolsManagerFlags& devtools_manager_flags, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(devtools_manager_flags, IFBEngineDevToolsManagerFlags_Arena,    value); }
    inline ifb_void devtools_manager_flags_set_graphics (IFBEngineDevToolsManagerFlags& devtools_manager_flags, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(devtools_manager_flags, IFBEngineDevToolsManagerFlags_Graphics, value); }

    const ifb_b8 devtools_manager_flags_get_tag         (IFBEngineDevToolsManagerFlags& devtools_manager_flags) { return(devtools_manager_flags & IFBEngineDevToolsManagerFlags_Tag);      }
    const ifb_b8 devtools_manager_flags_get_arena       (IFBEngineDevToolsManagerFlags& devtools_manager_flags) { return(devtools_manager_flags & IFBEngineDevToolsManagerFlags_Arena);    }
    const ifb_b8 devtools_manager_flags_get_graphics    (IFBEngineDevToolsManagerFlags& devtools_manager_flags) { return(devtools_manager_flags & IFBEngineDevToolsManagerFlags_Graphics); }
};

/**********************************************************************************/
/* MEMORY TOOLS                                                                   */
/**********************************************************************************/

enum IFBEngineDevToolsMemoryFlags_ {
    IFBEngineDevToolsMemoryFlags_None              = 0,
    IFBEngineDevToolsMemoryFlags_GlobalStack       = (1 << 0),
    IFBEngineDevToolsMemoryFlags_SystemReservation = (1 << 1),
    IFBEngineDevToolsMemoryFlags_SystemInfo        = (1 << 2),
};

ifb_global const ifb_char* IFB_ENGINE_DEVTOOLS_MEMORY_MENU_ITEM_NAMES[] = {
    "Global Stack",
    "System Reservation",
    "System Info"
};

ifb_global const IFBEngineDevToolsMemoryFlags IFB_ENGINE_DEVTOOLS_MEMORY_MENU_ITEM_FLAGS[] = {
    IFBEngineDevToolsMemoryFlags_GlobalStack,
    IFBEngineDevToolsMemoryFlags_SystemReservation,
    IFBEngineDevToolsMemoryFlags_SystemInfo
};

ifb_global const ifb_u32 IFB_ENGINE_DEVTOOLS_MEMORY_MENU_ITEM_COUNT = 
    sizeof(IFB_ENGINE_DEVTOOLS_MEMORY_MENU_ITEM_FLAGS) / sizeof(IFBEngineDevToolsMemoryFlags);

struct IFBEngineDevToolsMemoryGlobalStackProperties {
    ifb_char size    [IFB_ENGINE_DEVTOOLS_PROPERTY_STRING_LENGTH];
    ifb_char position[IFB_ENGINE_DEVTOOLS_PROPERTY_STRING_LENGTH];
    ifb_char percent [IFB_ENGINE_DEVTOOLS_PROPERTY_STRING_LENGTH];
};

struct IFBEngineDevToolsMemoryGlobalStack {
    IFBEngineDevToolsMemoryGlobalStackProperties names;
    IFBEngineDevToolsMemoryGlobalStackProperties values;
};

struct IFBEngineDevToolsMemorySystemReservationProperties {
    ifb_char start               [IFB_ENGINE_DEVTOOLS_PROPERTY_STRING_LENGTH];
    ifb_char page_count_total    [IFB_ENGINE_DEVTOOLS_PROPERTY_STRING_LENGTH];
    ifb_char page_count_committed[IFB_ENGINE_DEVTOOLS_PROPERTY_STRING_LENGTH];
    ifb_char commit_count_max    [IFB_ENGINE_DEVTOOLS_PROPERTY_STRING_LENGTH];
    ifb_char commit_count_current[IFB_ENGINE_DEVTOOLS_PROPERTY_STRING_LENGTH];
};

struct IFBEngineDevToolsMemorySystemReservation {
    IFBEngineDevToolsMemorySystemReservationProperties names;
    IFBEngineDevToolsMemorySystemReservationProperties values;
};

struct IFBEngineDevToolsMemorySystemInfoProperties {
    ifb_char page_size              [IFB_ENGINE_DEVTOOLS_PROPERTY_STRING_LENGTH];
    ifb_char allocation_granularity [IFB_ENGINE_DEVTOOLS_PROPERTY_STRING_LENGTH];
};

struct IFBEngineDevToolsMemorySystemInfo {
    IFBEngineDevToolsMemorySystemInfoProperties names;
    IFBEngineDevToolsMemorySystemInfoProperties values;
};

namespace ifb_engine {

    ifb_void devtools_memory_render                    (IFBEngineDevToolsMemoryFlags& memory_flags_ref);
    ifb_void devtools_memory_render_global_stack       (IFBEngineDevToolsMemoryFlags& memory_flags_ref, IFBEngineMemory* engine_memory_ptr);
    ifb_void devtools_memory_render_system_reservation (IFBEngineDevToolsMemoryFlags& memory_flags_ref, IFBEngineMemory* engine_memory_ptr);
    ifb_void devtools_memory_render_system_info        (IFBEngineDevToolsMemoryFlags& memory_flags_ref, IFBEngineMemory* engine_memory_ptr);

    ifb_void devtools_memory_get_global_stack_info       (IFBEngineDevToolsMemoryGlobalStack&       dev_global_stack_ref,       IFBEngineMemory* engine_memory_ptr);
    ifb_void devtools_memory_get_system_reservation_info (IFBEngineDevToolsMemorySystemReservation& dev_system_reservation_ref, IFBEngineMemory* engine_memory_ptr);
    ifb_void devtools_memory_get_system_info             (IFBEngineDevToolsMemorySystemInfo&        dev_system_info_ref,        IFBEngineMemory* engine_memory_ptr);

    const ifb_b8 devtools_memory_flags_get_global_stack       (const IFBEngineDevToolsMemoryFlags memory_flags) { return(memory_flags & IFBEngineDevToolsMemoryFlags_GlobalStack);       }
    const ifb_b8 devtools_memory_flags_get_system_reservation (const IFBEngineDevToolsMemoryFlags memory_flags) { return(memory_flags & IFBEngineDevToolsMemoryFlags_SystemReservation); }
    const ifb_b8 devtools_memory_flags_get_system_info        (const IFBEngineDevToolsMemoryFlags memory_flags) { return(memory_flags & IFBEngineDevToolsMemoryFlags_SystemInfo);        }

    inline ifb_void devtools_memory_flags_set_global_stack       (IFBEngineDevToolsMemoryFlags& memory_flags_ref, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(memory_flags_ref, IFBEngineDevToolsMemoryFlags_GlobalStack,        value); }
    inline ifb_void devtools_memory_flags_set_system_reservation (IFBEngineDevToolsMemoryFlags& memory_flags_ref, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(memory_flags_ref, IFBEngineDevToolsMemoryFlags_SystemReservation,  value); }
    inline ifb_void devtools_memory_flags_set_system_info        (IFBEngineDevToolsMemoryFlags& memory_flags_ref, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(memory_flags_ref, IFBEngineDevToolsMemoryFlags_SystemInfo,         value); }

};

/**********************************************************************************/
/* DEVTOOLS                                                                       */
/**********************************************************************************/

struct IFBEngineDevTools {
    IFBEngineDevToolsFlags              flags;
    IFBEngineDevToolsEngineContextFlags engine_context_flags;
    IFBEngineDevToolsMemoryFlags        memory_flags;
    IFBEngineDevToolsManagerFlags       manager_flags;
};

namespace ifb_engine {

    ifb_void devtools_initialize  (IFBEngineDevTools* devtools_ptr);
    ifb_void devtools_update      (IFBEngineDevTools* devtools_ptr, IFBInput& input_ref);
    ifb_void devtools_render_menu (IFBEngineDevTools* devtools_ptr);
    
    const ifb_b8 devtools_check_active_status(IFBEngineDevTools* devtools_ptr, IFBInput& input_ref);
    
    ifb_void devtools_render_imgui_demo(IFBEngineDevTools* devtools_ptr);

    ifb_void devtools_render_menu_items(
              ifb_u32&   menu_item_flags_ref,
        const ifb_u32    menu_item_count,
        const ifb_char** menu_item_names,
        const ifb_u32*   menu_item_flag_bits);

    ifb_void devtools_render_property_table(
        const ifb_char*  table_name,
        const ifb_u32    table_row_count,
        const ifb_char** table_property_names,
        const ifb_char** table_property_values);
};

#endif //IFB_ENGINE_INTERNAL_DEVTOOLS_HPP