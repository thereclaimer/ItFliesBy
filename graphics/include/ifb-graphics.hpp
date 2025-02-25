#ifndef IFB_GRAPHICS_HPP
#define IFB_GRAPHICS_HPP

#include <ifb.hpp>
#include <ifb-data-structures.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

//handles
struct IFBHNDWindow  : IFBHNDPTR { };
struct IFBHNDMonitor : IFBHND32  { };

struct IFBGraphicsContextInfo {
    IFBHNDArena    arena;
    IFBColorFormat color_format;
    IFBU32         monitor_count;
};

/**********************************************************************************/
/* CONTEXT                                                                        */
/**********************************************************************************/

struct IFBWindowArgs {
    IFBChar*      title;
    IFBDimensions dimensions;
    IFBPosition   position;
};

namespace ifb_graphics {

    const IFBB8 
    context_create(
        const IFBHNDArena    arena_handle,
        const IFBColorFormat color_format);
    
    const IFBB8        context_get_info            (IFBGraphicsContextInfo* ptr_graphics_context_info);

    const IFBHNDWindow context_commit_window       (const IFBWindowArgs* ptr_window_args);
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


namespace ifb_graphics {

    const IFBB8        window_show         (const IFBHNDWindow   window_handle);
    const IFBB8        window_frame_start  (const IFBHNDWindow   window_handle);
    const IFBB8        window_frame_render (const IFBHNDWindow   window_handle);
};

/**********************************************************************************/
/* MONITOR                                                                        */
/**********************************************************************************/

struct IFBMonitorInfo {
    IFBU32        index;
    IFBU32        refresh_hz;
    IFBDimensions dimensions;
    IFBPosition   position;
};

namespace ifb_graphics {

    const IFBB8
    monitor_get_info(
        const IFBU32          monitor_index,
              IFBMonitorInfo* ptr_monitor_info);
    
    const IFBB8
    monitor_center_window(
        const IFBU32         monitor_index,
        const IFBDimensions* ptr_window_dimensions,
              IFBPosition*   ptr_window_center);
};

#endif //IFB_GRAPHICS_HPP