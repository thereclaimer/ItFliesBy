#ifndef IFB_TYPES_HPP
#define IFB_TYPES_HPP

#include <cstdint>
#include <xmmintrin.h>

/**********************************************************************************/
/* PRIMITIVES                                                                     */
/**********************************************************************************/

//signed integers
typedef int8_t   IFBS8;
typedef int16_t  IFBS16;
typedef int32_t  IFBS32;
typedef int64_t  IFBS64;

//unsigned integ 
typedef uint8_t  IFBU8;
typedef uint16_t IFBU16;
typedef uint32_t IFBU32;
typedef uint64_t IFBU64;

//floats
typedef float    IFBF32;
typedef double   IFBF64;

//booleans
typedef int8_t   IFBB8;
typedef int16_t  IFBB16;
typedef int32_t  IFBB32;
typedef int64_t  IFBB64;

//characters
typedef char     IFBChar;
typedef wchar_t  IFBWChar;

//memory
typedef void     IFBVoid;
typedef void*    IFBPtr;
typedef uint8_t  IFBByte;
typedef size_t   IFBSize;
typedef IFBU32   IFBIndex;
typedef IFBPtr   IFBHandle;
typedef intptr_t IFBAddr;

//time
typedef uint64_t IFBTimems;

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

struct IFBHND8   { IFBU8  offset;  };
struct IFBHND16  { IFBU16 offset;  };
struct IFBHND32  { IFBU32 offset;  };
struct IFBHND64  { IFBU64 offset;  };
struct IFBHNDPTR { IFBPtr pointer; };

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
            IFBF32 x;
            IFBF32 y;
        };
        IFBF32 xy[2];
    };
};

struct IFBVec3 {
    union {
        struct {
            IFBF32 x;
            IFBF32 y;
            IFBF32 z;
        };
        IFBF32 xyz[3];
    };
};

/**********************************************************************************/
/* MATRICES                                                                       */
/**********************************************************************************/

struct IFBMat3 {
    union {
        struct {
            IFBF32 r0c0;
            IFBF32 r0c1;
            IFBF32 r0c2;
            IFBF32 r1c0;
            IFBF32 r1c1;
            IFBF32 r1c2;
            IFBF32 r2c0;
            IFBF32 r2c1;
            IFBF32 r2c2;
        };
        struct {
            IFBVec3 row_vec_0;
            IFBVec3 row_vec_1;
            IFBVec3 row_vec_2;
        };
        IFBF32 array[9];        
    };
};

/**********************************************************************************/
/* TRANSFORMS                                                                     */
/**********************************************************************************/

struct IFBTransform {
    IFBVec2 translation;
    IFBVec2 scale;
    IFBF32  rotation_radians;
};

/**********************************************************************************/
/* GEOMETRY                                                                       */
/**********************************************************************************/

struct IFBDimensions {
    IFBU32 width;
    IFBU32 height;
};

struct IFBPosition {
    IFBU32 x;
    IFBU32 y;
};

struct IFBDimensionsAndPosition {
    IFBDimensions dimensions;
    IFBPosition   position;    
};

struct IFBPoint {
    IFBF32 x;
    IFBF32 y;
};

struct IFBLine {
    IFBPoint point_a;
    IFBPoint point_b;
};

#endif //IFB_TYPES_HPP