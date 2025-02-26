#ifndef IFB_MATH_VEC2_HPP
#define IFB_MATH_VEC2_HPP

#include <math.h>

#include <ifb.hpp>

namespace ifb_math {
    //----------------------
    // instance operations
    //----------------------

    void vec2_a_add_b           (IFBVec2& v2_a_add_b,    const IFBVec2& v2_a,  const IFBVec2& v2_b);
    void vec2_a_sub_b           (IFBVec2& v2_a_sub_b,    const IFBVec2& v2_a,  const IFBVec2& v2_b);
    void vec2_a_project_b       (IFBVec2& v2_a_proj_b,   const IFBVec2& v2_a,  const IFBVec2& v2_b);
    void vec2_a_reject_b        (IFBVec2& v2_a_rej_b,    const IFBVec2& v2_a,  const IFBVec2& v2_b);
    void vec2_scalar            (IFBVec2& v2_scalar,     const IFBVec2& v2_in, const IFBF32  scalar);
    void vec2_a_dot_b           (IFBF32& v2_a_dot_b,    const IFBVec2& v2_a,  const IFBVec2& v2_b);
    void vec2_magnitude         (IFBF32& v2_magnitude,  const IFBVec2& v2_in);
    void vec2_normalize         (IFBVec2& v2_normalized, const IFBVec2& v2_in);

    //----------------------
    // batch operations
    //----------------------

    void vec2_batch_a_add_b     (IFBVec2* v2_a_add_b,    const IFBU32 count, const IFBVec2* v2_a,  const IFBVec2* v2_b);
    void vec2_batch_a_sub_b     (IFBVec2* v2_a_sub_b,    const IFBU32 count, const IFBVec2* v2_a,  const IFBVec2* v2_b);
    void vec2_batch_a_dot_b     (IFBF32* v2_a_dot_b,    const IFBU32 count, const IFBVec2* v2_a,  const IFBVec2* v2_b);
    void vec2_batch_a_project_b (IFBVec2* v2_a_proj_b,   const IFBU32 count, const IFBVec2* v2_a,  const IFBVec2* v2_b);
    void vec2_batch_a_reject_b  (IFBVec2* v2_a_rej_b,    const IFBU32 count, const IFBVec2* v2_a,  const IFBVec2* v2_b);
    void vec2_batch_scalar      (IFBVec2* v2_scalar,     const IFBU32 count, const IFBVec2* v2_in, const IFBF32* scalar);
    void vec2_batch_magnitude   (IFBF32* v2_magnitude,  const IFBU32 count, const IFBVec2* v2_in);
    void vec2_batch_normalize   (IFBVec2* v2_normalized, const IFBU32 count, const IFBVec2* v2_in);
};

inline void
ifb_math::vec2_a_add_b(
          IFBVec2& v2_a_add_b,
    const IFBVec2& v2_a,
    const IFBVec2& v2_b) {

    v2_a_add_b.x = v2_a.x + v2_b.x;
    v2_a_add_b.y = v2_a.y + v2_b.y;
}

inline void
ifb_math::vec2_a_sub_b(
          IFBVec2& v2_a_sub_b,
    const IFBVec2& v2_a,
    const IFBVec2& v2_b) {

    v2_a_sub_b.x = v2_a.x - v2_b.x;
    v2_a_sub_b.y = v2_a.y - v2_b.y;
}

inline void
ifb_math::vec2_a_dot_b(
          IFBF32& v2_a_dot_b,
    const IFBVec2& v2_a,
    const IFBVec2& v2_b) {

    const IFBF32 v2_ax_bx = v2_a.x * v2_b.x;
    const IFBF32 v2_ay_by = v2_a.y * v2_b.y;
    
    v2_a_dot_b = v2_ax_bx * v2_ay_by;    
}

inline void
ifb_math::vec2_a_project_b(
          IFBVec2& v2_a_proj_b,
    const IFBVec2& v2_a,
    const IFBVec2& v2_b) {

    //forward declarations
    IFBF32 v2_a_dot_b, v2_b_dot_b;

    //calculate (a dot b) and (b dot b)
    ifb_math::vec2_a_dot_b(v2_a_dot_b, v2_a, v2_b);    
    ifb_math::vec2_a_dot_b(v2_b_dot_b, v2_b, v2_b);    

    //calculate the scalar
    const IFBF32 scalar = v2_a_dot_b / v2_b_dot_b;

    //apply the scalar to b to get the projection
    ifb_math::vec2_scalar(v2_a_proj_b,v2_a_proj_b, scalar);
}

inline void
ifb_math::vec2_a_reject_b(
          IFBVec2& v2_a_rej_b,
    const IFBVec2& v2_a,
    const IFBVec2& v2_b) {

    //calculate a proj b
    IFBVec2 v2_a_proj_b;
    ifb_math::vec2_a_project_b(v2_a_proj_b, v2_a, v2_b);

    //subtract the projection from a to get the rejection
    ifb_math::vec2_a_sub_b(v2_a_rej_b,v2_a,v2_a_proj_b);
}

