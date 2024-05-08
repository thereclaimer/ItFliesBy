#ifndef ITFLIESBY_MATH_MAT3_HPP
#define ITFLIESBY_MATH_MAT3_HPP

#include <common/itfliesby-types.hpp>
#include "itfliesby-math-trig.hpp"

struct ItfliesbyMathMat3 {
    
    union {
        
        f32 m[9];
    
        f32 row_col[3][3];   

        struct {
            f32 row_0[3];
            f32 row_1[3];
            f32 row_2[3];
        } rows;

    };
};

inline ItfliesbyMathMat3 
itfliesby_math_mat3_identity() {

    ItfliesbyMathMat3 m3 = {0};

    m3.rows.row_0[0] = 1.0f;
    m3.rows.row_0[1] = 0.0f;
    m3.rows.row_0[2] = 0.0f;

    m3.rows.row_1[0] = 0.0f;
    m3.rows.row_1[1] = 1.0f;
    m3.rows.row_1[2] = 0.0f;

    m3.rows.row_2[0] = 0.0f;
    m3.rows.row_2[1] = 0.0f;
    m3.rows.row_2[2] = 1.0f;

    return(m3);
}

inline void
itfliesby_math_mat3_transpose(
    ItfliesbyMathMat3* in_m3,
    ItfliesbyMathMat3* out_m3) {

    f32* in_m3_m  = in_m3->m;
    f32* out_m3_m = out_m3->m;

    out_m3_m[0] = in_m3_m[0]; 
    out_m3_m[1] = in_m3_m[3]; 
    out_m3_m[2] = in_m3_m[6];
    out_m3_m[3] = in_m3_m[1]; 
    out_m3_m[4] = in_m3_m[4]; 
    out_m3_m[5] = in_m3_m[7];
    out_m3_m[6] = in_m3_m[2]; 
    out_m3_m[7] = in_m3_m[5]; 
    out_m3_m[8] = in_m3_m[8];
}

inline ItfliesbyMathMat3
itfliesby_math_mat3_translation(
    f32 x,
    f32 y) {

    ItfliesbyMathMat3 m3 = itfliesby_math_mat3_identity();

    m3.rows.row_0[2] = x;
    m3.rows.row_1[2] = y;

    return(m3);
}

inline ItfliesbyMathMat3
itfliesby_math_mat3_scaling(
    f32 x,
    f32 y) {

    ItfliesbyMathMat3 m3 = itfliesby_math_mat3_identity();

    m3.rows.row_0[0] = x;
    m3.rows.row_1[1] = y;

    return(m3);
}

inline ItfliesbyMathMat3
itfliesby_math_mat3_rotation_degrees(
    f32 degrees) {

    f32 radians = itfliesby_math_trig_degrees_to_radians(degrees);

    f32 cos_r = cosf(radians);
    f32 sin_r = sinf(radians);
    
    ItfliesbyMathMat3 m3 = itfliesby_math_mat3_identity();

    m3.rows.row_0[0] = cos_r;
    m3.rows.row_0[1] = -(sin_r);

    m3.rows.row_1[0] = sin_r;
    m3.rows.row_1[1] = cos_r;

    return(m3);
}

inline ItfliesbyMathMat3
itfliesby_math_mat3_rotation_radians(
    f32 radians) {

    f32 cos_r = cosf(radians);
    f32 sin_r = sinf(radians);
    
    ItfliesbyMathMat3 m3 = itfliesby_math_mat3_identity();

    m3.rows.row_0[0] = cos_r;
    m3.rows.row_0[1] = -(sin_r);

    m3.rows.row_1[0] = sin_r;
    m3.rows.row_1[1] = cos_r;

    return(m3);
}

