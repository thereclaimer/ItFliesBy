#ifndef IFB_ENGINE_INTERNAL_DEVTOOLS_HPP
#define IFB_ENGINE_INTERNAL_DEVTOOLS_HPP

#include "ifb-engine.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBEngineDevTools;

typedef ifb_u32 IFBEngineDevToolsFlagsControl;
typedef ifb_u32 IFBEngineDevToolsFlagsManagers;
typedef ifb_u32 IFBEngineDevToolsFlagsMemory;
typedef ifb_u32 IFBEngineDevToolsFlagsContext;

#define ifb_engine_macro_devtools_set_flag_value(flags_u32, flag_bit, value_b8) flags_u32 = value_b8 ? (flags_u32 | flag_bit) : (flags_u32 & ~(flag_bit))

#define IFB_ENGINE_DEVTOOLS_PROPERTY_STRING_LENGTH 32

/**********************************************************************************/
/* CONTROL                                                                        */
/**********************************************************************************/

enum IFBEngineDevToolsFlagsControl_ {
    IFBEngineDevToolsFlagsControl_None          = 0,
    IFBEngineDevToolsFlagsControl_HotKeyPressed = IFB_BIT_FLAG_0,
    IFBEngineDevToolsFlagsControl_Active        = IFB_BIT_FLAG_1
};

namespace ifb_engine {

    //set flags
    inline ifb_void devtools_control_flags_set_hotkey_pressed     (IFBEngineDevToolsFlagsControl& devtools_flags, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(devtools_flags, IFBEngineDevToolsFlagsControl_HotKeyPressed, value); } 
    inline ifb_void devtools_control_flags_set_active             (IFBEngineDevToolsFlagsControl& devtools_flags, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(devtools_flags, IFBEngineDevToolsFlagsControl_Active,        value); } 

    //get flags
    inline const ifb_b8 devtools_control_flags_get_hotkey_pressed (const IFBEngineDevToolsFlagsControl devtools_flags) { return(devtools_flags & IFBEngineDevToolsFlagsControl_HotKeyPressed); }
    inline const ifb_b8 devtools_control_flags_get_active         (const IFBEngineDevToolsFlagsControl devtools_flags) { return(devtools_flags & IFBEngineDevToolsFlagsControl_Active);        }

    const ifb_b8 
    devtools_control_check_active_status(
        IFBEngineDevToolsFlagsControl& control_flags_ref,
        IFBKeyboard&                   keyboard_ref);
};

/**********************************************************************************/
/* CONTEXT TOOLS                                                                  */
/**********************************************************************************/

enum IFBEngineDevToolsFlagsContext_ {
    IFBEngineDevToolsFlagsContext_None       = 0,
    IFBEngineDevToolsFlagsContext_Context    = IFB_BIT_FLAG_0,
    IFBEngineDevToolsFlagsContext_SystemInfo = IFB_BIT_FLAG_1,
    IFBEngineDevToolsFlagsContext_UserInput  = IFB_BIT_FLAG_2,
    IFBEngineDevToolsFlagsContext_ImGuiDemo  = IFB_BIT_FLAG_3,
    IFBEngineDevToolsFlagsContext_Exit       = IFB_BIT_FLAG_4
};

namespace ifb_engine {

    ifb_void devtools_context_render(IFBEngineDevToolsFlagsContext& devtools_context_flags);

    ifb_void devtools_context_render_context                   (IFBEngineDevToolsFlagsContext& devtools_context_flags);
    ifb_void devtools_context_render_system_info               (IFBEngineDevToolsFlagsContext& devtools_context_flags);
    ifb_void devtools_context_render_user_input                (IFBEngineDevToolsFlagsContext& devtools_context_flags);
    ifb_void devtools_context_render_imgui_demo                (IFBEngineDevToolsFlagsContext& devtools_context_flags);

