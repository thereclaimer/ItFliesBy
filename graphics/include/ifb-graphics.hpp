#ifndef IFB_GRAPHICS_HPP
#define IFB_GRAPHICS_HPP

#include <ifb.hpp>
#include <ifb-data-structures.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBColorNormalized;
struct IFBColorHex;
struct IFBColor32;
struct IFBDimensions;
struct IFBPosition;
struct IFBDimensionsAndPosition;
struct IFBGraphicsContexts;
struct IFBWindow;
struct IFBMonitor;

typedef IFBPtr IFBGLContext;
typedef IFBPtr IFBImGuiContext;

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
              IFBMemoryArena* ptr_arena,
        const IFBColorFormat  color_format,
        const IFBU32          color_count,
        const IFBChar**       color_key_array,
        const IFBColorHex*    color_hex_array);

    const IFBU32
    color_table_commit_to_arena_relative(
              IFBMemoryArena* ptr_arena,
        const IFBColorFormat  color_format,
        const IFBU32          color_count,
        const IFBChar**       color_key_array,
        const IFBColorHex*    color_hex_array);

    const IFBColorTable*
    color_table_load_from_arena(
              IFBMemoryArena* ptr_arena,
        const IFBU32          color_table_offset);

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

#define IFB_WINDOW_TITLE_LENGTH_MAX 255

struct IFBGraphicsContexts {
    IFBGLContext    opengl;
    IFBImGuiContext imgui;
};

struct IFBWindow {
    IFBPosition         position;
    IFBDimensions       dimensions;
    IFBGraphicsContexts graphics_contexts;
    IFBB32              visible;
    IFBB32              quit_received;
    IFBChar*            title;
};

namespace ifb_graphics {

    IFBWindow*   window_commit_to_arena_absolute (IFBMemoryArena* ptr_arena);
    const IFBU32 window_commit_to_arena_relative (IFBMemoryArena* ptr_arena);

    const IFBB8  window_show                     (IFBWindow* ptr_window);
    const IFBB8  window_frame_start              (IFBWindow* ptr_window);
    const IFBB8  window_frame_render             (IFBWindow* ptr_window);
    const IFBB8  window_context_gl_create        (IFBWindow* ptr_window);
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

    const IFBB8 monitor_table_initialize          (IFBMonitorTable* monitor_table_ptr, IFBMemoryArena* ptr_arena);
    const IFBB8 monitor_table_update              (IFBMonitorTable* monitor_table_ptr);
    const IFBB8 monitor_table_get_monitor         (const IFBMonitorTable* monitor_table_ptr, IFBMonitor* monitor_ptr);
    const IFBB8 monitor_table_get_monitor_primary (const IFBMonitorTable* monitor_table_ptr, IFBMonitor* monitor_ptr);

    const IFBB8 monitor_get_center                (const IFBMonitor* monitor_ptr, IFBPosition* center_position_ptr);
};

/**********************************************************************************/
/* MACROS                                                                         */
/**********************************************************************************/

#define ifb_graphics_macro_commit_absolute_window(ptr_arena)              ifb_memory_macro_commit_struct_to_arena_absolute(ptr_arena,IFBWindow)
#define ifb_graphics_macro_commit_absolute_monitor_table(ptr_arena)       ifb_memory_macro_commit_struct_to_arena_absolute(ptr_arena,IFBMonitorTable)
#define ifb_graphics_macro_commit_absolute_monitor(ptr_arena)             ifb_memory_macro_commit_struct_to_arena_absolute(ptr_arena,IFBMonitor)

#define ifb_graphics_macro_commit_relative_window(ptr_arena)              ifb_memory_macro_commit_struct_to_arena_relative(ptr_arena,IFBWindow)
#define ifb_graphics_macro_commit_relative_monitor(ptr_arena)             ifb_memory_macro_commit_struct_to_arena_relative(ptr_arena,IFBMonitor)
#define ifb_graphics_macro_commit_relative_monitor_table(ptr_arena)       ifb_memory_macro_commit_struct_to_arena_relative(ptr_arena,IFBMonitorTable)

#define ifb_graphics_macro_get_pointer_to_window(ptr_arena,offset)        ifb_memory_macro_get_pointer_from_arena(ptr_arena,offset,IFBWindow)
#define ifb_graphics_macro_get_pointer_to_monitor(ptr_arena,offset)       ifb_memory_macro_get_pointer_from_arena(ptr_arena,offset,IFBMonitor)
#define ifb_graphics_macro_get_pointer_to_monitor_table(ptr_arena,offset) ifb_memory_macro_get_pointer_from_arena(ptr_arena,offset,IFBMonitorTable)

#endif //IFB_GRAPHICS_HPP