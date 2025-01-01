#ifndef IFB_TYPES_HPP
#define IFB_TYPES_HPP

#include <cstdint>
#include <xmmintrin.h>

/**********************************************************************************/
/* PRIMITIVES                                                                     */
/**********************************************************************************/

//signed integers
typedef int8_t     ifb_s8;
typedef int16_t    ifb_s16;
typedef int32_t    ifb_s32;
typedef int64_t    ifb_s64;

//unsigned integers
typedef uint8_t    ifb_u8;
typedef uint16_t   ifb_u16;
typedef uint32_t   ifb_u32;
typedef uint64_t   ifb_u64;

//enum
typedef uint32_t   ifb_enum;

//floats
typedef float      ifb_f32;
typedef double     ifb_f64;

//booleans
typedef int8_t     ifb_b8;
typedef int16_t    ifb_b16;
typedef int32_t    ifb_b32;
typedef int64_t    ifb_b64;

//strings
typedef char       ifb_char;
typedef wchar_t    ifb_wchar;
typedef char*      ifb_cstr;
typedef wchar_t*   ifb_wstr;

//memory
typedef void       ifb_void;
typedef void*      ifb_ptr;
typedef uint8_t    ifb_byte;
typedef uint8_t*   ifb_memory;
typedef size_t     ifb_size;
typedef ifb_u32    ifb_index;
typedef ifb_ptr    ifb_handle;
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

/**********************************************************************************/
/* IDENTIFIERS                                                                    */
/**********************************************************************************/

struct IFBID   { ifb_index index;  }; // id            | unique index in a collection
struct IFBHND  { ifb_u32   offset; }; // handle        | offset from engine memory reservation
struct IFBGHND { ifb_u32   offset; }; // global handle | offset from engine global stack

#endif //IFB_TYPES_HPP