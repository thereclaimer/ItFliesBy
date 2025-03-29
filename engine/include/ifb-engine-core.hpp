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

/**********************************************************************************/
/* GRAPHICS MANAGER                                                               */
/**********************************************************************************/

#define IFB_ENGINE_GRAPHICS_WINDOW_TITLE       "It Flies By (DEBUG)"
#define IFB_ENGINE_GRAPHICS_WINDOW_INIT_WIDTH  1024
#define IFB_ENGINE_GRAPHICS_WINDOW_INIT_HEIGHT 768

struct IFBEngineGraphicsManager {
    IFBGFXWindow window_handle;
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
    IFBChar* window_title;
    IFBU32   window_init_width;
    IFBU32   window_init_height;
};

namespace ifb_engine {

    ifb_global IFBEngineCoreGlobals _global_core = {
        IFB_ENGINE_GRAPHICS_WINDOW_TITLE,
        IFB_ENGINE_GRAPHICS_WINDOW_INIT_WIDTH,
        IFB_ENGINE_GRAPHICS_WINDOW_INIT_HEIGHT
    };

};

#endif //IFB_ENGINE_SYSTEMS_HPP