#ifndef IFB_ENGINE_INTERNAL_CONTROLLERS_HPP
#define IFB_ENGINE_INTERNAL_CONTROLLERS_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-tables.hpp"

/**********************************************************************************/
/* TAG CONTROLLER                                                                 */
/**********************************************************************************/

namespace ifb_engine {

    const IFBHashValue controller_tag_hash_value       (IFBEngineTableTag& tag_table,    const IFBEngineTagId tag_id);
    const ifb_cstr     controller_tag_cstr_value       (IFBEngineTableTag& tag_table,    const IFBEngineTagId tag_id);
    const ifb_b8       controller_tag_collision_check  (IFBEngineTableTag& tag_table,    const IFBHashValue   hash_value);
    const ifb_b8       controller_tag_table_delete     (IFBEngineTableTag& tag_table,    const IFBEngineTagId tag_id);
    const ifb_b8       controller_tag_table_insert     (IFBEngineTableTag& in_tag_table, const ifb_cstr       in_tag_value, IFBEngineTagId& out_tag_id);
    const ifb_b8       controller_tag_table_search     (IFBEngineTableTag& in_tag_table, const ifb_cstr       in_tag_value, IFBEngineTagId& out_tag_id);
};

#endif //IFB_ENGINE_INTERNAL_CONTROLLERS_HPP