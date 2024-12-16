#ifndef IFB_MATH_VEC2_HPP
#define IFB_MATH_VEC2_HPP

#include <ifb.hpp>

#include "ifb-math-types.hpp"

namespace ifb_math {

    ifb_void vec2_a_add_b           (const ifb_v2* v2_a, const ifb_v2* v2_b, ifb_v2* v2_c);
    ifb_void vec2_a_sub_b           (const ifb_v2* v2_a, const ifb_v2* v2_b, ifb_v2* v2_c);
    ifb_void vec2_a_dot_b           (const ifb_v2* v2_a, const ifb_v2* v2_b, ifb_v2* v2_c);
    ifb_void vec2_a_project_b       (const ifb_v2* v2_a, const ifb_v2* v2_b, ifb_v2* v2_c);
    ifb_void vec2_a_reject_b        (const ifb_v2* v2_a, const ifb_v2* v2_b, ifb_v2* v2_c);

    ifb_void vec2_scalar            (const ifb_v2* v2, const ifb_f32* scalar, ifb_v2* v2_scalar);

    ifb_void vec2_magnitude         (const ifb_v2* v2, ifb_f32* v2_magnitude);
    ifb_void vec2_normalize         (const ifb_v2* v2, ifb_v2*  v2_normalized);

    ifb_void vec2_transform         (const ifb_v2* v2, const ifb_m3* m3, ifb_v2* v2_transform)

    ifb_void vec2_batch_a_add_b     (const ifb_u32 count, const ifb_v2* v2_a, const ifb_v2* v2_b, ifb_v2* v2_c);
    ifb_void vec2_batch_a_sub_b     (const ifb_u32 count, const ifb_v2* v2_a, const ifb_v2* v2_b, ifb_v2* v2_c);
    ifb_void vec2_batch_a_dot_b     (const ifb_u32 count, const ifb_v2* v2_a, const ifb_v2* v2_b, ifb_v2* v2_c);
    ifb_void vec2_batch_a_project_b (const ifb_u32 count, const ifb_v2* v2_a, const ifb_v2* v2_b, ifb_v2* v2_c);
    ifb_void vec2_batch_a_reject_b  (const ifb_u32 count, const ifb_v2* v2_a, const ifb_v2* v2_b, ifb_v2* v2_c);

    ifb_void vec2_batch_scalar      (const ifb_u32 count, const ifb_v2* v2, const ifb_f32* scalar, ifb_v2* v2_scalar);

    ifb_void vec2_batch_magnitude   (const ifb_u32 count, const ifb_v2* v2, ifb_f32* v2_magnitude);
    ifb_void vec2_batch_normalize   (const ifb_u32 count, const ifb_v2* v2, ifb_v2*  v2_normalized);
    
    ifb_void vec2_batch_transform    (const ifb_u32 count, const ifb_v2* v2, const ifb_m3* m3, ifb_v2* v2_transform)


};

#endif //IFB_MATH_VEC2_HPP