#ifndef IFB_ENGINE_HPP
#define IFB_ENGINE_HPP

#include <ifb.hpp>
#include <ifb-math.hpp>


/**********************************************************************************/
/* CONFIG                                                                         */
/**********************************************************************************/

#define IFB_ENGINE_CONFIG_MEMORY_MINIMUM_GB       2
#define IFB_ENGINE_CONFIG_MEMORY_COMMIT_COUNT_MAX 128
#define IFB_ENGINE_CONFIG_GLOBAL_STACK_KB         64
#define IFB_ENGINE_CONFIG_ARENA_MINIMUM_KB        4
#define IFB_ENGINE_CONFIG_ARENA_COUNT_MAX         64
#define IFB_ENGINE_CONFIG_TAG_C_STR_LENGTH        32
#define IFB_ENGINE_CONFIG_TAG_COUNT_MAX           1024
#define IFB_ENGINE_CONFIG_WINDOW_TITLE            "It Flies By"                 
#define IFB_ENGINE_CONFIG_DEVTOOLS                1            

struct IFBEngineConfig {
    ifb_u16  memory_minimum_gb;
    ifb_u16  memory_commit_count_max;
    ifb_u16  global_stack_kb;
    ifb_u16  arena_minimum_kb;
    ifb_u16  arena_count_max;
    ifb_u16  tag_c_str_length;
    ifb_u16  tag_count_max;
    ifb_b16  use_devtools;
    ifb_cstr window_title_cstr;
};

namespace ifb_engine {

    inline ifb_void 
    config_get_values(IFBEngineConfig* ptr_engine_config) {

        ptr_engine_config->memory_minimum_gb       = IFB_ENGINE_CONFIG_MEMORY_MINIMUM_GB;
        ptr_engine_config->memory_commit_count_max = IFB_ENGINE_CONFIG_MEMORY_COMMIT_COUNT_MAX;
        ptr_engine_config->global_stack_kb         = IFB_ENGINE_CONFIG_GLOBAL_STACK_KB;
        ptr_engine_config->arena_minimum_kb        = IFB_ENGINE_CONFIG_ARENA_MINIMUM_KB;
        ptr_engine_config->arena_count_max         = IFB_ENGINE_CONFIG_ARENA_COUNT_MAX;
        ptr_engine_config->tag_c_str_length        = IFB_ENGINE_CONFIG_TAG_C_STR_LENGTH;
        ptr_engine_config->tag_count_max           = IFB_ENGINE_CONFIG_TAG_COUNT_MAX;
        ptr_engine_config->window_title_cstr       = IFB_ENGINE_CONFIG_WINDOW_TITLE; 
        ptr_engine_config->use_devtools            = IFB_ENGINE_CONFIG_DEVTOOLS; 
    }
};

/**********************************************************************************/
/* UPDATE                                                                         */
/**********************************************************************************/

enum IFBEngineUpdateWindowFlags_ {
    IFBEngineUpdateWindowFlags_None       = 0,
    IFBEngineUpdateWindowFlags_Close      = (1 << 0),
    IFBEngineUpdateWindowFlags_Resize     = (1 << 1),
    IFBEngineUpdateWindowFlags_Reposition = (1 << 2),
    IFBEngineUpdateWindowFlags_Maximize   = (1 << 3)
};

typedef ifb_u32 IFBEngineUpdateWindowFlags;

struct IFBEngineUpdateWindow {
    IFBPosition                position;
    IFBDimensions              dimensions;
    IFBEngineUpdateWindowFlags flags;
};

struct IFBEngineUpdate {
    IFBInput              input;
    IFBEngineUpdateWindow window;
};

namespace ifb_engine {

    inline ifb_void context_update_window_flags_set_close          (IFBEngineUpdate& update_ref) { update_ref.window.flags |= IFBEngineUpdateWindowFlags_Close;      }
    inline ifb_void context_update_window_flags_set_resize         (IFBEngineUpdate& update_ref) { update_ref.window.flags |= IFBEngineUpdateWindowFlags_Resize;     }
    inline ifb_void context_update_window_flags_set_reposition     (IFBEngineUpdate& update_ref) { update_ref.window.flags |= IFBEngineUpdateWindowFlags_Reposition; }
    inline ifb_void context_update_window_flags_set_maximize       (IFBEngineUpdate& update_ref) { update_ref.window.flags |= IFBEngineUpdateWindowFlags_Maximize;   }

