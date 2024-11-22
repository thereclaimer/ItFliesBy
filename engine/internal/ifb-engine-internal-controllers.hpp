#ifndef IFB_ENGINE_INTERNAL_CONTROLLERS_HPP
#define IFB_ENGINE_INTERNAL_CONTROLLERS_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-tables.hpp"

/**********************************************************************************/
/* TAG CONTROLLER                                                                 */
/**********************************************************************************/

namespace ifb_engine {

    const IFBHashValue controller_tag_hash_value       (const IFBEngineTagId tag_id);
    const ifb_cstr     controller_tag_cstr_value       (const IFBEngineTagId tag_id);
    const ifb_b8       controller_tag_collision_check  (const IFBHashValue   hash_value);
    const ifb_b8       controller_tag_table_delete     (const IFBEngineTagId tag_id);
    const ifb_b8       controller_tag_table_insert     (const ifb_cstr       in_tag_value, IFBEngineTagId& out_tag_id);
    const ifb_b8       controller_tag_table_search     (const ifb_cstr       in_tag_value, IFBEngineTagId& out_tag_id);
};

#endif //IFB_ENGINE_INTERNAL_CONTROLLERS_HPP