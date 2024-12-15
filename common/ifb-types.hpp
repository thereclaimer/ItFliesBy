#ifndef IFB_TYPES_HPP
#define IFB_TYPES_HPP

#include <cstdint>

/**********************************************************************************/
/* PRIMITIVES                                                                     */
/**********************************************************************************/

//signed integers
typedef int8_t  ifb_s8;
typedef int16_t ifb_s16;
typedef int32_t ifb_s32;
typedef int64_t ifb_s64;

//unsigned integers
typedef uint8_t  ifb_u8;
typedef uint16_t ifb_u16;
typedef uint32_t ifb_u32;
typedef uint64_t ifb_u64;

//floats
typedef float  ifb_f32;
typedef double ifb_f64;

//booleans
typedef int8_t  ifb_b8;
typedef int16_t ifb_b16;
typedef int32_t ifb_b32;
typedef int64_t ifb_b64;

//strings
typedef char     ifb_char;
typedef wchar_t  ifb_wchar;
typedef char*    ifb_cstr;
typedef wchar_t* ifb_wstr;

//memory
typedef void       ifb_void;
typedef void*      ifb_ptr;
typedef uint8_t    ifb_byte;
typedef uint8_t*   ifb_memory;
typedef size_t     ifb_size;
typedef ifb_u32    ifb_index;
typedef ifb_u32    ifb_handle;
typedef intptr_t   ifb_address;
typedef uint32_t   ifb_page;

//time
typedef uint64_t ifb_timems;


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

struct IFBIDMonitor : IFBID { };

//handle
struct IFBHND {
    ifb_u32 offset;
};

//global handle
struct IFBGHND {
    ifb_u32 offset;
};


struct IFBHNDLinearAllocator : IFBHND { };
struct IFBHNDBlockAllocator  : IFBHND { };


/**********************************************************************************/
/* STRINGS                                                                        */
/**********************************************************************************/

union IFBHash {
    struct {
        ifb_u32 h1;
        ifb_u32 h2;
        ifb_u32 h3;
        ifb_u32 h4;
    };
    ifb_u32 h[4];
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

/**********************************************************************************/
/* GRAPHICS                                                                       */
/**********************************************************************************/

typedef ifb_u32 IFBAspectRatioType; 

struct IFBMonitor {
    IFBIDMonitor       id;
    ifb_u32            refresh_hz;
    IFBDimensions      dimensions;
    IFBAspectRatioType aspect_ratio;
};

struct IFBWindow {
    IFBIDMonitor  monitor_id;
    IFBDimensions dimensions;

};

#endif //IFB_TYPES_HPP
