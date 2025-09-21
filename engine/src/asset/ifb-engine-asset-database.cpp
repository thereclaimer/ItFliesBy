#pragma once

#include "ifb-engine-asset-internal.hpp"

namespace ifb {

    IFB_ENG_FUNC eng_asset_db_t*
    eng_asset_db_create(
        void) {

        bool can_init = true;
        
        // create structures and allocate memory
        eng_asset_db_file_t*  db_file   = eng_asset_db_file_create ();
        eng_asset_config_t*   config    = eng_asset_config_create  ();
        eng_mem_arena_t*      arena     = eng_mem_arena_commit_asset();
        eng_asset_db_t*       db        = eng_mem_arena_push_struct       (arena, eng_asset_db_t);        
        eng_asset_db_table_t* db_tables = eng_mem_arena_push_struct_array (arena, eng_asset_e32_type_count, eng_asset_db_table_t);
        can_init &= (db_file   != NULL);
        can_init &= (config    != NULL);
        can_init &= (arena     != NULL);
        can_init &= (db        != NULL);
        can_init &= (db_tables != NULL);
        if (!can_init) {
            if (arena) assert(eng_mem_arena_decommit(arena));
            return(NULL);
        }

        // initialize the struct
        db->arena       = arena;
        db->file        = db_file;
        db->config      = config;
        db->table.text  = &db_tables [eng_asset_e32_type_text];
        db->table.image = &db_tables [eng_asset_e32_type_image];
        db->table.sound = &db_tables [eng_asset_e32_type_sound];
        db->table.font  = &db_tables [eng_asset_e32_type_font];
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
            is_valid &= sld::arena_validate(db->arena); 
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