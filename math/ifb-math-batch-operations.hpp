#ifndef IFB_MATH_BATCH_OPERATIONS_HPP
#define IFB_MATH_BATCH_OPERATIONS_HPP

#include <math.h>

#include <ifb.hpp>

namespace ifb_math {

    ifb_void batch_a_add_b  (const ifb_u32 count, const ifb_f32* a, const ifb_f32* b, ifb_f32* c);
    ifb_void batch_a_sub_b  (const ifb_u32 count, const ifb_f32* a, const ifb_f32* b, ifb_f32* c);
    ifb_void batch_a_mul_b  (const ifb_u32 count, const ifb_f32* a, const ifb_f32* b, ifb_f32* c);
    ifb_void batch_a_div_b  (const ifb_u32 count, const ifb_f32* a, const ifb_f32* b, ifb_f32* c);

    ifb_void batch_sqrt     (const ifb_u32 count, const ifb_f32* val, ifb_f32* val_sqrt);
    ifb_void batch_trig_sin (const ifb_u32 count, const ifb_f32* val, ifb_f32* val_trig_sin);
    ifb_void batch_trig_cos (const ifb_u32 count, const ifb_f32* val, ifb_f32* val_trig_cos);
};

inline ifb_void 
ifb_math::batch_a_add_b(
    const ifb_u32  count,
    const ifb_f32* a,
    const ifb_f32* b,
          ifb_f32* c) {

    ifb_xmm_f128 xmm_a;
    ifb_xmm_f128 xmm_b;
    ifb_xmm_f128 xmm_c;

    ifb_macro_assert(count % 4 == 0);

    for (
        ifb_u32 index = 0;
        index < count;
        index += 4) {

        //load xmm registers
        xmm_a = ifb_macro_xmm_f128_load_aligned(&a[index]);
        xmm_b = ifb_macro_xmm_f128_load_aligned(&b[index]);
        
        //xmm add
        xmm_c = ifb_macro_xmm_f128_add(xmm_a,xmm_b);
        
        //store result from xmm
        ifb_macro_xmm_f128_store(&c[index],xmm_c);
    }
}

inline ifb_void 
ifb_math::batch_a_sub_b(
    const ifb_u32  count,
    const ifb_f32* a,
    const ifb_f32* b,
          ifb_f32* c) {

    ifb_xmm_f128 xmm_a;
    ifb_xmm_f128 xmm_b;
    ifb_xmm_f128 xmm_c;

    ifb_macro_assert(count % 4 == 0);

    for (
        ifb_u32 index = 0;
        index < count;
        index += 4) {

        //load xmm registers
        xmm_a = ifb_macro_xmm_f128_load_aligned(&a[index]);
        xmm_b = ifb_macro_xmm_f128_load_aligned(&b[index]);
        
        //xmm add
        xmm_c = ifb_macro_xmm_f128_subtract(xmm_a,xmm_b);
        
        //store result from xmm
        ifb_macro_xmm_f128_store(&c[index],xmm_c);
    }
}

inline ifb_void 
ifb_math::batch_a_mul_b(
    const ifb_u32  count,
    const ifb_f32* a,
    const ifb_f32* b,
          ifb_f32* c) {

    ifb_xmm_f128 xmm_a;
    ifb_xmm_f128 xmm_b;
    ifb_xmm_f128 xmm_c;

    ifb_macro_assert(count % 4 == 0);

    for (
        ifb_u32 index = 0;
        index < count;
        index += 4) {

        //load xmm registers
        xmm_a = ifb_macro_xmm_f128_load_aligned(&a[index]);
        xmm_b = ifb_macro_xmm_f128_load_aligned(&b[index]);
        
        //xmm add
        xmm_c = ifb_macro_xmm_f128_multiply(xmm_a,xmm_b);
        
        //store result from xmm
        ifb_macro_xmm_f128_store(&c[index],xmm_c);
    }
}

inline ifb_void 
ifb_math::batch_a_div_b(
    const ifb_u32  count,
    const ifb_f32* a,
    const ifb_f32* b,
          ifb_f32* c) {

    ifb_xmm_f128 xmm_a;
    ifb_xmm_f128 xmm_b;
    ifb_xmm_f128 xmm_c;

    ifb_macro_assert(count % 4 == 0);

    for (
        ifb_u32 index = 0;
        index < count;
        index += 4) {

        //load xmm registers
        xmm_a = ifb_macro_xmm_f128_load_aligned(&a[index]);
        xmm_b = ifb_macro_xmm_f128_load_aligned(&b[index]);
        
        //xmm add
        xmm_c = ifb_macro_xmm_f128_divide(xmm_a,xmm_b);
        
        //store result from xmm
        ifb_macro_xmm_f128_store(&c[index],xmm_c);
    }
}

inline ifb_void
ifb_math::batch_sqrt(
    const ifb_u32  count,
    const ifb_f32* val,
          ifb_f32* val_sqrt) {

    ifb_xmm_f128 xmm_a;
    ifb_xmm_f128 xmm_b;

    ifb_macro_assert(count % 4 == 0);

    for (
        ifb_u32 index = 0;
        index < count;
        index += 4) {

        //load xmm registers
        xmm_a = ifb_macro_xmm_f128_load_aligned(&val[index]);
        
        //xmm add
        xmm_b = ifb_macro_xmm_f128_sqrt(xmm_a);
        
        //store result from xmm
        ifb_macro_xmm_f128_store(&val_sqrt[index],xmm_b);
    }
}

inline ifb_void
ifb_math::batch_trig_sin(
    const ifb_u32  count,
    const ifb_f32* val,
          ifb_f32* val_trig_sin) {

    ifb_macro_assert(count % 4 == 0);

    for (
        ifb_u32 index = 0;
        index < count;
        index += 4) {
            
        val_trig_sin[index]   = sinf(val[index]);
        val_trig_sin[index+1] = sinf(val[index+1]);
        val_trig_sin[index+2] = sinf(val[index+2]);
        val_trig_sin[index+3] = sinf(val[index+3]);
    }
}

inline ifb_void
ifb_math::batch_trig_cos(
    const ifb_u32  count,
    const ifb_f32* val,
          ifb_f32* val_trig_cos) {

    ifb_macro_assert(count % 4 == 0);

    for (
        ifb_u32 index = 0;
        index < count;
        index += 4) {
            
        val_trig_sin[index]   = cosf(val[index]);
        val_trig_sin[index+1] = cosf(val[index+1]);
        val_trig_sin[index+2] = cosf(val[index+2]);
        val_trig_sin[index+3] = cosf(val[index+3]);
    }
}

#endif //IFB_MATH_BATCH_OPERATIONS_HPP