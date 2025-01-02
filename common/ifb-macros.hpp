#ifndef IFB_MACROS_HPP
#define IFB_MACROS_HPP

#define ifb_macro_assert(cond) if (!(cond)) (*((int*)(NULL)) = 1)
#define ifb_macro_nop()        ifb_macro_assert(true) 
#define ifb_macro_panic()      ifb_macro_assert(false)

#define ifb_macro_size_kilobytes(kb) (1024 * kb) 
#define ifb_macro_size_megabytes(mb) (1024 * 1024 * mb) 
#define ifb_macro_size_gigabytes(gb) (1024UL * 1024UL * 1024UL * gb)

#define ifb_macro_size_array(type,count) (sizeof(type) * count)

#define ifb_macro_align_a_to_b(a,b)             (a + b - 1) & ~(b - 1)
#define ifb_macro_align_size_struct(struct)     ifb_macro_align_a_to_b(sizeof(struct),alignof(struct))
#define ifb_macro_align_a_to_multiple_of_b(x,y) (((x + (y / 2)) / y) * y)

#define ifb_macro_struct_member_offset(struct,member) ((size_t)&(((struct*)0)->member))

#define ifb_macro_bit_set(bit,val)       val |=  (1 << bit)  
#define ifb_macro_bit_clear(bit,val)     val &= ~(1 << bit)  
#define ifb_macro_bit_toggle(bit,val)    val ^=  (1 << bit)
#define ifb_macro_bit_test(bit,val)      (val >> bit) & 1
#define ifb_macro_bit_is_set(bit,val)    ifb_macro_bit_test(bit,val)
#define ifb_macro_bit_is_clear(bit,val)  !ifb_macro_bit_test(bit,val)



#define ifb_macro_xmm_f128_load_aligned(f32_ptr)   _mm_load_ps(f32_ptr)
#define ifb_macro_xmm_f128_load_unaligned(f32_ptr) _mm_loadu_ps(f32_ptr)
#define ifb_macro_xmm_f128_add(xmm_a, xmm_b)       _mm_add_ps(xmm_a, xmm_b)
#define ifb_macro_xmm_f128_subtract(xmm_a, xmm_b)  _mm_sub_ps(xmm_a, xmm_b)
#define ifb_macro_xmm_f128_multiply(xmm_a, xmm_b)  _mm_mul_ps(xmm_a, xmm_b)
#define ifb_macro_xmm_f128_divide(xmm_a, xmm_b)    _mm_div_ps(xmm_a, xmm_b)
#define ifb_macro_xmm_f128_sqrt(xmm)               _mm_sqrt_ps(xmm)
#define ifb_macro_xmm_f128_store(f32_ptr, xmm)     _mm_store_ps(f32_ptr, xmm)

#define ifb_macro_color_normalize_byte(byte) (ifb_f32)(((ifb_f32)byte) / ((ifb_f32)0xFF))

#define ifb_macro_pointer_from_offset(start,offset,type) (type*)((ifb_address)start + (ifb_address)offset)

#endif //IFB_MACROS_HPP