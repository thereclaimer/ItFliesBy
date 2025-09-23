#pragma once

#include <ifb-engine.hpp>
#include <ifb-engine-asset.hpp>

#include "ifb-win32.hpp"

int WINAPI
wWinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PWSTR     pCmdLine,
    int       nCmdShow) {

    ifb::eng_init();
    return(S_OK);
}