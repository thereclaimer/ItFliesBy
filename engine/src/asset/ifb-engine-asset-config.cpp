#pragma once

#include "ifb-engine-asset-internal.hpp"

namespace ifb {

    constexpr eng_asset_config_xml_properties_t _properties;

    IFB_ENG_FUNC eng_asset_config_t*
    eng_asset_config_create(
        void) {

        // get an arena
        eng_mem_arena_t* arena = eng_mem_mngr_arena_commit_asset();
        if (!arena) return(NULL);

        // allocate memory
        auto config = eng_mem_mngr_arena_push_struct(arena, eng_asset_config_t);
        if (!config) {
            const eng_bool is_decommit = eng_mem_mngr_arena_decommit(arena);
            assert(is_decommit);
        }

        // create the document
        eng_xml_h32_doc_t xml_doc = sld::xml_doc_create();
        assert(xml_doc.val != SLD_XML_INVALID_HANDLE);

        // open the file
        static const eng_c8* file_path   = IFB_ENG_ASSET_CONFIG_PATH;
        const eng_file_h32_t file_handle = eng_file_mngr_open_rw(file_path);
        assert(file_handle.val != IFB_ENG_FILE_H32_INVALID);

        // initialize the config
        config->arena   = arena;
        config->file    = file_handle;
        config->xml_doc = xml_doc;
        return(config);
    }

    IFB_ENG_FUNC void
    eng_asset_config_destroy(
        eng_asset_config_t* config) {

        eng_asset_config_validate   (config);
        eng_file_mngr_close         (config->file);
        sld::xml_doc_destroy        (config->xml_doc);
        eng_mem_mngr_arena_decommit (config->arena);
    }

    IFB_ENG_FUNC void
    eng_asset_config_validate(
        eng_asset_config_t* const config) {

        eng_bool is_valid = (config != NULL);
        if (is_valid) {
            is_valid &= (config->arena        != NULL);
            is_valid &= (config->xml_file.val != IFB_ENG_FILE_H32_INVALID);
        }
        assert(is_valid);
    }

    IFB_ENG_FUNC void
    eng_asset_config_load_default(
        eng_asset_config_t* const config) {

        eng_asset_config_validate(config);
    }

    IFB_ENG_FUNC void
    eng_asset_config_node_read_text(
        eng_asset_config_t* const config,
        eng_asset_config_node_t&  node) {

        eng_asset_config_validate(config);

    }

    IFB_ENG_FUNC void
    eng_asset_config_node_read_image(
        eng_asset_config_t* const config,
        eng_asset_config_node_t&  node) {

        eng_asset_config_validate(config);

    }

    IFB_ENG_FUNC void
    eng_asset_config_node_read_sound(
        eng_asset_config_t* const config,
        eng_asset_config_node_t&  node) {

        eng_asset_config_validate(config);

    }

    IFB_ENG_FUNC void
    eng_asset_config_node_read_font(
        eng_asset_config_t* const config,
        eng_asset_config_node_t&  node) {

        eng_asset_config_validate(config);

    }

    IFB_ENG_FUNC void
    eng_asset_config_node_write_text(
        eng_asset_config_t* const config,
        eng_asset_config_node_t&  node) {

        eng_asset_config_validate(config);

    }

    IFB_ENG_FUNC void
    eng_asset_config_node_write_image(
        eng_asset_config_t* const config,
        eng_asset_config_node_t&  node) {

        eng_asset_config_validate(config);

    }

    IFB_ENG_FUNC void
    eng_asset_config_node_write_sound(
        eng_asset_config_t* const config,
        eng_asset_config_node_t&  node) {

        eng_asset_config_validate(config);

    }

    IFB_ENG_FUNC void
    eng_asset_config_node_write_font(
        eng_asset_config_t* const config,
        eng_asset_config_node_t&  node) {

        eng_asset_config_validate(config);

    }


};