#pragma once

#include "ifb-engine-asset-internal.hpp"

namespace ifb {

    constexpr eng_u32 _db_file_index_array_size  = (sizeof(eng_asset_db_file_index_t) * eng_asset_type_e32_count);
    constexpr eng_c8  _db_file_path_cstr  []     = IFB_ENG_ASSET_DB_PATH;
    constexpr eng_c8  _db_file_verif_cstr []     = IFB_ENG_ASSET_VERIF_STR;
    constexpr eng_u32 _db_file_verif_size        = sizeof(_db_file_verif_cstr) - 1; 
    constexpr eng_u32 _db_file_header_data_size  = _db_file_verif_size + sizeof(eng_hash_u128_t) + _db_file_index_array_size;
    constexpr eng_u32 _db_file_start_verif_data  = 0;
    constexpr eng_u32 _db_file_start_hash        = _db_file_verif_size;
    constexpr eng_u32 _db_file_start_index_array = _db_file_start_hash + sizeof(eng_hash_u128_t);

    IFB_ENG_FUNC eng_asset_db_file_t*
    eng_asset_db_file_create(
        void) {

        // commit arena
        eng_mem_arena_t* arena = eng_mem_arena_commit_asset();
        if (!arena) return(NULL);

        // allocate memory and open the file
        eng_asset_db_file_t* db_file     = eng_mem_arena_push_struct(arena, eng_asset_db_file_t);
        eng_byte*            header_data = eng_mem_arena_push_bytes (arena, _db_file_header_data_size); 
        eng_file_h32_t       file_handle = eng_file_mngr_open_rw    (_db_file_path_cstr);

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
        eng_hash_u128_t*   ptr_hash        =   (eng_hash_u128_t*)&header_data[_db_file_start_hash];  
        eng_asset_index_t* ptr_index_array = (eng_asset_index_t*)&header_data[_db_file_start_index_array]; 

        // initialize the struct
        db_file->handle                    = file_handle;
        db_file->index_count               = eng_asset_type_e32_count;
        db_file->index_array               = NULL;
        db_file->size                      = 0;
        db_file->verif.data                = (eng_c8*)ptr_verif_data;
        db_file->verif.length              = _db_file_verif_size;
        db_file->hash                      = ptr_hash; 
        db_file->header_buffer.data        = header_data;
        db_file->header_buffer.size        = _db_file_header_data_size;
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
    eng_asset_db_file_read(
        eng_asset_db_file_t* const db_file) {
    }

    IFB_ENG_FUNC void
    eng_asset_db_file_write(
        eng_asset_db_file_t* const db_file) {
    }


};