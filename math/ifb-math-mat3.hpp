#ifndef IFB_MATH_MAT3_HPP
#define IFB_MATH_MAT3_HPP

#include <ifb.hpp>
#include "ifb-math-types.hpp"

namespace ifb_math {

    void mat3_identity          (ifb_m3* m3);

    void mat3_scale             (const ifb_v3* scale,    ifb_m3* m3);
    void mat3_translate         (const ifb_v3* position, ifb_m3* m3);
    void mat3_reflect           (const ifb_v3* axis,     ifb_m3* m3);
    void mat3_involute          (const ifb_v3* axis,     ifb_m3* m3);

    void mat3_rotate            (const ifb_v3* axis, const ifb_f32 angle, ifb_m3* m3);
    void mat3_skew              (const ifb_v3* axis, const ifb_f32 angle, ifb_m3* m3);

    void mat3_a_mul_b           (const ifb_m3* m3_a, const ifb_m3* m3_b, ifb_m3* m3_c);
    
    void mat3_determinant       (const ifb_m3* m3, ifb_m3* m3_determinant);
    void mat3_inverse           (const ifb_m3* m3, ifb_m3* m3_inverse);

    void mat3_batch_identity    (const ifb_u32 count, ifb_m3* m3);

    void mat3_batch_scale       (const ifb_u32 count, const ifb_f32* scale,    ifb_m3* m3);
    void mat3_batch_translate   (const ifb_u32 count, const ifb_v3*  position, ifb_m3* m3);
    void mat3_batch_rotate      (const ifb_u32 count, const ifb_v3*  axis,     ifb_m3* m3);

    void mat3_batch_a_mul_b     (const ifb_u32 count, const ifb_m3* m3_a, const ifb_m3* m3_b, ifb_m3* m3_c);
    
    void mat3_batch_determinant (const ifb_u32 count, const ifb_m3* m3, ifb_m3* m3_determinant);
    void mat3_batch_inverse     (const ifb_u32 count, const ifb_m3* m3, ifb_m3* m3_inverse);
};

#endif //IFB_MATH_MAT3_HPP