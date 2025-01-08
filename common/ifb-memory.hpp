#ifndef IFB_MEMORY_HPP
#define IFB_MEMORY_HPP

#include "ifb-types.hpp"
#include "ifb-tag.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBIDCommit  : IFBID { };
struct IFBIDArena   : IFBID { };

struct IFBCommit;
struct IFBArena;
struct IFBLinearArena;
struct IFBBlockArena;
struct IFBScratchArena;

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

struct IFBCommit : IFBIDCommit{
    ifb_u32 page_start;
    ifb_u32 page_count;
};

struct IFBArena : IFBIDArena {
    IFBIDTag    tag_id;
    ifb_address start;
    ifb_u32     size;
};

struct IFBLinearArena : IFBArena {
    ifb_u32 position;
};

#define IFB_BLOCK_ARENA_MAX_BLOCKS 32

struct IFBBlockArena : IFBArena {
    ifb_u32 flags;
    ifb_u32 block_count;
    ifb_u32 block_size;
};

struct IFBScratchArena : IFBLinearArena { };

#endif //IFB_MEMORY_HPP