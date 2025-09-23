#pragma once

#include "ifb-engine-asset-internal.hpp"

namespace ifb {

    constexpr eng_c8  _db_file_default_header[]  = 
        "IFBASSETDATABASE"                                                                                  // (16 bytes) verification string
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"                                  // (16 bytes) hash (everything after this point)
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"  // (24 bytes) text table index
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"  // (24 bytes) image table index
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"  // (24 bytes) sound table index
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"; // (24 bytes) font table index


    constexpr eng_u32 _db_file_index_array_size  = (sizeof(eng_asset_db_file_index_t) * eng_asset_e32_type_count);
    constexpr eng_c8  _db_file_path_cstr  []     = IFB_ENG_ASSET_DB_PATH;
    constexpr eng_c8  _db_file_verif_cstr []     = IFB_ENG_ASSET_VERIF_STR;
    constexpr eng_u32 _db_file_verif_size        = sizeof(_db_file_verif_cstr) - 1; 
    constexpr eng_u32 _db_file_start_verif_data  = 0;
    constexpr eng_u32 _db_file_start_hash        = _db_file_verif_size;
    constexpr eng_u32 _db_file_start_index_array = _db_file_start_hash + sizeof(eng_hash128_t);
    constexpr eng_u32 _db_file_header_size       = sizeof(_db_file_default_header) - 1; 

    IFB_ENG_FUNC eng_asset_db_file_t*
    eng_asset_db_file_create(
        void) {

        // commit arena
        eng_mem_arena_t* arena = eng_mem_arena_commit_asset();
        if (!arena) return(NULL);

        // allocate memory and open the file
        eng_asset_db_file_t* db_file     = eng_mem_arena_push_struct(arena, eng_asset_db_file_t);
        eng_byte*            header_data = eng_mem_arena_push_bytes (arena, _db_file_header_size); 
        eng_file_h32_t       file_handle = eng_file_mngr_open_rw    (_db_file_path_cstr);
        assert(eng_mem_arena_save_position(arena));

        // sanity check
        bool can_create = true;
        can_create &= (db_file         != NULL);
        can_create &= (header_data     != NULL);
        can_create &= (file_handle.val != IFB_ENG_FILE_H32_INVALID);
        if (!can_create) {
            assert(eng_mem_arena_decommit(arena));
            return(NULL);
        }

        // calculate pointers
        eng_byte*          ptr_verif_data  =                     &header_data[_db_file_start_verif_data];
        eng_hash128_t*   ptr_hash        =   (eng_hash128_t*)&header_data[_db_file_start_hash];  
        eng_asset_index_t* ptr_index_array = (eng_asset_index_t*)&header_data[_db_file_start_index_array]; 

        // initialize the struct
        db_file->handle                    = file_handle;
        db_file->index_count               = eng_asset_e32_type_count;
        db_file->index_array               = NULL;
        db_file->size                      = 0;
        db_file->verif.data                = (eng_c8*)ptr_verif_data;
        db_file->verif.length              = _db_file_verif_size;
        db_file->hash                      = ptr_hash; 
        db_file->header_buffer.data        = header_data;
        db_file->header_buffer.size        = _db_file_header_size;
        db_file->header_buffer.length      = 0;
        db_file->header_buffer.cursor      = 0;
        db_file->header_buffer.transferred = 0;
        db_file->arena                     = arena;
        return(db_file);
    }

    IFB_ENG_FUNC void
    eng_asset_db_file_destroy(
        eng_asset_db_file_t* const db_file) {
    }

    IFB_ENG_FUNC void
    eng_asset_db_file_validate(
        eng_asset_db_file_t* const db_file) {

        eng_bool is_valid = (db_file != NULL);
        if (!is_valid) {

            is_valid &= (db_file->handle.val         != IFB_ENG_FILE_H32_INVALID); 
            is_valid &= (db_file->index_array        != NULL);
            is_valid &= (db_file->verif.data         != NULL);
            is_valid &= (db_file->verif.length       == _db_file_verif_size); 
            is_valid &= (db_file->hash               != NULL); 
            is_valid &= (db_file->header_buffer.data != NULL);
            is_valid &= (db_file->header_buffer.size != _db_file_header_size);
            is_valid &= (db_file->arena              != NULL);          
        }
        assert(is_valid);
    }

    IFB_ENG_FUNC eng_bool
    eng_asset_db_file_read_header(
        eng_asset_db_file_t* const db_file) {

        eng_asset_db_file_validate(db_file);

        //get the header and check the size
        eng_bool      is_valid_header = true;
        const eng_u64 file_size       = eng_file_mngr_get_size(db_file->handle);
        is_valid_header &= file_size >= (_db_file_header_size - 1); // account for null terminator
        is_valid_header &= eng_file_mngr_read(db_file->handle, db_file->header_buffer);
        if (!is_valid_header) return(is_valid_header);

        // check the verification string
        for (
            eng_u32 index = 0;
            index < _db_file_verif_size;
            ++index) {

            const eng_c8 c = db_file->verif.data[index];
            is_valid_header &= (c == _db_file_verif_cstr[index]);
        }
        return(is_valid_header);
    }

    IFB_ENG_FUNC void
    eng_asset_db_file_write_header(
        eng_asset_db_file_t* const db_file) {
    }

    IFB_ENG_FUNC void
    eng_asset_db_file_write_header_default(
        eng_asset_db_file_t* const db_file) {

        eng_asset_db_file_validate(db_file);

        static eng_file_buffer_t default_buffer;
        default_buffer.data        = (byte*)_db_file_default_header;
        default_buffer.size        = _db_file_header_size;
        default_buffer.length      = _db_file_header_size;
        default_buffer.cursor      = 0;
        default_buffer.transferred = 0;

        eng_bool did_write = eng_file_mngr_write(db_file->handle, default_buffer);
        assert(did_write);
    }
};