#ifndef IFB_ENGINE_INTERNAL_TAG_HPP
#define IFB_ENGINE_INTERNAL_TAG_HPP
t cgg
#include "ifb-engine.hpp"
#include "ifb-engine-internal-memory.hpp"

#define IFB_ENGINE_TAG_MANAGER_TAG_LENGTH    32
#define IFB_ENGINE_TAG_MANAGER_TAG_COUNT_MAX 1024

struct IFBEngineTagManager {
    ifb_u32                 tag_length;
    ifb_u32                 tag_count_total;
    struct {
        IFBEngineMemoryCommitId char_buffer;
        IFBEngineMemoryCommitId hash_buffer;
    } commit_ids;
};

namespace ifb_engine {

    const ifb_handle tag_manager_create  (ifb_void);

    IFBEngineTagManager* tag_manager_pointer             (const ifb_handle tag_manager_handle);    
    ifb_char*            tag_manager_pointer_char_buffer (IFBEngineTagManager* ptr_tag_manager);
    IFBHash*             tag_manager_pointer_hash_buffer (IFBEngineTagManager* ptr_tag_manager);

    const IFBTagId tag_manager_reserve_tag (IFBEngineTagManager* ptr_tag_manager, const ifb_cstr c_str_tag_value);
    const ifb_void tag_manager_release_tag (IFBEngineTagManager* ptr_tag_manager, const IFBTagId tag_id);
    const ifb_cstr tag_manager_tag_c_str   (IFBEngineTagManager* ptr_tag_manager, const IFBTagId tag_id);
    const IFBHash  tag_manager_tag_hash    (IFBEngineTagManager* ptr_tag_manager, const IFBTagId tag_id);


};

#endif //IFB_ENGINE_INTERNAL_TAG_HPP