    inline ifb_void context_update_window_flags_clear_close        (IFBEngineUpdate& update_ref) { update_ref.window.flags &= ~(IFBEngineUpdateWindowFlags_Close);      }
    inline ifb_void context_update_window_flags_clear_resize       (IFBEngineUpdate& update_ref) { update_ref.window.flags &= ~(IFBEngineUpdateWindowFlags_Resize);     }
    inline ifb_void context_update_window_flags_clear_reposition   (IFBEngineUpdate& update_ref) { update_ref.window.flags &= ~(IFBEngineUpdateWindowFlags_Reposition); }
    inline ifb_void context_update_window_flags_clear_maximize     (IFBEngineUpdate& update_ref) { update_ref.window.flags &= ~(IFBEngineUpdateWindowFlags_Maximize);   }

    inline const ifb_b8 context_update_window_flags_get_close      (IFBEngineUpdate& update_ref) { return(update_ref.window.flags & IFBEngineUpdateWindowFlags_Close);      }
    inline const ifb_b8 context_update_window_flags_get_resize     (IFBEngineUpdate& update_ref) { return(update_ref.window.flags & IFBEngineUpdateWindowFlags_Resize);     }
    inline const ifb_b8 context_update_window_flags_get_reposition (IFBEngineUpdate& update_ref) { return(update_ref.window.flags & IFBEngineUpdateWindowFlags_Reposition); }
    inline const ifb_b8 context_update_window_flags_get_maximize   (IFBEngineUpdate& update_ref) { return(update_ref.window.flags & IFBEngineUpdateWindowFlags_Maximize);   }

};

/**********************************************************************************/
/* ENGINE                                                                         */
/**********************************************************************************/

enum IFBEngineState_ {
    IFBEngineState_NotRunning   = 0,
    IFBEngineState_Fatal        = 1,
    IFBEngineState_Startup      = 2,
    IFBEngineState_Shutdown     = 3,
    IFBEngineState_Idle         = 4,
    IFBEngineState_FrameExecute = 5,
};

typedef ifb_u32 IFBEngineState;

namespace ifb_engine {

    ifb_api const ifb_b8 context_create            (IFBPlatformApi& platform_api_ref);
    ifb_api const ifb_b8 context_destroy           (ifb_void);
    ifb_api const ifb_b8 context_startup           (ifb_void);
    ifb_api const ifb_b8 context_update_and_render (IFBEngineUpdate& update);
};

/**********************************************************************************/
/* TAG                                                                            */
/**********************************************************************************/

namespace ifb_engine {

    ifb_api const ifb_b8   tag_reserve  (const ifb_cstr  tag_cstr, IFBIDTag& tag_id_ref); 
    ifb_api const ifb_b8   tag_release  (const IFBIDTag& tag_id_ref);
    ifb_api const ifb_cstr tag_get_cstr (const IFBIDTag& tag_id_ref);
    ifb_api const IFBHash  tag_get_hash (const IFBIDTag& tag_id_ref);
};

/**********************************************************************************/
/* ARENA                                                                            */
/**********************************************************************************/

namespace ifb_engine {

    ifb_api const ifb_u32    arena_get_page_start     (const IFBIDArena& arena_id_ref);
    ifb_api const ifb_u32    arena_get_page_count     (const IFBIDArena& arena_id_ref);
    ifb_api const ifb_cstr   arena_get_tag_cstr       (const IFBIDArena& arena_id_ref);
    ifb_api const ifb_memory arena_get_pointer_start  (const IFBIDArena& arena_id_ref);
    ifb_api const ifb_memory arena_get_pointer_offset (const IFBIDArena& arena_id_ref, const ifb_u32 offset);
};

#endif //IFB_ENGINE_HPP