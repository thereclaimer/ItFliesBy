#pragma once

#include "ifb-engine-internal-graphics.hpp"

inline const IFBB8 
ifb_engine::graphics_window_initialize(
    IFBEngineGraphicsManager* ptr_graphics_manager) {

    //get the window and arena
    IFBWindow* window_ptr = ifb_engine::graphics_memory_load_window(ptr_graphics_manager->ptr_memory);
    const IFBHNDArena arena_handle = ptr_graphics_manager->ptr_memory->arena;

    //title
    window_ptr->title = (IFBChar*)ifb_memory::arena_commit_string(arena_handle,"It Flies By (DEBUG)",32);
    if (!window_ptr->title) return(false);
    
    //initial dimensions
    IFBDimensions& dimensions_ref = window_ptr->dimensions;
    dimensions_ref.width  = 800;
    dimensions_ref.height = 600;

    //initial position
    IFBPosition& position_ref = window_ptr->position;
    position_ref.x = 0;
    position_ref.y = 0;

    //create the platform contexts and show the window
    IFBB8 result = true; 
    result &= ifb_graphics::window_context_gl_create (window_ptr);
    result &= ifb_graphics::window_show              (window_ptr);

    //we're done
    return(result);
}


inline IFBVoid
ifb_engine::graphics_window_get_dimensions(
    IFBEngineGraphicsManager* ptr_graphics_manager,
    IFBDimensions*            ptr_window_dimensions) {

    //sanity check
    ifb_macro_assert(ptr_graphics_manager);
    ifb_macro_assert(ptr_window_dimensions);

    //load the window
    IFBWindow* window_ptr = ifb_engine::graphics_memory_load_window(ptr_graphics_manager->ptr_memory);

    //set the dimensions
    ptr_window_dimensions->width  = window_ptr->dimensions.width;
    ptr_window_dimensions->height = window_ptr->dimensions.height;
}

inline IFBVoid
ifb_engine::graphics_window_get_position(
    IFBEngineGraphicsManager* ptr_graphics_manager,
    IFBPosition*              ptr_window_position) {
        
    //sanity check
    ifb_macro_assert(ptr_graphics_manager);
    ifb_macro_assert(ptr_window_position);

    //load the window
    IFBWindow* window_ptr = ifb_engine::graphics_memory_load_window(ptr_graphics_manager->ptr_memory);

    //set the dimensions
    ptr_window_position->x = window_ptr->position.x;
    ptr_window_position->y = window_ptr->position.y;
}


inline const IFBB8 
ifb_engine::graphics_window_frame_start(
    IFBEngineGraphicsManager* ptr_graphics_manager) {

    //load the window
    IFBWindow* window_ptr = ifb_engine::graphics_memory_load_window(ptr_graphics_manager->ptr_memory);

    //new frame start is successful IF...
    IFBB8 result = true; 
    result &= ifb_graphics::window_show        (window_ptr); // the window is visible AND
    result &= ifb_graphics::window_frame_start (window_ptr); // the window has started a new frame

    //we're done
    return(result);
}

inline const IFBB8 
ifb_engine::graphics_window_frame_render(
    IFBEngineGraphicsManager* ptr_graphics_manager) {

    //load the window
    IFBWindow* window_ptr = ifb_engine::graphics_memory_load_window(ptr_graphics_manager->ptr_memory);

    //frame render is successful IF...
    IFBB8 result = true; 
    result &= ifb_graphics::window_show         (window_ptr); // the window is visible AND
    result &= ifb_graphics::window_frame_render (window_ptr); // the window frame is rendered

    //we're done
    return(result);
}