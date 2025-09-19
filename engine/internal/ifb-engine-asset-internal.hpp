#ifndef IFB_ENG_ASSET_INTERNAL_HPP
#define IFB_ENG_ASSET_INTERNAL_HPP

#include <sld-xml.hpp>

#include "ifb-engine.hpp"
#include "ifb-engine-hash.hpp"
#include "ifb-engine-asset.hpp"
#include "ifb-engine-memory-internal.hpp"
#include "ifb-engine-file-internal.hpp"

namespace ifb {

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    struct eng_asset_block_t;
    struct eng_asset_slot_t;

    struct eng_asset_mngr_t;

    struct eng_asset_db_t;
    struct eng_asset_db_table_t;
    struct eng_asset_db_builder_t;
    struct eng_asset_db_record_t;

    struct eng_asset_config_t;
    struct eng_asset_config_assets_t;
    struct eng_asset_config_xml_properties_t;

    struct eng_asset_db_t;
    struct eng_asset_db_file_index_t;
    struct eng_asset_db_file_verif_t;
    struct eng_asset_db_file_header_t;
    struct eng_asset_db_file_t;
    struct eng_asset_db_builder_t;

    //-------------------------------------------------------------------
    // ASSET
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

    //-------------------------------------------------------------------
    // MANAGER
    //-------------------------------------------------------------------

    struct eng_asset_mngr_t {
        struct {
            eng_asset_slot_t* text;
            eng_asset_slot_t* image;
            eng_asset_slot_t* sound;
            eng_asset_slot_t* font;
        } slot_list;
        eng_asset_db_t* db;
    };

    //-------------------------------------------------------------------
    // DATABASE
    //-------------------------------------------------------------------

    IFB_ENG_FUNC eng_asset_db_t* eng_asset_db_create     (void);
    IFB_ENG_FUNC eng_void        eng_asset_db_destroy    (eng_asset_db_t* const db);
    IFB_ENG_FUNC eng_void        eng_asset_db_validate   (eng_asset_db_t* const db);
    IFB_ENG_FUNC eng_bool        eng_asset_db_load_text  (eng_asset_db_t* const db, eng_asset_db_record_t& record);
    IFB_ENG_FUNC eng_bool        eng_asset_db_load_image (eng_asset_db_t* const db, eng_asset_db_record_t& record);
    IFB_ENG_FUNC eng_bool        eng_asset_db_load_sound (eng_asset_db_t* const db, eng_asset_db_record_t& record);
    IFB_ENG_FUNC eng_bool        eng_asset_db_load_font  (eng_asset_db_t* const db, eng_asset_db_record_t& record);

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

    struct eng_asset_db_t {
        eng_mem_arena_t*     arena;
        eng_asset_db_file_t* file;
        struct {
            eng_asset_db_table_t* text;
            eng_asset_db_table_t* image;
            eng_asset_db_table_t* sound;
            eng_asset_db_table_t* font;
        } table;
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
        eng_c8* data;
        eng_u64 length;
    };

    struct eng_asset_db_file_t {
        eng_file_h32_t             handle;
        eng_u32                    index_count;
        eng_asset_db_file_index_t* index_array;
        eng_u64                    size;
        eng_asset_db_file_verif_t  verif;
        eng_hash_u128_t*           hash;
        eng_file_buffer_t          header_buffer;
        eng_mem_arena_t*           arena;
    };

    struct eng_asset_db_builder_t {
        eng_file_h32_t config_file_handle;
    };

    IFB_ENG_FUNC eng_asset_db_file_t* eng_asset_db_file_create        (void);
    IFB_ENG_FUNC void                 eng_asset_db_file_destroy       (eng_asset_db_file_t* const db_file);
    IFB_ENG_FUNC void                 eng_asset_db_file_validate      (eng_asset_db_file_t* const db_file);
    IFB_ENG_FUNC void                 eng_asset_db_file_read_header   (eng_asset_db_file_t* const db_file);
    IFB_ENG_FUNC void                 eng_asset_db_file_write_header  (eng_asset_db_file_t* const db_file);
    IFB_ENG_FUNC void                 eng_asset_db_file_write_default (eng_asset_db_file_t* const db_file);

    //-------------------------------------------------------------------
    // CONFIG
    //-------------------------------------------------------------------