//scale,rotate,translate
inline void
itfliesby_math_mat3_transform_srt(
    size_t             transform_count,
    ItfliesbyMathMat3* in_transform_translate, 
    ItfliesbyMathMat3* in_transform_scale,
    ItfliesbyMathMat3* in_transform_rotate,
    ItfliesbyMathMat3* out_transform) {

    ItfliesbyMathMat3 a = {0};
    ItfliesbyMathMat3 b = {0};
    ItfliesbyMathMat3 c = {0};
    ItfliesbyMathMat3 transform = {0};
    ItfliesbyMathMat3 temp      = {0};

    for (
        size_t transform_index = 0;
        transform_index < transform_count;
        ++transform_index) {

        a = in_transform_scale[transform_index];
        b = in_transform_rotate[transform_index];
        c = in_transform_translate[transform_index];

        temp.rows.row_0[0] = (a.rows.row_0[0] * b.rows.row_0[0]) + (a.rows.row_0[1] * b.rows.row_1[0]) + (a.rows.row_0[2] * b.rows.row_2[0]); 
        temp.rows.row_0[1] = (a.rows.row_0[0] * b.rows.row_0[1]) + (a.rows.row_0[1] * b.rows.row_1[1]) + (a.rows.row_0[2] * b.rows.row_2[1]);
        temp.rows.row_0[2] = (a.rows.row_0[0] * b.rows.row_0[2]) + (a.rows.row_0[1] * b.rows.row_1[2]) + (a.rows.row_0[2] * b.rows.row_2[2]);

        temp.rows.row_1[0] = (a.rows.row_1[0] * b.rows.row_0[0]) + (a.rows.row_1[1] * b.rows.row_1[0]) + (a.rows.row_1[2] * b.rows.row_2[0]);
        temp.rows.row_1[1] = (a.rows.row_1[0] * b.rows.row_0[1]) + (a.rows.row_1[1] * b.rows.row_1[1]) + (a.rows.row_1[2] * b.rows.row_2[1]);
        temp.rows.row_1[2] = (a.rows.row_1[0] * b.rows.row_0[2]) + (a.rows.row_1[1] * b.rows.row_1[2]) + (a.rows.row_1[2] * b.rows.row_2[2]);

        temp.rows.row_2[0] = (a.rows.row_2[0] * b.rows.row_0[0]) + (a.rows.row_2[1] * b.rows.row_1[0]) + (a.rows.row_2[2] * b.rows.row_2[0]);
        temp.rows.row_2[1] = (a.rows.row_2[0] * b.rows.row_0[1]) + (a.rows.row_2[1] * b.rows.row_1[1]) + (a.rows.row_2[2] * b.rows.row_2[1]);
        temp.rows.row_2[2] = (a.rows.row_2[0] * b.rows.row_0[2]) + (a.rows.row_2[1] * b.rows.row_1[2]) + (a.rows.row_2[2] * b.rows.row_2[2]);

        transform.rows.row_0[0] = (temp.rows.row_0[0] * c.rows.row_0[0]) + (temp.rows.row_0[1] * c.rows.row_1[0]) + (temp.rows.row_0[2] * c.rows.row_2[0]); 
        transform.rows.row_0[1] = (temp.rows.row_0[0] * c.rows.row_0[1]) + (temp.rows.row_0[1] * c.rows.row_1[1]) + (temp.rows.row_0[2] * c.rows.row_2[1]);
        transform.rows.row_0[2] = (temp.rows.row_0[0] * c.rows.row_0[2]) + (temp.rows.row_0[1] * c.rows.row_1[2]) + (temp.rows.row_0[2] * c.rows.row_2[2]);
        
        transform.rows.row_1[0] = (temp.rows.row_1[0] * c.rows.row_0[0]) + (temp.rows.row_1[1] * c.rows.row_1[0]) + (temp.rows.row_1[2] * c.rows.row_2[0]);
        transform.rows.row_1[1] = (temp.rows.row_1[0] * c.rows.row_0[1]) + (temp.rows.row_1[1] * c.rows.row_1[1]) + (temp.rows.row_1[2] * c.rows.row_2[1]);
        transform.rows.row_1[2] = (temp.rows.row_1[0] * c.rows.row_0[2]) + (temp.rows.row_1[1] * c.rows.row_1[2]) + (temp.rows.row_1[2] * c.rows.row_2[2]);
        
        transform.rows.row_2[0] = (temp.rows.row_2[0] * c.rows.row_0[0]) + (temp.rows.row_2[1] * c.rows.row_1[0]) + (temp.rows.row_2[2] * c.rows.row_2[0]);
        transform.rows.row_2[1] = (temp.rows.row_2[0] * c.rows.row_0[1]) + (temp.rows.row_2[1] * c.rows.row_1[1]) + (temp.rows.row_2[2] * c.rows.row_2[1]);
        transform.rows.row_2[2] = (temp.rows.row_2[0] * c.rows.row_0[2]) + (temp.rows.row_2[1] * c.rows.row_1[2]) + (temp.rows.row_2[2] * c.rows.row_2[2]);

        out_transform[transform_index] = transform;
    }
}

