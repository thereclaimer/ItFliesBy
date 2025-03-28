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

#endif //IFB_ENGINE_SYSTEMS_HPP