    IFB_ENG_FUNC eng_asset_config_t* eng_asset_config_create              (void);    
    IFB_ENG_FUNC eng_void            eng_asset_config_destroy             (eng_asset_config_t* const config);
    IFB_ENG_FUNC eng_void            eng_asset_config_validate            (eng_asset_config_t* const config);
    IFB_ENG_FUNC eng_void            eng_asset_config_load_default        (eng_asset_config_t* const config);
    IFB_ENG_FUNC eng_void            eng_asset_config_save_file           (eng_asset_config_t* const config);
    IFB_ENG_FUNC eng_u64             eng_asset_config_get_xml_buffer_size (eng_asset_config_t* const config);
    IFB_ENG_FUNC eng_void            eng_asset_config_get_xml_buffer      (eng_asset_config_t* const config, eng_buffer_t& buffer);
    IFB_ENG_FUNC eng_bool            eng_asset_config_node_read_text      (eng_asset_config_t* const config, eng_asset_config_assets_t& assets);
    IFB_ENG_FUNC eng_bool            eng_asset_config_node_read_image     (eng_asset_config_t* const config, eng_asset_config_assets_t& assets);
    IFB_ENG_FUNC eng_bool            eng_asset_config_node_read_sound     (eng_asset_config_t* const config, eng_asset_config_assets_t& assets);
    IFB_ENG_FUNC eng_bool            eng_asset_config_node_read_font      (eng_asset_config_t* const config, eng_asset_config_assets_t& assets);
    IFB_ENG_FUNC eng_bool            eng_asset_config_node_write_text     (eng_asset_config_t* const config, eng_asset_config_assets_t& assets);
    IFB_ENG_FUNC eng_bool            eng_asset_config_node_write_image    (eng_asset_config_t* const config, eng_asset_config_assets_t& assets);
    IFB_ENG_FUNC eng_bool            eng_asset_config_node_write_sound    (eng_asset_config_t* const config, eng_asset_config_assets_t& assets);
    IFB_ENG_FUNC eng_bool            eng_asset_config_node_write_font     (eng_asset_config_t* const config, eng_asset_config_assets_t& assets);
    IFB_ENG_FUNC eng_bool            eng_asset_config_node_read_assets    (eng_asset_config_t* const config, eng_asset_config_assets_t& node, const eng_c8* type_name);
    IFB_ENG_FUNC eng_bool            eng_asset_config_node_write_assets   (eng_asset_config_t* const config, eng_asset_config_assets_t& node, const eng_c8* type_name);

    struct eng_asset_config_xml_properties_t {
        struct {
            static constexpr eng_c8 ifb_assets [] = "ifb-assets";
            static constexpr eng_c8 text       [] = "text";
            static constexpr eng_c8 image      [] = "image";
            static constexpr eng_c8 sound      [] = "sound";
            static constexpr eng_c8 font       [] = "font";
            static constexpr eng_c8 asset      [] = "asset";
        } node;
        struct {
            static constexpr eng_c8 name [] = "name"; 
            static constexpr eng_c8 path [] = "path"; 
        } attrib;
        static constexpr eng_c8 default_config[] = 
            "<ifb-assets>"
                "<text path=\"../assets/text\">"
                "</text>"
                "<image path=\"../assets/image\">"
                "</image>"
                "<sound path=\"../assets/sound\">"
                "</sound>"
                "<font path=\"../assets/font\">"
                "</font>"
            "</ifb-assets>";
    };

    struct eng_asset_config_t {
        eng_mem_arena_t*  arena;
        eng_file_h32_t    file;
        eng_xml_h32_doc_t xml_doc;
    };

    struct eng_asset_config_assets_t {
        eng_u32 count;
        struct {
            eng_xml_h32_node_t*    node;
            eng_asset_name_str8_t* name;
            eng_asset_path_str8_t* path;
        } array;
    };

    //-------------------------------------------------------------------
    // GLOBALS
    //-------------------------------------------------------------------


    static eng_asset_db_t             _db;
    static eng_asset_db_table_t       _db_table_text;
    static eng_asset_db_table_t       _db_table_image;
    static eng_asset_db_table_t       _db_table_sound;
    static eng_asset_db_table_t       _db_table_font;
};

#endif //IFB_ENG_ASSET_INTERNAL_HPP