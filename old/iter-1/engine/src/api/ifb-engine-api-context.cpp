#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-internal-context.hpp"
#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal-devtools.hpp"

ifb_api const ifb_b8
ifb_engine::context_create(
    IFBPlatformApi& platform_api_ref) {

    //initialize the api
    ifb_engine::platform_initialize(platform_api_ref);

    //get the context
    IFBEngineContext& context_ref = ifb_engine::context();

    //get the config values
    ifb_engine::config_get_values(&context_ref.config);

    //reserve memory
    const ifb_u64 memory_reservation_size = ifb_macro_size_gigabytes(context_ref.config.memory_minimum_gb);
    const ifb_u32 memory_commit_count_max = context_ref.config.memory_commit_count_max;
    ifb_engine::memory_reserve(
        &context_ref.memory,
        memory_reservation_size,
        memory_commit_count_max);

    //allocate context structures
    ifb_engine_macro_memory_global_push_struct(&context_ref.memory, context_ref.handles.managers,   IFBEngineContextManagers);
    ifb_engine_macro_memory_global_push_struct(&context_ref.memory, context_ref.handles.core,       IFBEngineContextCore);
    ifb_engine_macro_memory_global_push_struct(&context_ref.memory, context_ref.handles.devtools,   IFBEngineDevTools);

    //create the managers
    IFBEngineContextManagers* managers_ptr = ifb_engine::context_get_managers();
    ifb_engine::context_managers_create_all(
        managers_ptr,
        &context_ref.memory,
        &context_ref.config);

    //we're done
    return(true);
}

ifb_api const ifb_b8 
ifb_engine::context_destroy(
    ifb_void) {

    //TODO
    ifb_macro_panic();
    return(true);
}

ifb_api const ifb_b8 
ifb_engine::context_startup(
    ifb_void) {

    IFBEngineContext& context_ref = ifb_engine::context();

    //get the pointers
    IFBEngineContextManagers* managers_ptr         = ifb_engine::context_get_managers();
    IFBEngineManagerGraphics* graphics_manager_ptr = ifb_engine::context_managers_get_graphics_manager(managers_ptr);

    //set the window flags
    const IFBWindowFlags window_flags = 
        IFBWindowFlags_Visible | 
        IFBWindowFlags_ImGui   | 
        IFBWindowFlags_OpenGL;

    //create the window
    ifb_engine::graphics_manager_create_window(
        graphics_manager_ptr,
        context_ref.config.window_title_cstr,
        window_flags);

    //create the viewport
    ifb_engine::graphics_manager_create_viewport(graphics_manager_ptr);

    //style imgui
    ifb_engine::graphics_manager_style_imgui(graphics_manager_ptr);

    //we're done
    return(true);
}

ifb_api const ifb_b8 
ifb_engine::context_update_and_render(
    IFBEngineUpdate& update) {

    //get the pointers
    IFBEngineContextManagers* managers_ptr         = ifb_engine::context_get_managers();
    IFBEngineManagerGraphics* graphics_manager_ptr = ifb_engine::context_managers_get_graphics_manager(managers_ptr);

    //start a new frame
    ifb_engine::graphics_manager_frame_start(graphics_manager_ptr);

    //devtools
    IFBEngineDevTools* devtools_ptr = ifb_engine::context_get_devtools();
    ifb_engine::devtools_render(devtools_ptr,update.input);

    //render the frame
    ifb_engine::graphics_manager_frame_render(graphics_manager_ptr);

    //determine if we should close
    ifb_b8 close = false;
    close |= ifb_engine::context_update_window_flags_get_close(update); 
    close |= ifb_engine::devtools_context_flags_get_exit(devtools_ptr->flags.context); 

    //we're done
    return(!close);
}
