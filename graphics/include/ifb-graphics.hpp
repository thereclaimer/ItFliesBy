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
    ifb::f32 red;
    ifb::f32 blue;
    ifb::f32 green;
    ifb::f32 alpha;
};

struct IFBColorHex {
    ifb::u8 red;
    ifb::u8 blue;
    ifb::u8 green;
    ifb::u8 alpha;
};

struct IFBColor32 {
    ifb::u32 value;
};

enum IFBColorFormat : ifb::u32 {
     IFBColorFormat_RGBA = 0,
     IFBColorFormat_ARGB = 1,
     IFBColorFormat_ABGR = 2,
     IFBColorFormat_BGRA = 3
};

namespace ifb_graphics {
    
    const ifb::b8      color_normalize             (const IFBColorHex*        ptr_color_hex,        IFBColorNormalized*       ptr_color_normalized);
    const ifb::b8      color_denormalize           (const IFBColorNormalized* ptr_color_normalized, IFBColorHex*              ptr_color_hex); 
    
    const IFBColor32 color_pack_hex_to_32        (const IFBColorFormat      color_format,         const IFBColorHex*        ptr_color_hex); 
    const IFBColor32 color_pack_normalized_to_32 (const IFBColorFormat      color_format,         const IFBColorNormalized* ptr_color_normalized); 
};

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

struct IFBGraphicsWindowArgs {
    ifb::utf8*      title;
    ifb::u32        title_length;
    ifb::dimensions_t dims;
    ifb::position_t   pos;
};  

namespace ifb_graphics {

    const ifb::u32   window_memory_size       (const ifb::u32     window_title_length);

    IFBGFXWindow   window_memory_initialize (const IFBMemory& memory);

    const ifb::b8    window_create            (IFBGFXWindow window_handle, const IFBGraphicsWindowArgs& args);
    const ifb::b8    window_show              (IFBGFXWindow window_handle);
    const ifb::b8    window_process_events    (IFBGFXWindow window_handle);
    const ifb::b8    window_swap_buffers      (IFBGFXWindow window_handle);

    IFBPlatformWindowFlags
    window_get_flags(IFBGFXWindow window_handle);
};


/**********************************************************************************/
/* MONITOR                                                                        */
/**********************************************************************************/

struct IFBMonitor {
    ifb::dimensions_t dimensions;
    ifb::position_t   position;
    ifb::u32        refresh_hz;
    ifb::u32        index;
};

struct IFBMonitorTable {
    ifb::u32      monitor_primary;
    ifb::u32      monitor_count;
    IFBMonitor* monitor_array;
};

namespace ifb_graphics {

    const ifb::u32     monitor_table_memory_size         (void);
    IFBMonitorTable* monitor_table_memory_initialize   (const ifb::ptr memory);

    const ifb::b8      monitor_table_update              (IFBMonitorTable* monitor_table_ptr);
    const ifb::b8      monitor_table_get_monitor         (const IFBMonitorTable* monitor_table_ptr, IFBMonitor* monitor_ptr);
    const ifb::b8      monitor_table_get_monitor_primary (const IFBMonitorTable* monitor_table_ptr, IFBMonitor* monitor_ptr);

    const ifb::b8      monitor_get_center                (const IFBMonitor* monitor_ptr, ifb::position_t* center_position_ptr);
};

#endif //IFB_GRAPHICS_HPP