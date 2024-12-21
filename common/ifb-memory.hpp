#ifndef IFB_MEMORY_HPP
#define IFB_MEMORY_HPP

#include "ifb-types.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBIDTag     : IFBID { };
struct IFBIDCommit  : IFBID { };
struct IFBIDArena   : IFBID { };

struct IFBHNDLinearAllocator : IFBHND { };
struct IFBHNDBlockAllocator  : IFBHND { };

struct IFBTag;
struct IFBCommit;
struct IFBArena;
struct IFBLinearAllocator;
struct IFBBlockAllocator;

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

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
    ifb_u32    start;
    ifb_cstr   tag_c_str;
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

#endif //IFB_MEMORY_HPP