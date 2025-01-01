#ifndef IFB_ENGINE_INTERNAL_DEVTOOLS_HPP
#define IFB_ENGINE_INTERNAL_DEVTOOLS_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal-context.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBEngineDevTools;

typedef ifb_u32 IFBEngineDevToolsMenuNames;

typedef ifb_u32 IFBEngineDevToolsFlagsControl;
typedef ifb_u32 IFBEngineDevToolsFlagsContext;
typedef ifb_u32 IFBEngineDevToolsFlagsMemory;
typedef ifb_u32 IFBEngineDevToolsFlagsManagers;
typedef ifb_u32 IFBEngineDevToolsFlagsTools;

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
/* CONTEXT                                                                        */
/**********************************************************************************/

enum IFBEngineDevToolsFlagsContext_ {
    IFBEngineDevToolsFlagsContext_None       = 0,
    IFBEngineDevToolsFlagsContext_Context    = IFB_BIT_FLAG_0,
    IFBEngineDevToolsFlagsContext_SystemInfo = IFB_BIT_FLAG_1,
    IFBEngineDevToolsFlagsContext_UserInput  = IFB_BIT_FLAG_2,
    IFBEngineDevToolsFlagsContext_Config     = IFB_BIT_FLAG_3,
    IFBEngineDevToolsFlagsContext_Exit       = IFB_BIT_FLAG_4,
};

struct IFBEngineContext;

namespace ifb_engine {

    inline ifb_void devtools_context_flags_set_context         (IFBEngineDevToolsFlagsContext& devtools_context_flags, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(devtools_context_flags, IFBEngineDevToolsFlagsContext_Context,    value); }
    inline ifb_void devtools_context_flags_set_system_info     (IFBEngineDevToolsFlagsContext& devtools_context_flags, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(devtools_context_flags, IFBEngineDevToolsFlagsContext_SystemInfo, value); }
    inline ifb_void devtools_context_flags_set_user_input      (IFBEngineDevToolsFlagsContext& devtools_context_flags, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(devtools_context_flags, IFBEngineDevToolsFlagsContext_UserInput,  value); }
    inline ifb_void devtools_context_flags_set_config          (IFBEngineDevToolsFlagsContext& devtools_context_flags, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(devtools_context_flags, IFBEngineDevToolsFlagsContext_Config,     value); }
    inline ifb_void devtools_context_flags_set_exit            (IFBEngineDevToolsFlagsContext& devtools_context_flags, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(devtools_context_flags, IFBEngineDevToolsFlagsContext_Exit,       value); }

    inline const ifb_b8 devtools_context_flags_get_context     (IFBEngineDevToolsFlagsContext& devtools_context_flags) { return(devtools_context_flags & IFBEngineDevToolsFlagsContext_Context);    }
    inline const ifb_b8 devtools_context_flags_get_system_info (IFBEngineDevToolsFlagsContext& devtools_context_flags) { return(devtools_context_flags & IFBEngineDevToolsFlagsContext_SystemInfo); }
    inline const ifb_b8 devtools_context_flags_get_user_input  (IFBEngineDevToolsFlagsContext& devtools_context_flags) { return(devtools_context_flags & IFBEngineDevToolsFlagsContext_UserInput);  }
    inline const ifb_b8 devtools_context_flags_get_config      (IFBEngineDevToolsFlagsContext& devtools_context_flags) { return(devtools_context_flags & IFBEngineDevToolsFlagsContext_Config);     }
    inline const ifb_b8 devtools_context_flags_get_exit        (IFBEngineDevToolsFlagsContext& devtools_context_flags) { return(devtools_context_flags & IFBEngineDevToolsFlagsContext_Exit);       }
};

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

enum IFBEngineDevToolsFlagsMemory_ {
    IFBEngineDevToolsFlagsMemory_None              = 0,
    IFBEngineDevToolsFlagsMemory_GlobalStack       = IFB_BIT_FLAG_0,
    IFBEngineDevToolsFlagsMemory_SystemReservation = IFB_BIT_FLAG_1,
    IFBEngineDevToolsFlagsMemory_SystemInfo        = IFB_BIT_FLAG_2
};

namespace ifb_engine {

    const ifb_b8 devtools_memory_flags_get_global_stack          (const IFBEngineDevToolsFlagsMemory memory_flags) { return(memory_flags & IFBEngineDevToolsFlagsMemory_GlobalStack);       }
    const ifb_b8 devtools_memory_flags_get_system_reservation    (const IFBEngineDevToolsFlagsMemory memory_flags) { return(memory_flags & IFBEngineDevToolsFlagsMemory_SystemReservation); }
    const ifb_b8 devtools_memory_flags_get_system_info           (const IFBEngineDevToolsFlagsMemory memory_flags) { return(memory_flags & IFBEngineDevToolsFlagsMemory_SystemInfo);        }

