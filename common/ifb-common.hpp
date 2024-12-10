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

struct IFBID {
    ifb_index index;
};

struct IFBIDTag    : IFBID { };
struct IFBIDCommit : IFBID { };

struct IFBIDArena : IFBID {
    IFBIDTag    tag_id;
    IFBIDCommit commit_id;
};

struct IFBHND {
    ifb_u32 offset;
};

struct IFBHNDLinearAllocator : IFBHND { };
struct IFBHNDBlockAllocator  : IFBHND { };

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

struct IFBMemory {
    ifb_u32 reservation_offset;
};

struct IFBTag {
    IFBID    id;
    ifb_cstr value;
    IFBHash  hash;
};

struct IFBCommit {
    IFBIDCommit id;
    ifb_u32     page_start;
    ifb_u32     page_count;
};

struct IFBArena {
    IFBIDArena id;
    ifb_u32    size;
    ifb_cstr   tag_c_str;
    ifb_handle start;
};

struct IFBLinearAllocator {
    IFBIDArena arena_id;
    ifb_u32    start;
    ifb_u32    size;
    ifb_u32    position;
    ifb_u32    save_point;
};

struct IFBBlockAllocator {
    IFBIDArena          arena_id;
    ifb_u32             block_size;
    ifb_u32             block_count;
};

#endif //IFB_COMMON_HPP