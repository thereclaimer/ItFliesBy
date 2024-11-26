#pragma once

#include "ifb-engine-internal-core.hpp"
#include "ifb-engine-internal-platform.hpp"
#include "ifb-engine-internal-tables.hpp"

inline const ifb_b8 
ifb_engine::core_task_create_core_handle(
    IFBEngineMemoryHandle& engine_core_handle_ref) {
    
    //calculate size
    const ifb_u32 core_size = ifb_macro_align_size_struct(IFBEngineCore);

    //commit memory
    const IFBEngineMemoryCommit memory_commit = ifb_engine::memory_commit(core_size);

    //get handle
    engine_core_handle_ref = memory_commit.handle;

    //we're done
    return(true);
}

inline const ifb_b8 
ifb_engine::core_task_create_managers(
    IFBEngineCoreManagers& engine_core_managers_ref) {


    //we're done
    return(true);
}

inline const ifb_b8 
ifb_engine::core_task_create_allocators(
    IFBEngineCoreAllocators& core_allocators_ref) {

    //create the stack allocators
    ifb_b8 result = true;

    result &= ifb_engine::linear_allocator_create(IFB_ENGINE_CORE_LINEAR_ALLOCATOR_TAG_FRAME,   IFB_ENGINE_CORE_LINEAR_ALLOCATOR_SIZE, core_allocators_ref.linear_allocators.frame);
    result &= ifb_engine::linear_allocator_create(IFB_ENGINE_CORE_LINEAR_ALLOCATOR_TAG_PLATFORM,IFB_ENGINE_CORE_LINEAR_ALLOCATOR_SIZE, core_allocators_ref.linear_allocators.platform);

    //we're done
    return(result);
}

inline const ifb_b8 
ifb_engine::core_task_create_and_show_window(
    ifb_void) {

    ifb_b8 result = true;

    //get default dimensions
    IFBDimensions window_dimensions;
    ifb_engine::platform_window_default_dimensions(window_dimensions);

    //create the window
    result &= ifb_engine::platform_window_create(
        "It Flies By",
        window_dimensions.width,
        window_dimensions.height,
        window_dimensions.position_x,
        window_dimensions.position_y);

    //create other contexts
    result &= ifb_engine::platform_window_opengl_init();

    //show the window    
    result &= ifb_engine::platform_window_show();

    return(result);
}

inline const ifb_b8
ifb_engine::core_task_window_frame_start(
    ifb_void) {

    ifb_b8 result = true;

    result &= ifb_engine::platform_window_frame_start();

    return(result);
}

inline const ifb_b8
ifb_engine::core_task_window_frame_render(
    ifb_void) {

    ifb_b8 result = true;

    result &= ifb_engine::platform_window_frame_render();
    
    return(result);
}