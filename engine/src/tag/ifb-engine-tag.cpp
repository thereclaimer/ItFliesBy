#pragma once

#include "ifb-engine-internal-controllers.hpp"
#include "ifb-engine-internal.hpp"

ifb_api const IFBEngineTagId
ifb_engine::tag_create(
    const ifb_cstr tag_value) {
    
    //get core reference
    IFBEngineCore* engine_core = ifb_engine::context_core();

    //insert the value
    const IFBEngineTagId tag_id = ifb_engine::controller_tag_create(
        engine_core,
        tag_value);

    //we're done
    return(tag_id);
}

ifb_api const ifb_b8
ifb_engine::tag_destroy(
    const IFBEngineTagId tag_id) {

    //get core reference
    IFBEngineCore* engine_core = ifb_engine::context_core();

    //do the delete
    const ifb_b8 result = ifb_engine::controller_tag_destroy(
        engine_core,
        tag_id);

    //we're done
    return(result);
}

ifb_api const ifb_cstr
ifb_engine::tag_value(
    const IFBEngineTagId tag_id) {

    //get core reference
    IFBEngineCore* engine_core = ifb_engine::context_core();

    //get the value
    const ifb_cstr tag_value = ifb_engine::controller_tag_cstr_value(
        engine_core,
        tag_id);

    //we're done
    return(tag_value);
}