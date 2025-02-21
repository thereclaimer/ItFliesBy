#ifndef IFB_ENGINE_INTERNAL_CONTEXT_HPP
#define IFB_ENGINE_INTERNAL_CONTEXT_HPP

#include <ifb.hpp>
#include <ifb-memory.hpp>

#include "ifb-engine.hpp"
#include "ifb-engine-internal-core.hpp"
#include "ifb-engine-internal-devtools.hpp"
#include "ifb-engine-internal-graphics.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

//singletons
struct IFBEngineSingletons;
struct IFBEngineSingletonBuffer;
struct IFBEngineSingletonHandles;

//arenas
struct IFBEngineArenas;

//handles
struct IFBHNDSingleton : IFBHND16 { };

/**********************************************************************************/
/* ARENAS                                                                         */
/**********************************************************************************/

struct IFBEngineArenas {
    IFBHNDArena graphics_manager;
    IFBHNDArena renderer;
    IFBHNDArena dev_tools;
};

/**********************************************************************************/
/* SINGLETONS                                                                     */
/**********************************************************************************/

#define IFB_ENGINE_SINGLETON_STACK_SIZE 0xFFFF

struct IFBEngineSingletonBuffer {
    IFBByte memory[IFB_ENGINE_SINGLETON_STACK_SIZE];
};

struct IFBEngineSingletonHandles {
    IFBHNDSingleton config;
    IFBHNDSingleton input;
    IFBHNDSingleton dev_tools;
    IFBHNDSingleton graphics_manager;
    IFBHNDSingleton renderer;
};

struct IFBEngineSingletons {
    IFBEngineSingletonBuffer  buffer;
    IFBEngineSingletonHandles handles;
};

namespace ifb_engine {

    IFBVoid                   singletons_commit_all            (IFBEngineSingletons* ptr_singletons);

    IFBEngineConfig*          singletons_load_config           (const IFBEngineSingletons* ptr_singletons);
    IFBInput*                 singletons_load_input            (const IFBEngineSingletons* ptr_singletons);
    IFBEngineDevTools*        singletons_load_devtools         (const IFBEngineSingletons* ptr_singletons);
    IFBEngineGraphicsManager* singletons_load_graphics_manager (const IFBEngineSingletons* ptr_singletons);
};

/**********************************************************************************/
/* CONTEXT                                                                        */
/**********************************************************************************/

struct IFBEngineContext {
    IFBEngineCore*              ptr_core;
    IFBEngineSingletons*        ptr_singletons;
    IFBEngineArenas*            ptr_arenas;
};

namespace ifb_engine {
    
    IFBEngineContext&    context_ref                  (IFBVoid);
    IFBEngineCore*       context_get_ptr_core         (IFBVoid); 
    IFBEngineSingletons* context_get_ptr_singletons   (IFBVoid);
    IFBEngineSingletons* context_get_ptr_arenas       (IFBVoid);
};

#endif //IFB_ENGINE_INTERNAL_CONTEXT_HPP