#ifndef IFB_MACROS_HPP
#define IFB_MACROS_HPP

#define ifb_macro_assert(cond)                           if (!(cond)) (*((int*)(NULL)) = 1)
#define ifb_macro_nop()                                  ifb_macro_assert(true) 
#define ifb_macro_panic()                                ifb_macro_assert(false)

#define ifb_macro_hnd8_is_valid (hnd8)                   (hnd8.offset  != IFB_HANDLE_INVALID_U8)  
#define ifb_macro_hnd16_is_valid(hnd16)                  (hnd16.offset != IFB_HANDLE_INVALID_U16) 
#define ifb_macro_hnd32_is_valid(hnd32)                  (hnd32.offset != IFB_HANDLE_INVALID_U32) 
#define ifb_macro_hnd64_is_valid(hnd64)                  (hnd64.offset != IFB_HANDLE_INVALID_U64) 

#define ifb_macro_size_kilobytes(kb)                     (1024 * kb) 
#define ifb_macro_size_megabytes(mb)                     (1024 * 1024 * mb) 
#define ifb_macro_size_gigabytes(gb)                     (1024UL * 1024UL * 1024UL * gb)

#define ifb_macro_array_size(type,count)                 (sizeof(type)  * count)
#define ifb_macro_array_count(type,array)                (sizeof(array) / sizeof(type))

#define ifb_macro_align_a_to_b(a,b)                      (b > 0 ? (a + b - 1) & ~(b - 1) : a)
#define ifb_macro_align_size_struct(struct)              ifb_macro_align_a_to_b(sizeof(struct),alignof(struct))
#define ifb_macro_align_a_to_multiple_of_b(x,y)          (((x + (y / 2)) / y) * y)

#define ifb_macro_struct_member_offset(struct,member)    ((size_t)&(((struct*)0)->member))

#define ifb_macro_bit_set(bit,val)                       (val |=  (1 << bit))  
#define ifb_macro_bit_clear(bit,val)                     (val &= ~(1 << bit))  
#define ifb_macro_bit_toggle(bit,val)                    (val ^=  (1 << bit))
#define ifb_macro_bit_test(bit,val)                      ((val >> bit) & 1)
#define ifb_macro_bit_is_set(bit,val)                    ifb_macro_bit_test(bit,val)
#define ifb_macro_bit_is_clear(bit,val)                  !ifb_macro_bit_test(bit,val)

// TODO(SAM): these don't work
// #define ifb_macro_flags_set(flags,val)                   (val |=  (flags))  
// #define ifb_macro_flags_clear(flags,val)                 (val &= ~(flags))  
// #define ifb_macro_flags_toggle(flags,val)                (val ^=  (flags))
// #define ifb_macro_flags_test(flags,val)                  (val & flags)
// #define ifb_macro_flags_is_set(flags,val)                ifb_macro_flags_test(flags,val)
// #define ifb_macro_flags_is_clear(flags,val)              !ifb_macro_flags_test(flags,val)

#define ifb_macro_xmm_f128_load_aligned(f32_ptr)         _mm_load_ps(f32_ptr)
#define ifb_macro_xmm_f128_load_unaligned(f32_ptr)       _mm_loadu_ps(f32_ptr)
#define ifb_macro_xmm_f128_add(xmm_a, xmm_b)             _mm_add_ps(xmm_a, xmm_b)
#define ifb_macro_xmm_f128_subtract(xmm_a, xmm_b)        _mm_sub_ps(xmm_a, xmm_b)
#define ifb_macro_xmm_f128_multiply(xmm_a, xmm_b)        _mm_mul_ps(xmm_a, xmm_b)
#define ifb_macro_xmm_f128_divide(xmm_a, xmm_b)          _mm_div_ps(xmm_a, xmm_b)
#define ifb_macro_xmm_f128_sqrt(xmm)                     _mm_sqrt_ps(xmm)
#define ifb_macro_xmm_f128_store(f32_ptr, xmm)           _mm_store_ps(f32_ptr, xmm)

#define ifb_macro_color_normalize_byte(byte)             (IFBF32)(((IFBF32)byte) / ((IFBF32)0xFF))

#define ifb_macro_pointer_from_offset(start,offset,type)    (type*)((IFBAddr)start + (IFBAddr)offset)
#define ifb_macro_pointer_advance(pointer,offset,size,type) (type*)(((IFBPtr*)pointer) + offset); offset += size

#define ifb_macro_pack_u8_to_u32(u8_a,u8_b,u8_c,u8_d)    (IFBU32)((((IFBU32)u8_a) << 24) | (((IFBU32)u8_b) << 16) | (((IFBU32)u8_c) << 8) | (((IFBU32)u8_d)))

#endif //IFB_MACROS_HPP