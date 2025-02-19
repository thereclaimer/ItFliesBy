#ifndef IFB_GRAPHICS_HPP
#define IFB_GRAPHICS_HPP

#include <ifb.hpp>
#include <ifb-data-structures.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

//handles
struct IFBHNDGraphics {
    IFBU32 offset;
};

struct IFBHNDGraphicsWindow  : IFBHNDGraphics { };
struct IFBHNDGraphicsMonitor : IFBHNDGraphics { };

struct IFBGraphicsContextInfo {
    IFBHNDLinearAllocator  linear_arena_handle;
    IFBColorFormat           color_format;
    IFBU32                   monitor_count;
    IFBHNDGraphicsWindow     primary_window_handle;
    IFBHNDGraphicsMonitor    primary_monitor_handle;
};

/**********************************************************************************/
/* CONTEXT                                                                        */
/**********************************************************************************/

namespace ifb_graphics {

    const IFBB8 
    context_reserve_and_initialize(
        const IFBHNDLinearAllocator linear_arena_handle,
        const IFBPlatformApi*         ptr_platform_api,
        const IFBColorFormat          color_format);
    
    const IFBB8 
    context_get_info(
        IFBGraphicsContextInfo* graphics_context_info);
};

/**********************************************************************************/
/* COLORS                                                                         */
/**********************************************************************************/

namespace ifb_graphics {

    const IFBB8
    color_normalize(
        const IFBColorHex*        ptr_color_hex,
              IFBColorNormalized* ptr_color_normalized);

    const IFBColor32 color32 (const IFBColorHex*        ptr_color_hex); 
    const IFBColor32 color32 (const IFBColorNormalized* ptr_color_normalized); 
};

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

struct IFBGraphicsWindowArgs {
    IFBChar*      title;
    IFBDimensions dimensions;
    IFBPosition   position;
};

namespace ifb_graphics {

    const IFBHNDGraphicsWindow 
    window_commit(
        IFBGraphicsWindowArgs* ptr_window_args);

    const IFBB8 window_show         (const IFBHNDGraphicsWindow window_handle);
    const IFBB8 window_frame_start  (const IFBHNDGraphicsWindow window_handle);
    const IFBB8 window_frame_render (const IFBHNDGraphicsWindow window_handle);
};

/**********************************************************************************/
/* MONITOR                                                                        */
/**********************************************************************************/

#endif //IFB_GRAPHICS_HPP