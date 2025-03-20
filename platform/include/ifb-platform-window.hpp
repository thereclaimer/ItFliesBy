#ifndef IFB_PLATFORM_WINDOW_HPP
#define IFB_PLATFORM_WINDOW_HPP

#include <ifb.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

typedef IFBVoid* IFBGLContext;

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

typedef const IFBB8
(*IFBPlatformWindowCreate) (
    const IFBChar* title,
    const IFBU32   width,
    const IFBU32   height,
    const IFBU32   position_x,
    const IFBU32   position_y);

typedef const IFBB8   (*IFBPlatformWindowDestroy)     (IFBVoid);
typedef const IFBB8   (*IFBPlatformWindowFrameStart)  (IFBVoid);
typedef const IFBB8   (*IFBPlatformWindowFrameRender) (IFBVoid);
typedef const IFBB8   (*IFBPlatformWindowShow)        (IFBVoid);
typedef IFBGLContext  (*IFBPlatformWindowOpenGLInit)  (IFBVoid);
typedef ImGuiContext* (*IFBPlatformWindowImGUIInit)   (IFBVoid);

#endif //IFB_PLATFORM_WINDOW_HPP