//scale,rotate,translate,transpose
inline void
itfliesby_math_mat3_transform_and_transpose_srt(
    const size_t             transform_count,
    const ItfliesbyMathMat3* in_transform_translate, 
    const ItfliesbyMathMat3* in_transform_scale,
    const ItfliesbyMathMat3* in_transform_rotate,
          ItfliesbyMathMat3* out_transform) {

    ItfliesbyMathMat3 transform = {0};
    ItfliesbyMathMat3 transpose = {0};
    ItfliesbyMathMat3 temp      = {0};
    ItfliesbyMathMat3 a         = {0};
    ItfliesbyMathMat3 b         = {0};
    ItfliesbyMathMat3 c         = {0};

    for (
        size_t transform_index = 0;
        transform_index < transform_count;
        ++transform_index) {

        a = in_transform_scale[transform_index];
        b = in_transform_rotate[transform_index];
        c = in_transform_translate[transform_index];

        temp.rows.row_0[0] = (a.rows.row_0[0] * b.rows.row_0[0]) + (a.rows.row_0[1] * b.rows.row_1[0]) + (a.rows.row_0[2] * b.rows.row_2[0]); 
        temp.rows.row_0[1] = (a.rows.row_0[0] * b.rows.row_0[1]) + (a.rows.row_0[1] * b.rows.row_1[1]) + (a.rows.row_0[2] * b.rows.row_2[1]);
        temp.rows.row_0[2] = (a.rows.row_0[0] * b.rows.row_0[2]) + (a.rows.row_0[1] * b.rows.row_1[2]) + (a.rows.row_0[2] * b.rows.row_2[2]);

        temp.rows.row_1[0] = (a.rows.row_1[0] * b.rows.row_0[0]) + (a.rows.row_1[1] * b.rows.row_1[0]) + (a.rows.row_1[2] * b.rows.row_2[0]);
        temp.rows.row_1[1] = (a.rows.row_1[0] * b.rows.row_0[1]) + (a.rows.row_1[1] * b.rows.row_1[1]) + (a.rows.row_1[2] * b.rows.row_2[1]);
        temp.rows.row_1[2] = (a.rows.row_1[0] * b.rows.row_0[2]) + (a.rows.row_1[1] * b.rows.row_1[2]) + (a.rows.row_1[2] * b.rows.row_2[2]);

        temp.rows.row_2[0] = (a.rows.row_2[0] * b.rows.row_0[0]) + (a.rows.row_2[1] * b.rows.row_1[0]) + (a.rows.row_2[2] * b.rows.row_2[0]);
        temp.rows.row_2[1] = (a.rows.row_2[0] * b.rows.row_0[1]) + (a.rows.row_2[1] * b.rows.row_1[1]) + (a.rows.row_2[2] * b.rows.row_2[1]);
        temp.rows.row_2[2] = (a.rows.row_2[0] * b.rows.row_0[2]) + (a.rows.row_2[1] * b.rows.row_1[2]) + (a.rows.row_2[2] * b.rows.row_2[2]);

        transform.rows.row_0[0] = (temp.rows.row_0[0] * c.rows.row_0[0]) + (temp.rows.row_0[1] * c.rows.row_1[0]) + (temp.rows.row_0[2] * c.rows.row_2[0]); 
        transform.rows.row_0[1] = (temp.rows.row_0[0] * c.rows.row_0[1]) + (temp.rows.row_0[1] * c.rows.row_1[1]) + (temp.rows.row_0[2] * c.rows.row_2[1]);
        transform.rows.row_0[2] = (temp.rows.row_0[0] * c.rows.row_0[2]) + (temp.rows.row_0[1] * c.rows.row_1[2]) + (temp.rows.row_0[2] * c.rows.row_2[2]);
        
        transform.rows.row_1[0] = (temp.rows.row_1[0] * c.rows.row_0[0]) + (temp.rows.row_1[1] * c.rows.row_1[0]) + (temp.rows.row_1[2] * c.rows.row_2[0]);
        transform.rows.row_1[1] = (temp.rows.row_1[0] * c.rows.row_0[1]) + (temp.rows.row_1[1] * c.rows.row_1[1]) + (temp.rows.row_1[2] * c.rows.row_2[1]);
        transform.rows.row_1[2] = (temp.rows.row_1[0] * c.rows.row_0[2]) + (temp.rows.row_1[1] * c.rows.row_1[2]) + (temp.rows.row_1[2] * c.rows.row_2[2]);
        
        transform.rows.row_2[0] = (temp.rows.row_2[0] * c.rows.row_0[0]) + (temp.rows.row_2[1] * c.rows.row_1[0]) + (temp.rows.row_2[2] * c.rows.row_2[0]);
        transform.rows.row_2[1] = (temp.rows.row_2[0] * c.rows.row_0[1]) + (temp.rows.row_2[1] * c.rows.row_1[1]) + (temp.rows.row_2[2] * c.rows.row_2[1]);
        transform.rows.row_2[2] = (temp.rows.row_2[0] * c.rows.row_0[2]) + (temp.rows.row_2[1] * c.rows.row_1[2]) + (temp.rows.row_2[2] * c.rows.row_2[2]);

        itfliesby_math_mat3_transpose(
            &transform,
            &transpose);

        out_transform[transform_index] = transform;
    }
}

