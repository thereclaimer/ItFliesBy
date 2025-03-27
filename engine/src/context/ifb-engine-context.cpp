#pragma once

#include "ifb-engine.hpp"

#include "ifb-engine-context-internal.cpp"

/**********************************************************************************/
/* CREATE / DESTROY                                                               */
/**********************************************************************************/

// create/destroy
ifb_engine_api const IFBENG64Context
ifb_engine::context_create(
    IFBEngineContextArgs* args) {

    IFBENG64Context context;
    context.h64 = 0;

    return(context);
}

ifb_engine_api const IFBB8
ifb_engine::context_destroy(
    IFBVoid) {

    return(false);
}

/**********************************************************************************/
/* STARTUP / SHUTDOWN                                                             */
/**********************************************************************************/

ifb_engine_api const IFBB8
ifb_engine::context_startup(
    IFBVoid) {

    return(false);
}

ifb_engine_api const IFBB8
ifb_engine::context_shutdown(
    IFBVoid) {

    return(false);
}

/**********************************************************************************/
/* RENDERING                                                                      */
/**********************************************************************************/

ifb_engine_api const IFBB8
ifb_engine::context_render_frame(
    IFBVoid) {

    return(false);
}