#ifndef IFB_GRAPHICS_INTERNAL_HPP
#define IFB_GRAPHICS_INTERNAL_HPP

#include "ifb-graphics.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBGraphicsContext;

struct IFBGraphicsMemory;
struct IFBGraphicsMemoryOffsets;

struct IFBGraphicsWindow;
struct IFBGraphicsWindowList;

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

struct IFBGraphicsMemoryOffsets {
    IFBU32 window_list_active;
    IFBU32 window_list_inactive;
};

struct IFBGraphicsMemory {
    IFBHNDLinearAllocator  linear_arena_handle;
    IFBGraphicsMemoryOffsets offsets;
};

namespace ifb_graphics {

    const IFBHNDLinearAllocator
    memory_get_linear_arena(IFBVoid);

    IFBGraphicsWindow*     memory_commit_window            (IFBVoid);
    const IFBB8            memory_commit_window_lists      (IFBVoid);

    IFBGraphicsWindow*     memory_get_window               (const IFBHNDGraphicsWindow window_handle);
    IFBGraphicsWindowList* memory_get_window_list_active   (IFBVoid);
    IFBGraphicsWindowList* memory_get_window_list_inactive (IFBVoid);

};

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

struct IFBGraphicsWindow {
    IFBGraphicsWindow*      next;
    IFBHNDGraphicsWindow    handle;
    IFBDimensions           dimensions;
    IFBPosition             position;
};

struct IFBGraphicsWindowList {
    IFBGraphicsWindow* first;
    IFBGraphicsWindow* last;
    IFBU32             count;
};

/**********************************************************************************/
/* CONTEXT                                                                        */
/**********************************************************************************/


struct IFBGraphicsContext {
    IFBGraphicsMemory memory;
    IFBPlatformApi*   ptr_platform_api;
    IFBColorFormat    color_format;
};

namespace ifb_graphics {
    
    IFBGraphicsMemory&    context_get_memory       (IFBVoid);
    const IFBPlatformApi* context_get_platform_api (IFBVoid);
    const IFBColorFormat  context_get_color_format (IFBVoid);
};

#endif //IFB_GRAPHICS_INTERNAL_HPP