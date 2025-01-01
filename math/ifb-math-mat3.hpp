#ifndef IFB_MATH_MAT3_HPP
#define IFB_MATH_MAT3_HPP

#include <math.h>

#include <ifb.hpp>
#include "ifb-math-types.hpp"

namespace ifb_math {

    void mat3_identity  (IFBMat3& m3);

    void mat3_scale                  (IFBMat3& m3,     const IFBVec2& scale);
    void mat3_translate              (IFBMat3& m3,     const IFBVec2& translation);
    void mat3_rotate                 (IFBMat3& m3,     const ifb_f32  radians);
    void mat3_translate_scale        (IFBMat3& m3,     const IFBVec2& translation, const IFBVec2& scale);
    void mat3_translate_scale_rotate (IFBMat3& m3,     const IFBVec2& translation, const IFBVec2& scale, const ifb_f32 radians);
    void mat3_reflect                (IFBMat3& m3,     const IFBVec2& axis);
    void mat3_involute               (IFBMat3& m3,     const IFBVec2& axis);
    void mat3_rotate                 (IFBMat3& m3,     const IFBVec2& axis, const ifb_f32  radians);
    void mat3_skew                   (IFBMat3& m3,     const IFBVec2& axis, const ifb_f32  radians);
    void mat3_a_mul_b                (IFBMat3& m3_ab,  const IFBMat3& m3_a, const IFBMat3& m3_b);
    void mat3_determinant            (IFBMat3& m3_det, const IFBMat3& m3);
    void mat3_inverse                (IFBMat3& m3_inv, const IFBMat3& m3);
    void mat3_transform              (IFBMat3& m3_trs, const IFBTransform& transform);

    void mat3_batch_identity         (IFBMat3* m3,     const ifb_u32 count);
    void mat3_batch_scale            (IFBMat3* m3,     const ifb_u32 count, const IFBVec2* scale);
    void mat3_batch_translate        (IFBMat3* m3,     const ifb_u32 count, const IFBVec2* position);
    void mat3_batch_rotate           (IFBMat3* m3,     const ifb_u32 count, const ifb_f32* radians);
    void mat3_batch_a_mul_b          (IFBMat3* m3_ab,  const ifb_u32 count, const IFBMat3* m3_a, const IFBMat3* m3_b);
    void mat3_batch_determinant      (IFBMat3* m3_det, const ifb_u32 count, const IFBMat3* m3);
    void mat3_batch_inverse          (IFBMat3* m3_inv, const ifb_u32 count, const IFBMat3* m3);
};

inline void 
ifb_math::mat3_identity(
    IFBMat3& m3) {
    
    m3.r0c0 = 1;   
    m3.r0c1 = 0; 
    m3.r0c2 = 0; 
    m3.r1c0 = 0; 
    m3.r1c1 = 1; 
    m3.r1c2 = 0; 
    m3.r2c0 = 0; 
    m3.r2c1 = 0; 
    m3.r2c2 = 1; 
}

inline void 
ifb_math::mat3_scale(
          IFBMat3& m3,
    const IFBVec2& scale) {

    m3.r0c0 = scale.x; 
    m3.r0c1 = 0; 
    m3.r0c2 = 0; 
    m3.r1c0 = 0; 
    m3.r1c1 = scale.y; 
    m3.r1c2 = 0; 
    m3.r2c0 = 0; 
    m3.r2c1 = 0; 
    m3.r2c2 = 1; 

}

inline void
ifb_math::mat3_translate(
          IFBMat3& m3,
    const IFBVec2& translation) {

    m3.r0c0 = 1; 
    m3.r0c1 = 0; 
    m3.r0c2 = translation.x; 
    m3.r1c0 = 0; 
    m3.r1c1 = 1; 
    m3.r1c2 = translation.y; 
    m3.r2c0 = 0; 
    m3.r2c1 = 0; 
    m3.r2c2 = 1; 
}

inline void
ifb_math::mat3_rotate(
          IFBMat3& m3,
    const ifb_f32  radians) {

    const ifb_f32 cos_r = cosf(radians);
    const ifb_f32 sin_r = sinf(radians);

    m3.r0c0 = cos_r;   
    m3.r0c1 = sin_r * -1; 
    m3.r0c2 = sin_r; 
    m3.r1c0 = cos_r; 
    m3.r1c1 = 1;
    m3.r1c2 = 0;
    m3.r2c0 = 0;
    m3.r2c1 = 0;
    m3.r2c2 = 1;
}


inline void 
ifb_math::mat3_translate_scale(
          IFBMat3& m3, 
    const IFBVec2& translation,
    const IFBVec2& scale) {
    
    m3.r0c0 = scale.x; 
    m3.r0c1 = 0; 
    m3.r0c2 = translation.x; 
    m3.r1c0 = 0; 
    m3.r1c1 = scale.y; 
    m3.r1c2 = translation.y; 
    m3.r2c0 = 0; 
    m3.r2c1 = 0; 
    m3.r2c2 = 1; 
}

inline void
ifb_engine::mat3_translate_scale_rotate(
          IFBMat3& m3, 
    const IFBVec2& translation,
    const IFBVec2& scale, 
    const ifb_f32  radians) {

    const ifb_f32 cos_r = cosf(radians);
    const ifb_f32 sin_r = sinf(radians);

    const ifb_f32 scale_x_cos_r = scale.x * cos_r;
    const ifb_f32 scale_y_sin_r = scale.y * sin_r; 
    const ifb_f32 scale_x_sin_r = scale.x * sin_r;
    const ifb_f32 scale_y_cos_r = scale.y * cos_r;

    m3.r0c0 = scale_x_cos_r; 
    m3.r0c1 = scale_y_sin_r * -1; 
    m3.r0c2 = translation.x; 
    m3.r1c0 = scale_x_sin_r; 
    m3.r1c1 = scale_y_cos_r; 
    m3.r1c2 = translation.y; 
    m3.r2c0 = 0; 
    m3.r2c1 = 0;
    m3.r2c2 = 1; 
}

inline void 
ifb_math::mat3_transform(
          IFBMat3&      m3_trs,
    const IFBTransform& transform) {

    ifb_math::mat3_translate_scale_rotate(
        m3_trs,
        transform.translation,
        transform.scale,
        transform.rotation_radians);
}


#endif //IFB_MATH_MAT3_HPP