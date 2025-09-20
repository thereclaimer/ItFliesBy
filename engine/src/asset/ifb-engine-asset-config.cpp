#pragma once

#include "ifb-engine-asset-internal.hpp"

namespace ifb {

    constexpr eng_asset_config_xml_properties_t _properties;

    IFB_ENG_FUNC eng_asset_config_t*
    eng_asset_config_create(
        void) {

        // get an arena
        eng_mem_arena_t* arena = eng_mem_arena_commit_asset();
        if (!arena) return(NULL);

        // allocate memory
        auto config = eng_mem_arena_push_struct(arena, eng_asset_config_t);
        if (!config) {
            const eng_bool is_decommit = eng_mem_arena_decommit(arena);
            assert(is_decommit);
        }

        // save memory position
        const eng_bool is_mem_ok = sld::arena_save_position(arena); 
        assert(is_mem_ok);

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
        eng_mem_arena_decommit (config->arena);
    }

    IFB_ENG_FUNC void
    eng_asset_config_validate(
        eng_asset_config_t* const config) {

        eng_bool is_valid = (config != NULL);
        if (is_valid) {
            is_valid &= (config->arena       != NULL);
            is_valid &= (config->xml_doc.val != IFB_ENG_FILE_H32_INVALID);
        }
        assert(is_valid);
    }

    IFB_ENG_FUNC void
    eng_asset_config_load_default(
        eng_asset_config_t* const config) {

        eng_asset_config_validate(config);

        static const eng_u32 size           = sizeof(_properties.default_config);
        static eng_buffer_t  default_buffer = {
            (byte*)_properties.default_config, // data
            size,                              // size
            size                               // length
        };

        sld::xml_doc_buffer_read(config->xml_doc, default_buffer);
    }

