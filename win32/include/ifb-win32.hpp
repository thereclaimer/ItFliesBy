#ifndef IFB_WIN32_HPP
#define IFB_WIN32_HPP

#include <Windows.h>
#include <ifb.hpp>
#include <ifb-engine.hpp>

/**********************************************************************************/
/* WIN32 CONTEXT                                                                  */
/**********************************************************************************/


struct IFBWin32Handles {
    IFBU32 args;
    IFBU32 window;
};

struct IFBWin32Memory {
    IFBHNDEngineArena arena_handle;
    IFBWin32Handles   win32_handles;
};

struct IFBWin32Context {
    IFBWin32Memory*         ptr_memory;
    IFBEngineContextUpdate* ptr_engine_update;
};

namespace ifb_win32 {

    const IFBB8
    context_create(
        const IFBPlatformAPI& platform_api_ref,
        const IFBWin32Args&   win32_args_ref);
        
    const IFBB8
    context_main_loop(IFBVoid);
    
    const IFBB8
    context_destroy(IFBVoid);

    IFBWin32Memory*         context_get_memory        (IFBVoid);
    IFBEngineContextUpdate* context_get_engine_update (IFBVoid);

    IFBWin32Window* context_get_window (IFBVoid);
};


#endif //IFB_WIN32_HPP