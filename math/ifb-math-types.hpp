#ifndef IFB_MATH_TYPES_HPP
#define IFB_MATH_TYPES_HPP

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBMathVec2;
struct IFBMathVec3;
struct IFBMathMat3;
struct IFBMathPoint2;
struct IFBMathLine2;

typedef IFBMathVec2   ifb_v2;
typedef IFBMathVec3   ifb_v3;
typedef IFBMathMat3   ifb_m3;
typedef IFBMathPoint2 ifb_p2;
typedef IFBMathLine2  ifb_l2;

/**********************************************************************************/
/* VECTORS                                                                        */
/**********************************************************************************/

struct IFBMathVec2 {
    ifb_f32 x;
    ifb_f32 y;
};

struct IFBMathVec3 {
    ifb_f32 x;
    ifb_f32 y;
    ifb_f32 z;
};

/**********************************************************************************/
/* MATRICES                                                                       */
/**********************************************************************************/

struct IFBMathMat3 {
    union {
        struct {
            ifb_f32 r0c0;
            ifb_f32 r0c1;
            ifb_f32 r0c2;
            ifb_f32 r1c0;
            ifb_f32 r1c1;
            ifb_f32 r1c2;
            ifb_f32 r2c0;
            ifb_f32 r2c1;
            ifb_f32 r2c2;
        };
        struct {
            ifb_v3 row_0;
            ifb_v3 row_1;
            ifb_v3 row_2;
        };
        ifb_f32 array[9];
    };
};

/**********************************************************************************/
/* POINTS AND LINES                                                               */
/**********************************************************************************/

struct IFBMathPoint2 : IFBMathVec2 { };

struct IFBMathLine2 {
    ifb_p2 point_a;
    ifb_p2 point_b;
};


#endif //IFB_MATH_TYPES_HPP