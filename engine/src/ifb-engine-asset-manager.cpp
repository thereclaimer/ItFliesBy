#pragma once

#include "ifb-engine-internal-asset.hpp"

ifb_internal const r_b8
ifb_engine::asset_manager_create(
    const ifb_size                in_asset_data_arena_size,
          IFBEngineAssetManager& out_asset_manager_ref) {

    ifb_b8 result = true;

    result &= ifb_engine::asset_file_table_create(out_asset_manager_ref.tables.file);

    return(result);
}