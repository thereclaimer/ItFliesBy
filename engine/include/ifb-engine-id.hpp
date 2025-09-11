#ifndef IFB_ENG_ID_HPP
#define IFB_ENG_ID_HPP

#include "ifb-engine.hpp"

namespace ifb {

    struct eng_id_u128_t : sld::hash_t { };

    IFB_ENG_API eng_void eng_id_generate (const eng_u32 in_count, const eng_u32       in_stride, const eng_byte*      in_data,   eng_id_u128_t* out_id);
    IFB_ENG_API eng_bool eng_id_search   (const eng_u32 in_count, const eng_id_u128_t in_id,     const eng_id_u128_t* in_search, eng_u32&       out_index);
    
    inline const eng_id_u128_t
    eng_id_init(
        const eng_u32 a,
        const eng_u32 b,
        const eng_u32 c,
        const eng_u32 d) {

        eng_id_u128_t id;
        id.val.as_u32[0] = a; 
        id.val.as_u32[1] = b; 
        id.val.as_u32[2] = c; 
        id.val.as_u32[3] = d;
        return(id); 
    }
};


#endif //IFB_ENG_ID_HPP