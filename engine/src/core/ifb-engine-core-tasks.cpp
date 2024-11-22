#pragma once

#include "ifb-engine-internal-core.hpp"
#include "ifb-engine-internal-platform.hpp"
#include "ifb-engine-internal-tables.hpp"

inline const ifb_b8 
ifb_engine::core_task_create_core_handle(
    ifb_handle_memory& engine_core_handle_ref) {

    //get page
    const ifb_u32 core_size       = ifb_macro_align_size_struct(IFBEngineCore);
    const ifb_u32 core_page_count = ifb_engine::memory_page_count(core_size);
    const ifb_u32 core_page_start = ifb_engine::memory_page_commit(core_page_count);
    
    //get handle
    engine_core_handle_ref = ifb_engine::memory_handle(core_page_start,0);

    //sanity check
    const ifb_b8 result = ifb_engine::memory_handle_valid(engine_core_handle_ref);

    //update the context
    _engine_context->core_handle = engine_core_handle_ref;

    //we're done
    return(result);
}

inline const ifb_b8 
ifb_engine::core_task_create_managers(
    IFBEngineCoreManagers& engine_core_managers_ref) {

    //create the managers
    engine_core_managers_ref.memory     = ifb_engine::memory_manager_startup();
    engine_core_managers_ref.tables     = ifb_engine::table_manager_create();

    //sanity check
    ifb_b8 result = true;
    result &= ifb_engine::memory_handle_valid(engine_core_managers_ref.memory);
    result &= ifb_engine::memory_handle_valid(engine_core_managers_ref.tables);

    //we're done
    return(result);
}

inline const ifb_b8 
ifb_engine::core_task_create_stack_allocators(
    IFBEngineCoreStackAllocators& engine_core_stack_allocators_ref) {

    //create the stack allocators
    ifb_b8 result = true;
    result &= ifb_engine::stack_allocator_create(IFB_ENGINE_CORE_STACK_ALLOCATOR_TAG_FRAME,   IFB_ENGINE_CORE_STACK_SIZE, engine_core_stack_allocators_ref.frame);
    result &= ifb_engine::stack_allocator_create(IFB_ENGINE_CORE_STACK_ALLOCATOR_TAG_PLATFORM,IFB_ENGINE_CORE_STACK_SIZE, engine_core_stack_allocators_ref.platform);
    result &= ifb_engine::stack_allocator_create(IFB_ENGINE_CORE_STACK_ALLOCATOR_TAG_WINDOW,  IFB_ENGINE_CORE_STACK_SIZE, engine_core_stack_allocators_ref.window);

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