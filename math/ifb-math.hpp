#ifndef IFB_MATH_HPP
#define IFB_MATH_HPP

typedef struct IFBMathVec2;
typedef struct IFBMathMat3;

typedef IFBMathVec2 ifb_vec_2_t;
typedef IFBMathMat3 ifb_mat_3_t;


namespace ifb_math {

    vec_2_add(ifb_vec_2_t& vec_2_a_ref, ifb_vec_2_t& vec_2_b_ref, ifb_vec_2_t& out_vec_2_c_ref);

};

#endif //IFB_MATH_HPP