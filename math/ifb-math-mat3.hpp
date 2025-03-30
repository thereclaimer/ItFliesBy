#ifndef IFB_MATH_MAT3_HPP
#define IFB_MATH_MAT3_HPP

#include <math.h>

#include <ifb.hpp>

namespace ifb_math {

    void mat3_identity  (ifb::mat3_t& m3);

    void mat3_scale                  (ifb::mat3_t& m3,     const ifb::vec2_t& scale);
    void mat3_translate              (ifb::mat3_t& m3,     const ifb::vec2_t& translation);
    void mat3_rotate                 (ifb::mat3_t& m3,     const ifb::f32  radians);
    void mat3_translate_scale        (ifb::mat3_t& m3,     const ifb::vec2_t& translation, const ifb::vec2_t& scale);
    void mat3_translate_scale_rotate (ifb::mat3_t& m3,     const ifb::vec2_t& translation, const ifb::vec2_t& scale, const ifb::f32 radians);
    void mat3_reflect                (ifb::mat3_t& m3,     const ifb::vec2_t& axis);
    void mat3_involute               (ifb::mat3_t& m3,     const ifb::vec2_t& axis);
    void mat3_rotate                 (ifb::mat3_t& m3,     const ifb::vec2_t& axis, const ifb::f32  radians);
    void mat3_skew                   (ifb::mat3_t& m3,     const ifb::vec2_t& axis, const ifb::f32  radians);
    void mat3_a_mul_b                (ifb::mat3_t& m3_ab,  const ifb::mat3_t& m3_a, const ifb::mat3_t& m3_b);
    void mat3_determinant            (ifb::mat3_t& m3_det, const ifb::mat3_t& m3);
    void mat3_inverse                (ifb::mat3_t& m3_inv, const ifb::mat3_t& m3);
    void mat3_transform              (ifb::mat3_t& m3_trs, const IFBTransform& transform);

    void mat3_batch_identity         (ifb::mat3_t* m3,     const ifb::u32 count);
    void mat3_batch_scale            (ifb::mat3_t* m3,     const ifb::u32 count, const ifb::vec2_t* scale);
    void mat3_batch_translate        (ifb::mat3_t* m3,     const ifb::u32 count, const ifb::vec2_t* position);
    void mat3_batch_rotate           (ifb::mat3_t* m3,     const ifb::u32 count, const ifb::f32* radians);
    void mat3_batch_a_mul_b          (ifb::mat3_t* m3_ab,  const ifb::u32 count, const ifb::mat3_t* m3_a, const ifb::mat3_t* m3_b);
    void mat3_batch_determinant      (ifb::mat3_t* m3_det, const ifb::u32 count, const ifb::mat3_t* m3);
    void mat3_batch_inverse          (ifb::mat3_t* m3_inv, const ifb::u32 count, const ifb::mat3_t* m3);
    void mat3_batch_transform        (ifb::mat3_t* m3_trs, const ifb::u32 count, const IFBTransform* transform);
};

inline void 
ifb_math::mat3_identity(
    ifb::mat3_t& m3) {
    
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
          ifb::mat3_t& m3,
    const ifb::vec2_t& scale) {

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
          ifb::mat3_t& m3,
    const ifb::vec2_t& translation) {

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
          ifb::mat3_t& m3,
    const ifb::f32  radians) {

    const ifb::f32 cos_r = cosf(radians);
    const ifb::f32 sin_r = sinf(radians);

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
          ifb::mat3_t& m3, 
    const ifb::vec2_t& translation,
    const ifb::vec2_t& scale) {
    
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
ifb_math::mat3_translate_scale_rotate(
          ifb::mat3_t& m3, 
    const ifb::vec2_t& translation,
    const ifb::vec2_t& scale, 
    const ifb::f32  radians) {

    const ifb::f32 cos_r = cosf(radians);
    const ifb::f32 sin_r = sinf(radians);

    const ifb::f32 scale_x_cos_r = scale.x * cos_r;
    const ifb::f32 scale_y_sin_r = scale.y * sin_r; 
    const ifb::f32 scale_x_sin_r = scale.x * sin_r;
    const ifb::f32 scale_y_cos_r = scale.y * cos_r;

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
          ifb::mat3_t&      m3_trs,
    const IFBTransform& transform) {

    ifb_math::mat3_translate_scale_rotate(
        m3_trs,
        transform.translation,
        transform.scale,
        transform.rotation_radians);
}

inline void 
ifb_math::mat3_batch_transform(
          ifb::mat3_t*      m3_trs,
    const ifb::u32       count,
    const IFBTransform* transform) {

    for (
        ifb::u32 index = 0;
        index < count;
        ++index) {

        const IFBTransform& transform_ref = transform[index];

        // ifb_math::mat3_transform(
        //     m3_trs[index],
        //     transform_ref.translation,
        //     transform_ref.scale,
        //     transform_ref.rotation_radians);
    }

}



#endif //IFB_MATH_MAT3_HPP