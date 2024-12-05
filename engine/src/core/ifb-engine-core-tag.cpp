#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-internal-core.hpp"

inline const IFBTagId 
ifb_engine::core_tag_reserve(
    const IFBEngineCore* ptr_core,
    const ifb_cstr       tag_c_str) {

    //get the managers
    IFBEngineTagManager* ptr_tag_manager = ifb_engine::core_managers_get_pointer_tag_manager(ptr_core->manager_handles); 

    //reserve the tag
    const IFBTagId tag_id = ifb_engine::tag_manager_reserve_tag(
        ptr_tag_manager,
        tag_c_str);

    //we're done
    return(tag_id);
}

inline const IFBTagId 
ifb_engine::core_tag_release(
    const IFBEngineCore* ptr_core,
    const IFBTagId       tag_id) {

    //get the managers
    IFBEngineTagManager* ptr_tag_manager = ifb_engine::core_managers_get_pointer_tag_manager(ptr_core->manager_handles); 

    //release the tag
    ifb_engine::tag_manager_release_tag(
        ptr_tag_manager,
        tag_id);

    //we're done
    return(tag_id);
}

inline const ifb_cstr 
ifb_engine::core_tag_get_value(
    const IFBEngineCore* ptr_core,
    const IFBTagId       tag_id) {

    //get the managers
    IFBEngineTagManager* ptr_tag_manager = ifb_engine::core_managers_get_pointer_tag_manager(ptr_core->manager_handles); 

    //get the tag value
    const ifb_cstr tag_c_str = ifb_engine::tag_manager_get_tag_c_str(
        ptr_tag_manager,
        tag_id);

    //we're done
    return(tag_c_str);
}

inline const ifb_cstr 
ifb_engine::core_tag_get_hash(
    const IFBEngineCore* ptr_core,
    const IFBTagId       tag_id) {

    //get the managers
    IFBEngineTagManager* ptr_tag_manager = ifb_engine::core_managers_get_pointer_tag_manager(ptr_core->manager_handles); 

    //get the tag hash
    const IFBHash tag_hash = ifb_engine::tag_manager_get_hash(
        ptr_tag_manager,
        tag_id);

    //we're done
    return(tag_hash);
}