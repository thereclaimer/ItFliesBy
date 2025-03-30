#ifndef IFB_ENGINE_SYSTEMS_HPP
#define IFB_ENGINE_SYSTEMS_HPP

#include "ifb-engine.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

//engine core
struct IFBEngineCore;
struct IFBEngineCoreArenas;

//managers
struct IFBEngineGraphicsManager;
struct IFBEngineFileManager;
struct IFBEngineThreadManager;

/**********************************************************************************/
/* ENGINE CORE                                                                    */
/**********************************************************************************/

struct IFBEngineCore {
    IFBEngineMemory*          memory;
    IFBEngineGraphicsManager* graphics;
    IFBEngineFileManager*     files;
    IFBEngineThreadManager*   threads;
};

namespace ifb_engine {

    const ifb::b8 core_initialize   (IFBEngineCore* core);
    const ifb::b8 core_startup      (IFBEngineCore* core);
    const ifb::b8 core_frame_start  (IFBEngineCore* core);
    const ifb::b8 core_frame_render (IFBEngineCore* core);
    const ifb::b8 core_should_quit  (IFBEngineCore* core);
};

#define IFB_ENGINE_CORE_STRUCT_SIZE ifb_macro_align_size_struct(IFBEngineCore)

/**********************************************************************************/
/* GRAPHICS MANAGER                                                               */
/**********************************************************************************/

#define IFB_ENGINE_GRAPHICS_WINDOW_TITLE        "It Flies By (DEBUG)"
#define IFB_ENGINE_GRAPHICS_WINDOW_TITLE_LENGTH 255
#define IFB_ENGINE_GRAPHICS_WINDOW_INIT_WIDTH   1024
#define IFB_ENGINE_GRAPHICS_WINDOW_INIT_HEIGHT  768

struct IFBEngineGraphicsManager {
    IFBGFXWindow window_handle;
};

namespace ifb_engine {

    const ifb::b8 graphics_manager_initialize             (IFBEngineGraphicsManager* graphics_manager, IFBEngineMemory* engine_memory);
    const ifb::b8 graphics_manager_create_and_show_window (IFBEngineGraphicsManager* graphics_manager);
    const ifb::b8 graphics_manager_frame_start            (IFBEngineGraphicsManager* graphics_manager);
    const ifb::b8 graphics_manager_frame_render           (IFBEngineGraphicsManager* graphics_manager);
    const ifb::b8 graphics_manager_window_quit_received   (IFBEngineGraphicsManager* graphics_manager);
};

/**********************************************************************************/
/* FILE MANAGER                                                                   */
/**********************************************************************************/

struct IFBEngineFileManager {
    ifb::u32 x;
};



/**********************************************************************************/
/* THREAD MANAGER                                                                 */
/**********************************************************************************/

struct IFBEngineThreadManager {
    ifb::u32 x;
};

/**********************************************************************************/
/* GLOBALS                                                                        */
/**********************************************************************************/

struct IFBEngineCoreGlobals {
    ifb::u32   core_struct_size;
    ifb::u32   window_init_width;
    ifb::u32   window_init_height;
    ifb::u32   window_title_length;
    ifb::utf8* window_title;
};

namespace ifb_engine {

    ifb_global IFBEngineCoreGlobals _global_core = {
        IFB_ENGINE_CORE_STRUCT_SIZE,
        IFB_ENGINE_GRAPHICS_WINDOW_INIT_WIDTH,
        IFB_ENGINE_GRAPHICS_WINDOW_INIT_HEIGHT,
        IFB_ENGINE_GRAPHICS_WINDOW_TITLE_LENGTH,
        IFB_ENGINE_GRAPHICS_WINDOW_TITLE
    };
};

#endif //IFB_ENGINE_SYSTEMS_HPP