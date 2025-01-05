#ifndef IFB_ENGINE_INTERNAL_CONTEXT_HPP
#define IFB_ENGINE_INTERNAL_CONTEXT_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-platform.hpp"
#include "ifb-engine-internal-allocators.hpp"
#include "ifb-engine-internal-devtools.hpp"
#include "ifb-engine-internal-data.hpp"

/**********************************************************************************/
/* MANAGERS                                                                       */
/**********************************************************************************/

struct IFBEngineContextManagers {
    struct {
        IFBGHNDEngineManagerTag       tag;
        IFBGHNDEngineManagerArena     arena;
        IFBGHNDEngineManagerGraphics  graphics;
        IFBGHNDEngineManagerShader    shader;
        IFBGHNDEngineManagerTransform transform;
        IFBGHNDEngineManagerSprite    sprite;
    } handles;
};

namespace ifb_engine {

    ifb_void
    context_managers_create_all(
              IFBEngineContextManagers* managers_ptr, 
              IFBEngineMemory*          memory_ptr, 
        const IFBEngineConfig*          config_ptr);
        
    IFBEngineManagerTag*      context_managers_get_tag_manager      (const IFBEngineContextManagers* managers_ptr);
    IFBEngineManagerArena*    context_managers_get_arena_manager    (const IFBEngineContextManagers* managers_ptr);
    IFBEngineManagerGraphics* context_managers_get_graphics_manager (const IFBEngineContextManagers* managers_ptr);
};

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