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

using namespace ifb;

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct engine_context_t;
struct engine_context_t;
struct engine_memory_t;

/**********************************************************************************/
/* HANDLES                                                                        */
/**********************************************************************************/

typedef engine_context_t* engine_context_h;

/**********************************************************************************/
/* CONTEXT                                                                        */
/**********************************************************************************/

struct engine_context_args_t {
    memory_t          global_stack_memory;
    platform::api_t * platform_api;
};

namespace ifb::engine {

    // create/destroy
    ifb_engine_api engine_context_h context_create    (const engine_context_args_t& args);
    ifb_engine_api const b8         context_destroy   (engine_context_h context_handle);
        
    // startup/shutdown
    ifb_engine_api const b8         context_startup   (engine_context_h context_handle);
    ifb_engine_api const b8         context_shutdown  (engine_context_h context_handle);

    // rendering
    ifb_engine_api const b8         context_main_loop (engine_context_h context_handle);
};

#endif //IFB_ENGINE_HPP