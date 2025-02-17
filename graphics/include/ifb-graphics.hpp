#ifndef IFB_GRAPHICS_HPP
#define IFB_GRAPHICS_HPP

#include <ifb.hpp>
#include <ifb-data-structures.hpp>

struct IFBGraphicsContext;

struct IFBGraphicsColorNormalized;
struct IFBGraphicsColorHex;

struct IFBGraphicsHandle {
    ifb_u32 offset;
};

struct IFBGraphicsWindowHandle  : IFBGraphicsHandle { };
struct IFBGraphicsMonitorHandle : IFBGraphicsHandle { };

enum IFBGraphicsContextColorFormat;

/**********************************************************************************/
/* COLORS                                                                         */
/**********************************************************************************/

struct IFBGraphicsColor {
    ifb_u8 red;
    ifb_u8 green;
    ifb_u8 blue;
    ifb_u8 alpha;
};

struct IFBGraphicsColorNormalized {
    ifb_f32 red;
    ifb_f32 green;
    ifb_f32 blue;
    ifb_f32 alpha;
};

struct IFBGraphicsColorHex {
    ifb_u32 hex;
};

namespace ifb_graphics {

    const ifb_b8
    color_normalize(
        const IFBGraphicsColorHex*        ptr_color_hex,
              IFBGraphicsColorNormalized* ptr_color_normalized);

    const IFBGraphicsColorHex 
    color_hex(
        const IFBGraphicsColor* color_32_ptr); 
};


/**********************************************************************************/
/* CONTEXT                                                                        */
/**********************************************************************************/

enum IFBGraphicsColorFormat : ifb_u32 {
    IFBGraphicsColorFormat_RGBA = 0,
    IFBGraphicsColorFormat_ARGB = 1,
    IFBGraphicsColorFormat_ABGR = 2,
    IFBGraphicsColorFormat_BGRA = 3
};

namespace ifb_graphics {

    const ifb_b8
    context_create(
        const IFBPlatformApi*        ptr_platform_api,
        const IFBStack*              ptr_stack,
        const IFBGraphicsColorFormat color_format);
        
    const ifb_b8
    context_destroy(
        ifb_void);
};

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

struct IFBGraphicsWindowTitle {
    ifb_char title_cstr[256];
};

namespace ifb_graphics {

    const IFBGraphicsWindowHandle window_reserve(ifb_void);
    const ifb_b8                  window_release(const IFBGraphicsWindowHandle);


    const ifb_b8 window_show         (const IFBGraphicsWindowHandle window_handle);
    const ifb_b8 window_frame_start  (const IFBGraphicsWindowHandle window_handle);
    const ifb_b8 window_frame_render (const IFBGraphicsWindowHandle window_handle);

};

/**********************************************************************************/
/* MONITOR                                                                        */
/**********************************************************************************/

#endif //IFB_GRAPHICS_HPP