    inline ifb_void devtools_memory_flags_set_global_stack       (IFBEngineDevToolsFlagsMemory& memory_flags_ref, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(memory_flags_ref, IFBEngineDevToolsFlagsMemory_GlobalStack,       value); }
    inline ifb_void devtools_memory_flags_set_system_reservation (IFBEngineDevToolsFlagsMemory& memory_flags_ref, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(memory_flags_ref, IFBEngineDevToolsFlagsMemory_SystemReservation, value); }
    inline ifb_void devtools_memory_flags_set_system_info        (IFBEngineDevToolsFlagsMemory& memory_flags_ref, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(memory_flags_ref, IFBEngineDevToolsFlagsMemory_SystemInfo,        value); }
};

/**********************************************************************************/
/* MANAGERS                                                                       */
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

    inline const ifb_b8 devtools_manager_flags_get_tag         (IFBEngineDevToolsFlagsManagers& devtools_manager_flags) { return(devtools_manager_flags & IFBEngineDevToolsFlagsManagers_Tag);      }
    inline const ifb_b8 devtools_manager_flags_get_arena       (IFBEngineDevToolsFlagsManagers& devtools_manager_flags) { return(devtools_manager_flags & IFBEngineDevToolsFlagsManagers_Arena);    }
    inline const ifb_b8 devtools_manager_flags_get_graphics    (IFBEngineDevToolsFlagsManagers& devtools_manager_flags) { return(devtools_manager_flags & IFBEngineDevToolsFlagsManagers_Graphics); }
};

/**********************************************************************************/
/* TOOLS                                                                          */
/**********************************************************************************/

enum IFBEngineDevToolsFlagsTools_ {
    IFBEngineDevToolsFlagsTools_None      = 0,
    IFBEngineDevToolsFlagsTools_ImGuiDemo = IFB_BIT_FLAG_0
};

namespace ifb_engine {

    ifb_void devtools_tools_render                          (IFBEngineDevToolsFlagsTools& tools_flags_ref);
    ifb_void devtools_tools_render_imgui                    (IFBEngineDevToolsFlagsTools& tools_flags_ref);

    inline ifb_void devtools_tools_flags_set_imgui_demo     (IFBEngineDevToolsFlagsTools& tools_flags_ref, const ifb_b8 value) { ifb_engine_macro_devtools_set_flag_value(tools_flags_ref, IFBEngineDevToolsFlagsTools_ImGuiDemo, value); }

    inline const ifb_b8 devtools_tools_flags_get_imgui_demo (IFBEngineDevToolsFlagsTools& tools_flags_ref) { return(tools_flags_ref & IFBEngineDevToolsFlagsTools_ImGuiDemo); }

};

/**********************************************************************************/
/* MENU BAR                                                                       */
/**********************************************************************************/

enum IFBEngineDevToolsMenuNames_ {
    IFBEngineDevToolsMenuNames_Menu_Context                       = 0, 
    IFBEngineDevToolsMenuNames_Menu_Context_Item_ContextStructure = 1, 
    IFBEngineDevToolsMenuNames_Menu_Context_Item_SystemInfo       = 2, 
    IFBEngineDevToolsMenuNames_Menu_Context_Item_UserInput        = 3, 
    IFBEngineDevToolsMenuNames_Menu_Context_Item_Config           = 4, 
    IFBEngineDevToolsMenuNames_Menu_Context_Item_Exit             = 5, 
    IFBEngineDevToolsMenuNames_Menu_Memory                        = 6, 
    IFBEngineDevToolsMenuNames_Menu_Memory_Item_GlobalStack       = 7, 
    IFBEngineDevToolsMenuNames_Menu_Memory_Item_SystemReservation = 8, 
    IFBEngineDevToolsMenuNames_Menu_Memory_Item_SystemInfo        = 9, 
    IFBEngineDevToolsMenuNames_Menu_Managers                      = 10, 
    IFBEngineDevToolsMenuNames_Menu_Managers_Item_Tag             = 11, 
    IFBEngineDevToolsMenuNames_Menu_Managers_Item_Arena           = 12, 
    IFBEngineDevToolsMenuNames_Menu_Managers_Item_Graphics        = 13, 
    IFBEngineDevToolsMenuNames_Menu_Tools                         = 14, 
    IFBEngineDevToolsMenuNames_Menu_Tools_Item_ImGuiDemo          = 15
};

