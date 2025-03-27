#ifndef IFB_PLATFORM_WINDOW_HPP
#define IFB_PLATFORM_WINDOW_HPP

#include <ifb.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

typedef IFBVoid* IFBGLContext;

enum IFBPlatformWindowFlags_ {
    IFBPlatformWindowFlags_None    = IFB_BIT_FLAG_0,
    IFBPlatformWindowFlags_Closed  = IFB_BIT_FLAG_1,
    IFBPlatformWindowFlags_Visible = IFB_BIT_FLAG_2,
    IFBPlatformWindowFlags_Resized = IFB_BIT_FLAG_3,
    IFBPlatformWindowFlags_Moved   = IFB_BIT_FLAG_4,
};

typedef IFBU64 IFBPlatformWindowFlags; 

struct IFBPlatformWindow {
    IFBChar*               title;
    IFBPlatformWindowFlags flags;
    IFBDimensions          dims;
    IFBPosition            pos;
    struct {
        ImGuiContext* imgui;
        IFBGLContext  opengl;
    } graphics_contexts;
};

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

typedef const IFBU32  (*IFBPlatformWindowSize)          (IFBVoid);
typedef const IFBB8   (*IFBPlatformWindowCreate)        (IFBPlatformWindow* window);
typedef const IFBB8   (*IFBPlatformWindowDestroy)       (IFBPlatformWindow* window);
typedef const IFBB8   (*IFBPlatformWindowProcessEvents) (IFBPlatformWindow* window);
typedef const IFBB8   (*IFBPlatformWindowSwapBuffers)   (IFBPlatformWindow* window);
typedef const IFBB8   (*IFBPlatformWindowShow)          (IFBPlatformWindow* window);

#endif //IFB_PLATFORM_WINDOW_HPP