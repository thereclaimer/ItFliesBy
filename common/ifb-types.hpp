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

struct IFBVec2;
struct IFBVec3;
struct IFBMat3;
struct IFBPoint;
struct IFBLine;
struct IFBTransform;
struct IFBDimensions;
struct IFBPosition;
struct IFBDimensionsAndPosition;

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

typedef __m128 IFBXMMF128;

/**********************************************************************************/
/* HANDLES                                                                        */
/**********************************************************************************/

struct IFBHND8  { ifb::u8   h8;  };
struct IFBHND16 { ifb::u16  h16; };
struct IFBHND32 { ifb::u32  h32; };
struct IFBHND64 { ifb::addr h64; };

#define IFB_HANDLE_INVALID_U8  0xFF
#define IFB_HANDLE_INVALID_U16 0xFFFF 
#define IFB_HANDLE_INVALID_U32 0xFFFFFFFF 
#define IFB_HANDLE_INVALID_U64 0xFFFFFFFFFFFFFFFF

/**********************************************************************************/
/* VECTORS                                                                        */
/**********************************************************************************/

struct IFBVec2 {
    union {
        struct {
            ifb::f32 x;
            ifb::f32 y;
        };
        ifb::f32 xy[2];
    };
};

struct IFBVec3 {
    union {
        struct {
            ifb::f32 x;
            ifb::f32 y;
            ifb::f32 z;
        };
        ifb::f32 xyz[3];
    };
};

/**********************************************************************************/
/* MATRICES                                                                       */
/**********************************************************************************/

struct IFBMat3 {
    union {
        struct {
            ifb::f32 r0c0;
            ifb::f32 r0c1;
            ifb::f32 r0c2;
            ifb::f32 r1c0;
            ifb::f32 r1c1;
            ifb::f32 r1c2;
            ifb::f32 r2c0;
            ifb::f32 r2c1;
            ifb::f32 r2c2;
        };
        struct {
            IFBVec3 row_vec_0;
            IFBVec3 row_vec_1;
            IFBVec3 row_vec_2;
        };
        ifb::f32 array[9];        
    };
};

/**********************************************************************************/
/* TRANSFORMS                                                                     */
/**********************************************************************************/

struct IFBTransform {
    IFBVec2 translation;
    IFBVec2 scale;
    ifb::f32  rotation_radians;
};

/**********************************************************************************/
/* GEOMETRY                                                                       */
/**********************************************************************************/

struct IFBDimensions {
    ifb::u32 width;
    ifb::u32 height;
};

struct IFBPosition {
    ifb::u32 x;
    ifb::u32 y;
};

struct IFBDimensionsAndPosition {
    IFBDimensions dimensions;
    IFBPosition   position;    
};

struct IFBPoint {
    ifb::f32 x;
    ifb::f32 y;
};

struct IFBLine {
    IFBPoint point_a;
    IFBPoint point_b;
};

#endif //IFB_TYPES_HPP