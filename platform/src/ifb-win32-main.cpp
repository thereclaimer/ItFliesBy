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

    const ifb::eng_file_h32_t test_file        = ifb::eng_file_mngr_open_rw("test.txt");
    const ifb::eng_c8         test_file_data[] = "TESTTESTTEST";

    ifb::eng_file_buffer_t* test_file_buffer = ifb::eng_file_mngr_get_buffer(test_file);
    test_file_buffer->length = sizeof(test_file_data);    
    test_file_buffer->offset = 0; 

    memmove_s(
        test_file_buffer->data,
        test_file_buffer->size,
        test_file_data,
        test_file_buffer->length
    );

    ifb::eng_file_mngr_write(test_file);

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