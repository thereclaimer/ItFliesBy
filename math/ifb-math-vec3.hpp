#ifndef IFB_MATH_VEC3_HPP
#define IFB_MATH_VEC3_HPP

#include <ifb.hpp>

namespace ifb_math {

    //----------------------
    // instance operations
    //----------------------

    void vec3_a_add_b           (const ifb::vec3_t& v3_a, const ifb::vec3_t& v3_b, ifb::vec3_t& v3_c);
    void vec3_a_sub_b           (const ifb::vec3_t& v3_a, const ifb::vec3_t& v3_b, ifb::vec3_t& v3_c);
    void vec3_a_dot_b           (const ifb::vec3_t& v3_a, const ifb::vec3_t& v3_b, ifb::vec3_t& v3_c);
    void vec3_a_cross_b         (const ifb::vec3_t& v3_a, const ifb::vec3_t& v3_b, ifb::vec3_t& v3_c);
    void vec3_a_project_b       (const ifb::vec3_t& v3_a, const ifb::vec3_t& v3_b, ifb::vec3_t& v3_c);
    void vec3_a_reject_b        (const ifb::vec3_t& v3_a, const ifb::vec3_t& v3_b, ifb::vec3_t& v3_c);

    void vec3_scalar            (const ifb::vec3_t& v3, const ifb::f32 scalar, ifb::vec3_t& v3_scalar);

    void vec3_magnitude         (const ifb::vec3_t& v3, ifb::f32& v3_magnitude);
    void vec3_normalize         (const ifb::vec3_t& v3, ifb::vec3_t& v3_normalized);

    //----------------------
    // batch operations
    //----------------------

    void vec3_batch_a_add_b     (const ifb::u32 count, const ifb::vec3_t* v3_a, const ifb::vec3_t* v3_b, ifb::vec3_t* v3_c);
    void vec3_batch_a_sub_b     (const ifb::u32 count, const ifb::vec3_t* v3_a, const ifb::vec3_t* v3_b, ifb::vec3_t* v3_c);
    void vec3_batch_a_dot_b     (const ifb::u32 count, const ifb::vec3_t* v3_a, const ifb::vec3_t* v3_b, ifb::vec3_t* v3_c);
    void vec3_batch_a_cross_b   (const ifb::u32 count, const ifb::vec3_t* v3_a, const ifb::vec3_t* v3_b, ifb::vec3_t* v3_c);
    void vec3_batch_a_project_b (const ifb::u32 count, const ifb::vec3_t* v3_a, const ifb::vec3_t* v3_b, ifb::vec3_t* v3_c);
    void vec3_batch_a_reject_b  (const ifb::u32 count, const ifb::vec3_t* v3_a, const ifb::vec3_t* v3_b, ifb::vec3_t* v3_c);

    void vec3_batch_scalar      (const ifb::u32 count, const ifb::vec3_t* v3, const ifb::f32* scalar, ifb::vec3_t* v3_scalar);

    void vec3_batch_magnitude   (const ifb::u32 count, const ifb::vec3_t* v3, ifb::f32* v3_magnitude);
    void vec3_batch_normalize   (const ifb::u32 count, const ifb::vec3_t* v3, ifb::vec3_t* v3_normalized);
};


#endif //IFB_MATH_VEC3_HPP