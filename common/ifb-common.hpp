#ifndef IFB_COMMON_HPP
#define IFB_COMMON_HPP

#include "ifb-common-aspect-ratio.hpp"
#include "ifb-common-color.hpp"
#include "ifb-common-dependencies.hpp"
#include "ifb-common-hash.hpp"
#include "ifb-common-macros.hpp"
#include "ifb-common-memory.hpp"
#include "ifb-common-resolution.hpp"
#include "ifb-common-scopes.hpp"
#include "ifb-common-stack.hpp"
#include "ifb-common-types.hpp"
#include "ifb-common-user-input.hpp"
#include "ifb-common-platform.hpp"

struct IFBDimensions {
    ifb_u32 width;
    ifb_u32 height;
};

struct IFBPosition {
    ifb_u32 x;
    ifb_u32 y;
};

struct IFBTagId {
    ifb_index index;
};

struct IFBTag {
    IFBTagId id;
    ifb_cstr value;
    IFBHash  hash;
};

struct IFBMemory {
    ifb_u32 page_start;
    ifb_u32 page_count;
};

struct IFBMemoryCommitId {
    ifb_index index;
};

struct IFBMemoryCommit {
    IFBMemoryCommitId id;
    IFBMemory         memory;
};

struct IFBArenaId {
    ifb_index         index;
    IFBMemoryCommitId commit_id;
    IFBTagId          tag_id;
};

struct IFBArena {
    IFBArenaId id;
    ifb_u32    size;
    ifb_cstr   tag_c_str;
    ifb_handle start;
};


#endif //IFB_COMMON_HPP