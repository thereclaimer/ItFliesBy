#ifndef IFB_ENGINE_INTERNAL_CONTEXT_HPP
#define IFB_ENGINE_INTERNAL_CONTEXT_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-platform.hpp"
#include "ifb-engine-internal-allocators.hpp"

/**********************************************************************************/
/* MANAGERS                                                                       */
/**********************************************************************************/

struct IFBGHNDEngineTagManager    : IFBGHND { };
struct IFBGHNDEngineArenaManager  : IFBGHND { };
struct IFBGHNDEngineWindowManager : IFBGHND { };

struct IFBEngineContextManagers {
    struct {
        IFBGHNDEngineTagManager    tag_manager;
        IFBGHNDEngineArenaManager  arena_manager;
        IFBGHNDEngineWindowManager window_manager;
    } handles;
};

namespace ifb_engine {

    ifb_void                context_managers_create_all         (IFBEngineContextManagers* managers_ptr, IFBEngineMemory* memory_ptr, const IFBEngineConfig* config_ptr);
    IFBEngineTagManager*    context_managers_get_tag_manager    (const IFBEngineContextManagers* managers_ptr);
    IFBEngineArenaManager*  context_managers_get_arena_manager  (const IFBEngineContextManagers* managers_ptr);
    IFBEngineWindowManager* context_managers_get_window_manager (const IFBEngineContextManagers* managers_ptr);
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

struct IFBGHNDEngineContextManagers  : IFBGHND { };
struct IFBGHNDEngineContextConfig    : IFBGHND { };
struct IFBGHNDEngineContextCore      : IFBGHND { }; 
struct IFBGHNDEngineContextUserInput : IFBGHND { };

struct IFBEngineContext {
    IFBEngineMemory memory;
    struct {
        IFBGHNDEngineContextManagers  managers;
        IFBGHNDEngineContextCore      core;
        IFBGHNDEngineContextConfig    config;
        IFBGHNDEngineContextUserInput user_input;
    } handles;
};

namespace ifb_engine {

    ifb_global IFBEngineContext _context;

    IFBEngineContext& context() { return(_context); }

    IFBEngineMemory*          context_get_memory   (ifb_void);
    IFBEngineContextManagers* context_get_managers (ifb_void);
    IFBEngineContextCore*     context_get_core     (ifb_void);
    IFBEngineConfig*          context_get_config   (ifb_void);

    const ifb_ptr context_get_pointer (const IFBHND&  handle);
    const ifb_ptr context_get_pointer (const IFBGHND& global_handle);
};

#endif //IFB_ENGINE_INTERNAL_CONTEXT_HPP