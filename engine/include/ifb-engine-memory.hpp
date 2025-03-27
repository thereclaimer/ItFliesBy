#ifndef IFB_ENGINE_MEMORY_HPP
#define IFB_ENGINE_MEMORY_HPP

#include "ifb-engine.hpp"


#define IFB_MEMORY_MANAGER_SIZE_GB_RESERVATION 4
#define IFB_MEMORY_MANAGER_SIZE_KB_ARENA       64



struct IFBEngineMemoryManager {
    IFBMEM64Stack       global_stack;
    IFBMEM32Reservation system_reservation;
    struct {
        IFBMEM32Arena graphics_manager;
    } arenas;
};

namespace ifb_engine {

    IFBEngineMemoryManager* memory_manager_create(const IFBMEM64Stack global_stack);    
}

#endif //IFB_ENGINE_MEMORY_HPP