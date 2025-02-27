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

#define IFB_WINDOW_TITLE_LENGTH_MAX 255

struct IFBWindowPlatformContexts {
    IFBGLContext  opengl;
    ImGuiContext* imgui;
};

struct IFBWindow {
    IFBPosition               position;
    IFBDimensions             dimensions;
    IFBWindowPlatformContexts platform_contexts;
    IFBB32                    visible;
    IFBB32                    quit_received;
    IFBChar*                  title;
};

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

struct IFBMonitor {
    IFBU32        index;
    IFBU32        refresh_hz;
    IFBDimensions dimensions;
    IFBPosition   position;
};

namespace ifb_graphics {

    IFBMonitor*  monitor_commit_to_arena_absolute (const IFBHNDArena arena_handle);
    const IFBU32 monitor_commit_to_arena_relative (const IFBHNDArena arena_handle);
    const IFBU32 monitor_get_system_count         (IFBVoid);
    const IFBB8  monitor_initialize               (IFBMonitor* ptr_monitor);
};

#endif //IFB_GRAPHICS_HPP