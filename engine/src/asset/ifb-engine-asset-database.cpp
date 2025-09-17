#pragma once

#include "ifb-engine-asset-internal.hpp"

namespace ifb {

    //-------------------------------------------------------------------
    // GLOBALS
    //-------------------------------------------------------------------

    static eng_asset_db_t             _db;
    static eng_asset_db_file_t        _db_file;
    static eng_asset_db_file_header_t _db_file_header;
    static eng_asset_db_table_t       _db_table_text;
    static eng_asset_db_table_t       _db_table_image;
    static eng_asset_db_table_t       _db_table_sound;
    static eng_asset_db_table_t       _db_table_font;

    //-------------------------------------------------------------------
    // INTERNAL
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL eng_bool
    eng_asset_db_init(
        const eng_hash_u128_t db_file_hash) {

        static bool is_init = false;
        if (is_init) return(is_init);

        is_init = true;

        // initialize the header buffer 
        eng_file_buffer_t header_buffer;
        header_buffer.data        = _db_file_header.data;
        header_buffer.size        = _db_file_header_data_size;
        header_buffer.transferred = 0;
        header_buffer.cursor      = 0;

        // open the file, get the size, and read the header
        const eng_file_h32_t file_handle     = eng_file_mngr_open_ro  (_db_file_path_cstr);
        const eng_u64        file_size       = eng_file_mngr_get_size (file_handle); 
        const eng_bool       is_valid_read   = eng_file_mngr_read     (file_handle, header_buffer);
        const eng_bool       is_valid_length = (
            file_size                 >= header_buffer.size &&
            header_buffer.transferred == header_buffer.size
        );

        is_init &= is_valid_read;
        is_init &= is_valid_length;
        if (!is_init) return(is_init);

        // check the verification string
        for (
            eng_u32 char_index = 0;
            char_index < _db_file_verif_size;
            ++char_index) {

            const eng_c8 c  = _db_file_header.verif.data[char_index];
            is_init        &= (c == _db_file_verif_cstr[char_index]);
        }
        if (!is_init) return(is_init);

        // check the hash
        is_init &= db_file_hash.val.as_u64[0] == _db_file_header.hash.val.as_u64[0]; 
        is_init &= db_file_hash.val.as_u64[1] == _db_file_header.hash.val.as_u64[1]; 
        if (!is_init) return(is_init);

        // check the indexes
        static const eng_u32 index_size = sizeof(eng_asset_db_file_index_t);
        for (
            eng_u32 index_num = 0;
            index_num < eng_asset_type_e32_count - 1;
            ++index_num) {

            eng_asset_db_file_index_t& index_current             = _db_file_header.index_array[index_num];
            eng_asset_db_file_index_t& index_next                = _db_file_header.index_array[index_num + 1];
            const eng_u32              index_next_start_expected = (index_current.start + index_current.size); 
            is_init &= (index_next.start == index_next_start_expected);

        }

        // initialize the structure
        _db.arena        = NULL;
        _db.table.text   = &_db_table_text;
        _db.table.image  = &_db_table_image;
        _db.table.sound  = &_db_table_sound;
        _db.table.font   = &_db_table_font;
        _db.file         = &_db.file;
        _db.file->handle = NULL;
        _db.file->size   = 0;
        _db.file->header = &_db_file_header;



        // verify the data
        for (
            eng_u32 index = 0;
            index < _db_file_verif_size
            ++index) {

            const eng_c8 c =  read_buffer.data[index];
            
            is_init        &= (c == _db_file_verif_cstr[index]);
        }

        // commit arena
        eng_mem_arena_t* arena = eng_mem_mngr_arena_commit_asset(); 

        is_init &= (arena != NULL);
        if (!is_init) return(is_init);



        return(is_init);
        

    }

};