#ifndef IFB_ENGINE_MEMORY_HPP
#define IFB_ENGINE_MEMORY_HPP

#include "ifb-engine-types.hpp"
#include "ifb-engine-scopes.hpp"
#include "ifb-engine-macros.hpp"

struct IFBEngineMemoryHandle {
    ifb_u32 page_start;
    ifb_u32 page_offset;
};

struct IFBEngineMemoryCommit {
    ifb_memory start;
    ifb_u32    page_start;
    ifb_u32    page_count;
};

namespace ifb_engine {

    //pointers
    ifb_api const ifb_memory memory_pointer_from_handle       (IFBEngineMemoryHandle& memory_handle_ref);
    ifb_api const ifb_memory memory_pointer_from_page         (const ifb_u32 page_number);
    ifb_api const ifb_memory memory_pointer_from_current_page (ifb_void);

    //pages    
    ifb_api const ifb_u32 memory_size_page_aligned   (const ifb_u32 size);
    ifb_api const ifb_u32 memory_page_count          (const ifb_u32 size);
    ifb_api const ifb_u32 memory_page_size           (const ifb_u32 page_count);

    //commit handles    
    ifb_api const ifb_b8 memory_commit_size  (const ifb_u32 in_commit_size_minimum, IFBEngineMemoryCommit& out_commit_ref);
    ifb_api const ifb_b8 memory_commit_pages (const ifb_u32 in_commit_page_count,   IFBEngineMemoryCommit& out_commit_ref);

    //commit immediate    
    ifb_api const ifb_memory memory_commit_size_immediate  (const ifb_u32 size_minimum);
    ifb_api const ifb_memory memory_commit_pages_immediate (const ifb_u32 page_count);
};

#endif //IFB_ENGINE_MEMORY_HPP