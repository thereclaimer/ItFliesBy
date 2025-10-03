#pragma once

#include "ifb-engine-asset-internal.hpp"

namespace ifb {

    IFB_ENG_FUNC void
    eng_asset_db_create(
        void) {

        bool can_init = true;
        
        // create structures and allocate memory
        eng_mem_arena_t*      arena     = eng_mem_arena_commit_asset();
        eng_asset_db_t*       db        = eng_mem_arena_push_struct       (arena, eng_asset_db_t);        
        eng_asset_db_table_t* db_tables = eng_mem_arena_push_struct_array (arena, eng_asset_e32_type_count, eng_asset_db_table_t);
        can_init &= (arena     != NULL);
        can_init &= (db        != NULL);
        can_init &= (db_tables != NULL);
        assert(can_init);

        // initialize the struct
        db->arena          = arena;
        db->table.text     = &db_tables [eng_asset_e32_type_text];
        db->table.image    = &db_tables [eng_asset_e32_type_image];
        db->table.sound    = &db_tables [eng_asset_e32_type_sound];
        db->table.font     = &db_tables [eng_asset_e32_type_font];
        _eng_asset_mngr.db = db;
    }

    IFB_ENG_FUNC eng_void
    eng_asset_db_destroy(
        void) {

        eng_asset_db_validate();

        const eng_bool did_decommit = eng_mem_arena_decommit(_eng_asset_mngr.db->arena);
        assert(did_decommit);

        _eng_asset_mngr.db->arena       = NULL;
        _eng_asset_mngr.db->table.text  = NULL;
        _eng_asset_mngr.db->table.image = NULL;
        _eng_asset_mngr.db->table.sound = NULL;
        _eng_asset_mngr.db->table.font  = NULL;
    }

    IFB_ENG_FUNC eng_void
    eng_asset_db_validate(
        void) {

        bool is_valid = (_eng_asset_mngr.db != NULL);
        if (is_valid) {
            is_valid &= sld::arena_validate(_eng_asset_mngr.db->arena); 
            is_valid &= (_eng_asset_mngr.db->table.text  != NULL);
            is_valid &= (_eng_asset_mngr.db->table.image != NULL);
            is_valid &= (_eng_asset_mngr.db->table.sound != NULL);
            is_valid &= (_eng_asset_mngr.db->table.font  != NULL);
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