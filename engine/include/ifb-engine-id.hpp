#ifndef IFB_ENG_ID_HPP
#define IFB_ENG_ID_HPP

#include "ifb-engine.hpp"

namespace ifb {

    struct eng_id_u32_t : sld::hash32_t { };

    IFB_ENG_API eng_void
    eng_id_generate(
        // const eng_u32   in_count,
        // const eng_u32   in_stride,
        // const eng_byte* in_data,
        // eng_id_u32_t*   out_id
        );

    IFB_ENG_API eng_bool eng_id_search   ();
    
};


#endif //IFB_ENG_ID_HPP