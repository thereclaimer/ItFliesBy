#ifndef IFB_GRAPHICS_INTERNAL_HPP
#define IFB_GRAPHICS_INTERNAL_HPP

#include "ifb-graphics.hpp"

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

struct IFBGraphicsWindow {
    IFBGraphicsWindow*      next;
    IFBGraphicsWindowHandle handle;
    IFBDimensions           dimensions;
    IFBPosition             position;
    ifb_ptr                 platform_handle;
};

struct IFBGraphicsWindowList {
    IFBGraphicsWindow* first;
    IFBGraphicsWindow* last;
    ifb_u32            count;
};

/**********************************************************************************/
/* CONTEXT                                                                        */
/**********************************************************************************/

struct IFBGraphicsContext {
    IFBStack*                     ptr_stack;                      
    IFBPlatformApi*               ptr_platform_api;
    IFBGraphicsContextColorFormat color_format;
    IFBGraphicsWindowList         window_list;
};


namespace ifb_graphics {
    
    IFBStack*                           context_get_stack        (ifb_void);
    const IFBPlatformApi*               context_get_platform_api (ifb_void);
    const IFBGraphicsContextColorFormat context_get_color_format (ifb_void);    
    IFBGraphicsWindowList&              context_get_window_list  (ifb_void);
};

#endif //IFB_GRAPHICS_INTERNAL_HPP