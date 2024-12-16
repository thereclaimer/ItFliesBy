#ifndef IFB_TYPES_HPP
#define IFB_TYPES_HPP

#include <cstdint>
#include <xmmintrin.h>

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
/* SIMD                                                                           */
/**********************************************************************************/

#if _MSC_VER
    #if !defined(__clang__)
        #define INSTRUCTION_REORDER_BARRIER _ReadWriteBarrier()
    #endif //!defined(__clang__)
    #include <intrin.h>
#else //_MSC_VER
    #include <x86intrin.h>
#endif //_MSC_VER

typedef __m128 ifb_xmm_f128;

#define ifb_xmm_f128_load_aligned(f32_ptr)          _mm_load_ps(f32_4_ptr)
#define ifb_xmm_f128_load_unaligned(f32_ptr)        _mm_loadu_ps(f32_4_ptr)
#define ifb_xmm_f128_add(f32_ptr_a, f32_ptr_b)      _mm_add_ps(f32_ptr_a, f32_ptr_b)
#define ifb_xmm_f128_subtract(f32_ptr_a, f32_ptr_b) _mm_sub_ps(f32_ptr_a, f32_ptr_b)
#define ifb_xmm_f128_multiply(f32_ptr_a, f32_ptr_b) _mm_mul_ps(f32_ptr_a, f32_ptr_b)
#define ifb_xmm_f128_divide(f32_ptr_a, f32_ptr_b)   _mm_div_ps(f32_ptr_a, f32_ptr_b)
#define ifb_xmm_f128_store(f32_4_ptr, f32_simd)     _mm_store_ps(f32_4_ptr, f32_simd)

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

#endif //IFB_TYPES_HPP