ifb_global const ifb_char* IFB_ENGINE_DEVTOOLS_MENU_ITEM_NAMES[] = {

    //------------------------
    // context
    //------------------------
    "Engine",               // IFBEngineDevToolsMenuNames_Menu_Context
    "Context Structure",    // IFBEngineDevToolsMenuNames_Menu_Context_Item_ContextStructure
    "System Info",          // IFBEngineDevToolsMenuNames_Menu_Context_Item_SystemInfo
    "User Input",           // IFBEngineDevToolsMenuNames_Menu_Context_Item_UserInput
    "Config",               // IFBEngineDevToolsMenuNames_Menu_Context_Item_Config
    "Exit",                 // IFBEngineDevToolsMenuNames_Menu_Context_Item_Exit

    //------------------------
    // menu
    //------------------------
    "Memory",               // IFBEngineDevToolsMenuNames_Menu_Memory
    "Global Stack",         // IFBEngineDevToolsMenuNames_Menu_Memory_Item_GlobalStack
    "System Reservation",   // IFBEngineDevToolsMenuNames_Menu_Memory_Item_SystemReservation
    "System Info",          // IFBEngineDevToolsMenuNames_Menu_Memory_Item_SystemInfo

    //------------------------
    // managers
    //------------------------
    "Managers",             // IFBEngineDevToolsMenuNames_Menu_Managers
    "Tag Manager",          // IFBEngineDevToolsMenuNames_Menu_Managers_Item_Tag 
    "Arena Manager",        // IFBEngineDevToolsMenuNames_Menu_Managers_Item_Arena 
    "Graphics Manager",     // IFBEngineDevToolsMenuNames_Menu_Managers_Item_Graphics 

    //------------------------
    // tools
    //------------------------
    "Tools",                // IFBEngineDevToolsMenuNames_Menu_Tools
    "ImGui Demo"            // IFBEngineDevToolsMenuNames_Menu_Tools_Item_ImGuiDemo
};

#define IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_CONTEXT                         IFB_ENGINE_DEVTOOLS_MENU_ITEM_NAMES[IFBEngineDevToolsMenuNames_Menu_Context]
#define IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_CONTEXT_ITEM_CONTEXT_STRUCTURE  IFB_ENGINE_DEVTOOLS_MENU_ITEM_NAMES[IFBEngineDevToolsMenuNames_Menu_Context_Item_ContextStructure]
#define IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_CONTEXT_ITEM_SYSTEM_INFO        IFB_ENGINE_DEVTOOLS_MENU_ITEM_NAMES[IFBEngineDevToolsMenuNames_Menu_Context_Item_SystemInfo]
#define IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_CONTEXT_ITEM_USER_INPUT         IFB_ENGINE_DEVTOOLS_MENU_ITEM_NAMES[IFBEngineDevToolsMenuNames_Menu_Context_Item_UserInput]
#define IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_CONTEXT_ITEM_CONFIG             IFB_ENGINE_DEVTOOLS_MENU_ITEM_NAMES[IFBEngineDevToolsMenuNames_Menu_Context_Item_Config]
#define IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_CONTEXT_ITEM_EXIT               IFB_ENGINE_DEVTOOLS_MENU_ITEM_NAMES[IFBEngineDevToolsMenuNames_Menu_Context_Item_Exit]

#define IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_MEMORY                          IFB_ENGINE_DEVTOOLS_MENU_ITEM_NAMES[IFBEngineDevToolsMenuNames_Menu_Memory]
#define IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_MEMORY_ITEM_GLOBAL_STACK        IFB_ENGINE_DEVTOOLS_MENU_ITEM_NAMES[IFBEngineDevToolsMenuNames_Menu_Memory_Item_GlobalStack]
#define IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_MEMORY_ITEM_SYSTEM_RESERVATION  IFB_ENGINE_DEVTOOLS_MENU_ITEM_NAMES[IFBEngineDevToolsMenuNames_Menu_Memory_Item_SystemReservation]
#define IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_MEMORY_ITEM_SYSTEM_INFO         IFB_ENGINE_DEVTOOLS_MENU_ITEM_NAMES[IFBEngineDevToolsMenuNames_Menu_Memory_Item_SystemInfo]

#define IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_MANAGERS                        IFB_ENGINE_DEVTOOLS_MENU_ITEM_NAMES[IFBEngineDevToolsMenuNames_Menu_Managers]
#define IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_MANAGERS_ITEM_TAG_MANAGER       IFB_ENGINE_DEVTOOLS_MENU_ITEM_NAMES[IFBEngineDevToolsMenuNames_Menu_Managers_Item_Tag]
#define IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_MANAGERS_ITEM_ARENA_MANAGER     IFB_ENGINE_DEVTOOLS_MENU_ITEM_NAMES[IFBEngineDevToolsMenuNames_Menu_Managers_Item_Arena]
#define IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_MANAGERS_ITEM_GRAPHICS_MANAGER  IFB_ENGINE_DEVTOOLS_MENU_ITEM_NAMES[IFBEngineDevToolsMenuNames_Menu_Managers_Item_Graphics]

#define IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_TOOLS                           IFB_ENGINE_DEVTOOLS_MENU_ITEM_NAMES[IFBEngineDevToolsMenuNames_Menu_Tools]
#define IFB_ENGINE_IFB_ENGINE_DEVTOOLS_MENU_TOOLS_ITEM_IMGUI_DEMO           IFB_ENGINE_DEVTOOLS_MENU_ITEM_NAMES[IFBEngineDevToolsMenuNames_Menu_Tools_Item_ImGuiDemo]

namespace ifb_engine {

    ifb_void devtools_menu_bar_render      (IFBEngineDevTools* devtools_ptr);
    ifb_void devtools_menu_render_context  (IFBEngineDevToolsFlagsContext&  context_flags_ref);
    ifb_void devtools_menu_render_memory   (IFBEngineDevToolsFlagsMemory&   memory_flags_ref);
    ifb_void devtools_menu_render_managers (IFBEngineDevToolsFlagsManagers& managers_flags_ref);
    ifb_void devtools_menu_render_tools    (IFBEngineDevToolsFlagsManagers& managers_flags_ref);

