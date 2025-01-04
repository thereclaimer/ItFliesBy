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

#define IFB_TAG_LENGTH 32

struct IFBTag : IFBIDTag {
    ifb_char value[IFB_TAG_LENGTH];
    IFBHash  hash;
};

struct IFBCommit : IFBIDCommit{
    ifb_u32     page_start;
    ifb_u32     page_count;
};

struct IFBArena : IFBIDArena {
    ifb_u32    size;
    ifb_u32    start;
    ifb_cstr   tag_c_str;
};

#endif //IFB_MEMORY_HPP