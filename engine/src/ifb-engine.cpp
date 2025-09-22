#pragma once

#include <sld-xml.hpp>

#include "ifb-engine.hpp"
#include "ifb-engine-asset-internal.hpp"
#include "ifb-engine-core-internal.hpp"
#include "ifb-engine-file-internal.hpp"
#include "ifb-engine-memory-internal.hpp"

#include "ifb-engine-file-manager.cpp"
#include "ifb-engine-memory-manager.cpp"

#include "ifb-engine-asset-config.cpp"
#include "ifb-engine-asset-database-builder.cpp"
#include "ifb-engine-asset-database-file.cpp"
#include "ifb-engine-asset-database.cpp"
#include "ifb-engine-asset-manager.cpp"
#include "ifb-engine-asset.cpp"

#include "ifb-engine-core-id.cpp"
#include "ifb-engine-core-image.cpp"
#include "ifb-engine-core.cpp"


namespace ifb {

    IFB_ENG_API bool
    eng_init(void) {

        bool is_init = true;

        eng_mem_mngr_init  ();
        eng_file_mngr_init ();
        eng_core_init      ();

        eng_asset_cstr_t asset_names[3] = {
            {"name1"},
            {"name2"},
            {"name3"}
        };
        eng_asset_cstr_t asset_paths[3] = {
            {"path1"},
            {"path2"},
            {"path3"}
        };

        eng_asset_config_assets_t assets;
        assets.count = 3;
        assets.array.name = asset_names;
        assets.array.path = asset_paths;

        eng_asset_config_t* config  = eng_asset_config_create();
        const bool did_write_config = eng_asset_config_node_write_image(config, assets);

        eng_asset_config_save_file(config);


        return(is_init);
    }

};