    ifb_void devtools_menu_render(
              ifb_u32&   menu_flags_ref,
        const ifb_char*  menu_title,
        const ifb_u32    menu_item_count,
        const ifb_char** menu_item_names,
        const ifb_u32*   menu_item_flag_bits);
};

/**********************************************************************************/
/* WINDOWS                                                                        */
/**********************************************************************************/

enum IFBEngineDevToolsWindows_ {
    IFBEngineDevToolsWindows_EngineContext = 0,
    IFBEngineDevToolsWindows_Memory        = 1,
};

ifb_global const ifb_char* IFB_ENGINE_DEVTOOLS_WINDOW_NAMES[] = {
    "Engine Context", // IFBEngineDevToolsWindows_EngineContext
    "Memory"          // IFBEngineDevToolsWindows_Memory
};

#define IFB_ENGINE_DEVTOOLS_WINDOW_NAME_ENGINE_CONTEXT IFB_ENGINE_DEVTOOLS_WINDOW_NAMES[IFBEngineDevToolsWindows_EngineContext]
#define IFB_ENGINE_DEVTOOLS_WINDOW_NAME_MEMORY         IFB_ENGINE_DEVTOOLS_WINDOW_NAMES[IFBEngineDevToolsWindows_Memory]

typedef void
(*funcptr_devtools_window_render_callback)(
    ifb_u32& flags_ref);

namespace ifb_engine {

    ifb_void devtools_window_render_all(IFBEngineDevTools* devtools_ptr);

    ifb_void
    devtools_window_render(
              ifb_u32&                                 window_flags_ref,
        const ifb_char*                                window_title,
        const funcptr_devtools_window_render_callback  window_callback);

    ifb_void devtools_window_render_callback_context (IFBEngineDevToolsFlagsContext& flags_ref_context);
    ifb_void devtools_window_render_callback_memory  (IFBEngineDevToolsFlagsMemory&  flags_ref_memory);
};


/**********************************************************************************/
/* TABS                                                                           */
/**********************************************************************************/

enum IFBEngineDevToolsTabBar_ {
    IFBEngineDevToolsTabBar_Context = 0,
    IFBEngineDevToolsTabBar_Memory  = 1
};

ifb_global const ifb_char* IFB_ENGINE_DEVTOOLS_TAB_BAR_NAMES[] = {
    "tab-bar-context",
    "tab-bar-memory"
};

#define IFB_ENGINE_DEVTOOLS_TAB_BAR_NAME_CONTEXT IFB_ENGINE_DEVTOOLS_TAB_BAR_NAMES[IFBEngineDevToolsTabBar_Context]
#define IFB_ENGINE_DEVTOOLS_TAB_BAR_NAME_MEMORY  IFB_ENGINE_DEVTOOLS_TAB_BAR_NAMES[IFBEngineDevToolsTabBar_Memory]

typedef ifb_void
(*devtools_tab_item_render_callback)(
    ifb_void* tab_item_data_ptr);

namespace ifb_engine {

    //-----------------------
    // tab bars
    //-----------------------
    ifb_void devtools_tab_bar_render_context (IFBEngineDevToolsFlagsContext& flags_ref_context, IFBEngineContext* context_ptr);
    ifb_void devtools_tab_bar_render_memory  (IFBEngineDevToolsFlagsMemory&  flags_ref_memory,  IFBEngineMemory*  memory_ptr);

    //-----------------------
    // context tab items
    //-----------------------    
    ifb_void devtools_tab_item_render_callback_context_structure   (IFBEngineContext* context_ptr);
    ifb_void devtools_tab_item_render_callback_context_system_info (IFBEngineContext* context_ptr);
    ifb_void devtools_tab_item_render_callback_context_user_input  (IFBEngineContext* context_ptr);
    ifb_void devtools_tab_item_render_callback_context_config      (IFBEngineContext* context_ptr);

    //-----------------------
    // memory tab items
    //-----------------------
    ifb_void devtools_tab_item_render_callback_memory_global_stack       (IFBEngineMemory* memory_ptr);
    ifb_void devtools_tab_item_render_callback_memory_system_reservation (IFBEngineMemory* memory_ptr);
    ifb_void devtools_tab_item_render_callback_memory_system_info        (IFBEngineMemory* memory_ptr);

    //-----------------------
    // tab bar control
    //-----------------------
    ifb_void
    devtools_tab_bar_render(
              ifb_u32&                           tab_item_flags_ref,
              ifb_void*                          tab_item_data,
        const ifb_char*                          tab_bar_title,
        const ifb_u32                            tab_item_count,
        const ifb_char**                         tab_item_titles,
        const devtools_tab_item_render_callback* tab_item_callbacks,
        const ifb_u32*                           tab_item_flag_bits);
};

