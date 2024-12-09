#pragma once

#include "ifb-engine-internal-global.hpp"

namespace ifb_engine {

    ifb_global IFBEngineGlobals _globals;
};

inline ifb_void 
ifb_engine::globals_initialize(
    ifb_void) {

    _globals = {0};

    _globals.handles.context = ifb_engine_global_stack_push_type(IFBEngineContext);
    _globals.handles.memory  = ifb_engine_global_stack_push_type(IFBEngineMemory);

    ifb_engine::config_get_values(_globals.config);
}

inline IFBEngineGlobalStack& 
ifb_engine::global_stack_ref(
    ifb_void) {

    return(_globals.stack);
}

inline const IFBEngineConfig&
ifb_engine::global_config_ref(
    ifb_void) {

    return(_globals.config)
}

inline IFBEngineContext*     
ifb_engine::global_context_ptr(
    ifb_void) {

    return((IFBEngineContext*)ifb_engine::global_stack_pointer(_globals.handles.context));
}

inline IFBEngineMemory*
ifb_engine::global_memory_ptr(
    ifb_void) {
    
    return((IFBEngineMemory*)ifb_engine::global_stack_pointer(_globals.handles.memory));
}
