#pragma once

#include <ifb-engine.hpp>
#include <ifb-engine-core.hpp>

#include "ifb-win32.hpp"

int WINAPI
wWinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PWSTR     pCmdLine,
    int       nCmdShow) {

    bool is_running = ifb::eng_core_startup();

    while (is_running) {

        is_running &= ifb::eng_core_update();
        is_running &= ifb::eng_core_render();
        is_running &= !ifb::eng_core_should_quit();
    };

    return(S_OK);
}