enum IFBEngineDevToolsTabItems_ {
    IFBEngineDevToolsTabItems_Context_EngineContext    = 0,
    IFBEngineDevToolsTabItems_Context_SystemInfo       = 1,
    IFBEngineDevToolsTabItems_Context_UserInput        = 2,
    IFBEngineDevToolsTabItems_Context_Config           = 3,
    IFBEngineDevToolsTabItems_Memory_GlobalStack       = 4,
    IFBEngineDevToolsTabItems_Memory_SystemReservation = 5,
    IFBEngineDevToolsTabItems_Memory_SystemInfo        = 6
};

ifb_global const devtools_tab_item_render_callback IFB_ENGINE_DEVTOOLS_TAB_ITEM_RENDER_CALLBACKS[] = {
    (devtools_tab_item_render_callback)ifb_engine::devtools_tab_item_render_callback_context_structure,
    (devtools_tab_item_render_callback)ifb_engine::devtools_tab_item_render_callback_context_system_info,
    (devtools_tab_item_render_callback)ifb_engine::devtools_tab_item_render_callback_context_user_input,
    (devtools_tab_item_render_callback)ifb_engine::devtools_tab_item_render_callback_context_config,
    (devtools_tab_item_render_callback)ifb_engine::devtools_tab_item_render_callback_memory_global_stack,
    (devtools_tab_item_render_callback)ifb_engine::devtools_tab_item_render_callback_memory_system_reservation,
    (devtools_tab_item_render_callback)ifb_engine::devtools_tab_item_render_callback_memory_system_info
};

#define IFB_ENGINE_DEVTOOLS_TAB_ITEM_RENDER_CALLBACK_CONTEXT_ENGINE_CONTEXT      IFB_ENGINE_DEVTOOLS_TAB_ITEM_RENDER_CALLBACKS[IFBEngineDevToolsTabItems_Context_EngineContext] 
#define IFB_ENGINE_DEVTOOLS_TAB_ITEM_RENDER_CALLBACK_CONTEXT_SYSTEM_INFO         IFB_ENGINE_DEVTOOLS_TAB_ITEM_RENDER_CALLBACKS[IFBEngineDevToolsTabItems_Context_SystemInfo] 
#define IFB_ENGINE_DEVTOOLS_TAB_ITEM_RENDER_CALLBACK_CONTEXT_USER_INPUT          IFB_ENGINE_DEVTOOLS_TAB_ITEM_RENDER_CALLBACKS[IFBEngineDevToolsTabItems_Context_UserInput] 
#define IFB_ENGINE_DEVTOOLS_TAB_ITEM_RENDER_CALLBACK_CONTEXT_CONFIG              IFB_ENGINE_DEVTOOLS_TAB_ITEM_RENDER_CALLBACKS[IFBEngineDevToolsTabItems_Context_Config] 

#define IFB_ENGINE_DEVTOOLS_TAB_ITEM_RENDER_CALLBACK_MEMORY_GLOBAL_STACK         IFB_ENGINE_DEVTOOLS_TAB_ITEM_RENDER_CALLBACKS[IFBEngineDevToolsTabItems_Memory_GlobalStack] 
#define IFB_ENGINE_DEVTOOLS_TAB_ITEM_RENDER_CALLBACK_MEMORY_SYSTEM_RESERVATION   IFB_ENGINE_DEVTOOLS_TAB_ITEM_RENDER_CALLBACKS[IFBEngineDevToolsTabItems_Memory_SystemReservation] 
#define IFB_ENGINE_DEVTOOLS_TAB_ITEM_RENDER_CALLBACK_MEMORY_SYSTEM_INFO          IFB_ENGINE_DEVTOOLS_TAB_ITEM_RENDER_CALLBACKS[IFBEngineDevToolsTabItems_Memory_SystemInfo] 

/**********************************************************************************/
/* PROPERTY TABLES                                                                */
/**********************************************************************************/

enum IFBEngineDevToolsPropertyTable_ {
    IFBEngineDevToolsPropertyTable_ContextSizes            = 0,
    IFBEngineDevToolsPropertyTable_ContextHandles          = 1,
    IFBEngineDevToolsPropertyTable_ContextConfig           = 2,
    IFBEngineDevToolsPropertyTable_MemoryGlobalStack       = 3,
    IFBEngineDevToolsPropertyTable_MemorySystemReservation = 4,
    IFBEngineDevToolsPropertyTable_MemorySystemInfo        = 5
};

ifb_global const ifb_char* IFB_ENGINE_DEVTOOLS_PROPERTY_TABLE_NAMES[] = {
    "property-table-context-sizes",
    "property-table-context-handles",
    "property-table-context-config",
    "property-table-memory-global-stack",
    "property-table-memory-system-reservation",
    "property-table-memory-system-info"
};

