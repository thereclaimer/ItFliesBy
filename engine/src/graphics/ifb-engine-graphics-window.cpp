#pragma once

#include "ifb-engine-internal-graphics.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

#define IFB_ENGINE_GRAPHICS_WINDOW_TITLE            "It Flies By (Debug)"
#define IFB_ENGINE_GRAPHICS_WINDOW_TITLE_MAX_LENGTH 32
#define IFB_ENGINE_GRAPHICS_WINDOW_INITIAL_WIDTH    1920
#define IFB_ENGINE_GRAPHICS_WINDOW_INITIAL_HEIGHT   1080

namespace ifb_engine {

    const IFBB8 graphics_window_initialize(IFBEngineGraphics* ptr_graphics);
};

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

inline const IFBB8 
ifb_engine::graphics_window_frame_start(
    const IFBEngineGraphics* ptr_graphics) {

    ifb_macro_assert(ptr_graphics);

    //load the window
    IFBWindow* ptr_window = ifb_engine::graphics_load_pointer_to_window(ptr_graphics);
    
    //start a new frame
    IFBB8 result = true; 
    result &= ifb_graphics::window_show        (ptr_window);
    result &= ifb_graphics::window_frame_start (ptr_window);

    //we're done
    return(result);
}

inline const IFBB8 
ifb_engine::graphics_window_frame_render(
    const IFBEngineGraphics* ptr_graphics) {

    ifb_macro_assert(ptr_graphics);
    
    //load the window
    IFBWindow* ptr_window = ifb_engine::graphics_load_pointer_to_window(ptr_graphics);
    
    //render the frame
    IFBB8 result = true;
    result &= ifb_graphics::window_show         (ptr_window);
    result &= ifb_graphics::window_frame_render (ptr_window);

    //we're done
    return(result);
}

inline const IFBB8 
ifb_engine::graphics_window_get_dimensions(
    const IFBEngineGraphics* ptr_graphics,
          IFBDimensions*     ptr_dimensions) {

    //sanity check
    ifb_macro_assert(ptr_graphics);
    if (!ptr_dimensions) return(false);

    //load the window dimensions
    const IFBWindow*     ptr_window     = ifb_engine::graphics_load_pointer_to_window(ptr_graphics);
    const IFBDimensions& ref_dimensions = ptr_window->dimensions;

    //the dimensions should never be zero
    IFBB8 result = true;
    result &= (ref_dimensions.width  != 0);
    result &= (ref_dimensions.height != 0);

    //set the values
    ptr_dimensions->width  = ref_dimensions.width;
    ptr_dimensions->height = ref_dimensions.height;

    //we're done
    return(result);
}

inline const IFBB8 
ifb_engine::graphics_window_get_position(
    const IFBEngineGraphics* ptr_graphics,
          IFBPosition*       ptr_position) {

    //sanity check
    ifb_macro_assert(ptr_graphics);
    if (!ptr_position) return(false);
    
    //load the window position
    const IFBWindow*   ptr_window   = ifb_engine::graphics_load_pointer_to_window(ptr_graphics);
    const IFBPosition& ref_position = ptr_window->position;

    //set the values
    ptr_position->x = ref_position.x;
    ptr_position->y = ref_position.y;

    //we're done
    return(true);
}

inline const IFBB8 
ifb_engine::graphics_window_update_dimensions(
    const IFBEngineGraphics* ptr_graphics,
    const IFBDimensions*     ptr_dimensions) {

    //sanity check
    ifb_macro_assert(ptr_graphics);
    if (!ptr_dimensions) return(false);

    //the dimensions should not be zero
    IFBB8 result = true;
    result &= (ptr_dimensions->width  != 0);
    result &= (ptr_dimensions->height != 0);
    if (!result) return(false);

    //load the window
    IFBWindow* ptr_window = ifb_engine::graphics_load_pointer_to_window(ptr_graphics);

    //update the dimensions
    ptr_window->dimensions.width  = ptr_dimensions->width;
    ptr_window->dimensions.height = ptr_dimensions->height;

    //we're done
    return(true);
}

inline const IFBB8 
ifb_engine::graphics_window_update_position(
    const IFBEngineGraphics* ptr_graphics,
    const IFBPosition*       ptr_position) {

    //sanity check
    ifb_macro_assert(ptr_graphics);
    if (!ptr_position) return(false);

    //load the window
    IFBWindow* ptr_window = ifb_engine::graphics_load_pointer_to_window(ptr_graphics);

    //update the position
    ptr_window->position.x = ptr_position->x;
    ptr_window->position.y = ptr_position->y;

    //we're done
    return(true);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline const IFBB8
ifb_engine::graphics_window_initialize(
    IFBEngineGraphics* ptr_graphics) {

    IFBB8 result = true;
    
    //sanity check
    ifb_macro_assert(ptr_graphics);

    //load the pointers
    IFBWindow*  ptr_window  = ifb_engine::graphics_load_pointer_to_window          (ptr_graphics);
    IFBMonitor* ptr_monitor = ifb_engine::graphics_load_pointer_to_monitor_primary (ptr_graphics);    

    //cache window properties
    IFBDimensions& ref_window_dimensions = ptr_window->dimensions;
    IFBPosition&   ref_window_position   = ptr_window->position;

    //default window properties
    const IFBU32   window_width            = IFB_ENGINE_GRAPHICS_WINDOW_INITIAL_WIDTH;
    const IFBU32   window_height           = IFB_ENGINE_GRAPHICS_WINDOW_INITIAL_HEIGHT;
    const IFBU32   window_title_max_length = IFB_ENGINE_GRAPHICS_WINDOW_TITLE_MAX_LENGTH; 
    const IFBChar* window_title_cstr       = IFB_ENGINE_GRAPHICS_WINDOW_TITLE;

    //initial dimensions
    ref_window_dimensions.width  = window_width;
    ref_window_dimensions.height = window_height;
    
    //get the center of the monitor
    result &= ifb_graphics::monitor_get_center(ptr_monitor,&ref_window_position);

    //position the window in the center of the monitor
    const IFBU32 offset_x  = ref_window_dimensions.width  / 2;
    const IFBU32 offset_y  = ref_window_dimensions.height / 2;
    ref_window_position.x -= offset_x;
    ref_window_position.y -= offset_y;

    //commit the window title
    ptr_window->title = (IFBChar*)ifb_memory::arena_commit_string(
        ptr_graphics->arena,
        window_title_cstr,
        window_title_max_length);
    result &= (ptr_window->title != NULL);

    //create  the window
    result &= ifb_graphics::window_context_gl_create (ptr_window);

    //we're done
    return(result);
}