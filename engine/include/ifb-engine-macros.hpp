#ifndef IFB_ENGINE_MACROS_HPP
#define IFB_ENGINE_MACROS_HPP

#define ifb_engine_macro_size_kilobytes(kb) kb * 1024 
#define ifb_engine_macro_size_megabytes(mb) mb * 1024 * 1024 
#define ifb_engine_macro_size_gigabytes(gb) gb * 1024 * 1024 * 1024

#define ifb_engine_macro_align_a_to_b(a,b)         (a + b - 1) & ~(b - 1)
#define ifb_engine_macro_align_size_struct(struct) ifb_engine_macro_align_a_to_b(sizeof(struct),alignof(struct))

#define ifb_engine_macro_bit_set(bit,val)    val |=  (1 << bit)  
#define ifb_engine_macro_bit_clear(bit,val)  val &= ~(1 << bit)  
#define ifb_engine_macro_bit_toggle(bit,val) val ^=  (1 << bit)
#define ifb_engine_macro_bit_test(bit,val)  (val >> bit) & 1

#endif //IFB_ENGINE_MACROS_HPP