//translate,rotate,scale
inline void
itfliesby_math_mat3_transform_trs(
    const size_t             transform_count,
    const ItfliesbyMathMat3* in_transform_translate, 
    const ItfliesbyMathMat3* in_transform_scale,
    const ItfliesbyMathMat3* in_transform_rotate,
          ItfliesbyMathMat3* out_transform) {

    ItfliesbyMathMat3 a = {0};
    ItfliesbyMathMat3 b = {0};
    ItfliesbyMathMat3 c = {0};
    ItfliesbyMathMat3 transform = {0};
    ItfliesbyMathMat3 temp      = {0};

    for (
        size_t transform_index = 0;
        transform_index < transform_count;
        ++transform_index) {

        a = in_transform_translate[transform_index];
        b = in_transform_rotate[transform_index];
        c = in_transform_scale[transform_index];

        temp.rows.row_0[0] = (a.rows.row_0[0] * b.rows.row_0[0]) + (a.rows.row_0[1] * b.rows.row_1[0]) + (a.rows.row_0[2] * b.rows.row_2[0]); 
        temp.rows.row_0[1] = (a.rows.row_0[0] * b.rows.row_0[1]) + (a.rows.row_0[1] * b.rows.row_1[1]) + (a.rows.row_0[2] * b.rows.row_2[1]);
        temp.rows.row_0[2] = (a.rows.row_0[0] * b.rows.row_0[2]) + (a.rows.row_0[1] * b.rows.row_1[2]) + (a.rows.row_0[2] * b.rows.row_2[2]);

        temp.rows.row_1[0] = (a.rows.row_1[0] * b.rows.row_0[0]) + (a.rows.row_1[1] * b.rows.row_1[0]) + (a.rows.row_1[2] * b.rows.row_2[0]);
        temp.rows.row_1[1] = (a.rows.row_1[0] * b.rows.row_0[1]) + (a.rows.row_1[1] * b.rows.row_1[1]) + (a.rows.row_1[2] * b.rows.row_2[1]);
        temp.rows.row_1[2] = (a.rows.row_1[0] * b.rows.row_0[2]) + (a.rows.row_1[1] * b.rows.row_1[2]) + (a.rows.row_1[2] * b.rows.row_2[2]);

        temp.rows.row_2[0] = (a.rows.row_2[0] * b.rows.row_0[0]) + (a.rows.row_2[1] * b.rows.row_1[0]) + (a.rows.row_2[2] * b.rows.row_2[0]);
        temp.rows.row_2[1] = (a.rows.row_2[0] * b.rows.row_0[1]) + (a.rows.row_2[1] * b.rows.row_1[1]) + (a.rows.row_2[2] * b.rows.row_2[1]);
        temp.rows.row_2[2] = (a.rows.row_2[0] * b.rows.row_0[2]) + (a.rows.row_2[1] * b.rows.row_1[2]) + (a.rows.row_2[2] * b.rows.row_2[2]);

        transform.rows.row_0[0] = (temp.rows.row_0[0] * c.rows.row_0[0]) + (temp.rows.row_0[1] * c.rows.row_1[0]) + (temp.rows.row_0[2] * c.rows.row_2[0]); 
        transform.rows.row_0[1] = (temp.rows.row_0[0] * c.rows.row_0[1]) + (temp.rows.row_0[1] * c.rows.row_1[1]) + (temp.rows.row_0[2] * c.rows.row_2[1]);
        transform.rows.row_0[2] = (temp.rows.row_0[0] * c.rows.row_0[2]) + (temp.rows.row_0[1] * c.rows.row_1[2]) + (temp.rows.row_0[2] * c.rows.row_2[2]);
        
        transform.rows.row_1[0] = (temp.rows.row_1[0] * c.rows.row_0[0]) + (temp.rows.row_1[1] * c.rows.row_1[0]) + (temp.rows.row_1[2] * c.rows.row_2[0]);
        transform.rows.row_1[1] = (temp.rows.row_1[0] * c.rows.row_0[1]) + (temp.rows.row_1[1] * c.rows.row_1[1]) + (temp.rows.row_1[2] * c.rows.row_2[1]);
        transform.rows.row_1[2] = (temp.rows.row_1[0] * c.rows.row_0[2]) + (temp.rows.row_1[1] * c.rows.row_1[2]) + (temp.rows.row_1[2] * c.rows.row_2[2]);
        
        transform.rows.row_2[0] = (temp.rows.row_2[0] * c.rows.row_0[0]) + (temp.rows.row_2[1] * c.rows.row_1[0]) + (temp.rows.row_2[2] * c.rows.row_2[0]);
        transform.rows.row_2[1] = (temp.rows.row_2[0] * c.rows.row_0[1]) + (temp.rows.row_2[1] * c.rows.row_1[1]) + (temp.rows.row_2[2] * c.rows.row_2[1]);
        transform.rows.row_2[2] = (temp.rows.row_2[0] * c.rows.row_0[2]) + (temp.rows.row_2[1] * c.rows.row_1[2]) + (temp.rows.row_2[2] * c.rows.row_2[2]);

        out_transform[transform_index] = transform;
    }
}