    IFB_ENG_FUNC eng_void
    eng_asset_config_save_file(
        eng_asset_config_t* const config) {
        
        eng_asset_config_validate(config);

        // allocate memory
        const eng_u64  buffer_size = sld::xml_doc_buffer_length (config->xml_doc);  
        eng_byte*      buffer_data = sld::arena_push_bytes      (config->arena, buffer_size); 
        assert(buffer_size != 0 && buffer_data != NULL);

        // initialize file buffer
        eng_file_buffer_t xml_file_buffer;
        xml_file_buffer.data        = buffer_data;
        xml_file_buffer.size        = buffer_size; 
        xml_file_buffer.length      = 0;
        xml_file_buffer.cursor      = 0;
        xml_file_buffer.transferred = 0;

        bool did_save = true;
        did_save &= sld::xml_doc_buffer_write (config->xml_doc, xml_file_buffer);
        did_save &= eng_file_mngr_write       (config->file,    xml_file_buffer); 
        assert(did_save);

    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_read_text(
        eng_asset_config_t* const  config,
        eng_asset_config_assets_t& node) {

        eng_asset_config_validate(config);

        const bool did_read = eng_asset_config_node_read_assets(
            config, node, _properties.node.text
        );
    
        return(did_read);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_read_image(
        eng_asset_config_t* const config,
        eng_asset_config_assets_t&  node) {

        eng_asset_config_validate(config);

        const bool did_read = eng_asset_config_node_read_assets(
            config, node, _properties.node.image
        );
    
        return(did_read);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_read_sound(
        eng_asset_config_t* const config,
        eng_asset_config_assets_t&  node) {

        eng_asset_config_validate(config);

        const bool did_read = eng_asset_config_node_read_assets(
            config, node, _properties.node.sound
        );
    
        return(did_read);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_read_font(
        eng_asset_config_t* const config,
        eng_asset_config_assets_t&  node) {

        eng_asset_config_validate(config);

        const bool did_read = eng_asset_config_node_read_assets(
            config, node, _properties.node.font
        );
    
        return(did_read);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_write_text(
        eng_asset_config_t* const config,
        eng_asset_config_assets_t&  node) {

        eng_asset_config_validate(config);

    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_write_image(
        eng_asset_config_t* const config,
        eng_asset_config_assets_t&  node) {

        eng_asset_config_validate(config);
    
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_write_sound(
        eng_asset_config_t* const config,
        eng_asset_config_assets_t&  node) {

        eng_asset_config_validate(config);

    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_write_font(
        eng_asset_config_t* const config,
        eng_asset_config_assets_t&  node) {

        eng_asset_config_validate(config);

    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_read_assets(
        eng_asset_config_t* const  config,
        eng_asset_config_assets_t& node,
        const eng_c8*              type_name) {

        bool is_mem_ok = sld::arena_roll_back(config->arena);
        assert(is_mem_ok);

        const eng_xml_h32_node_t config_node = sld::xml_doc_get_child_node(config->xml_doc, type_name);
        bool did_read = (config_node.val != SLD_XML_INVALID_HANDLE); 
        if (did_read) {

            // allocate memory
            node.count      =  sld::xml_node_get_child_count(config_node, _properties.node.asset);
            is_mem_ok       =  sld::arena_save_position(config->arena);
            node.array.name =  eng_mem_arena_push_struct_array(config->arena, node.count, eng_asset_name_str8_t);
            node.array.path =  eng_mem_arena_push_struct_array(config->arena, node.count, eng_asset_path_str8_t);
            is_mem_ok       &= (node.array.name != NULL);            
            is_mem_ok       &= (node.array.path != NULL);            
            assert(is_mem_ok);

            sld::str8_t name_str = { NULL,  sizeof(eng_asset_name_str8_t) };
            sld::str8_t path_str = { NULL,  sizeof(eng_asset_path_str8_t) };
            sld::xml_attrib_value_t attrib_asset_name;
            sld::xml_attrib_value_t attrib_asset_path;
            eng_u32 index = 0;
            for (
                eng_xml_h32_node_t asset_node =  sld::xml_node_get_child(config_node, _properties.node.asset);
                asset_node.val                != SLD_XML_INVALID_HANDLE;
                asset_node                    =  sld::xml_node_get_sibling(asset_node, _properties.node.asset)) {

                did_read &= sld::xml_node_get_attrib_utf8(asset_node, _properties.attrib.name, attrib_asset_name); 
                did_read &= sld::xml_node_get_attrib_utf8(asset_node, _properties.attrib.path, attrib_asset_path);

                name_str.chars = node.array.name[index].chars;
                path_str.chars = node.array.path[index].chars;
                sld::str8_copy(name_str, attrib_asset_name.as_utf8, name_str.size);
                sld::str8_copy(path_str, attrib_asset_path.as_utf8, path_str.size);
            
                ++index;
                assert(index < node.count);
            }
        }

        sld::xml_doc_reset(config->xml_doc);
        return(did_read);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_write_assets(
        eng_asset_config_t* const  config,
        eng_asset_config_assets_t& node,
        const eng_c8*              type_name) {

        const eng_xml_h32_node_t config_node = sld::xml_doc_get_child_node(config->xml_doc, type_name);
        bool did_read = (config_node.val != SLD_XML_INVALID_HANDLE); 
      
        for (
            eng_u32 index = 0;
            index < node.count;
            ++index) {

            sld::xml_node_add_child()

        }

        sld::xml_doc_reset(config->xml_doc);
        return(did_read);
    }

    IFB_ENG_FUNC eng_u64
    eng_asset_config_get_xml_buffer_size(
        eng_asset_config_t* const config) {

        eng_asset_config_validate(config);

        const eng_u64 size = sld::xml_doc_buffer_length(config->xml_doc);
        return(size);
    }

    IFB_ENG_FUNC eng_void
    eng_asset_config_get_xml_buffer(
        eng_asset_config_t* const config,
        eng_buffer_t&             buffer) {

        const eng_bool did_write = sld::xml_doc_buffer_write(
            config->xml_doc,
            buffer
        );

        assert(did_write);
    }
};