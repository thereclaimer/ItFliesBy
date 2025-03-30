#ifndef IFB_GRAPHICS_HPP
#define IFB_GRAPHICS_HPP

#include <ifb.hpp>
#include <ifb-memory.hpp>
#include <ifb-data-structures.hpp>
#include <ifb-platform.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBGraphicsWindow;

struct IFBColorNormalized;
struct IFBColorHex;
struct IFBColor32;
struct IFBMonitor;

typedef IFBGraphicsWindow* IFBGFXWindow; 

/**********************************************************************************/
/* COLORS                                                                         */
/**********************************************************************************/

struct IFBColorNormalized {
    IFBF32 red;
    IFBF32 blue;
    IFBF32 green;
    IFBF32 alpha;
};

struct IFBColorHex {
    IFBU8 red;
    IFBU8 blue;
    IFBU8 green;
    IFBU8 alpha;
};

struct IFBColor32 {
    IFBU32 value;
};

enum IFBColorFormat : IFBU32 {
     IFBColorFormat_RGBA = 0,
     IFBColorFormat_ARGB = 1,
     IFBColorFormat_ABGR = 2,
     IFBColorFormat_BGRA = 3
};

namespace ifb_graphics {
    
    const IFBB8      color_normalize             (const IFBColorHex*        ptr_color_hex,        IFBColorNormalized*       ptr_color_normalized);
    const IFBB8      color_denormalize           (const IFBColorNormalized* ptr_color_normalized, IFBColorHex*              ptr_color_hex); 
    
    const IFBColor32 color_pack_hex_to_32        (const IFBColorFormat      color_format,         const IFBColorHex*        ptr_color_hex); 
    const IFBColor32 color_pack_normalized_to_32 (const IFBColorFormat      color_format,         const IFBColorNormalized* ptr_color_normalized); 
};

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

struct IFBGraphicsWindowArgs {
    IFBChar*      title;
    IFBU32        title_length;
    IFBDimensions dims;
    IFBPosition   pos;
};  

namespace ifb_graphics {

    const IFBU32   window_memory_size       (const IFBU32     window_title_length);

    IFBGFXWindow   window_memory_initialize (const IFBMemory& memory);

    const IFBB8    window_create            (IFBGFXWindow window_handle, const IFBGraphicsWindowArgs& args);
    const IFBB8    window_show              (IFBGFXWindow window_handle);
    const IFBB8    window_process_events    (IFBGFXWindow window_handle);
    const IFBB8    window_swap_buffers      (IFBGFXWindow window_handle);

    IFBPlatformWindowFlags
    window_get_flags(IFBGFXWindow window_handle);
};


/**********************************************************************************/
/* MONITOR                                                                        */
/**********************************************************************************/

struct IFBMonitor {
    IFBDimensions dimensions;
    IFBPosition   position;
    IFBU32        refresh_hz;
    IFBU32        index;
};

struct IFBMonitorTable {
    IFBU32      monitor_primary;
    IFBU32      monitor_count;
    IFBMonitor* monitor_array;
};

namespace ifb_graphics {

    const IFBU32     monitor_table_memory_size         (IFBVoid);
    IFBMonitorTable* monitor_table_memory_initialize   (const IFBPtr memory);

    const IFBB8      monitor_table_update              (IFBMonitorTable* monitor_table_ptr);
    const IFBB8      monitor_table_get_monitor         (const IFBMonitorTable* monitor_table_ptr, IFBMonitor* monitor_ptr);
    const IFBB8      monitor_table_get_monitor_primary (const IFBMonitorTable* monitor_table_ptr, IFBMonitor* monitor_ptr);

    const IFBB8      monitor_get_center                (const IFBMonitor* monitor_ptr, IFBPosition* center_position_ptr);
};

#endif //IFB_GRAPHICS_HPP