#define IFB_ENGINE_DEVTOOLS_PROPERTY_TABLE_NAME_CONTEXT_SIZES             IFB_ENGINE_DEVTOOLS_PROPERTY_TABLE_NAMES[IFBEngineDevToolsPropertyTable_ContextSizes]
#define IFB_ENGINE_DEVTOOLS_PROPERTY_TABLE_NAME_CONTEXT_HANDLES           IFB_ENGINE_DEVTOOLS_PROPERTY_TABLE_NAMES[IFBEngineDevToolsPropertyTable_ContextHandles]
#define IFB_ENGINE_DEVTOOLS_PROPERTY_TABLE_NAME_CONTEXT_CONFIG            IFB_ENGINE_DEVTOOLS_PROPERTY_TABLE_NAMES[IFBEngineDevToolsPropertyTable_ContextConfig]
#define IFB_ENGINE_DEVTOOLS_PROPERTY_TABLE_NAME_MEMORY_GLOBAL_STACK       IFB_ENGINE_DEVTOOLS_PROPERTY_TABLE_NAMES[IFBEngineDevToolsPropertyTable_MemoryGlobalStack]
#define IFB_ENGINE_DEVTOOLS_PROPERTY_TABLE_NAME_MEMORY_SYSTEM_RESERVATION IFB_ENGINE_DEVTOOLS_PROPERTY_TABLE_NAMES[IFBEngineDevToolsPropertyTable_MemorySystemReservation]
#define IFB_ENGINE_DEVTOOLS_PROPERTY_TABLE_NAME_MEMORY_SYSTEM_INFO        IFB_ENGINE_DEVTOOLS_PROPERTY_TABLE_NAMES[IFBEngineDevToolsPropertyTable_MemorySystemInfo]

enum IFBEngineDevToolsProperty_ {

    //----------------------------------------------------------------
    // context sizes
    //----------------------------------------------------------------
    IFBEngineDevToolsProperty_ContextSizes_Context                   = 0,
    IFBEngineDevToolsProperty_ContextSizes_Memory                    = 1,
    IFBEngineDevToolsProperty_ContextSizes_Handles                   = 2,
    IFBEngineDevToolsProperty_ContextSizes_Config                    = 3,
    //----------------------------------------------------------------
    // context handles 
    //----------------------------------------------------------------
    IFBEngineDevToolsProperty_ContextHandles_Managers                = 4,
    IFBEngineDevToolsProperty_ContextHandles_Core                    = 5,
    IFBEngineDevToolsProperty_ContextHandles_DevTools                = 6,
    //----------------------------------------------------------------
    // context config
    //----------------------------------------------------------------
    IFBEngineDevToolsProperty_ContextConfig_MemoryMinimumGB          = 7,
    IFBEngineDevToolsProperty_ContextConfig_CommitCountMax           = 8,
    IFBEngineDevToolsProperty_ContextConfig_GlobalStackKB            = 9,
    IFBEngineDevToolsProperty_ContextConfig_ArenaMinimumKB           = 10,
    IFBEngineDevToolsProperty_ContextConfig_ArenaCountMax            = 11,
    IFBEngineDevToolsProperty_ContextConfig_TagLength                = 12,
    IFBEngineDevToolsProperty_ContextConfig_TagCountMax              = 13,
    IFBEngineDevToolsProperty_ContextConfig_UseDevTools              = 14,
    IFBEngineDevToolsProperty_ContextConfig_WindowTitle              = 15,
    //----------------------------------------------------------------
    // memory global stack
    //----------------------------------------------------------------
    IFBEngineDevToolsProperty_MemoryGlobalStack_Size                 = 16,
    IFBEngineDevToolsProperty_MemoryGlobalStack_Position             = 17,
    IFBEngineDevToolsProperty_MemoryGlobalStack_PercentUsed          = 18,
    //----------------------------------------------------------------
    // memory system reservation
    //----------------------------------------------------------------
    IFBEngineDevToolsProperty_MemoryReservation_StartingAddress      = 19,
    IFBEngineDevToolsProperty_MemoryReservation_PagesTotal           = 20,
    IFBEngineDevToolsProperty_MemoryReservation_PagesCommitted       = 21,
    IFBEngineDevToolsProperty_MemoryReservation_CommitCountMax       = 22,
    IFBEngineDevToolsProperty_MemoryReservation_CommitCountCurrent   = 23,
    //----------------------------------------------------------------
    // memory system info
    //----------------------------------------------------------------
    IFBEngineDevToolsProperty_MemorySystemInfo_PageSize              = 24,
    IFBEngineDevToolsProperty_MemorySystemInfo_AllocationGranularity = 25
};