//translate,rotate,scale,transpose
inline void
itfliesby_math_mat3_transform_and_transpose_trs(
    const size_t             transform_count,
    const ItfliesbyMathMat3* in_transform_translate, 
    const ItfliesbyMathMat3* in_transform_scale,
    const ItfliesbyMathMat3* in_transform_rotate,
          ItfliesbyMathMat3* out_transform) {

    ItfliesbyMathMat3 a         = {0};
    ItfliesbyMathMat3 b         = {0};
    ItfliesbyMathMat3 c         = {0};
    ItfliesbyMathMat3 transform = {0};
    ItfliesbyMathMat3 transpose = {0};
    ItfliesbyMathMat3 temp      = {0};

    for (
        size_t transform_index = 0;
        transform_index < transform_count;
        ++transform_index) {

        a = in_transform_translate[transform_index];
        b = in_transform_rotate[transform_index];
        c = in_transform_scale[transform_index];

        temp.rows.row_0[0] = (a.rows.row_0[0] * b.rows.row_0[0]) + (a.rows.row_0[1] * b.rows.row_1[0]) + (a.rows.row_0[2] * b.rows.row_2[0]); 
        temp.rows.row_0[1] = (a.rows.row_0[0] * b.rows.row_0[1]) + (a.rows.row_0[1] * b.rows.row_1[1]) + (a.rows.row_0[2] * b.rows.row_2[1]);
        temp.rows.row_0[2] = (a.rows.row_0[0] * b.rows.row_0[2]) + (a.rows.row_0[1] * b.rows.row_1[2]) + (a.rows.row_0[2] * b.rows.row_2[2]);

        temp.rows.row_1[0] = (a.rows.row_1[0] * b.rows.row_0[0]) + (a.rows.row_1[1] * b.rows.row_1[0]) + (a.rows.row_1[2] * b.rows.row_2[0]);
        temp.rows.row_1[1] = (a.rows.row_1[0] * b.rows.row_0[1]) + (a.rows.row_1[1] * b.rows.row_1[1]) + (a.rows.row_1[2] * b.rows.row_2[1]);
        temp.rows.row_1[2] = (a.rows.row_1[0] * b.rows.row_0[2]) + (a.rows.row_1[1] * b.rows.row_1[2]) + (a.rows.row_1[2] * b.rows.row_2[2]);

        temp.rows.row_2[0] = (a.rows.row_2[0] * b.rows.row_0[0]) + (a.rows.row_2[1] * b.rows.row_1[0]) + (a.rows.row_2[2] * b.rows.row_2[0]);
        temp.rows.row_2[1] = (a.rows.row_2[0] * b.rows.row_0[1]) + (a.rows.row_2[1] * b.rows.row_1[1]) + (a.rows.row_2[2] * b.rows.row_2[1]);
        temp.rows.row_2[2] = (a.rows.row_2[0] * b.rows.row_0[2]) + (a.rows.row_2[1] * b.rows.row_1[2]) + (a.rows.row_2[2] * b.rows.row_2[2]);

        transform.rows.row_0[0] = (temp.rows.row_0[0] * c.rows.row_0[0]) + (temp.rows.row_0[1] * c.rows.row_1[0]) + (temp.rows.row_0[2] * c.rows.row_2[0]); 
        transform.rows.row_0[1] = (temp.rows.row_0[0] * c.rows.row_0[1]) + (temp.rows.row_0[1] * c.rows.row_1[1]) + (temp.rows.row_0[2] * c.rows.row_2[1]);
        transform.rows.row_0[2] = (temp.rows.row_0[0] * c.rows.row_0[2]) + (temp.rows.row_0[1] * c.rows.row_1[2]) + (temp.rows.row_0[2] * c.rows.row_2[2]);
        
        transform.rows.row_1[0] = (temp.rows.row_1[0] * c.rows.row_0[0]) + (temp.rows.row_1[1] * c.rows.row_1[0]) + (temp.rows.row_1[2] * c.rows.row_2[0]);
        transform.rows.row_1[1] = (temp.rows.row_1[0] * c.rows.row_0[1]) + (temp.rows.row_1[1] * c.rows.row_1[1]) + (temp.rows.row_1[2] * c.rows.row_2[1]);
        transform.rows.row_1[2] = (temp.rows.row_1[0] * c.rows.row_0[2]) + (temp.rows.row_1[1] * c.rows.row_1[2]) + (temp.rows.row_1[2] * c.rows.row_2[2]);
        
        transform.rows.row_2[0] = (temp.rows.row_2[0] * c.rows.row_0[0]) + (temp.rows.row_2[1] * c.rows.row_1[0]) + (temp.rows.row_2[2] * c.rows.row_2[0]);
        transform.rows.row_2[1] = (temp.rows.row_2[0] * c.rows.row_0[1]) + (temp.rows.row_2[1] * c.rows.row_1[1]) + (temp.rows.row_2[2] * c.rows.row_2[1]);
        transform.rows.row_2[2] = (temp.rows.row_2[0] * c.rows.row_0[2]) + (temp.rows.row_2[1] * c.rows.row_1[2]) + (temp.rows.row_2[2] * c.rows.row_2[2]);

        itfliesby_math_mat3_transpose(
            &transform,
            &transpose);

        out_transform[transform_index] = transpose;
    }
}

#endif //ITFLIESBY_MATH_MAT3_HPP