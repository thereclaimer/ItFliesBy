#pragma once

#include "ifb-engine-internal-core.hpp"
#include "ifb-engine-internal.hpp"

inline const ifb_b8 
ifb_engine::core_routine_initialize(
    ifb_void) {

    ifb_b8 result = true;

    //create the handle
    IFBEngineMemoryHandle core_memory_handle;
    result &= ifb_engine::core_task_create_core_handle(core_memory_handle);

    //get pointer
    IFBEngineCore* engine_core_ptr = (IFBEngineCore*)ifb_engine::memory_pointer_from_handle(core_memory_handle);

    //create the managers and allocators
    result &= ifb_engine::core_task_create_managers   (engine_core_ptr->managers);
    result &= ifb_engine::core_task_create_allocators (engine_core_ptr->allocators);

    //we're done
    return(result);
}

inline const ifb_b8 
ifb_engine::core_routine_startup(
    ifb_void) {

    ifb_b8 result = true;

    result &= ifb_engine::core_task_create_and_show_window();

    const ifb_f32 gray = (ifb_f32)0x28 / (ifb_f32)0xFF;

    glClearColor(gray,gray,gray,1.0f);

    return(result);
}

inline const ifb_b8
ifb_engine::core_routine_frame_start(
    ifb_void) {

    ifb_b8 result = true;

    result &= ifb_engine::core_task_window_frame_start();

    glClear(GL_COLOR_BUFFER_BIT);

    return(result);
}

inline const ifb_b8
ifb_engine::core_routine_frame_render(
    ifb_void) {

    ifb_b8 result = true;

    result &= ifb_engine::core_task_window_frame_render();

    return(result);
}