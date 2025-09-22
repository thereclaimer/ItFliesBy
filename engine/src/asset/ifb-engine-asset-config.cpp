#pragma once

#include "ifb-engine-asset-internal.hpp"

namespace ifb {

    struct eng_asset_config_xml_properties_t {
        struct {
            static constexpr eng_c8 ifb_assets [] = "ifb-assets";
            static constexpr eng_c8 text       [] = "text";
            static constexpr eng_c8 image      [] = "image";
            static constexpr eng_c8 sound      [] = "sound";
            static constexpr eng_c8 font       [] = "font";
            static constexpr eng_c8 asset      [] = "asset";
        } node;
        struct {
            static constexpr eng_c8 name [] = "name"; 
            static constexpr eng_c8 path [] = "path"; 
        } attrib;
        static constexpr eng_c8 default_config[] = 
            "<ifb-assets>"
                "<text path=\"../assets/text\">"
                "</text>"
                "<image path=\"../assets/image\">"
                "</image>"
                "<sound path=\"../assets/sound\">"
                "</sound>"
                "<font path=\"../assets/font\">"
                "</font>"
            "</ifb-assets>";
    };

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

        // create the document and nodes
        eng_xml_h32_doc_t  xml_doc        = sld::xml_doc_create         ();
        eng_xml_h32_node_t xml_node_root  = sld::xml_doc_add_child_node (xml_doc,       _properties.node.ifb_assets);
        eng_xml_h32_node_t xml_node_text  = sld::xml_node_add_child     (xml_node_root, _properties.node.text); 
        eng_xml_h32_node_t xml_node_image = sld::xml_node_add_child     (xml_node_root, _properties.node.image); 
        eng_xml_h32_node_t xml_node_sound = sld::xml_node_add_child     (xml_node_root, _properties.node.sound); 
        eng_xml_h32_node_t xml_node_font  = sld::xml_node_add_child     (xml_node_root, _properties.node.font); 
        assert(xml_doc.val        != SLD_XML_INVALID_HANDLE);
        assert(xml_node_root.val  != SLD_XML_INVALID_HANDLE);
        assert(xml_node_text.val  != SLD_XML_INVALID_HANDLE);
        assert(xml_node_image.val != SLD_XML_INVALID_HANDLE);
        assert(xml_node_sound.val != SLD_XML_INVALID_HANDLE);
        assert(xml_node_font.val  != SLD_XML_INVALID_HANDLE);

        // open the file
        static const eng_c8* file_path   = IFB_ENG_ASSET_CONFIG_PATH;
        const eng_file_h32_t file_handle = eng_file_mngr_open_rw(file_path);
        assert(file_handle.val != IFB_ENG_FILE_H32_INVALID);

