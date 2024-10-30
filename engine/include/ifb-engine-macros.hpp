#ifndef IFB_ENGINE_MACROS_HPP
#define IFB_ENGINE_MACROS_HPP


#define ifb_engine_macro_align_a_to_b(a,b)         (a + b - 1) & ~(b - 1)
#define ifb_engine_macro_align_size_struct(struct) ifb_engine_macro_align_a_to_b(sizeof(struct),alignof(struct))


#endif //IFB_ENGINE_MACROS_HPP