    inline ifb_void devtools_context_flags_set_context         (IFBEngineDevToolsFlagsContext& devtools_context_flags, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(devtools_context_flags, IFBEngineDevToolsFlagsContext_Context,    value); }
    inline ifb_void devtools_context_flags_set_system_info     (IFBEngineDevToolsFlagsContext& devtools_context_flags, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(devtools_context_flags, IFBEngineDevToolsFlagsContext_SystemInfo, value); }
    inline ifb_void devtools_context_flags_set_user_input      (IFBEngineDevToolsFlagsContext& devtools_context_flags, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(devtools_context_flags, IFBEngineDevToolsFlagsContext_UserInput,  value); }
    inline ifb_void devtools_context_flags_set_imgui_demo      (IFBEngineDevToolsFlagsContext& devtools_context_flags, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(devtools_context_flags, IFBEngineDevToolsFlagsContext_ImGuiDemo,  value); }
    inline ifb_void devtools_context_flags_set_exit            (IFBEngineDevToolsFlagsContext& devtools_context_flags, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(devtools_context_flags, IFBEngineDevToolsFlagsContext_Exit,       value); }

    inline const ifb_b8 devtools_context_flags_get_context     (IFBEngineDevToolsFlagsContext& devtools_context_flags) { return(devtools_context_flags & IFBEngineDevToolsFlagsContext_Context);    }
    inline const ifb_b8 devtools_context_flags_get_system_info (IFBEngineDevToolsFlagsContext& devtools_context_flags) { return(devtools_context_flags & IFBEngineDevToolsFlagsContext_SystemInfo); }
    inline const ifb_b8 devtools_context_flags_get_user_input  (IFBEngineDevToolsFlagsContext& devtools_context_flags) { return(devtools_context_flags & IFBEngineDevToolsFlagsContext_UserInput);  }
    inline const ifb_b8 devtools_context_flags_get_imgui_demo  (IFBEngineDevToolsFlagsContext& devtools_context_flags) { return(devtools_context_flags & IFBEngineDevToolsFlagsContext_ImGuiDemo);  }
    inline const ifb_b8 devtools_context_flags_get_exit        (IFBEngineDevToolsFlagsContext& devtools_context_flags) { return(devtools_context_flags & IFBEngineDevToolsFlagsContext_Exit);       }
};

/**********************************************************************************/
/* MANAGER TOOLS                                                                  */
/**********************************************************************************/

enum IFBEngineDevToolsFlagsManagers_ {
    IFBEngineDevToolsFlagsManagers_None     = 0,
    IFBEngineDevToolsFlagsManagers_Tag      = IFB_BIT_FLAG_0,
    IFBEngineDevToolsFlagsManagers_Arena    = IFB_BIT_FLAG_1,
    IFBEngineDevToolsFlagsManagers_Graphics = IFB_BIT_FLAG_2
};

namespace ifb_engine {

    inline ifb_void devtools_manager_flags_set_tag      (IFBEngineDevToolsFlagsManagers& devtools_manager_flags, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(devtools_manager_flags, IFBEngineDevToolsFlagsManagers_Tag,      value); }
    inline ifb_void devtools_manager_flags_set_arena    (IFBEngineDevToolsFlagsManagers& devtools_manager_flags, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(devtools_manager_flags, IFBEngineDevToolsFlagsManagers_Arena,    value); }
    inline ifb_void devtools_manager_flags_set_graphics (IFBEngineDevToolsFlagsManagers& devtools_manager_flags, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(devtools_manager_flags, IFBEngineDevToolsFlagsManagers_Graphics, value); }

    const ifb_b8 devtools_manager_flags_get_tag         (IFBEngineDevToolsFlagsManagers& devtools_manager_flags) { return(devtools_manager_flags & IFBEngineDevToolsFlagsManagers_Tag);      }
    const ifb_b8 devtools_manager_flags_get_arena       (IFBEngineDevToolsFlagsManagers& devtools_manager_flags) { return(devtools_manager_flags & IFBEngineDevToolsFlagsManagers_Arena);    }
    const ifb_b8 devtools_manager_flags_get_graphics    (IFBEngineDevToolsFlagsManagers& devtools_manager_flags) { return(devtools_manager_flags & IFBEngineDevToolsFlagsManagers_Graphics); }
};

/**********************************************************************************/
/* MEMORY TOOLS                                                                   */
/**********************************************************************************/

