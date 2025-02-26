#pragma once

#include "ifb-engine-internal-graphics.hpp"

inline const IFBB8 
ifb_engine::graphics_window_initialize(
    IFBEngineGraphicsManager* ptr_graphics_manager) {

    IFBWindow* window_ptr = ifb_engine::graphics_memory_load_window(ptr_graphics_manager->ptr_memory);

    const IFBU32   size_title       = ifb_macro_array_size(IFBChar, 255); 
    const IFBChar* title_str        = "It Flies By (DEBUG)"; 
}

inline const IFBB8
ifb_engine::graphics_window_get_dimensions(
    IFBEngineGraphicsManager* ptr_graphics_manager,
    IFBDimensions*            ptr_window_dimensions) {

    //sanity check
    ifb_macro_assert(ptr_graphics_manager);
    ifb_macro_assert(ptr_window_dimensions);

    return(true);
}

inline const IFBB8
ifb_engine::graphics_window_get_position(
    IFBEngineGraphicsManager* ptr_graphics_manager,
    IFBPosition*              ptr_window_position) {

}
