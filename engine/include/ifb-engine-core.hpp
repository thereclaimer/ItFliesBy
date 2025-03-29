#ifndef IFB_ENGINE_SYSTEMS_HPP
#define IFB_ENGINE_SYSTEMS_HPP

#include "ifb-engine.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

//engine core
struct IFBEngineCore;

//managers
struct IFBEngineGraphicsManager;
struct IFBEngineFileManager;
struct IFBEngineThreadManager;

/**********************************************************************************/
/* ENGINE CORE                                                                    */
/**********************************************************************************/

struct IFBEngineCore {
    IFBEngineGraphicsManager* graphics;
    IFBEngineFileManager*     files;
    IFBEngineThreadManager*   threads;
};

namespace ifb_engine {

    const IFBB8 core_startup      (IFBEngineCore* core);
    const IFBB8 core_frame_start  (IFBEngineCore* core);
    const IFBB8 core_frame_render (IFBEngineCore* core);
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

    const IFBB8 graphics_manager_create_and_show_window (IFBEngineGraphicsManager* graphics_manager);
    const IFBB8 graphics_manager_frame_start            (IFBEngineGraphicsManager* graphics_manager);
    const IFBB8 graphics_manager_frame_render           (IFBEngineGraphicsManager* graphics_manager);
};

/**********************************************************************************/
/* FILE MANAGER                                                                   */
/**********************************************************************************/

struct IFBEngineFileManager {
    IFBU32 x;
};



/**********************************************************************************/
/* THREAD MANAGER                                                                 */
/**********************************************************************************/

struct IFBEngineThreadManager {
    IFBU32 x;
};

/**********************************************************************************/
/* GLOBALS                                                                        */
/**********************************************************************************/

struct IFBEngineCoreGlobals {
    IFBU32   core_struct_size;
    IFBU32   window_init_width;
    IFBU32   window_init_height;
    IFBU32   window_title_length;
    IFBChar* window_title;
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