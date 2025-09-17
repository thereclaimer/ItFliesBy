#pragma once

#include "ifb-engine-asset-internal.hpp"

namespace ifb {

    static eng_asset_db_file_t _db_file;

    IFB_ENG_INTERNAL void
    eng_asset_db_file_open_and_read(
        void) {

        eng_mem_arena_t* arena_tmp = eng_mem_mngr_arena_commit_asset();
        
        _db_file.header.handle = eng_file_mngr_open_ro(_db_file_path);

    }
};