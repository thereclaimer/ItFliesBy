#pragma once

#include "ifb-engine-asset-internal.hpp"

namespace ifb {

    IFB_ENG_FUNC void
    eng_asset_mngr_startup(
        void) {

        eng_asset_db_create();
        eng_asset_db_file_create();
        eng_asset_config_create();
    }

    IFB_ENG_FUNC void
    eng_asset_mngr_shutdown(
        void) {

        eng_asset_db_destroy();
        eng_asset_db_file_destroy();
        eng_asset_config_destroy();

    }
};