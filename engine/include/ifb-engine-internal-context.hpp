#ifndef IFB_ENGINE_INTERNAL_CONTEXT_HPP
#define IFB_ENGINE_INTERNAL_CONTEXT_HPP

#include <ifb-memory.hpp>

#include "ifb-engine.hpp"
#include "ifb-engine-internal-core.hpp"

/**********************************************************************************/
/* SINGLETONS                                                                     */
/**********************************************************************************/

struct IFBEngineContextSingletons {
    IFBEngineSingletonHandle config;
};

namespace ifb_engine {

    const IFBEngineConfig* context_singletons_load_config (ifb_void);

};

/**********************************************************************************/
/* CONTEXT                                                                        */
/**********************************************************************************/

struct IFBEngineContext {
    IFBEngineCore*              core_ptr;
    IFBEngineContextSingletons* singletons_ptr;
};

namespace ifb_engine {
    
    IFBEngineCore*              context_get_core       (ifb_void); 
    IFBEngineContextSingletons* context_get_singletons (ifb_void);
};

#endif //IFB_ENGINE_INTERNAL_CONTEXT_HPP