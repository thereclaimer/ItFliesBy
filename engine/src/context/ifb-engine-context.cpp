#pragma once

#include <ifb.hpp>
#include "ifb-engine-internal-context.hpp"

#include "ifb-engine-context-singletons.cpp"
#include "ifb-engine-context-platform.cpp"
#include "ifb-engine-context-config.cpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

ifb_global IFBEngineContext _context;

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline IFBEngineContext&
ifb_engine::context_ref(
    IFBVoid) {

    return(_context);
}

inline IFBEngineCore*
ifb_engine::context_get_ptr_core(
    IFBVoid) {

    IFBEngineCore* ptr_core = _context.ptr_core;
    ifb_macro_assert(ptr_core);

    return(ptr_core);
}

inline IFBEngineSingletons* 
ifb_engine::context_get_ptr_singletons(
    IFBVoid) {

    IFBEngineSingletons* ptr_singletons = _context.ptr_singletons;
    ifb_macro_assert(ptr_singletons);

    return(ptr_singletons);
}