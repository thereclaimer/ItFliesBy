#pragma once

#include "ifb-engine-internal-context.hpp"

inline ifb_void                
ifb_engine::context_managers_create_all(
          IFBEngineContextManagers* managers_ptr,
          IFBEngineMemory*          memory_ptr,
    const IFBEngineConfig*          config_ptr) {

    //allocate manager structures
    ifb_engine_macro_memory_global_push_struct(memory_ptr, managers_ptr->handles.tag,      IFBEngineManagerTag);
    ifb_engine_macro_memory_global_push_struct(memory_ptr, managers_ptr->handles.arena,    IFBEngineManagerArena);
    ifb_engine_macro_memory_global_push_struct(memory_ptr, managers_ptr->handles.graphics, IFBEngineManagerGraphics);

    //get the pointers
    IFBEngineManagerTag*      tag_manager_ptr      = ifb_engine::context_managers_get_tag_manager(managers_ptr);
    IFBEngineManagerArena*    arena_manager_ptr    = ifb_engine::context_managers_get_arena_manager(managers_ptr);
    IFBEngineManagerGraphics* graphics_manager_ptr = ifb_engine::context_managers_get_graphics_manager(managers_ptr);

    //tag manager    
    ifb_engine::tag_manager_initialize(
        tag_manager_ptr,
        memory_ptr,
        config_ptr->tag_c_str_length,
        config_ptr->tag_count_max);

    //arena manager
    ifb_engine::arena_manager_initialize(
        arena_manager_ptr,
        memory_ptr,
        config_ptr->arena_minimum_kb,
        config_ptr->arena_count_max);

    //graphics manager
    ifb_engine::graphics_manger_initialize(
        graphics_manager_ptr,
        memory_ptr);
}

inline IFBEngineManagerTag*    
ifb_engine::context_managers_get_tag_manager(
    const IFBEngineContextManagers* managers_ptr) {
    
    IFBEngineManagerTag* tag_manager_ptr = (IFBEngineManagerTag*)ifb_engine::context_get_pointer(
        managers_ptr->handles.tag);

    return(tag_manager_ptr);
}

inline IFBEngineManagerArena*  
ifb_engine::context_managers_get_arena_manager(
    const IFBEngineContextManagers* managers_ptr) {
    
    IFBEngineManagerArena* arena_manager_ptr = (IFBEngineManagerArena*)ifb_engine::context_get_pointer(
        managers_ptr->handles.arena);

    return(arena_manager_ptr);  
}

inline IFBEngineManagerGraphics* 
ifb_engine::context_managers_get_graphics_manager(
    const IFBEngineContextManagers* managers_ptr) {

    IFBEngineManagerGraphics* graphics_manager_ptr = (IFBEngineManagerGraphics*)ifb_engine::context_get_pointer(
        managers_ptr->handles.graphics);

    return(graphics_manager_ptr);
}