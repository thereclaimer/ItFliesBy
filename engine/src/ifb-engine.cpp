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

        eng_asset_db_file_t* db_file = eng_asset_db_file_create();
        eng_asset_db_file_write_header_default (db_file);
        eng_asset_db_file_read_header          (db_file);


        return(is_init);
    }

};