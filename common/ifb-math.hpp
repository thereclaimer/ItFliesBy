#ifndef IFB_MATH_HPP
#define IFB_MATH_HPP

#include "ifb-types.hpp"

struct IFBVec2 {
    union {
        struct {
            ifb_f32 x;
            ifb_f32 y;
        };
        ifb_f32 xy[2];
    };
};

struct IFBVec3 {
    union {
        struct {
            ifb_f32 x;
            ifb_f32 y;
            ifb_f32 z;
        };
        ifb_f32 xyz[3];
    };
};

struct IFBMat3 {
    union {
        struct {
            ifb_f32 row0_col0;
            ifb_f32 row0_col1;
            ifb_f32 row0_col2;
            ifb_f32 row1_col0;
            ifb_f32 row1_col1;
            ifb_f32 row1_col2;
            ifb_f32 row2_col0;
            ifb_f32 row2_col1;
            ifb_f32 row2_col2;
        };
        struct {
            IFBVec3 row_vec_0;
            IFBVec3 row_vec_1;
            IFBVec3 row_vec_2;
        };
        ifb_f32 array[9];        
    };
};

#endif //IFB_MATH_HPP