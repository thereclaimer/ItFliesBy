#ifndef IFB_PLATFORM_WINDOW_HPP
#define IFB_PLATFORM_WINDOW_HPP

#include <ifb.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

typedef void* IFBGLContext;

enum IFBPlatformWindowFlags_ {
    IFBPlatformWindowFlags_None    = 0,
    IFBPlatformWindowFlags_Closed  = 1,
    IFBPlatformWindowFlags_Visible = 2,
    IFBPlatformWindowFlags_Resized = 3,
    IFBPlatformWindowFlags_Moved   = 4,
};

typedef ifb::u64 IFBPlatformWindowFlags; 

struct IFBPlatformWindow {
    ifb::utf8*               title;
    IFBPlatformWindowFlags flags;
    ifb::dimensions_t          dims;
    ifb::position_t            pos;
    struct {
        ImGuiContext* imgui;
        IFBGLContext  opengl;
    } graphics_contexts;
};

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

typedef const ifb::u32  (*IFBPlatformWindowSize)          (void);
typedef const ifb::b8   (*IFBPlatformWindowCreate)        (IFBPlatformWindow* window);
typedef const ifb::b8   (*IFBPlatformWindowDestroy)       (IFBPlatformWindow* window);
typedef const ifb::b8   (*IFBPlatformWindowProcessEvents) (IFBPlatformWindow* window);
typedef const ifb::b8   (*IFBPlatformWindowSwapBuffers)   (IFBPlatformWindow* window);
typedef const ifb::b8   (*IFBPlatformWindowShow)          (IFBPlatformWindow* window);

namespace ifb_platform {

    inline void     window_set_flag_closed    (IFBPlatformWindowFlags& flags) { ifb_macro_bit_set(IFBPlatformWindowFlags_Closed,  flags); }
    inline void     window_set_flag_visible   (IFBPlatformWindowFlags& flags) { ifb_macro_bit_set(IFBPlatformWindowFlags_Visible, flags); }
    inline void     window_set_flag_resized   (IFBPlatformWindowFlags& flags) { ifb_macro_bit_set(IFBPlatformWindowFlags_Resized, flags); }
    inline void     window_set_flag_moved     (IFBPlatformWindowFlags& flags) { ifb_macro_bit_set(IFBPlatformWindowFlags_Moved,   flags); }

    inline const ifb::b8 window_get_flag_closed    (IFBPlatformWindowFlags& flags) { return(ifb_macro_bit_test(IFBPlatformWindowFlags_Closed,  flags)); }
    inline const ifb::b8 window_get_flag_visible   (IFBPlatformWindowFlags& flags) { return(ifb_macro_bit_test(IFBPlatformWindowFlags_Visible, flags)); }
    inline const ifb::b8 window_get_flag_resized   (IFBPlatformWindowFlags& flags) { return(ifb_macro_bit_test(IFBPlatformWindowFlags_Resized, flags)); }
    inline const ifb::b8 window_get_flag_moved     (IFBPlatformWindowFlags& flags) { return(ifb_macro_bit_test(IFBPlatformWindowFlags_Moved,   flags)); }

    inline void     window_clear_flag_closed  (IFBPlatformWindowFlags& flags) { ifb_macro_bit_clear(IFBPlatformWindowFlags_Closed,  flags); }
    inline void     window_clear_flag_visible (IFBPlatformWindowFlags& flags) { ifb_macro_bit_clear(IFBPlatformWindowFlags_Visible, flags); }
    inline void     window_clear_flag_resized (IFBPlatformWindowFlags& flags) { ifb_macro_bit_clear(IFBPlatformWindowFlags_Resized, flags); }
    inline void     window_clear_flag_moved   (IFBPlatformWindowFlags& flags) { ifb_macro_bit_clear(IFBPlatformWindowFlags_Moved,   flags); }
};

#endif //IFB_PLATFORM_WINDOW_HPP