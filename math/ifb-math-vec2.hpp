#ifndef IFB_MATH_VEC2_HPP
#define IFB_MATH_VEC2_HPP

#include <ifb.hpp>

struct IFBMathVec2 {
    ifb_f32 x;
    ifb_f32 y;
};

typedef IFBMathVec2 ifb_v2;

namespace ifb_math {

    void vec2_a_add_b (const ifb_u32 count, const IFBMathVec2* v2_a, const IFBMathVec2* v2_b, IFBMathVec2* v2_c);
    void vec2_a_sub_b (const ifb_u32 count, const IFBMathVec2* v2_a, const IFBMathVec2* v2_b, IFBMathVec2* v2_c);
    void vec2_a_dot_b (const ifb_u32 count, const IFBMathVec2* v2_a, const IFBMathVec2* v2_b, IFBMathVec2* v2_c);
};

#endif //IFB_MATH_VEC2_HPP