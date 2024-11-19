#ifndef IFB_ENGINE_INTERNAL_ASSET_HPP
#define IFB_ENGINE_INTERNAL_ASSET_HPP


#include "ifb-engine.hpp"

/**********************************************************************************/
/* FILE TABLE                                                                     */
/**********************************************************************************/

struct IFBEngineAssetFileTable {
    ifb_u32 file_count;

};


/**********************************************************************************/
/* ASSET_MANAGER                                                                  */
/**********************************************************************************/

struct IFBEngineAssetManager {
    ifb_u32 page_id;
};


namespace ifb_engine {

    const ifb_b8 asset_manager_create(ifb_void);

};


#endif //IFB_ENGINE_INTERNAL_ASSET_HPP