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

/**********************************************************************************/
/* IDENTIFIERS                                                                    */
/**********************************************************************************/

struct IFBId {
    ifb_index index;
};

struct IFBTagId    : IFBId;
struct IFBCommitId : IFBId;

struct IFBArenaId : IFBId {
    IFBTagId    tag_id;
    IFBCommitId commit_id;
};

struct IFBLinearAllocatorId : IFBId {
    IFBArenaId arena_id;
};

struct IFBBlockAllocatorId : IFBId {
    IFBArenaId arena_id;
};

struct IFBBlockId : IFBId {
    IFBBlockAllocatorId block_allocator_id;
};

/**********************************************************************************/
/* MISC                                                                           */
/**********************************************************************************/

struct IFBDimensions {
    ifb_u32 width;
    ifb_u32 height;
};

struct IFBPosition {
    ifb_u32 x;
    ifb_u32 y;
};

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

struct IFBTag {
    IFBTagId id;
    ifb_cstr value;
    IFBHash  hash;
};

struct IFBCommit {
    IFBCommitId id;
    ifb_u32 page_start;
    ifb_u32 page_count;
};

struct IFBArena {
    IFBArenaId id;
    ifb_u32    size;
    ifb_cstr   tag_c_str;
    ifb_handle start;
};

struct IFBLinearAllocator {
    IFBLinearAllocatorId id;
    ifb_u32              size;
    ifb_u32              position;
    ifb_u32              save_point;
};

struct IFBBlockAllocator {
    IFBBlockAllocatorId id;
    ifb_u32             block_size;
    ifb_u32             block_count;
};

struct IFBBlock {
    IFBBlockId  id;
    ifb_u32     size;
    ifb_address start;
};

#endif //IFB_COMMON_HPP