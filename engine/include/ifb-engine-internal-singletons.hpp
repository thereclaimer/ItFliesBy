#ifndef IFB_ENGINE_INTERNAL_SINGLETONS_HPP
#define IFB_ENGINE_INTERNAL_SINGLETONS_HPP

#include <ifb.hpp>

#include "ifb-engine.hpp"
#include "ifb-engine-internal-devtools.hpp"
#include "ifb-engine-internal-graphics.hpp"

#define IFB_ENGINE_SINGLETON_STACK_SIZE 0xFFFF

struct IFBEngineSingletonBuffer {
    ifb_byte memory[IFB_ENGINE_SINGLETON_STACK_SIZE];
};

struct IFBEngineSingletonHandles {
    ifb_u16 config;
    ifb_u16 input;
    ifb_u16 dev_tools;
    ifb_u16 graphics_manager;
};

struct IFBEngineSingletons {
    IFBEngineSingletonBuffer  buffer;
    IFBEngineSingletonHandles handles;
};

namespace ifb_engine {

    ifb_void                  singletons_commit_all            (IFBEngineSingletons* ptr_singletons);

    IFBEngineConfig*          singletons_load_config           (const IFBEngineSingletons* ptr_singletons);
    IFBInput*                 singletons_load_input            (const IFBEngineSingletons* ptr_singletons);
    IFBEngineDevTools*        singletons_load_devtools         (const IFBEngineSingletons* ptr_singletons);
    IFBEngineGraphicsManager* singletons_load_graphics_manager (const IFBEngineSingletons* ptr_singletons);
};

#endif //IFB_ENGINE_INTERNAL_SINGLETONS_HPP