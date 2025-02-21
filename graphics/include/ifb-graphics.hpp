#ifndef IFB_GRAPHICS_HPP
#define IFB_GRAPHICS_HPP

#include <ifb.hpp>
#include <ifb-data-structures.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

//handles
struct IFBHNDWindow  : IFBHND32 { };
struct IFBHNDMonitor : IFBHND32 { };

struct IFBGraphicsContextInfo {
    IFBHNDArena    arena;
    IFBColorFormat color_format;
    IFBU32         monitor_count;
};

/**********************************************************************************/
/* CONTEXT                                                                        */
/**********************************************************************************/

namespace ifb_graphics {

    const IFBB8 
    context_reserve_and_initialize(
        const IFBHNDArena    arena_handle,
        const IFBColorFormat color_format);
    
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

struct IFBWindowArgs {
    IFBChar*      title;
    IFBDimensions dimensions;
    IFBPosition   position;
};

namespace ifb_graphics {

    const IFBHNDWindow 
    window_commit(
        IFBWindowArgs* ptr_window_args);

    const IFBB8 window_show         (const IFBHNDWindow window_handle);
    const IFBB8 window_frame_start  (const IFBHNDWindow window_handle);
    const IFBB8 window_frame_render (const IFBHNDWindow window_handle);
};

/**********************************************************************************/
/* MONITOR                                                                        */
/**********************************************************************************/

#endif //IFB_GRAPHICS_HPP