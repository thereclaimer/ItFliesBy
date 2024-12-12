#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-internal-context.hpp"

inline ifb_void 
ifb_engine::context_handles_create_all(
    ifb_void) {

    IFBEngineContextHandles& handles_ref = ifb_engine::context_get_handles();

    ifb_engine_context_push_struct(handles_ref.user_input,    IFBUserInput);
    ifb_engine_context_push_struct(handles_ref.memory,        IFBEngineMemory);
    ifb_engine_context_push_struct(handles_ref.tag_manager,   IFBEngineTagManager);
    ifb_engine_context_push_struct(handles_ref.arena_manager, IFBEngineArenaManager);
    ifb_engine_context_push_struct(handles_ref.config,        IFBEngineConfig);
}

inline IFBUserInput*
ifb_engine::context_get_user_input(
    ifb_void) {

    IFBUserInput* ptr_user_input = (IFBUserInput*)ifb_engine::context_stack_get_pointer(
        _engine_context.handles.user_input);

    return(ptr_user_input);
}

inline IFBEngineMemory*
ifb_engine::context_get_memory(
    ifb_void) {

    IFBEngineMemory* ptr_memory = (IFBEngineMemory*)ifb_engine::context_stack_get_pointer(
        _engine_context.handles.memory);

    return(ptr_memory);
}

inline IFBEngineTagManager*
ifb_engine::context_get_tag_manager(
    ifb_void) {

    IFBEngineTagManager* ptr_tag_manager = (IFBEngineTagManager*)ifb_engine::context_stack_get_pointer(
        _engine_context.handles.tag_manager);

    return(ptr_tag_manager);
}

inline IFBEngineArenaManager*
ifb_engine::context_get_arena_manager(
    ifb_void) {

    IFBEngineArenaManager* ptr_arena_manager = (IFBEngineArenaManager*)ifb_engine::context_stack_get_pointer(
        _engine_context.handles.arena_manager);

    return(ptr_arena_manager);
}

inline IFBEngineConfig*
ifb_engine::context_get_config(
    ifb_void) {

    IFBEngineConfig* ptr_config = (IFBEngineConfig*)ifb_engine::context_stack_get_pointer(
        _engine_context.handles.config);

    return(ptr_config);
}
