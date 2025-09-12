#ifndef IFB_ENG_ASSET_INTERNAL_HPP
#define IFB_ENG_ASSET_INTERNAL_HPP

#include "ifb-engine-asset.hpp"
#include "ifb-engine-memory-internal.hpp"
#include "ifb-engine-file-internal.hpp"

namespace ifb {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    struct eng_asset_mngr_t;
    struct eng_asset_block_t;
    struct eng_asset_slot_t;
    struct eng_asset_db_t;
    struct eng_asset_db_table_t;
    struct eng_asset_db_builder_t;
    struct eng_asset_db_record_t;

    //-------------------------------------------------------------------
    // MANAGER
    //-------------------------------------------------------------------

    struct eng_asset_slot_t {
        eng_u64            block_size;
        eng_u32            block_count_free;
        eng_u32            block_count_used;
        eng_asset_block_t* block_list_free;
        eng_asset_block_t* block_list_used;        
        eng_mem_arena_t*   arena;
        eng_asset_slot_t*  next;
        eng_asset_slot_t*  prev;
    };

    struct eng_asset_block_t {
        eng_asset_id_u128_t  id;
        eng_asset_type_u32_t type;
        eng_u32              size;
        eng_byte*            data;
        eng_asset_block_t*   next;
        eng_asset_block_t*   prev; 
    };

    struct eng_asset_mngr_t {
        struct {
            eng_asset_slot_t* text;
            eng_asset_slot_t* image;
            eng_asset_slot_t* sound;
            eng_asset_slot_t* font;
        } slot_list;
    };

    //-------------------------------------------------------------------
    // DATABASE
    //-------------------------------------------------------------------

    eng_bool eng_asset_db_init       (const eng_hash_u128_t db_file_hash);
    eng_bool eng_asset_db_find_text  (eng_asset_db_record_t& record);
    eng_bool eng_asset_db_find_image (eng_asset_db_record_t& record);
    eng_bool eng_asset_db_find_sound (eng_asset_db_record_t& record);
    eng_bool eng_asset_db_find_font  (eng_asset_db_record_t& record);

    struct eng_asset_db_table_t {
        eng_u32   row_count;
        eng_pad32 pad;
        struct {
            eng_asset_id_u128_t* id;
            eng_u32*             size;
            eng_u64*             offset;
            eng_u64*             handle;
        } col;
    };

    struct eng_asset_db_record_t {
        eng_asset_id_u128_t id;
        eng_u32             index;
        eng_u32             size;
        eng_u64             offset;
        eng_u64             handle;
    };

    //-------------------------------------------------------------------
    // DATABASE FILE
    //-------------------------------------------------------------------

    struct eng_asset_db_file_index_t {
        eng_u32 type;
        eng_u32 count;
        eng_u64 start;
        eng_u64 size;
    };

    struct eng_asset_db_file_verif_t {
        eng_c8 data[16];
    };

    constexpr eng_u32 _db_file_verif_size       = sizeof(eng_asset_db_file_verif_t); 
    constexpr eng_u32 _db_file_index_array_size = (sizeof(eng_asset_db_file_index_t) * eng_asset_type_e32_count);
    constexpr eng_u32 _db_file_header_data_size = _db_file_verif_size + sizeof(eng_hash_u128_t) + _db_file_index_array_size;
    constexpr eng_c8  _db_file_path_cstr[]      = IFB_ENG_ASSET_DB_PATH;
    constexpr eng_c8  _db_file_verif_cstr[]     = IFB_ENG_ASSET_VERIF_STR;

    struct eng_asset_db_file_header_t {
        union {
            struct {
                eng_asset_db_file_verif_t verif;
                eng_hash_u128_t           hash;              
                eng_asset_db_file_index_t index_array[eng_asset_type_e32_count];
            };
            byte data[_db_file_header_data_size];
        }; 
    };

    struct eng_asset_db_file_t {
        eng_asset_db_file_header_t* header;
        eng_u64                     size;
        eng_file_h32_t              handle;
    };

    struct eng_asset_db_t {
        eng_mem_arena_t* arena;
        struct {
            eng_asset_db_table_t* text;
            eng_asset_db_table_t* image;
            eng_asset_db_table_t* sound;
            eng_asset_db_table_t* font;
        } table;
        eng_asset_db_file_t* file;
    };

    struct eng_asset_db_builder_t {
        eng_file_h32_t config_file_handle;
    };
};

#endif //IFB_ENG_ASSET_INTERNAL_HPP