inline void
ifb_math::vec2_scalar(
          IFBVec2& v2_scalar,
    const IFBVec2& v2_in,
    const IFBF32  scalar) {

    v2_scalar.x = scalar * v2_in.x; 
    v2_scalar.y = scalar * v2_in.y; 
}

inline void
ifb_math::vec2_magnitude(
          IFBF32& v2_magnitude,
    const IFBVec2& v2_in) {

    const IFBF32 v2_xx        = v2_in.x * v2_in.x;
    const IFBF32 v2_yy        = v2_in.y * v2_in.y;
    const IFBF32 v2_xx_add_yy = v2_xx   + v2_yy;

    v2_magnitude = sqrtf(v2_xx_add_yy);
}

inline void
ifb_math::vec2_normalize(
          IFBVec2& v2_normalized,
    const IFBVec2& v2_in) {

    //get the magnitude
    IFBF32 v2_magnitude = 0;
    ifb_math::vec2_magnitude(v2_magnitude,v2_in);

    //calculate the inverse magnitude
    const IFBF32 v2_inv = 1 / v2_magnitude;

    v2_normalized.x *= v2_inv;
    v2_normalized.y *= v2_inv;
}

inline void 
ifb_math::vec2_batch_a_add_b(
          IFBVec2* v2_a_add_b,
    const IFBU32  count,
    const IFBVec2* v2_a, 
    const IFBVec2* v2_b) {

    for (
        IFBU32 index = 0;
        index < count;
        ++index) {

        const IFBVec2& v2_a_i = v2_a[index];
        const IFBVec2& v2_b_i = v2_b[index];

        ifb_math::vec2_a_add_b(
            v2_a_add_b [index],
            v2_a       [index],
            v2_b       [index]);                       
    }
}

inline void
ifb_math::vec2_batch_a_sub_b(
          IFBVec2* v2_a_sub_b,
    const IFBU32  count,
    const IFBVec2* v2_a, 
    const IFBVec2* v2_b) {
    
    for (
        IFBU32 index = 0;
        index < count;
        ++index) {
    
        ifb_math::vec2_a_sub_b(
            v2_a_sub_b [index],
            v2_a       [index],
            v2_b       [index]);  
    }
}

inline void
ifb_math::vec2_batch_a_dot_b(
          IFBF32* v2_a_dot_b,
    const IFBU32  count,
    const IFBVec2* v2_a, 
    const IFBVec2* v2_b) {

    for (
        IFBU32 index = 0;
        index < count;
        ++index) {

        ifb_math::vec2_a_dot_b(
            v2_a_dot_b [index],
            v2_a       [index],
            v2_b       [index]);                
    }
}

inline void
ifb_math::vec2_batch_a_project_b(
          IFBVec2* v2_a_proj_b,
    const IFBU32  count,
    const IFBVec2* v2_a, 
    const IFBVec2* v2_b) {

    for (
        IFBU32 index = 0;
        index < count;
        ++index) {

        ifb_math::vec2_a_project_b(
            v2_a_proj_b [index],
            v2_a        [index],
            v2_b        [index]);   
    }
}

inline void
ifb_math::vec2_batch_a_reject_b(
          IFBVec2* v2_a_rej_b,
    const IFBU32  count,
    const IFBVec2* v2_a, 
    const IFBVec2* v2_b) {

    for (
        IFBU32 index = 0;
        index < count;
        ++index) {

        ifb_math::vec2_a_reject_b(
            v2_a_rej_b [index],
            v2_a       [index],
            v2_b       [index]);  
    }
}

inline void
ifb_math::vec2_batch_scalar(
          IFBVec2* v2_scalar,
    const IFBU32  count,
    const IFBVec2* v2_in,
    const IFBF32* scalar) {

    for (
        IFBU32 index = 0;
        index < count;
        ++index) {
        
        ifb_math::vec2_scalar(
            v2_scalar [index],
            v2_in     [index],
            scalar    [index]);  
    }
}

inline void
ifb_math::vec2_batch_magnitude(
          IFBF32* v2_magnitude,
    const IFBU32  count,
    const IFBVec2* v2_in) {

    for (
        IFBU32 index = 0;
        index < count;
        ++index) {
        
        ifb_math::vec2_magnitude(
            v2_magnitude [index],
            v2_in        [index]);
    }
}

inline void
ifb_math::vec2_batch_normalize(
          IFBVec2* v2_normalized,
    const IFBU32  count,
    const IFBVec2* v2_in) {

    for (
        IFBU32 index = 0;
        index < count;
        ++index) {

        ifb_math::vec2_normalize(
            v2_normalized [index],
            v2_in         [index]);
    }
}

#endif //IFB_MATH_VEC2_HPP