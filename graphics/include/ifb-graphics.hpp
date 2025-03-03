#ifndef IFB_GRAPHICS_HPP
#define IFB_GRAPHICS_HPP

#include <ifb.hpp>
#include <ifb-data-structures.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBWindow;
struct IFBWindowTitle;
struct IFBGraphicsContexts;

/**********************************************************************************/
/* COLORS                                                                         */
/**********************************************************************************/

struct IFBColorTable {
    IFBHashTable*  ptr_hash_table;
    IFBColorFormat color_format;
};

namespace ifb_graphics {
    
    const IFBB8      color_normalize             (const IFBColorHex*        ptr_color_hex,        IFBColorNormalized*       ptr_color_normalized);
    const IFBB8      color_denormalize           (const IFBColorNormalized* ptr_color_normalized, IFBColorHex*              ptr_color_hex); 
    
    const IFBColor32 color_pack_hex_to_32        (const IFBColorFormat      color_format,         const IFBColorHex*        ptr_color_hex); 
    const IFBColor32 color_pack_normalized_to_32 (const IFBColorFormat      color_format,         const IFBColorNormalized* ptr_color_normalized); 

    //color table
    const IFBColorTable*
    color_table_commit_to_arena_absolute(
        const IFBHNDArena    arena_handle,
        const IFBColorFormat color_format,
        const IFBU32         color_count,
        const IFBChar**      color_key_array,
        const IFBColorHex*   color_hex_array);

    const IFBU32
    color_table_commit_to_arena_relative(
        const IFBHNDArena    arena_handle,
        const IFBColorFormat color_format,
        const IFBU32         color_count,
        const IFBChar**      color_key_array,
        const IFBColorHex*   color_hex_array);

    const IFBColorTable*
    color_table_load_from_arena(
        const IFBHNDArena arena_handle,
        const IFBU32      color_table_offset);

    //lookup
    const IFBB8 color_table_lookup_hex        (const IFBColorTable* ptr_color_table, const IFBChar* ptr_color_key, IFBColorHex*        ptr_color_hex);
    const IFBB8 color_table_lookup_normalized (const IFBColorTable* ptr_color_table, const IFBChar* ptr_color_key, IFBColorNormalized* ptr_color_normalized);
    const IFBB8 color_table_lookup_packed_32  (const IFBColorTable* ptr_color_table, const IFBChar* ptr_color_key, IFBColor32*         ptr_color_32);

    //indexing
    const IFBB8 color_table_get_hex           (const IFBColorTable* ptr_color_table, const IFBU32   color_index,   IFBColorHex*        ptr_color_hex);
    const IFBB8 color_table_get_normalized    (const IFBColorTable* ptr_color_table, const IFBU32   color_index,   IFBColorNormalized* ptr_color_normalized);
    const IFBB8 color_table_get_packed_32     (const IFBColorTable* ptr_color_table, const IFBU32   color_index,   IFBColor32*         ptr_color_32);
};

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

namespace ifb_graphics {

    IFBWindow*   window_commit_to_arena_absolute (const IFBHNDArena arena_handle);
    const IFBU32 window_commit_to_arena_relative (const IFBHNDArena arena_handle);

    const IFBB8  window_show                     (IFBWindow* ptr_window);
    const IFBB8  window_frame_start              (IFBWindow* ptr_window);
    const IFBB8  window_frame_render             (IFBWindow* ptr_window);
    const IFBB8  window_context_gl_create        (IFBWindow* ptr_window);
};

/**********************************************************************************/
/* MONITOR                                                                        */
/**********************************************************************************/

struct IFBMonitorTable {
    IFBU32      monitor_primary;
    IFBU32      monitor_count;
    IFBMonitor* monitor_array;
};

namespace ifb_graphics {

    const IFBB8 monitor_table_initialize          (IFBMonitorTable* monitor_table_ptr, const IFBHNDArena arena_handle);
    const IFBB8 monitor_table_update              (IFBMonitorTable* monitor_table_ptr);
    const IFBB8 monitor_table_get_monitor         (const IFBMonitorTable* monitor_table_ptr, IFBMonitor* monitor_ptr);
    const IFBB8 monitor_table_get_monitor_primary (const IFBMonitorTable* monitor_table_ptr, IFBMonitor* monitor_ptr);

    const IFBB8 monitor_get_center                (const IFBMonitor* monitor_ptr, IFBPosition* center_position_ptr);
};

/**********************************************************************************/
/* MACROS                                                                         */
/**********************************************************************************/

#define ifb_graphics_macro_commit_absolute_window(arena_handle)              ifb_memory_macro_commit_struct_to_arena_absolute(arena_handle,IFBWindow)
#define ifb_graphics_macro_commit_absolute_monitor_table(arena_handle)       ifb_memory_macro_commit_struct_to_arena_absolute(arena_handle,IFBMonitorTable)
#define ifb_graphics_macro_commit_absolute_monitor(arena_handle)             ifb_memory_macro_commit_struct_to_arena_absolute(arena_handle,IFBMonitor)

#define ifb_graphics_macro_commit_relative_window(arena_handle)              ifb_memory_macro_commit_struct_to_arena_relative(arena_handle,IFBWindow)
#define ifb_graphics_macro_commit_relative_monitor(arena_handle)             ifb_memory_macro_commit_struct_to_arena_relative(arena_handle,IFBMonitor)
#define ifb_graphics_macro_commit_relative_monitor_table(arena_handle)       ifb_memory_macro_commit_struct_to_arena_relative(arena_handle,IFBMonitorTable)

#define ifb_graphics_macro_get_pointer_to_window(arena_handle,offset)        ifb_memory_macro_get_pointer_from_arena(arena_handle,offset,IFBWindow)
#define ifb_graphics_macro_get_pointer_to_monitor(arena_handle,offset)       ifb_memory_macro_get_pointer_from_arena(arena_handle,offset,IFBMonitor)
#define ifb_graphics_macro_get_pointer_to_monitor_table(arena_handle,offset) ifb_memory_macro_get_pointer_from_arena(arena_handle,offset,IFBMonitorTable)


#endif //IFB_GRAPHICS_HPP