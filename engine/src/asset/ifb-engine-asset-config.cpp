#pragma once

#include "ifb-engine-asset-config.hpp"

namespace ifb {

    IFB_ENG_INTERNAL eng_asset_config_editor_context_t*
    asset_config_editor_context_init(
        eng_mem_arena_t* arena) {

        assert(arena);

        auto config = sld::arena_push_struct<eng_asset_config_editor_context_t>(arena);
        assert(config);

        return(config);
    }

    IFB_ENG_INTERNAL eng_asset_config_file_node_t*
    asset_config_editor_context_add_text(
        eng_asset_config_editor_context_t* editor_context,
        eng_mem_arena_t*                   arena,
        const cchar*                       asset_name,
        const cchar*                       asset_path) {

        const bool can_add = (
            editor_context != NULL &&
            arena          != NULL &&
            asset_name     != NULL &&
            asset_path     != NULL 
        );
        assert(can_add);

        eng_asset_config_file_node_t* text_node = asset_config_arena_alloc_file_node(arena);
        asset_config_file_node_update_name (text_node, asset_name);
        asset_config_file_node_update_path (text_node, asset_path);
        asset_config_file_list_add_node    (&editor_context->file_list.text, text_node);

    }

    IFB_ENG_INTERNAL eng_asset_config_file_node_t*
    asset_config_editor_context_add_image(
        eng_asset_config_editor_context_t* editor_context,
        eng_mem_arena_t*                   arena,
        const cchar*                       asset_name,
        const cchar*                       asset_path) {

    }

    IFB_ENG_INTERNAL eng_asset_config_file_node_t*
    asset_config_editor_context_add_sound(
        eng_asset_config_editor_context_t* editor_context,
        eng_mem_arena_t*                   arena,
        const cchar*                       asset_name,
        const cchar*                       asset_path) {

    }

    IFB_ENG_INTERNAL eng_asset_config_file_node_t*
    asset_config_editor_context_add_font(
        eng_asset_config_editor_context_t* editor_context,
        eng_mem_arena_t*                   arena,
        const cchar*                       asset_name,
        const cchar*                       asset_path) {

    }

    IFB_ENG_INTERNAL void
    asset_config_editor_context_update_file_node_name(
        eng_asset_config_file_node_t* file_node,
        const cchar*                  asset_name) {

    }

    IFB_ENG_INTERNAL void
    asset_config_editor_context_update_file_node_path(
        eng_asset_config_file_node_t* file_node,
        const cchar*                  asset_path) {

    }

    IFB_ENG_INTERNAL void
    asset_config_editor_delete_file_node(
        eng_asset_config_file_node_t* file_node) {

    }

};