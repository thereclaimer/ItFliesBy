#ifndef IFB_ENGINE_INTERNAL_CONTEXT_HPP
#define IFB_ENGINE_INTERNAL_CONTEXT_HPP

#include <ifb-memory.hpp>

#include "ifb-engine.hpp"
#include "ifb-engine-internal-core.hpp"

/**********************************************************************************/
/* SINGLETONS                                                                     */
/**********************************************************************************/

struct IFBEngineContextSingletons {
    IFBEngineSingletonHandle context;
    IFBEngineSingletonHandle singletons;
    IFBEngineSingletonHandle config;
    IFBEngineSingletonHandle input;
};

namespace ifb_engine {

    const IFBEngineConfig* context_singletons_load_config (ifb_void);
};

/**********************************************************************************/
/* CONTEXT                                                                        */
/**********************************************************************************/

struct IFBEngineContext {
    IFBEngineCore*              ptr_core;
    IFBEngineContextSingletons* ptr_singletons;
};

namespace ifb_engine {
    
    IFBEngineCore*              context_get_core       (ifb_void); 
    IFBEngineContextSingletons* context_get_singletons (ifb_void);
};

#endif //IFB_ENGINE_INTERNAL_CONTEXT_HPP