#pragma once

#include "ifb-engine-asset-internal.hpp"

namespace ifb {

    //-------------------------------------------------------------------
    // INTERNAL
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL eng_bool
    eng_asset_db_init(
        const eng_hash_u128_t db_file_hash) {

        static bool is_init = false;
        if (is_init) return(is_init);

        is_init = true;

        // initialize the header
        eng_asset_db_file_header_t file_header;
        file_header.buffer.data        = _db_file_header_data;
        file_header.buffer.size        = _db_file_header_data_size;
        file_header.buffer.cursor      = 0;
        file_header.buffer.length      = 0;
        file_header.buffer.transferred = 0;
        file_header.verif.data         = (eng_c8*)&file_header.buffer.data[0];
        file_header.verif.length       = _db_file_verif_size - 1;
        file_header.hash.val.as_u64[0] = 0;
        file_header.hash.val.as_u64[1] = 0;
        file_header.index.count        = 0;
        file_header.index.array        = (eng_asset_db_file_index_t*)&file_header.buffer.data[file_header.verif.length];

        // open the file and get the size
        const eng_file_h32_t file_handle = eng_file_mngr_open_ro  (_db_file_path_cstr);
        const eng_u64        file_size   = eng_file_mngr_get_size (file_handle); 
        
        // read the file header
        is_init &= eng_file_mngr_read(file_handle, file_header.buffer);
        is_init &= (file_size                      >= file_header.buffer.length); 
        is_init &= (file_header.buffer.transferred == file_header.buffer.size);
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

            eng_asset_db_file_index_t& index_current             = _db_file_header.index.array[index_num];
            eng_asset_db_file_index_t& index_next                = _db_file_header.index.array[index_num + 1];
            const eng_u32              index_next_start_expected = (index_current.start + index_current.size); 
            is_init &= (index_next.start == index_next_start_expected);
        }

        // initialize the structure
        _db.arena            = NULL;
        _db.table.text       = &_db_table_text;
        _db.table.image      = &_db_table_image;
        _db.table.sound      = &_db_table_sound;
        _db.table.font       = &_db_table_font;
        _db.file             = _db.file;
        _db.file->handle.val = IFB_ENG_FILE_H32_INVALID;
        _db.file->size       = 0;
        _db.file->header     = &_db_file_header;

        // verify the data
        for (
            eng_u32 index = 0;
            index < _db_file_verif_size;
            ++index) {

            const eng_c8 c  = _db_file_header.buffer.data[index];
            is_init        &= (c == _db_file_verif_cstr[index]);
        }

        // commit arena
        eng_mem_arena_t* arena = eng_mem_mngr_arena_commit_asset(); 
        is_init &= (arena != NULL);


        return(is_init);
    }

};