#pragma once

#include "ifb-win32.hpp"

/**********************************************************************************/
/* WIN32 MAIN                                                                     */
/**********************************************************************************/

int WINAPI 
wWinMain(
    HINSTANCE h_instance,
    HINSTANCE h_prev_instance,
    PWSTR     p_cmd_line,
    int       n_cmd_show) {

    IFBB8 result = true;

    //set the args
    IFBWin32Args win32_args;
    win32_args.h_instance      = h_instance;
    win32_args.h_prev_instance = h_prev_instance;
    win32_args.p_cmd_line      = p_cmd_line;
    win32_args.n_cmd_show      = n_cmd_show;

    //initialize the platform api
    IFBPlatformApi platform_api;
    ifb_win32::platform_api_initialize(platform_api);

    //create the context
    result &= ifb_win32::context_create(
        platform_api,       
        win32_args);

    //main loop
    result &= ifb_win32::context_main_loop();

    //destroy the context
    result &= ifb_win32::context_destroy();

    //done
    return(result ? S_OK : S_FALSE);
}
