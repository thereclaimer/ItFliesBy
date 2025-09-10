#pragma once

#include <ifb-engine-asset.hpp>
#include "ifb-win32.hpp"

int WINAPI
wWinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PWSTR     pCmdLine,
    int       nCmdShow) {

    ifb::eng_asset_name_str8_t names[] = {
        {"connor"},
        {"jig"},
        {"rosie"},
        {"liam"}
    };

    ifb::eng_asset_id_u128_t id[3];

    ifb::eng_asset_generate_id(3, names, id);


    return(S_OK);
}