#ifndef IFB_ENGINE_ASSET_HPP
#define IFB_ENGINE_ASSET_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-file.hpp"
#include "ifb-engine-id.hpp"

#ifndef    IFB_ENG_ASSET_DB_PATH   
#   define IFB_ENG_ASSET_DB_PATH     "IFB.AssetDB.ifb"
#endif
#ifndef    IFB_ENG_ASSET_VERIF_STR   
#   define IFB_ENG_ASSET_VERIF_STR   "IFBASSETDATABASE"
#endif
#ifndef    IFB_ENG_ASSET_CONFIG_PATH   
#   define IFB_ENG_ASSET_CONFIG_PATH "IFB.AssetConfig.xml"
#endif
#ifndef    IFB_ENG_ASSET_NAME_SIZE
#   define IFB_ENG_ASSET_NAME_SIZE   32 
#endif

namespace ifb {

    typedef eng_byte        eng_asset_data_u64_t;
    typedef eng_u64         eng_asset_size_u64_t;
    typedef eng_error_s32_t eng_asset_error_s32_t;

    struct eng_asset_text_h64_t  : eng_h64_t { };
    struct eng_asset_image_h64_t : eng_h64_t { };
    struct eng_asset_sound_h64_t : eng_h64_t { };
    struct eng_asset_font_h64_t  : eng_h64_t { };

    struct eng_asset_t;
    struct eng_asset_type_u32_t;
    struct eng_asset_id_u128_t;
    struct eng_asset_name_str8_t;
    struct eng_asset_buffer_t;
    struct eng_asset_db_builder_h64_t;

    IFB_ENG_API void                             eng_asset_generate_id         (const eng_u32 i_count, const eng_asset_name_str8_t* i_name, eng_asset_id_u128_t* o_id);
    IFB_ENG_API void                             eng_asset_name_sanitize       (const eng_u32 i_count, eng_asset_name_str8_t* io_name);

    IFB_ENG_API const eng_asset_text_h64_t       eng_asset_mngr_load_text      (const eng_asset_id_u128_t id);
    IFB_ENG_API const eng_asset_image_h64_t      eng_asset_mngr_load_image     (const eng_asset_id_u128_t id);
    IFB_ENG_API const eng_asset_sound_h64_t      eng_asset_mngr_load_sound     (const eng_asset_id_u128_t id);
    IFB_ENG_API const eng_asset_font_h64_t       eng_asset_mngr_load_font      (const eng_asset_id_u128_t id);
    IFB_ENG_API const eng_asset_error_s32_t      eng_asset_mngr_get_last_error (void); 

    IFB_ENG_API const eng_asset_db_builder_h64_t eng_asset_db_builder_init     (void);

    enum eng_asset_type_e32_ {
        eng_asset_type_e32_text  = 0,
        eng_asset_type_e32_image = 1,
        eng_asset_type_e32_sound = 2,
        eng_asset_type_e32_font  = 3,
        eng_asset_type_e32_count = 4
    };

    struct eng_asset_type_u32_t : eng_u32_t     { };
    struct eng_asset_id_u128_t  : eng_id_u128_t { };

    struct eng_asset_buffer_t {
        eng_asset_data_u64_t* data;
        eng_asset_size_u64_t  size;
    };

    struct eng_asset_index_t {
        eng_asset_size_u64_t offset;
        eng_asset_size_u64_t size;
        eng_asset_type_u32_t type;
    };

    struct eng_asset_name_str8_t {
        eng_c8 chars[IFB_ENG_ASSET_NAME_SIZE];
    };

    struct eng_asset_t {
        eng_asset_name_str8_t* name;        
        eng_asset_index_t      index;
        eng_asset_id_u128_t    id;
        eng_asset_buffer_t     buffer;
    };

};

#endif //IFB_ENGINE_ASSET_HPP