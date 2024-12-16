#ifndef IFB_MATH_MAT3_HPP
#define IFB_MATH_MAT3_HPP

#include <ifb.hpp>
#include "ifb-math-vec2.hpp"

struct IFBMathMat3 {
    union {
        struct {
            ifb_f32 r0c0;
            ifb_f32 r0c1;
            ifb_f32 r0c2;
            ifb_f32 r1c0;
            ifb_f32 r1c1;
            ifb_f32 r1c2;
            ifb_f32 r2c0;
            ifb_f32 r2c1;
            ifb_f32 r2c2;
        };
        ifb_f32 array[9];
    };
};

typedef IFBMathMat3 ifb_m3;

namespace ifb_math {

    void mat3_identity (const ifb_u32 count, ifb_m3* m3);
    void mat3_a_mul_b  (const ifb_u32 count, const ifb_m3* m3_a, const ifb_m3* m3_b, ifb_m3* m3_c);
};

#endif //IFB_MATH_MAT3_HPP