enum IFBEngineDevToolsFlagsMemory_ {
    IFBEngineDevToolsFlagsMemory_None              = 0,
    IFBEngineDevToolsFlagsMemory_GlobalStack       = IFB_BIT_FLAG_0,
    IFBEngineDevToolsFlagsMemory_SystemReservation = IFB_BIT_FLAG_1,
    IFBEngineDevToolsFlagsMemory_SystemInfo        = IFB_BIT_FLAG_2
};

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

    ifb_void devtools_memory_render_window             (IFBEngineDevToolsFlagsMemory& memory_flags_ref);
    ifb_void devtools_memory_render_tab_bar            (IFBEngineDevToolsFlagsMemory& memory_flags_ref, IFBEngineMemory* engine_memory_ptr);
    
    ifb_void devtools_memory_render_global_stack       (IFBEngineMemory* engine_memory_ptr);
    ifb_void devtools_memory_render_system_reservation (IFBEngineMemory* engine_memory_ptr);
    ifb_void devtools_memory_render_system_info        (IFBEngineMemory* engine_memory_ptr);

    ifb_void devtools_memory_get_global_stack_info       (IFBEngineDevToolsMemoryGlobalStack&       dev_global_stack_ref,       IFBEngineMemory* engine_memory_ptr);
    ifb_void devtools_memory_get_system_reservation_info (IFBEngineDevToolsMemorySystemReservation& dev_system_reservation_ref, IFBEngineMemory* engine_memory_ptr);
    ifb_void devtools_memory_get_system_info             (IFBEngineDevToolsMemorySystemInfo&        dev_system_info_ref,        IFBEngineMemory* engine_memory_ptr);

    const ifb_b8 devtools_memory_flags_get_global_stack       (const IFBEngineDevToolsFlagsMemory memory_flags) { return(memory_flags & IFBEngineDevToolsFlagsMemory_GlobalStack);       }
    const ifb_b8 devtools_memory_flags_get_system_reservation (const IFBEngineDevToolsFlagsMemory memory_flags) { return(memory_flags & IFBEngineDevToolsFlagsMemory_SystemReservation); }
    const ifb_b8 devtools_memory_flags_get_system_info        (const IFBEngineDevToolsFlagsMemory memory_flags) { return(memory_flags & IFBEngineDevToolsFlagsMemory_SystemInfo);        }

    inline ifb_void devtools_memory_flags_set_global_stack       (IFBEngineDevToolsFlagsMemory& memory_flags_ref, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(memory_flags_ref, IFBEngineDevToolsFlagsMemory_GlobalStack,       value); }
    inline ifb_void devtools_memory_flags_set_system_reservation (IFBEngineDevToolsFlagsMemory& memory_flags_ref, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(memory_flags_ref, IFBEngineDevToolsFlagsMemory_SystemReservation, value); }
    inline ifb_void devtools_memory_flags_set_system_info        (IFBEngineDevToolsFlagsMemory& memory_flags_ref, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(memory_flags_ref, IFBEngineDevToolsFlagsMemory_SystemInfo,        value); }
};

/**********************************************************************************/
/* DEVTOOLS MENU BAR                                                              */
/**********************************************************************************/

ifb_global const ifb_char* IFB_ENGINE_DEVTOOLS_MENU_TITLES[] = {
    "Engine",
    "Memory",
    "Managers"
}; 

#define IFB_ENGINE_DEVTOOLS_MENU_TITLE_ENGINE   IFB_ENGINE_DEVTOOLS_MENU_TITLES[0]
#define IFB_ENGINE_DEVTOOLS_MENU_TITLE_MEMORY   IFB_ENGINE_DEVTOOLS_MENU_TITLES[1]
#define IFB_ENGINE_DEVTOOLS_MENU_TITLE_MANAGERS IFB_ENGINE_DEVTOOLS_MENU_TITLES[2]

ifb_global const ifb_char* IFB_ENGINE_DEVTOOLS_MENU_ITEM_NAMES_CONTEXT[] = {
    "Context Structure",
    "System Info",
    "User Input",
    "ImGui Demo",
    "Exit"
};

ifb_global const ifb_char* IFB_ENGINE_DEVTOOLS_MENU_ITEM_NAMES_MEMORY[] = {
    "Global Stack",
    "System Reservation",
    "System Info"
};

ifb_global const ifb_char* IFB_ENGINE_DEVTOOLS_MENU_ITEM_NAMES_MANAGERS[] = {
    "Tag Manager",
    "Arena Manager",
    "Graphics Manager"
};

