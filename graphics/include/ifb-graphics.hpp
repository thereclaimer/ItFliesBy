#ifndef IFB_GRAPHICS_HPP
#define IFB_GRAPHICS_HPP

#include <ifb.hpp>
#include <ifb-memory.hpp>
#include <ifb-data-structures.hpp>
#include <ifb-platform.hpp>

using namespace ifb;
namespace ifb {

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct graphics_color_normalized_t;
struct graphics_color_hex_t;
struct graphics_color_32_t;

struct graphics_window_args_t;
struct graphics_window_t;


struct graphics_monitor_t;
struct graphics_monitor_table_t;


typedef graphics_window_t* graphics_window_h;

/**********************************************************************************/
/* COLORS                                                                         */
/**********************************************************************************/


struct graphics_color_normalized_t {
    f32 red;
    f32 blue;
    f32 green;
    f32 alpha;
};

struct graphics_color_hex_t {
    u8 red;
    u8 blue;
    u8 green;
    u8 alpha;
};

struct graphics_color_32_t {
    u32 value;
};

enum graphics_color_format_e : u32 {
    graphics_color_format_e_rgba = 0,
    graphics_color_format_e_argb = 1,
    graphics_color_format_e_abgr = 2,
    graphics_color_format_e_bgra = 3
}; 


namespace graphics {

    const b8                  color_normalize             (const graphics_color_hex_t*        ptr_color_hex,        graphics_color_normalized_t*       ptr_color_normalized);
    const b8                  color_denormalize           (const graphics_color_normalized_t* ptr_color_normalized, graphics_color_hex_t*              ptr_color_hex); 
    const graphics_color_32_t color_pack_hex_to_32        (const graphics_color_format_e      color_format,         const graphics_color_hex_t*        ptr_color_hex); 
    const graphics_color_32_t color_pack_normalized_to_32 (const graphics_color_format_e      color_format,         const graphics_color_normalized_t* ptr_color_normalized);

};

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/


struct graphics_window_args_t {
    utf8*        title;
    u32          title_length;
    dimensions_t dims;
    position_t   pos;
};  

namespace graphics {

    const u32         window_memory_size       (const u32       window_title_length);
    graphics_window_h window_memory_initialize (const memory_t& memory);

    const b8          window_create            (graphics_window_h window, const graphics_window_args_t& args);
    const b8          window_show              (graphics_window_h window);
    const b8          window_process_events    (graphics_window_h window);
    const b8          window_swap_buffers      (graphics_window_h window);

    platform_window_flags_t
    window_get_flags(graphics_window_h window);
};

/**********************************************************************************/
/* MONITOR                                                                        */
/**********************************************************************************/


struct graphics_monitor_table_t {
    u32                  monitor_primary;
    u32                  monitor_count;
    graphics_monitor_t*  monitor_array;
};

namespace graphics {

    const u32                 monitor_table_memory_size         (void);
    graphics_monitor_table_t* monitor_table_memory_initialize   (const ptr memory);

    const b8                  monitor_table_update              (graphics_monitor_table_t*       monitor_table_ptr);
    const b8                  monitor_table_get_monitor         (const graphics_monitor_table_t* monitor_table_ptr, graphics_monitor_t* monitor_ptr);
    const b8                  monitor_table_get_monitor_primary (const graphics_monitor_table_t* monitor_table_ptr, graphics_monitor_t* monitor_ptr);
    const b8                  monitor_get_center                (const graphics_monitor_t*       monitor_ptr,       position_t*         center_position_ptr);

}; //namespace ifb::graphics
}; //namespace ifb

#endif //IFB_GRAPHICS_HPP