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

#endif //ITFLIESBY_MATH_MAT3_HPP