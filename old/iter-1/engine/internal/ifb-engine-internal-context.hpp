#ifndef IFB_ENGINE_INTERNAL_CONTEXT_HPP
#define IFB_ENGINE_INTERNAL_CONTEXT_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-platform.hpp"
#include "ifb-engine-internal-devtools.hpp"
#include "ifb-engine-internal-data.hpp"

/**********************************************************************************/
/* CONTEXT CORE                                                                   */
/**********************************************************************************/

struct IFBEngineContextCore {
    IFBEngineState   state;
    ifb_timems       time_initialized;
    ifb_u32          frames_per_second_target;
};

/**********************************************************************************/
/* CONTEXT                                                                        */
/**********************************************************************************/

struct IFBGHNDEngineContextCore : IFBGHND { }; 
struct IFBGHNDEngineDevTools    : IFBGHND { };
struct IFBGHNDEngineDataStore   : IFBGHND { };

struct IFBEngineContext {
    IFBEngineMemory memory;
    struct {
        IFBGHNDEngineDataStore   data_store;
        IFBGHNDEngineContextCore core;
        IFBGHNDEngineDevTools    devtools;
    } handles;
    IFBEngineConfig config;
};

namespace ifb_engine {

    ifb_global IFBEngineContext _context;

    IFBEngineContext& context() { return(_context); }

    IFBEngineMemory*          context_get_memory     (ifb_void);
    IFBEngineDataStore*       context_get_data_store (ifb_void);
    IFBEngineContextCore*     context_get_core       (ifb_void);
    IFBEngineConfig*          context_get_config     (ifb_void);
    IFBEngineDevTools*        context_get_devtools   (ifb_void);

    const ifb_ptr context_get_pointer (const IFBHND&  handle);
    const ifb_ptr context_get_pointer (const IFBGHND& global_handle);

    ifb_void context_process_input(IFBInput& input_ref);
};

#endif //IFB_ENGINE_INTERNAL_CONTEXT_HPP