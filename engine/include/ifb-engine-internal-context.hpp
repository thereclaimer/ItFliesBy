#ifndef IFB_ENGINE_INTERNAL_CONTEXT_HPP
#define IFB_ENGINE_INTERNAL_CONTEXT_HPP

#include <ifb.hpp>
#include <ifb-memory.hpp>

#include "ifb-engine.hpp"
#include "ifb-engine-internal-core.hpp"
#include "ifb-engine-internal-devtools.hpp"
#include "ifb-engine-internal-graphics.hpp"
#include "ifb-engine-internal-renderer.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBEngineContext;

struct IFBEngineArenas;

struct IFBEngineSingletons;
struct IFBEngineSingletonBuffer;
struct IFBEngineSingletonHandles;

//handles
struct IFBHNDSingleton : IFBHND16 { };

/**********************************************************************************/
/* CONFIG                                                                         */
/**********************************************************************************/

#ifndef  IFB_ENGINE_CONFIG_MEMORY_STACK_SIZE_KB
#define  IFB_ENGINE_CONFIG_MEMORY_STACK_SIZE_KB 64
#endif //IFB_ENGINE_CONFIG_MEMORY_STACK_SIZE_KB

#ifndef  IFB_ENGINE_CONFIG_MEMORY_RESERVATION_SIZE_GB
#define  IFB_ENGINE_CONFIG_MEMORY_RESERVATION_SIZE_GB 4
#endif //IFB_ENGINE_CONFIG_MEMORY_RESERVATION_SIZE_GB

namespace ifb_engine {

    inline const IFBB8 config_initialize (IFBEngineConfig* ptr_config);
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
    IFBHNDSingleton arenas;
    IFBHNDSingleton dev_tools;
    IFBHNDSingleton graphics;
    IFBHNDSingleton renderer;
};

struct IFBEngineSingletons {
    IFBEngineSingletonBuffer  buffer;
    IFBEngineSingletonHandles handles;
};

namespace ifb_engine {

    IFBEngineSingletons* singletons_create        (IFBEngineCore* ptr_core);

    IFBEngineConfig*     singletons_load_config   (const IFBEngineSingletons* ptr_singletons);
    IFBInput*            singletons_load_input    (const IFBEngineSingletons* ptr_singletons);
    IFBEngineArenas*     singletons_load_arenas   (const IFBEngineSingletons* ptr_singletons);
    IFBEngineDevTools*   singletons_load_devtools (const IFBEngineSingletons* ptr_singletons);
    IFBEngineGraphics*   singletons_load_graphics (const IFBEngineSingletons* ptr_singletons);
    IFBEngineRenderer*   singletons_load_renderer (const IFBEngineSingletons* ptr_singletons);
};

/**********************************************************************************/
/* PLATFORM                                                                        */
/**********************************************************************************/

namespace ifb_engine {

    const IFBB8
    platform_api_initialize(
        const IFBPlatformAPI* ptr_platform_api);
};

/**********************************************************************************/
/* ARENAS                                                                         */
/**********************************************************************************/

struct IFBEngineArenas {
    IFBHNDArena platform;
    IFBHNDArena graphics;
    IFBHNDArena rendering;
};

/**********************************************************************************/
/* CONTEXT                                                                        */
/**********************************************************************************/

struct IFBEngineContext {
    IFBEngineCore*       ptr_core;
    IFBEngineSingletons* ptr_singletons;
};

namespace ifb_engine {
    
    const IFBB8
    context_initialize_config(
        IFBEngineCore*       core_ptr,
        IFBEngineSingletons* singletons_ptr);

    const IFBB8
    context_initialize_graphics_and_rendering(
        IFBEngineCore*            core_ptr,
        IFBEngineSingletons*      singletons_ptr);

    IFBEngineContext&    context_ref                (IFBVoid);
    IFBEngineCore*       context_get_ptr_core       (IFBVoid); 
    IFBEngineSingletons* context_get_ptr_singletons (IFBVoid);

    IFBEngineContextUpdate* context_commit_update   (IFBEngineCore* core_ptr);
};

#endif //IFB_ENGINE_INTERNAL_CONTEXT_HPP