#ifndef IFB_ENGINE_INTERNAL_CONTEXT_HPP
#define IFB_ENGINE_INTERNAL_CONTEXT_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-platform.hpp"
#include "ifb-engine-internal-allocators.hpp"

/**********************************************************************************/
/* CONTEXT STACK                                                                  */
/**********************************************************************************/

#ifndef IFB_ENGINE_CONFIG_CONTEXT_STACK_SIZE
    #define IFB_ENGINE_CONFIG_CONTEXT_STACK_SIZE ifb_macro_size_kilobytes(64)
#endif

struct IFBEngineContextStack {
    ifb_u32  size;
    ifb_u32  position;
    ifb_byte memory[IFB_ENGINE_CONFIG_CONTEXT_STACK_SIZE];
};

namespace ifb_engine {

    const ifb_void context_stack_push         (IFBHND& ref_handle, const ifb_u32 size);
    const ifb_void context_stack_push_aligned (IFBHND& ref_handle, const ifb_u32 size, const ifb_u32 alignment);
    const ifb_ptr  context_stack_get_pointer  (const IFBHND& ref_handle);
};

#define ifb_engine_context_push_struct(handle,type) ifb_engine::context_stack_push_aligned(handle,sizeof(type),alignof(type))

/**********************************************************************************/
/* CONTEXT HANDLES                                                                */
/**********************************************************************************/

struct IFBHNDUserInput          : IFBHND { };
struct IFBHNDEngineMemory       : IFBHND { };
struct IFBHNDEngineTagManager   : IFBHND { };
struct IFBHNDEngineArenaManager : IFBHND { };
struct IFBHNDEngineConfig       : IFBHND { };

struct IFBEngineContextHandles {
    IFBHNDUserInput          user_input;
    IFBHNDEngineMemory       memory;
    IFBHNDEngineTagManager   tag_manager;
    IFBHNDEngineArenaManager arena_manager;
    IFBHNDEngineConfig       config;
};

namespace ifb_engine {

    ifb_void context_handles_create_all(ifb_void);

    IFBUserInput*          context_get_user_input    (ifb_void);
    IFBEngineMemory*       context_get_memory        (ifb_void);
    IFBEngineTagManager*   context_get_tag_manager   (ifb_void);
    IFBEngineArenaManager* context_get_arena_manager (ifb_void);
    IFBEngineConfig*       context_get_config        (ifb_void);
};

/**********************************************************************************/
/* CONTEXT STATS                                                                  */
/**********************************************************************************/

struct IFBEngineContextStats {
    IFBEngineState     state;
    ifb_timems         time_initialized;
};

/**********************************************************************************/
/* CONTEXT                                                                        */
/**********************************************************************************/

struct IFBEngineContext {
    IFBEngineContextHandles handles;
    IFBEngineContextStack   stack;
    IFBEngineContextStats   stats;
};

namespace ifb_engine {

    ifb_global IFBEngineContext _engine_context;

    ifb_void context_reset (ifb_void);

    IFBEngineContextStack&   context_get_stack   (ifb_void);
    IFBEngineContextHandles& context_get_handles (ifb_void);
    IFBEngineContextStats&   context_get_stats   (ifb_void);

    ifb_void context_initialize_stack    (const IFBEngineConfig* config_ptr);
    ifb_void context_initialize_managers (const IFBEngineConfig* config_ptr);
    ifb_void context_initialize_memory   (const IFBEngineConfig* config_ptr);

    const ifb_ptr context_get_pointer(const IFBHND& handle);
};

#endif //IFB_ENGINE_INTERNAL_CONTEXT_HPP