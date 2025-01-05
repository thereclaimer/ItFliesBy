#pragma once

#include "ifb-engine-internal-data.hpp"

inline ifb_void
ifb_engine::data_store_initialize(
    IFBEngineDataStore* data_store_ptr,
    IFBEngineMemory*    engine_memory_ptr,
    IFBEngineConfig*    engine_config_ptr) {

}

inline ifb_void
ifb_engine::data_store_commit_memory(
    IFBEngineDataStore* data_store_ptr,
    IFBEngineDataQuery* data_query_ptr) {

}


inline ifb_void
ifb_engine::data_store_execute_query(
    IFBEngineDataStore* data_store_ptr,
    IFBEngineDataQuery* data_query_ptr) {

    if (data_query_ptr->request.property_flags.tag != IFBEngineDataPropertiesTag_None) {

        data_query_ptr->result.property_array[data_query_ptr->result.property_count] = data_query_ptr->request.property_flags.tag & XXX ? ifb_engine::data_memory_get_pointer() : NULL;
    }
    if (data_query_ptr->request.property_flags.arena != IFBEngineDataPropertiesArena_None) {

    }
    if (data_query_ptr->request.property_flags.graphics != IFBEngineDataPropertiesGraphics_None) {

    }
    if (data_query_ptr->request.property_flags.shader != IFBEngineDataPropertiesShader_None) {

    }
    if (data_query_ptr->request.property_flags.transform != IFBEngineDataPropertiesTransform_None) {

    }
    if (data_query_ptr->request.property_flags.sprite != IFBEngineDataPropertiesSprite_None) {

    }

}