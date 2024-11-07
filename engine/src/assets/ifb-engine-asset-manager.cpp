#pragma once

#include "ifb-engine-internal-asset.hpp"

ifb_internal const r_b8
ifb_engine::asset_manager_start_up(
    IFBEngineCoreMemory&    in_core_memory_ref,
    IFBEngineAssetManager& out_asset_manager_ref) {

    ifb_b8 result = true;

    //reserve memory
    result &= ifb_engine::asset_memory_reserve(in_core_memory_ref,out_asset_manager_ref.memory);

    //create the tables
    result &= ifb_engine::asset_file_table_create      (out_asset_manager_ref.memory,out_asset_manager_ref.asset_tables.file);
    result &= ifb_engine::asset_header_table_create    (out_asset_manager_ref.memory,out_asset_manager_ref.asset_tables.header);
    result &= ifb_engine::asset_data_block_table_create(out_asset_manager_ref.memory,out_asset_manager_ref.asset_tables.data_block);

    return(result);
}