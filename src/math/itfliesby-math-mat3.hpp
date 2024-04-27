#ifndef ITFLIESBY_MATH_MAT3_HPP
#define ITFLIESBY_MATH_MAT3_HPP

#include <common/itfliesby-types.hpp>

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

#endif //ITFLIESBY_MATH_MAT3_HPP