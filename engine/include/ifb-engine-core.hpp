#ifndef IFB_ENGINE_CORE_HPP
#define IFB_ENGINE_CORE_HPP

#include "ifb-engine.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBEngineCore;

/**********************************************************************************/
/* ENGINE CORE                                                                    */
/**********************************************************************************/

struct IFBEngineCore {
    IFBMEM64Stack      global_stack;
    IFBMEM32Manager    memory_manager;
    IFBGraphicsWindow* graphics_window;
};

namespace ifb_engine {

    IFBEngineCore* core_create_and_initialize (IFBMemoryStack* stack);

};

/**********************************************************************************/
/* ENGINE MEMORY                                                                  */
/**********************************************************************************/



#endif //IFB_ENGINE_CORE_HPP
