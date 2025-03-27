#ifndef IFB_ENGINE_HPP
#define IFB_ENGINE_HPP

#ifdef IFB_ENGINE_INTERNAL
    #define ifb_engine_api __declspec(dllexport)
#else
    #define ifb_engine_api __declspec(dllimport)
#endif

#include <ifb.hpp>
#include <ifb-memory.hpp>
#include <ifb-data-structures.hpp>
#include <ifb-graphics.hpp>
#include <ifb-rendering-gl.hpp>
#include <ifb-platform.hpp>

/**********************************************************************************/
/* HANDLES                                                                        */
/**********************************************************************************/

typedef IFBHND8  IFBENG8Handle;
typedef IFBHND16 IFBENG16Handle;
typedef IFBHND32 IFBENG32Handle;
typedef IFBHND64 IFBENG64Handle;

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBENG64Context : IFBENG64Handle { };

struct IFBEngineContextArgs;

/**********************************************************************************/
/* CONTEXT                                                                        */
/**********************************************************************************/

struct IFBEngineContextArgs {
    IFBMemory       global_stack;
    IFBPlatformAPI* platform_api;
};

namespace ifb_engine {

    // create/destroy
    ifb_engine_api const IFBENG64Context context_create       (const IFBEngineContextArgs& args);
    ifb_engine_api const IFBB8           context_destroy      (const IFBENG64Context context_handle);
        
    // startup/shutdown
    ifb_engine_api const IFBB8           context_startup      (const IFBENG64Context context_handle);
    ifb_engine_api const IFBB8           context_shutdown     (const IFBENG64Context context_handle);

    // rendering
    ifb_engine_api const IFBB8           context_render_frame (const IFBENG64Context context_handle);
};

#endif //IFB_ENGINE_HPP