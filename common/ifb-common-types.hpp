
#include <cstdint>

/**********************************************************************************/
/* BASE TYPES                                                                      */
/**********************************************************************************/

//signed integers
typedef int8_t  ifb_s8_t;
typedef int16_t ifb_s16_t;
typedef int32_t ifb_s32_t;
typedef int64_t ifb_s64_t;

//unsigned integers
typedef uint8_t  ifb_u8_t;
typedef uint16_t ifb_u16_t;
typedef uint32_t ifb_u32_t;
typedef uint64_t ifb_u64_t;

//floats
typedef float  ifb_f32_t;
typedef double ifb_f64_t;

//booleans
typedef int8_t  ifb_b8_t;
typedef int16_t ifb_b16_t;
typedef int32_t ifb_b32_t;
typedef int64_t ifb_b64_t;

//strings
typedef char     ifb_char_t;
typedef wchar_t  ifb_wchar_t;
typedef char*    ifb_cstr_p;
typedef wchar_t* ifb_wstr_p;

//memory
typedef void       ifb_void_t;
typedef void*      ifb_handle_p;
typedef uint8_t    ifb_byte_u8t;
typedef uint8_t*   ifb_memory_u8p;
typedef size_t     ifb_size_u64t;
typedef ifb_u32_t  ifb_index_u32t;
typedef intptr_t   ifb_address_u64t;
typedef uint32_t   ifb_page_u32t;

//time
typedef uint64_t ifb_timems_u64t;