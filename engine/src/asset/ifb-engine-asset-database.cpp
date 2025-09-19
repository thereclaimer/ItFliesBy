#pragma once

#include "ifb-engine-asset-internal.hpp"

namespace ifb {

    IFB_ENG_FUNC eng_asset_db_t*
    eng_asset_db_create(
        void) {

        // create the file struct
        eng_asset_db_file_t* db_file = eng_asset_db_file_create();
        if (!db_file) return(NULL);

        // commit arena
        eng_mem_arena_t* arena = eng_mem_arena_commit_asset();
        if (!arena) return(NULL);

        // allocate memory
        eng_asset_db_t*       db        = eng_mem_arena_push_struct       (arena, eng_asset_db_t);        
        eng_asset_db_table_t* db_tables = eng_mem_arena_push_struct_array (arena, eng_asset_type_e32_count, eng_asset_db_table_t);
        bool can_init = true;
        can_init &= (db        != NULL);
        can_init &= (db_tables != NULL);
        if (!can_init) {
            assert(eng_mem_arena_decommit(arena));
            return(NULL);
        }

        // initialize the struct
        db->arena       = arena;
        db->file        = db_file;
        db->table.text  = &db_tables [eng_asset_type_e32_text];
        db->table.image = &db_tables [eng_asset_type_e32_image];
        db->table.sound = &db_tables [eng_asset_type_e32_sound];
        db->table.font  = &db_tables [eng_asset_type_e32_font];
        return(db);
    }

    IFB_ENG_FUNC eng_void
    eng_asset_db_destroy(
        eng_asset_db_t* const db) {

        eng_asset_db_validate     (db);
        eng_asset_db_file_destroy (db->file);
        
        const eng_bool did_decommit = eng_mem_arena_decommit(db->arena);
        assert(did_decommit);

        db->arena       = NULL;
        db->file        = NULL;
        db->table.text  = NULL;
        db->table.image = NULL;
        db->table.sound = NULL;
        db->table.font  = NULL;
    }

    IFB_ENG_FUNC eng_void
    eng_asset_db_validate(
        eng_asset_db_t* const db) {

        bool is_valid = (db != NULL);
        if (is_valid) {
            is_valid &= sld::arena_validate(db->arena) 
            is_valid &= (db->file        != NULL);
            is_valid &= (db->table.text  != NULL);
            is_valid &= (db->table.image != NULL);
            is_valid &= (db->table.sound != NULL);
            is_valid &= (db->table.font  != NULL);
        }
        assert(is_valid);
    }

    IFB_ENG_FUNC eng_bool
    eng_asset_db_load_text(
        eng_asset_db_t* const  db,
        eng_asset_db_record_t& record) {

    }

    IFB_ENG_FUNC eng_bool
    eng_asset_db_load_image(
        eng_asset_db_t* const  db,
        eng_asset_db_record_t& record) {

    }

    IFB_ENG_FUNC eng_bool
    eng_asset_db_load_sound(
        eng_asset_db_t* const  db,
        eng_asset_db_record_t& record) {

    }

    IFB_ENG_FUNC eng_bool
    eng_asset_db_load_font(
        eng_asset_db_t* const  db,
        eng_asset_db_record_t& record) {

    }
};