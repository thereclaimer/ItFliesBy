#ifndef IFB_PLATFORM_WINDOW_HPP
#define IFB_PLATFORM_WINDOW_HPP

#include <ifb.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

typedef IFBVoid* IFBGLContext;

enum IFBPlatformWindowFlags_ {
    IFBPlatformWindowFlags_None    = 0,
    IFBPlatformWindowFlags_Closed  = 1,
    IFBPlatformWindowFlags_Visible = 2,
    IFBPlatformWindowFlags_Resized = 3,
    IFBPlatformWindowFlags_Moved   = 4,
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

namespace ifb_platform {

    inline IFBVoid     window_set_flag_closed    (IFBPlatformWindowFlags& flags) { ifb_macro_bit_set(IFBPlatformWindowFlags_Closed,  flags); }
    inline IFBVoid     window_set_flag_visible   (IFBPlatformWindowFlags& flags) { ifb_macro_bit_set(IFBPlatformWindowFlags_Visible, flags); }
    inline IFBVoid     window_set_flag_resized   (IFBPlatformWindowFlags& flags) { ifb_macro_bit_set(IFBPlatformWindowFlags_Resized, flags); }
    inline IFBVoid     window_set_flag_moved     (IFBPlatformWindowFlags& flags) { ifb_macro_bit_set(IFBPlatformWindowFlags_Moved,   flags); }

    inline const IFBB8 window_get_flag_closed    (IFBPlatformWindowFlags& flags) { return(ifb_macro_bit_test(IFBPlatformWindowFlags_Closed,  flags)); }
    inline const IFBB8 window_get_flag_visible   (IFBPlatformWindowFlags& flags) { return(ifb_macro_bit_test(IFBPlatformWindowFlags_Visible, flags)); }
    inline const IFBB8 window_get_flag_resized   (IFBPlatformWindowFlags& flags) { return(ifb_macro_bit_test(IFBPlatformWindowFlags_Resized, flags)); }
    inline const IFBB8 window_get_flag_moved     (IFBPlatformWindowFlags& flags) { return(ifb_macro_bit_test(IFBPlatformWindowFlags_Moved,   flags)); }

    inline IFBVoid     window_clear_flag_closed  (IFBPlatformWindowFlags& flags) { ifb_macro_bit_clear(IFBPlatformWindowFlags_Closed,  flags); }
    inline IFBVoid     window_clear_flag_visible (IFBPlatformWindowFlags& flags) { ifb_macro_bit_clear(IFBPlatformWindowFlags_Visible, flags); }
    inline IFBVoid     window_clear_flag_resized (IFBPlatformWindowFlags& flags) { ifb_macro_bit_clear(IFBPlatformWindowFlags_Resized, flags); }
    inline IFBVoid     window_clear_flag_moved   (IFBPlatformWindowFlags& flags) { ifb_macro_bit_clear(IFBPlatformWindowFlags_Moved,   flags); }
};

#endif //IFB_PLATFORM_WINDOW_HPP