ifb_global const ifb_char* IFB_ENGINE_DEVTOOLS_PROPERTY_NAMES[] = {
    
    //-----------------------------------
    // context sizes                     
    //-----------------------------------
    "Context Size Total",              // IFBEngineDevToolsProperty_ContextSizes_Context
    "Memory Size",                     // IFBEngineDevToolsProperty_ContextSizes_Memory
    "Handles Size",                    // IFBEngineDevToolsProperty_ContextSizes_Handles
    "Config Size",                     // IFBEngineDevToolsProperty_ContextSizes_Config
    //-----------------------------------
    // context handles                   
    //-----------------------------------
    "Managers Handle",                 // IFBEngineDevToolsProperty_ContextHandles_Managers
    "Core Handle",                     // IFBEngineDevToolsProperty_ContextHandles_Core
    "DevTools Handle",                 // IFBEngineDevToolsProperty_ContextHandles_DevTools
    //-----------------------------------
    // context config
    //-----------------------------------
    "Minimum Memory Requirement (GB)", // IFBEngineDevToolsProperty_ContextConfig_MemoryMinimumGB
    "Max Memory Commit Count",         // IFBEngineDevToolsProperty_ContextConfig_CommitCountMax 
    "Global Stack Size (KB)",          // IFBEngineDevToolsProperty_ContextConfig_GlobalStackKB 
    "Arena Minimum Size (KB)",         // IFBEngineDevToolsProperty_ContextConfig_ArenaMinimumKB 
    "Max Arena Count",                 // IFBEngineDevToolsProperty_ContextConfig_ArenaCountMax 
    "Tag Length",                      // IFBEngineDevToolsProperty_ContextConfig_TagLength 
    "Max Tag Count",                   // IFBEngineDevToolsProperty_ContextConfig_TagCountMax 
    "Use DevTools",                    // IFBEngineDevToolsProperty_ContextConfig_UseDevTools 
    "Window Title",                    // IFBEngineDevToolsProperty_ContextConfig_WindowTitle 
    //-----------------------------------
    // memory global stack
    //-----------------------------------
    "Stack Size",                      // IFBEngineDevToolsProperty_MemoryGlobalStack_Size
    "Stack Position",                  // IFBEngineDevToolsProperty_MemoryGlobalStack_Position
    "Percent Used",                    // IFBEngineDevToolsProperty_MemoryGlobalStack_PercentUsed
    //-----------------------------------
    // memory reservation
    //-----------------------------------
    "Starting Address",                // IFBEngineDevToolsProperty_MemoryReservation_StartingAddress
    "Pages Total",                     // IFBEngineDevToolsProperty_MemoryReservation_PagesTotal
    "Pages Committed",                 // IFBEngineDevToolsProperty_MemoryReservation_PagesCommitted
    "Commit Count Max",                // IFBEngineDevToolsProperty_MemoryReservation_CommitCountMax
    "Commit Count Current",            // IFBEngineDevToolsProperty_MemoryReservation_CommitCountCurrent
    //-----------------------------------
    // memory system info
    //-----------------------------------
    "Page Size",                       // IFBEngineDevToolsProperty_MemorySystemInfo_PageSize
    "Allocation Granularity"           // IFBEngineDevToolsProperty_MemorySystemInfo_AllocationGranularity
};

#define IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_SIZE_TABLE_CONTEXT                      IFB_ENGINE_DEVTOOLS_PROPERTY_NAMES[IFBEngineDevToolsProperty_ContextSizes_Context]
#define IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_SIZE_TABLE_MEMORY                       IFB_ENGINE_DEVTOOLS_PROPERTY_NAMES[IFBEngineDevToolsProperty_ContextSizes_Memory]
#define IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_SIZE_TABLE_HANDLES                      IFB_ENGINE_DEVTOOLS_PROPERTY_NAMES[IFBEngineDevToolsProperty_ContextSizes_Handles]
#define IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_SIZE_TABLE_CONFIG                       IFB_ENGINE_DEVTOOLS_PROPERTY_NAMES[IFBEngineDevToolsProperty_ContextSizes_Config]

#define IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_HANDLES_TABLE_MANAGERS                  IFB_ENGINE_DEVTOOLS_PROPERTY_NAMES[IFBEngineDevToolsProperty_ContextHandles_Managers]
#define IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_HANDLES_TABLE_CORE                      IFB_ENGINE_DEVTOOLS_PROPERTY_NAMES[IFBEngineDevToolsProperty_ContextHandles_Core]
#define IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_HANDLES_TABLE_DEVTOOLS                  IFB_ENGINE_DEVTOOLS_PROPERTY_NAMES[IFBEngineDevToolsProperty_ContextHandles_DevTools]

#define IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_CONFIG_TABLE_MEMORY_REQUIREMENT         IFB_ENGINE_DEVTOOLS_PROPERTY_NAMES[IFBEngineDevToolsProperty_ContextConfig_MemoryMinimumGB]
#define IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_CONFIG_TABLE_MEMORY_COMMIT_COUNT        IFB_ENGINE_DEVTOOLS_PROPERTY_NAMES[IFBEngineDevToolsProperty_ContextConfig_CommitCountMax]
#define IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_CONFIG_TABLE_GLOBAL_STACK_SIZE          IFB_ENGINE_DEVTOOLS_PROPERTY_NAMES[IFBEngineDevToolsProperty_ContextConfig_GlobalStackKB]
#define IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_CONFIG_TABLE_ARENA_SIZE                 IFB_ENGINE_DEVTOOLS_PROPERTY_NAMES[IFBEngineDevToolsProperty_ContextConfig_ArenaMinimumKB]
#define IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_CONFIG_TABLE_MAX_ARENA_COUNT            IFB_ENGINE_DEVTOOLS_PROPERTY_NAMES[IFBEngineDevToolsProperty_ContextConfig_ArenaCountMax]
#define IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_CONFIG_TABLE_TAG_LENGTH                 IFB_ENGINE_DEVTOOLS_PROPERTY_NAMES[IFBEngineDevToolsProperty_ContextConfig_TagLength]
#define IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_CONFIG_TABLE_MAX_TAG_COUNT              IFB_ENGINE_DEVTOOLS_PROPERTY_NAMES[IFBEngineDevToolsProperty_ContextConfig_TagCountMax]
#define IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_CONFIG_TABLE_USE_DEVTOOLS               IFB_ENGINE_DEVTOOLS_PROPERTY_NAMES[IFBEngineDevToolsProperty_ContextConfig_UseDevTools]
#define IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_CONTEXT_CONFIG_TABLE_WINDOW_TITLE               IFB_ENGINE_DEVTOOLS_PROPERTY_NAMES[IFBEngineDevToolsProperty_ContextConfig_WindowTitle]

