#ifndef IFB_MACROS_HPP
#define IFB_MACROS_HPP

#define ifb_macro_size_kilobytes(kb) (kb * 1024) 
#define ifb_macro_size_megabytes(mb) (mb * 1024 * 1024) 
#define ifb_macro_size_gigabytes(gb) (gb * 1024UL * 1024UL * 1024UL)

#define ifb_macro_size_array(type,count) (sizeof(type) * count)

#define ifb_macro_align_a_to_b(a,b)         (a + b - 1) & ~(b - 1)
#define ifb_macro_align_size_struct(struct) ifb_macro_align_a_to_b(sizeof(struct),alignof(struct))

#define ifb_macro_bit_set(bit,val)    val |=  (1 << bit)  
#define ifb_macro_bit_clear(bit,val)  val &= ~(1 << bit)  
#define ifb_macro_bit_toggle(bit,val) val ^=  (1 << bit)
#define ifb_macro_bit_test(bit,val)  (val >> bit) & 1

#endif //IFB_MACROS_HPP