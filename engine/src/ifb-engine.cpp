#pragma once

#include <sld-xml.hpp>

#include "ifb-engine.hpp"
#include "ifb-engine-asset-internal.hpp"
#include "ifb-engine-core-internal.hpp"
#include "ifb-engine-file-internal.hpp"
#include "ifb-engine-memory-internal.hpp"

#include "ifb-engine-asset-config.cpp"
#include "ifb-engine-asset-database-builder.cpp"
#include "ifb-engine-asset-database-file.cpp"
#include "ifb-engine-asset-database.cpp"
#include "ifb-engine-asset-manager.cpp"
#include "ifb-engine-asset.cpp"

#include "ifb-engine-core-id.cpp"
#include "ifb-engine-core-image.cpp"
#include "ifb-engine-core.cpp"

#include "ifb-engine-file-manager.cpp"
#include "ifb-engine-memory-manager.cpp"


namespace ifb {

    IFB_ENG_API bool
    eng_init(void) {

        bool is_init = true;

        eng_mem_mngr_init  ();
        eng_file_mngr_init ();
        eng_core_init      ();

        eng_byte      buffer_data[1024];
        eng_buffer_t  xml_buffer;
        xml_buffer.data   = buffer_data;
        xml_buffer.size   = 1024;
        xml_buffer.length = 0;

        eng_asset_config_t* asset_config = eng_asset_config_create();
        eng_asset_config_load_default (asset_config);
        eng_asset_config_save_file    (asset_config);
        eng_asset_config_destroy      (asset_config);

        return(is_init);
    }

};