#define IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_MEMORY_GLOBAL_STACK_TABLE_STACK_SIZE            IFB_ENGINE_DEVTOOLS_PROPERTY_NAMES[IFBEngineDevToolsProperty_MemoryGlobalStack_Size]
#define IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_MEMORY_GLOBAL_STACK_TABLE_STACK_POSITION        IFB_ENGINE_DEVTOOLS_PROPERTY_NAMES[IFBEngineDevToolsProperty_MemoryGlobalStack_Position]
#define IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_MEMORY_GLOBAL_STACK_TABLE_PERCENT_USED          IFB_ENGINE_DEVTOOLS_PROPERTY_NAMES[IFBEngineDevToolsProperty_MemoryGlobalStack_PercentUsed]

#define IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_MEMORY_RESERVATION_TABLE_STARTING_ADDRESS       IFB_ENGINE_DEVTOOLS_PROPERTY_NAMES[IFBEngineDevToolsProperty_MemoryReservation_StartingAddress]
#define IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_MEMORY_RESERVATION_TABLE_PAGES_TOTAL            IFB_ENGINE_DEVTOOLS_PROPERTY_NAMES[IFBEngineDevToolsProperty_MemoryReservation_PagesTotal]
#define IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_MEMORY_RESERVATION_TABLE_PAGES_COMMITTED        IFB_ENGINE_DEVTOOLS_PROPERTY_NAMES[IFBEngineDevToolsProperty_MemoryReservation_PagesCommitted]
#define IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_MEMORY_RESERVATION_TABLE_COMMIT_COUNT_MAX       IFB_ENGINE_DEVTOOLS_PROPERTY_NAMES[IFBEngineDevToolsProperty_MemoryReservation_CommitCountMax]
#define IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_MEMORY_RESERVATION_TABLE_COMMIT_COUNT_CURRENT   IFB_ENGINE_DEVTOOLS_PROPERTY_NAMES[IFBEngineDevToolsProperty_MemoryReservation_CommitCountCurrent] 

#define IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_MEMORY_SYSTEM_INFO_TABLE_PAGE_SIZE              IFB_ENGINE_DEVTOOLS_PROPERTY_NAMES[IFBEngineDevToolsProperty_MemorySystemInfo_PageSize]
#define IFB_ENGINE_DEVTOOLS_PROPERTY_NAME_MEMORY_SYSTEM_INFO_TABLE_ALLOCATION_GRANULARITY IFB_ENGINE_DEVTOOLS_PROPERTY_NAMES[IFBEngineDevToolsProperty_MemorySystemInfo_AllocationGranularity]
namespace ifb_engine {

    //-----------------------
    // context property tables
    //-----------------------
    ifb_void devtools_property_table_render_context_sizes   (IFBEngineContext* context_ptr);
    ifb_void devtools_property_table_render_context_handles (IFBEngineContext* context_ptr);
    ifb_void devtools_property_table_render_context_config  (IFBEngineConfig&  config_ref);

    //-----------------------
    // memory property tables
    //-----------------------
    ifb_void devtools_property_table_render_memory_global_stack       (IFBEngineMemoryGlobalStack& global_stack_ref);
    ifb_void devtools_property_table_render_memory_system_reservation (IFBEngineMemoryReservation& reservation_ref);
    ifb_void devtools_property_table_render_memory_system_info        (IFBEngineMemorySystemInfo&  system_info);

    //-----------------------
    // property table control
    //-----------------------
    ifb_void
    devtools_property_table_render(
        const ifb_char*  property_table_name,
        const ifb_u32    property_table_row_count,
        const ifb_char** property_table_property_names,
        const ifb_char** property_table_property_values);

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
        IFBEngineDevToolsFlagsTools    tools;
    } flags;
};

namespace ifb_engine {

    ifb_void devtools_initialize (IFBEngineDevTools* devtools_ptr);
    ifb_void devtools_render     (IFBEngineDevTools* devtools_ptr, IFBInput& input_ref);
};

#endif //IFB_ENGINE_INTERNAL_DEVTOOLS_HPP