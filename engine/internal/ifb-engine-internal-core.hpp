#ifndef IFB_ENGINE_CORE_HPP
#define IFB_ENGINE_CORE_HPP

#include <r-libs.hpp>

#include "ifb-engine.hpp"

/**********************************************************************************/
/* CORE                                                                           */
/**********************************************************************************/

struct IFBEngineCore {
    ifb_u32 page_index_memory_manager;
    ifb_u32 page_index_asset_manager;
};

#endif //IFB_ENGINE_CORE_HPP