ifb_global const IFBEngineDevToolsFlagsContext IFB_ENGINE_DEVTOOLS_MENU_ITEM_FLAGS_CONTEXT[] = {
    IFBEngineDevToolsFlagsContext_Context,
    IFBEngineDevToolsFlagsContext_SystemInfo,
    IFBEngineDevToolsFlagsContext_UserInput,
    IFBEngineDevToolsFlagsContext_ImGuiDemo,
    IFBEngineDevToolsFlagsContext_Exit
};

ifb_global const IFBEngineDevToolsFlagsMemory IFB_ENGINE_DEVTOOLS_MENU_ITEM_FLAGS_MEMORY[] = {
    IFBEngineDevToolsFlagsMemory_GlobalStack,
    IFBEngineDevToolsFlagsMemory_SystemReservation,
    IFBEngineDevToolsFlagsMemory_SystemInfo
};

ifb_global const IFBEngineDevToolsFlagsManagers IFB_ENGINE_DEVTOOLS_MENU_ITEM_FLAGS_MANAGERS[] = {
    IFBEngineDevToolsFlagsManagers_Tag,
    IFBEngineDevToolsFlagsManagers_Arena,
    IFBEngineDevToolsFlagsManagers_Graphics
};

ifb_global const ifb_u32 IFB_ENGINE_DEVTOOLS_MENU_ITEM_COUNT_CONTEXT  = sizeof(IFB_ENGINE_DEVTOOLS_MENU_ITEM_FLAGS_CONTEXT)  / sizeof(IFBEngineDevToolsFlagsContext);
ifb_global const ifb_u32 IFB_ENGINE_DEVTOOLS_MENU_ITEM_COUNT_MEMORY   = sizeof(IFB_ENGINE_DEVTOOLS_MENU_ITEM_FLAGS_MEMORY)   / sizeof(IFBEngineDevToolsFlagsMemory);
ifb_global const ifb_u32 IFB_ENGINE_DEVTOOLS_MENU_ITEM_COUNT_MANAGERS = sizeof(IFB_ENGINE_DEVTOOLS_MENU_ITEM_FLAGS_MANAGERS) / sizeof(IFBEngineDevToolsFlagsManagers);

namespace ifb_engine {

    ifb_void devtools_menu_render_main_bar (IFBEngineDevTools* devtools_ptr);
    ifb_void devtools_menu_render_context  (IFBEngineDevToolsFlagsContext&  context_flags_ref);
    ifb_void devtools_menu_render_memory   (IFBEngineDevToolsFlagsMemory&   memory_flags_ref);
    ifb_void devtools_menu_render_managers (IFBEngineDevToolsFlagsManagers& managers_flags_ref);
};

/**********************************************************************************/
/* DEVTOOLS                                                                       */
/**********************************************************************************/

struct IFBEngineDevTools {
    struct {
        IFBEngineDevToolsFlagsControl  control;
        IFBEngineDevToolsFlagsContext  context;
        IFBEngineDevToolsFlagsMemory   memory;
        IFBEngineDevToolsFlagsManagers managers;
    } flags;
};

typedef ifb_void
(*funcptr_devtools_render_tab_items_callback)(
    ifb_void* tab_item_data_ptr);

namespace ifb_engine {

    ifb_void devtools_initialize      (IFBEngineDevTools* devtools_ptr);
    ifb_void devtools_update          (IFBEngineDevTools* devtools_ptr, IFBInput& input_ref);

    ifb_void devtools_render_imgui_demo(IFBEngineDevTools* devtools_ptr);

    ifb_void
    devtools_render_menu(
              ifb_u32&   menu_flags_ref,
        const ifb_char*  menu_title,
        const ifb_u32    menu_item_count,
        const ifb_char** menu_item_names,
        const ifb_u32*   menu_item_flag_bits);

    ifb_void
    devtools_render_property_table(
        const ifb_char*  table_name,
        const ifb_u32    table_row_count,
        const ifb_char** table_property_names,
        const ifb_char** table_property_values);

    ifb_void
    devtools_render_tab_bar(
              ifb_u32&                                    tab_item_flags_ref,
              ifb_void*                                   tab_item_data,
        const ifb_char*                                   tab_bar_title,
        const ifb_u32                                     tab_item_count,
        const ifb_char**                                  tab_item_titles,
        const funcptr_devtools_render_tab_items_callback* tab_item_callbacks,
        const ifb_u32*                                    tab_item_flag_bits);
};

#endif //IFB_ENGINE_INTERNAL_DEVTOOLS_HPP