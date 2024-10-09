#pragma once

#include "ifb-engine-internal-asset.hpp"

ifb_internal const r_b8
ifb_engine::asset_manager_create(
    const ifb_size                in_asset_data_arena_size,
    const ifb_size                in_asset_data_arena_count,
          IFBEngineAssetManager& out_asset_manager_ref) {

    ifb_b8 result = true;

    //file table
    result &= ifb_engine::asset_file_table_create(out_asset_manager_ref.tables.file);
    
    //index table
    result &= ifb_engine::asset_table_create(out_asset_manager_ref.tables.asset);

    //data table
    result &= ifb_engine::asset_data_table_create(
        in_asset_data_arena_size,
        in_asset_data_arena_count,
        out_asset_manager_ref.tables.data);

    return(result);
}