        // initialize the config
        config->arena          = arena;
        config->file           = file_handle;
        config->xml.doc        = xml_doc;
        config->xml.node_root  = xml_node_root;
        config->xml.node_text  = xml_node_text;
        config->xml.node_image = xml_node_image;
        config->xml.node_sound = xml_node_sound;
        config->xml.node_font  = xml_node_font;
        return(config);
    }

    IFB_ENG_FUNC void
    eng_asset_config_destroy(
        eng_asset_config_t* config) {

        eng_asset_config_validate (config);
        eng_file_mngr_close       (config->file);
        sld::xml_doc_destroy      (config->xml.doc);
        eng_mem_arena_decommit    (config->arena);
    }

    IFB_ENG_FUNC void
    eng_asset_config_validate(
        eng_asset_config_t* const config) {

        eng_bool is_valid = (config != NULL);
        if (is_valid) {
            is_valid &= (config->arena       != NULL);
            is_valid &= (config->xml.doc.val != IFB_ENG_FILE_H32_INVALID);
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

        sld::xml_memory_reset();
        sld::xml_doc_buffer_read(config->xml.doc, default_buffer);

        config->xml.doc        = sld::xml_doc_create         ();
        config->xml.node_root  = sld::xml_doc_add_child_node (config->xml.doc,       _properties.node.ifb_assets);
        config->xml.node_text  = sld::xml_node_add_child     (config->xml.node_root, _properties.node.text); 
        config->xml.node_image = sld::xml_node_add_child     (config->xml.node_root, _properties.node.image); 
        config->xml.node_sound = sld::xml_node_add_child     (config->xml.node_root, _properties.node.sound); 
        config->xml.node_font  = sld::xml_node_add_child     (config->xml.node_root, _properties.node.font);
        assert(config->xml.doc.val        != SLD_XML_INVALID_HANDLE);
        assert(config->xml.node_root.val  != SLD_XML_INVALID_HANDLE);
        assert(config->xml.node_text.val  != SLD_XML_INVALID_HANDLE);
        assert(config->xml.node_image.val != SLD_XML_INVALID_HANDLE);
        assert(config->xml.node_sound.val != SLD_XML_INVALID_HANDLE);
        assert(config->xml.node_font.val  != SLD_XML_INVALID_HANDLE);
    }

    IFB_ENG_FUNC eng_void
    eng_asset_config_save_file(
        eng_asset_config_t* const config) {
        
        eng_asset_config_validate(config);

        // allocate memory
        const eng_u64  buffer_size = sld::xml_doc_buffer_length (config->xml.doc);  
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
        did_save &= sld::xml_doc_buffer_write (config->xml.doc, xml_file_buffer);
        did_save &= eng_file_mngr_write       (config->file,    xml_file_buffer); 
        assert(did_save);

    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_read_text(
        eng_asset_config_t* const  config,
        eng_asset_config_assets_t& node) {

        eng_asset_config_validate(config);

        bool is_valid = true;
        is_valid &= (config->xml.node_root.val != SLD_XML_INVALID_HANDLE); 
        is_valid &= (config->xml.node_text.val != SLD_XML_INVALID_HANDLE); 
        assert(is_valid);

        const bool did_read = eng_asset_config_node_read_assets(
            config, node, config->xml.node_text
        );
    
        return(did_read);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_read_image(
        eng_asset_config_t* const config,
        eng_asset_config_assets_t&  node) {

        eng_asset_config_validate(config);

        bool is_valid = true;
        is_valid &= (config->xml.node_root.val  != SLD_XML_INVALID_HANDLE); 
        is_valid &= (config->xml.node_image.val != SLD_XML_INVALID_HANDLE); 
        assert(is_valid);

        const bool did_read = eng_asset_config_node_read_assets(
            config, node, config->xml.node_image
        );
    
        return(did_read);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_read_sound(
        eng_asset_config_t* const config,
        eng_asset_config_assets_t&  node) {

        eng_asset_config_validate(config);

        bool is_valid = true;
        is_valid &= (config->xml.node_root.val  != SLD_XML_INVALID_HANDLE); 
        is_valid &= (config->xml.node_sound.val != SLD_XML_INVALID_HANDLE); 
        assert(is_valid);

        const bool did_read = eng_asset_config_node_read_assets(
            config, node, config->xml.node_sound
        );
    
        return(did_read);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_read_font(
        eng_asset_config_t* const config,
        eng_asset_config_assets_t&  node) {

        eng_asset_config_validate(config);

        bool is_valid = true;
        is_valid &= (config->xml.node_root.val  != SLD_XML_INVALID_HANDLE); 
        is_valid &= (config->xml.node_font.val != SLD_XML_INVALID_HANDLE); 
        assert(is_valid);

        const bool did_read = eng_asset_config_node_read_assets(
            config, node, config->xml.node_font
        );
    
        return(did_read);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_write_text(
        eng_asset_config_t* const config,
        eng_asset_config_assets_t&  node) {

        eng_asset_config_validate(config);

        bool is_valid = true;
        is_valid &= (config->xml.node_root.val  != SLD_XML_INVALID_HANDLE); 
        is_valid &= (config->xml.node_text.val != SLD_XML_INVALID_HANDLE); 
        assert(is_valid);

        const bool did_write = eng_asset_config_node_write_assets(
            config, node, config->xml.node_text
        );

        return(did_write);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_write_image(
        eng_asset_config_t* const config,
        eng_asset_config_assets_t&  node) {

        eng_asset_config_validate(config);    

        bool is_valid = true;
        is_valid &= (config->xml.node_root.val  != SLD_XML_INVALID_HANDLE); 
        is_valid &= (config->xml.node_image.val != SLD_XML_INVALID_HANDLE); 
        assert(is_valid);

        const bool did_write = eng_asset_config_node_write_assets(
            config, node, config->xml.node_image
        );

        return(did_write);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_write_sound(
        eng_asset_config_t* const config,
        eng_asset_config_assets_t&  node) {

        eng_asset_config_validate(config);

        bool is_valid = true;
        is_valid &= (config->xml.node_root.val  != SLD_XML_INVALID_HANDLE); 
        is_valid &= (config->xml.node_sound.val != SLD_XML_INVALID_HANDLE); 
        assert(is_valid);

        const bool did_write = eng_asset_config_node_write_assets(
            config, node, config->xml.node_sound
        );
        
        return(did_write);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_write_font(
        eng_asset_config_t* const config,
        eng_asset_config_assets_t&  node) {

        eng_asset_config_validate(config);

        bool is_valid = true;
        is_valid &= (config->xml.node_root.val != SLD_XML_INVALID_HANDLE); 
        is_valid &= (config->xml.node_font.val != SLD_XML_INVALID_HANDLE); 
        assert(is_valid);

        const bool did_write = eng_asset_config_node_write_assets(
            config, node, config->xml.node_font
        );

        return(did_write);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_read_assets(
        eng_asset_config_t* const  config,
        eng_asset_config_assets_t& node,
        eng_xml_h32_node_t         xml_type) {

        bool is_mem_ok = sld::arena_roll_back(config->arena);
        assert(is_mem_ok);

        bool did_read = (xml_type.val != SLD_XML_INVALID_HANDLE); 
        if (did_read) {

            // allocate memory
            node.count      =  sld::xml_node_get_child_count(xml_type, _properties.node.asset);
            is_mem_ok       =  sld::arena_save_position(config->arena);
            node.array.name =  eng_mem_arena_push_struct_array(config->arena, node.count, eng_asset_cstr_t);
            node.array.path =  eng_mem_arena_push_struct_array(config->arena, node.count, eng_asset_cstr_t);
            is_mem_ok       &= (node.array.name != NULL);            
            is_mem_ok       &= (node.array.path != NULL);            
            assert(is_mem_ok);

            sld::cstr_t name_str = { NULL,  sizeof(eng_asset_cstr_t) };
            sld::cstr_t path_str = { NULL,  sizeof(eng_asset_cstr_t) };
            sld::xml_attrib_value_t attrib_asset_name;
            sld::xml_attrib_value_t attrib_asset_path;
            eng_u32 index = 0;
            for (
                eng_xml_h32_node_t asset_node =  sld::xml_node_get_child(xml_type, _properties.node.asset);
                asset_node.val                != SLD_XML_INVALID_HANDLE;
                asset_node                    =  sld::xml_node_get_next_sibling(asset_node, _properties.node.asset)) {

                did_read &= sld::xml_attrib_get_val_utf8(asset_node, _properties.attrib.name, attrib_asset_name); 
                did_read &= sld::xml_attrib_get_val_utf8(asset_node, _properties.attrib.path, attrib_asset_path);

                name_str.chars = node.array.name[index].chars;
                path_str.chars = node.array.path[index].chars;
                sld::cstr_copy(name_str, attrib_asset_name.as_utf8, name_str.size);
                sld::cstr_copy(path_str, attrib_asset_path.as_utf8, path_str.size);
            
                ++index;
                assert(index < node.count);
            }
        }

        sld::xml_doc_reset(config->xml.doc);
        return(did_read);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_write_assets(
        eng_asset_config_t* const  config,
        eng_asset_config_assets_t& node,
        eng_xml_h32_node_t         xml_type) {

        bool did_write = (xml_type.val != SLD_XML_INVALID_HANDLE); 
        if (did_write) {

            sld::xml_attrib_value_t attrib_name;
            sld::xml_attrib_value_t attrib_path;

            for (
                eng_u32 index = 0;
                index < node.count;
                ++index) {

                attrib_name.as_utf8 = node.array.name[index].chars;
                attrib_path.as_utf8 = node.array.path[index].chars;

                const eng_xml_h32_node_t asset_node = sld::xml_node_add_child(xml_type, _properties.node.asset);
                did_write &= sld::xml_attrib_set_val_utf8(asset_node, _properties.attrib.name, attrib_name);
                did_write &= sld::xml_attrib_set_val_utf8(asset_node, _properties.attrib.path, attrib_path);
            }
        }

        sld::xml_doc_reset(config->xml.doc);
        return(did_write);
    }

    IFB_ENG_FUNC eng_u64
    eng_asset_config_get_xml_buffer_size(
        eng_asset_config_t* const config) {

        eng_asset_config_validate(config);

        const eng_u64 size = sld::xml_doc_buffer_length(config->xml.doc);
        return(size);
    }

    IFB_ENG_FUNC eng_void
    eng_asset_config_get_xml_buffer(
        eng_asset_config_t* const config,
        eng_buffer_t&             buffer) {

        const eng_bool did_write = sld::xml_doc_buffer_write(
            config->xml.doc,
            buffer
        );

        assert(did_write);
    }
};