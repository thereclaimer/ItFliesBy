#ifndef IFB_GRAPHICS_HPP
#define IFB_GRAPHICS_HPP

#include <ifb.hpp>
#include <ifb-data-structures.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBWindow;
struct IFBWindowTitle;
struct IFBWindowPlatformContexts;

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

#define ifb_grahpics_macro_get_pointer_to_window(arena_handle,offset)        ifb_memory_macro_get_pointer_from_arena(arena_handle,offset,IFBWindow)
#define ifb_grahpics_macro_get_pointer_to_monitor(arena_handle,offset)       ifb_memory_macro_get_pointer_from_arena(arena_handle,offset,IFBMonitor)
#define ifb_grahpics_macro_get_pointer_to_monitor_table(arena_handle,offset) ifb_memory_macro_get_pointer_from_arena(arena_handle,offset,IFBMonitorTable)

#endif //IFB_GRAPHICS_HPP