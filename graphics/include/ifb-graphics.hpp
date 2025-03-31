#ifndef IFB_GRAPHICS_HPP
#define IFB_GRAPHICS_HPP

#include <ifb.hpp>
#include <ifb-memory.hpp>
#include <ifb-data-structures.hpp>
#include <ifb-platform.hpp>

using namespace ifb;
namespace platform=ifb::platform;

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/
namespace ifb::graphics {

    struct color_normalized_t;
    struct color_hex_t;
    struct color_32_t;
    struct window_args_t;

    typedef platform::window_t* window_h;
};

/**********************************************************************************/
/* COLORS                                                                         */
/**********************************************************************************/

namespace ifb::graphics {

    struct color_normalized_t {
        f32 red;
        f32 blue;
        f32 green;
        f32 alpha;
    };

    struct color_hex_t {
        u8 red;
        u8 blue;
        u8 green;
        u8 alpha;
    };

    struct color_32_t {
        u32 value;
    };

    enum color_format_e : u32 {
        color_format_e_rgba = 0,
        color_format_e_argb = 1,
        color_format_e_abgr = 2,
        color_format_e_bgra = 3
    };
    
    const b8         color_normalize             (const color_hex_t*        ptr_color_hex,        color_normalized_t*       ptr_color_normalized);
    const b8         color_denormalize           (const color_normalized_t* ptr_color_normalized, color_hex_t*              ptr_color_hex); 
    const color_32_t color_pack_hex_to_32        (const color_format_e      color_format,         const color_hex_t*        ptr_color_hex); 
    const color_32_t color_pack_normalized_to_32 (const color_format_e      color_format,         const color_normalized_t* ptr_color_normalized); 
};

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/
namespace ifb::graphics {
    struct window_args_t {
        utf8*        title;
        u32          title_length;
        dimensions_t dims;
        position_t   pos;
    };  


    const u32   window_memory_size       (const u32       window_title_length);
    window_h    window_memory_initialize (const memory_t& memory);

    const b8    window_create            (window_h window, const window_args_t& args);
    const b8    window_show              (window_h window);
    const b8    window_process_events    (window_h window);
    const b8    window_swap_buffers      (window_h window);

    platform::window_flags_t
    window_get_flags(window_h window);
};

/**********************************************************************************/
/* MONITOR                                                                        */
/**********************************************************************************/

namespace ifb::graphics {

    struct monitor_table_t {
        u32                  monitor_primary;
        u32                  monitor_count;
        platform::monitor_t* monitor_array;
    };

    const ifb::u32   monitor_table_memory_size         (void);
    monitor_table_t* monitor_table_memory_initialize   (const ptr memory);

    const b8         monitor_table_update              (monitor_table_t*           monitor_table_ptr);
    const b8         monitor_table_get_monitor         (const monitor_table_t*     monitor_table_ptr, platform::monitor_t*  monitor_ptr);
    const b8         monitor_table_get_monitor_primary (const monitor_table_t*     monitor_table_ptr, platform::monitor_t*  monitor_ptr);
    const b8         monitor_get_center                (const platform::monitor_t* monitor_ptr,       position_t*           center_position_ptr);
};


#endif //IFB_GRAPHICS_HPP