#ifndef IFB_TYPES_MATH_HPP
#define IFB_TYPES_MATH_HPP

#include "ifb-types-primitives.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBVec2;
struct IFBVec3;
struct IFBMat3;
struct IFBPoint;
struct IFBLine;
struct IFBTransform;

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

struct IFBPoint {
    IFBF32 x;
    IFBF32 y;
};

struct IFBLine {
    IFBPoint point_a;
    IFBPoint point_b;
};

#endif //IFB_TYPES_MATH_HPP