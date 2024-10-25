#pragma once

#include "ifb-engine-internal-asset.hpp"

ifb_internal const r_b8
ifb_engine::asset_manager_start_up(
    IFBEngineCoreMemory     in_engine_core_memory_ref,
    IFBEngineAssetManager& out_asset_manager_ref) {

    ifb_b8 result = true;

    //create the file table
    result &= ifb_engine::asset_file_create_table(
        in_engine_core_memory_ref,
        out_asset_manager_ref.asset_tables.file);

    //create the header table
    result &= ifb_engine::asset_header_create_table(
        in_engine_core_memory_ref,
        out_asset_manager_ref.asset_tables.header);

    return(result);
}