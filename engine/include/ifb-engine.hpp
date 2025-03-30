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
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBEngineContext;
struct IFBEngineContextArgs;
struct IFBEngineMemory;

/**********************************************************************************/
/* HANDLES                                                                        */
/**********************************************************************************/

typedef IFBHND8  IFBENG8Handle;
typedef IFBHND16 IFBENG16Handle;
typedef IFBHND32 IFBENG32Handle;
typedef IFBHND64 IFBENG64Handle;

typedef IFBEngineContext* IFBENGContext;

/**********************************************************************************/
/* CONTEXT                                                                        */
/**********************************************************************************/

struct IFBEngineContextArgs {
    IFBMemory       global_stack_memory;
    IFBPlatformAPI* platform_api;
};

namespace ifb_engine {

    // create/destroy
    ifb_engine_api IFBENGContext context_create    (const IFBEngineContextArgs& args);
    ifb_engine_api const IFBB8   context_destroy   (const IFBENGContext context_handle);
        
    // startup/shutdown
    ifb_engine_api const IFBB8   context_startup   (const IFBENGContext context_handle);
    ifb_engine_api const IFBB8   context_shutdown  (const IFBENGContext context_handle);

    // rendering
    ifb_engine_api const IFBB8   context_main_loop (const IFBENGContext context_handle);
};

#endif //IFB_ENGINE_HPP