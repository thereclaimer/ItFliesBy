#pragma once

#include <ifb-engine-asset.hpp>
#include "ifb-win32.hpp"

int WINAPI
wWinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PWSTR     pCmdLine,
    int       nCmdShow) {

    ifb::eng_init();
    const ifb::eng_file_h32_t test_file = ifb::eng_file_mngr_open_rw("test.txt");

    ifb::eng_asset_name_str8_t names[] = {
        { "connor" },
        { "jig"    },
        { "rosie"  },
        { "liam"   }
    };

    ifb::eng_asset_id_u128_t id[3];

    ifb::eng_asset_generate_id(3, names, id);

    const ifb::eng_id_u128_t test = ifb::eng_id_init(0,1,2,3);

    ifb::eng_asset_name_str8_t name_test = {"AbCd$eF G 01239  x"};
    
    ifb::eng_asset_name_sanitize(1, &name_test);

    return(S_OK);
}