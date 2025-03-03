#ifndef IFB_MATH_VEC3_HPP
#define IFB_MATH_VEC3_HPP

#include <ifb.hpp>

namespace ifb_math {

    //----------------------
    // instance operations
    //----------------------

    void vec3_a_add_b           (const IFBVec3& v3_a, const IFBVec3& v3_b, IFBVec3& v3_c);
    void vec3_a_sub_b           (const IFBVec3& v3_a, const IFBVec3& v3_b, IFBVec3& v3_c);
    void vec3_a_dot_b           (const IFBVec3& v3_a, const IFBVec3& v3_b, IFBVec3& v3_c);
    void vec3_a_cross_b         (const IFBVec3& v3_a, const IFBVec3& v3_b, IFBVec3& v3_c);
    void vec3_a_project_b       (const IFBVec3& v3_a, const IFBVec3& v3_b, IFBVec3& v3_c);
    void vec3_a_reject_b        (const IFBVec3& v3_a, const IFBVec3& v3_b, IFBVec3& v3_c);

    void vec3_scalar            (const IFBVec3& v3, const IFBF32 scalar, IFBVec3& v3_scalar);

    void vec3_magnitude         (const IFBVec3& v3, IFBF32& v3_magnitude);
    void vec3_normalize         (const IFBVec3& v3, IFBVec3& v3_normalized);

    //----------------------
    // batch operations
    //----------------------

    void vec3_batch_a_add_b     (const IFBU32 count, const IFBVec3* v3_a, const IFBVec3* v3_b, IFBVec3* v3_c);
    void vec3_batch_a_sub_b     (const IFBU32 count, const IFBVec3* v3_a, const IFBVec3* v3_b, IFBVec3* v3_c);
    void vec3_batch_a_dot_b     (const IFBU32 count, const IFBVec3* v3_a, const IFBVec3* v3_b, IFBVec3* v3_c);
    void vec3_batch_a_cross_b   (const IFBU32 count, const IFBVec3* v3_a, const IFBVec3* v3_b, IFBVec3* v3_c);
    void vec3_batch_a_project_b (const IFBU32 count, const IFBVec3* v3_a, const IFBVec3* v3_b, IFBVec3* v3_c);
    void vec3_batch_a_reject_b  (const IFBU32 count, const IFBVec3* v3_a, const IFBVec3* v3_b, IFBVec3* v3_c);

    void vec3_batch_scalar      (const IFBU32 count, const IFBVec3* v3, const IFBF32* scalar, IFBVec3* v3_scalar);

    void vec3_batch_magnitude   (const IFBU32 count, const IFBVec3* v3, IFBF32* v3_magnitude);
    void vec3_batch_normalize   (const IFBU32 count, const IFBVec3* v3, IFBVec3* v3_normalized);
};


#endif //IFB_MATH_VEC3_HPP