#ifndef IFB_TYPES_HPP
#define IFB_TYPES_HPP

#include <cstdint>

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
typedef uint64_t   ifb_timems;

/**********************************************************************************/
/* IDENTIFIERS                                                                    */
/**********************************************************************************/

struct IFBID   { ifb_index index;  }; // id            | unique index in a collection
struct IFBHND  { ifb_u32   offset; }; // handle        | offset from engine memory reservation
struct IFBGHND { ifb_u32   offset; }; // global handle | offset from engine global stack

#endif //IFB_TYPES_HPP