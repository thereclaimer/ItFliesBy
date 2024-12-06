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

    ifb_engine::config_get_values(_globals.config);
}

inline IFBEngineGlobalStack& 
ifb_engine::globals_get_stack_reference(
    ifb_void) {

    return(_globals.stack);
}

inline const IFBEngineConfig&
ifb_engine::globals_get_config_reference(
    ifb_void) {

    return(_globals.config)
}

inline IFBEngineContext*     
ifb_engine::globals_get_context_pointer(
    ifb_void) {

    return((IFBEngineContext*)ifb_engine::global_stack_pointer(_globals.handles.context));
}