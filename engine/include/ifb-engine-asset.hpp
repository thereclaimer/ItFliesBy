#ifndef IFB_ENGINE_ASSET_HPP
#define IFB_ENGINE_ASSET_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-file.hpp"

#ifndef    IFB_ASSET_NAME_SIZE
#   define IFB_ASSET_NAME_SIZE 32 
#endif

namespace ifb {

    struct eng_asset_type_u32_t;
    struct eng_asset_id_u128_t;
    struct eng_asset_name_str8_t;

    IFB_ENG_API void eng_asset_generate_id (const eng_u32 in_count, const eng_asset_name_str8_t* in_name, eng_asset_id_u128_t* out_id);

    enum eng_asset_type_e32_ {
        eng_asset_type_e32_text  = 0,
        eng_asset_type_e32_image = 1,
        eng_asset_type_e32_sound = 2
    };

    struct eng_asset_buffer_t {
        eng_byte* data;
        eng_u64   size;
    };

    struct eng_asset_index_t {
        eng_u64 offset;
        eng_u64 size;
    }; 

    struct eng_asset_name_str8_t {
        eng_c8 chars[IFB_ASSET_NAME_SIZE];
    };

};

#endif //IFB_ENGINE_ASSET_HPP