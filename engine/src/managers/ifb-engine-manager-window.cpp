#pragma once

#include "ifb-engine-internal-managers.hpp"
#include "ifb-engine-internal-platform.hpp"

inline ifb_void 
ifb_engine::window_manger_initialize(
    IFBEngineWindowManager*  window_manager_ptr,
    IFBEngineMemory*         memory_ptr) {

    *window_manager_ptr = {0};
}

inline ifb_void 
ifb_engine::window_manager_create_window(
          IFBEngineWindowManager* window_manager_ptr,
    const ifb_cstr                window_title,
    const ifb_b8                  use_opengl,
    const ifb_b8                  use_imgui) {

    ifb_b8 result = true;

    //window dimensions
    const ifb_u32 window_width      = 800;
    const ifb_u32 window_height     = 600;
    const ifb_u32 window_position_x = 0;
    const ifb_u32 window_position_y = 0;

    //create window    
    result &= ifb_engine::platform_window_create(
        window_title,
        window_width,
        window_height,
        window_position_x,
        window_position_y);

    //initialize other systems
    if (use_opengl) {
        result &= ifb_engine::platform_window_opengl_init();
    }
    if (use_imgui) {
        result &= ifb_engine::platform_window_imgui_init();
    }

    //sanity check
    ifb_macro_assert(result);
}

inline ifb_void
ifb_engine::window_manager_set_visibility(
          IFBEngineWindowManager* window_manager_ptr,
    const ifb_b8                  visible) {

    if (visible) {
        ifb_engine::platform_window_show();    
    } 
    else {
        //TODO: add a way to hide the window
        ifb_macro_panic();
    }

    window_manager_ptr->window_visible = visible;
}

inline ifb_void
ifb_engine::window_manager_frame_start(
    IFBEngineWindowManager* window_manager_ptr) {

    const ifb_b8 result = ifb_engine::platform_window_frame_start();
    ifb_macro_assert(result);
}

inline ifb_void
ifb_engine::window_manager_frame_render(
    IFBEngineWindowManager* window_manager_ptr) {

    const ifb_b8 result = ifb_engine::platform_window_frame_render();
    ifb_macro_assert(result);
}