#ifndef IFB_TYPES_HPP
#define IFB_TYPES_HPP

#include <cstdint>
#include <xmmintrin.h>

/**********************************************************************************/
/* PRIMITIVES                                                                     */
/**********************************************************************************/

namespace ifb {

    //signed integers
    typedef int8_t  s8;
    typedef int16_t s16;
    typedef int32_t s32;
    typedef int64_t s64;

    //unsigned integer 
    typedef uint8_t  u8;
    typedef uint16_t u16;
    typedef uint32_t u32;
    typedef uint64_t u64;

    //floats
    typedef float    f32;
    typedef double   f64;
    
    //booleans
    typedef int8_t   b8;
    typedef int16_t  b16;
    typedef int32_t  b32;
    typedef int64_t  b64;

    //chars  
    typedef char     utf8;
    typedef wchar_t  utf16;

    //memory
    typedef void*    ptr;
    typedef uint8_t  byte;
    typedef intptr_t addr;
    
    //time
    typedef uint64_t ms;
};

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb {

    struct memory_t;
    struct iterator_t;
    struct vec2_t;
    struct vec3_t;
    struct mat3_t;
    struct point_t;
    struct line_t;
    struct transform_t;
    struct dimensions_t;
    struct position_t;
    struct dimensions_and_position_t;
};

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

namespace ifb {

    struct memory_t {
        addr start;
        u64  size;
    };

    struct iterator_t {
        ptr pointer;
        u64 index;
    };
};

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

namespace ifb {

    typedef __m128 xmm_f128;
}


/**********************************************************************************/
/* HANDLES                                                                        */
/**********************************************************************************/

namespace ifb {

    struct hnd8  { u8   h8;  };
    struct hnd16 { u16  h16; };
    struct hnd32 { u32  h32; };
    struct hnd64 { addr h64; };
};

#define IFB_HANDLE_INVALID_U8  0xFF
#define IFB_HANDLE_INVALID_U16 0xFFFF 
#define IFB_HANDLE_INVALID_U32 0xFFFFFFFF 
#define IFB_HANDLE_INVALID_U64 0xFFFFFFFFFFFFFFFF

/**********************************************************************************/
/* VECTORS                                                                        */
/**********************************************************************************/

namespace ifb {

    struct vec2_t {
        union {
            struct {
                f32 x;
                f32 y;
            };
            f32 xy[2];
        };
    };

    struct vec3_t {
        union {
            struct {
                f32 x;
                f32 y;
                f32 z;
            };
            f32 xyz[3];
        };
    };

};
/**********************************************************************************/
/* MATRICES                                                                       */
/**********************************************************************************/

namespace ifb {

    struct mat3_t {
        union {
            struct {
                f32 r0c0;
                f32 r0c1;
                f32 r0c2;
                f32 r1c0;
                f32 r1c1;
                f32 r1c2;
                f32 r2c0;
                f32 r2c1;
                f32 r2c2;
            };
            struct {
                vec3_t row_vec_0;
                vec3_t row_vec_1;
                vec3_t row_vec_2;
            };
            f32 array[9];        
        };
    };



};

/**********************************************************************************/
/* TRANSFORMS                                                                     */
/**********************************************************************************/

namespace ifb {

    struct transform_t {
        vec2_t translation;
        vec2_t scale;
        f32    rotation_radians;
    };
};

/**********************************************************************************/
/* GEOMETRY                                                                       */
/**********************************************************************************/

namespace ifb {

    struct dimensions_t {
        u32 width;
        u32 height;
    };

    struct position_t {
        u32 x;
        u32 y;
    };

    struct dimensions_and_position_t {
        dimensions_t dimensions;
        position_t   position;    
    };

    struct point_t {
        f32 x;
        f32 y;
    };

    struct IFBLine {
        point_t point_a;
        point_t point_b;
    };

};


#endif //IFB_TYPES_HPP