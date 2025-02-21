#ifndef IFB_MACROS_HPP
#define IFB_MACROS_HPP

#define ifb_macro_assert(cond) if (!(cond)) (*((int*)(NULL)) = 1)
#define ifb_macro_nop()        ifb_macro_assert(true) 
#define ifb_macro_panic()      ifb_macro_assert(false)

#define ifb_macro_size_kilobytes(kb) (1024 * kb) 
#define ifb_macro_size_megabytes(mb) (1024 * 1024 * mb) 
#define ifb_macro_size_gigabytes(gb) (1024UL * 1024UL * 1024UL * gb)

#define ifb_macro_array_size(type,count)  (sizeof(type)  * count)
#define ifb_macro_array_count(type,array) (sizeof(array) / sizeof(type))

#define ifb_macro_align_a_to_b(a,b)             b > 0 ? (a + b - 1) & ~(b - 1) : a
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

#define ifb_macro_color_normalize_byte(byte) (IFBF32)(((IFBF32)byte) / ((IFBF32)0xFF))

#define ifb_macro_pointer_from_offset(start,offset,type) (type*)((IFBAddr)start + (IFBAddr)offset)

#define ifb_macro_arena_commit_struct_absolute(arena,type)  (type*)ifb_memory::arena_commit_bytes_absolute (arena,sizeof(type),alignof(type))
#define ifb_macro_arena_commit_struct_relative(arena,type)         ifb_memory::arena_commit_bytes_relative (arena,sizeof(type),alignof(type))
#define ifb_macro_arena_reserve_struct_absolute(arena,type) (type*)ifb_memory::arena_reserve_bytes_absolute(arena,sizeof(type),alignof(type))
#define ifb_macro_arena_reserve_struct_relative(arena,type)        ifb_memory::arena_reserve_bytes_relative(arena,sizeof(type),alignof(type))
#define ifb_macro_arena_release_struct_absolute(arena,type)        ifb_memory::arena_release_bytes_absolute(arena,sizeof(type),alignof(type))
#define ifb_macro_arena_release_struct_relative(arena,type)        ifb_memory::arena_release_bytes_relative(arena,sizeof(type),alignof(type))

#endif //IFB_MACROS_HPP