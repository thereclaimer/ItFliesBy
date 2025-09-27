#pragma once

#include "ifb-engine-asset-internal.hpp"

namespace ifb {

    constexpr eng_cchar _xml_cstr_node_ifb_assets [] = "ifb-assets";
    constexpr eng_cchar _xml_cstr_node_text       [] = "text";
    constexpr eng_cchar _xml_cstr_node_image      [] = "image";
    constexpr eng_cchar _xml_cstr_node_sound      [] = "sound";
    constexpr eng_cchar _xml_cstr_node_font       [] = "font";
    constexpr eng_cchar _xml_cstr_node_asset      [] = "asset";

    constexpr eng_cchar _xml_cstr_attrib_name     [] = "name"; 
    constexpr eng_cchar _xml_cstr_attrib_path     [] = "path"; 

    constexpr eng_cchar _xml_cstr_default_config  [] = 
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

    IFB_ENG_FUNC eng_asset_config_t*
    eng_asset_config_create(
        void) {

        // get an arena
        eng_mem_arena_t* arena = eng_mem_arena_commit_asset();
        assert(arena);

        // check stack size
        const u32 xml_stack_size     = sld::size_kilobytes(IFB_ENG_ASSET_XML_STACK_SIZE_KB);
        const u32 xml_stack_size_min = sld::xml_stack_minimum_size();
        assert(xml_stack_size >= xml_stack_size_min);

        // allocate memory
        eng_asset_config_t* config           = eng_mem_arena_push_struct(arena, eng_asset_config_t);
        void*               xml_stack_memory = eng_mem_arena_push_bytes (arena, xml_stack_size);

        // check allocations and save position
        eng_bool is_mem_ok = true;        
        is_mem_ok &= (config           != NULL);
        is_mem_ok &= (xml_stack_memory != NULL);
        is_mem_ok &= sld::arena_save_position(arena); 
        assert(is_mem_ok);

        // initialize the config
        config->arena     = arena;
        config->file      = eng_file_mngr_open_rw(IFB_ENG_ASSET_CONFIG_PATH); 
        config->xml_stack = sld::xml_stack_init(xml_stack_memory, xml_stack_size);

        // check config and return
        bool is_init = true;
        is_init &= (config->file.val  != IFB_ENG_FILE_H32_INVALID);
        is_init &= (config->xml_stack != NULL);
        assert(is_init);
        return(config);
    }

    IFB_ENG_FUNC void
    eng_asset_config_destroy(
        eng_asset_config_t* config) {

        eng_asset_config_validate (config);
        eng_file_mngr_close       (config->file);
        eng_mem_arena_decommit    (config->arena);
    }

    IFB_ENG_FUNC void
    eng_asset_config_validate(
        eng_asset_config_t* const config) {

        eng_bool is_valid = (config != NULL);
        if (is_valid) {
            is_valid &= (config->arena     != NULL);
            is_valid &= (config->xml_stack != NULL);
            is_valid &= (config->file.val  != IFB_ENG_FILE_H32_INVALID);
        }
        assert(is_valid);
    }

    IFB_ENG_FUNC void
    eng_asset_config_load_default(
        eng_asset_config_t* const config) {

        eng_asset_config_validate(config);

        static const eng_u32 size           = sizeof(_xml_cstr_default_config);
        static eng_buffer_t  default_buffer = {
            (byte*)_xml_cstr_default_config, // data
            size,                            // size
            size                             // length
        };

        // reset the xml document
        sld::xml_stack_reset(config->xml_stack);
        config->xml_doc = sld::xml_stack_push_doc (config->xml_stack);
        assert(config->xml_doc);

        // read the default buffer
        bool did_read = sld::xml_doc_buffer_read(config->xml_doc, default_buffer);
        assert(did_read);
    }

    IFB_ENG_FUNC eng_void
    eng_asset_config_save_file(
        eng_asset_config_t* const config) {
        
        eng_asset_config_validate(config);

        // allocate memory
        const eng_u64  buffer_size = sld::xml_doc_buffer_length (config->xml_doc);  
        const eng_bool is_mem_ok   = sld::arena_roll_back       (config->arena);
        eng_byte*      buffer_data = sld::arena_push_bytes      (config->arena, buffer_size); 
        assert(
            buffer_size != 0    &&
            buffer_data != NULL &&
            is_mem_ok   == true
        );

        // initialize file buffer
        eng_file_buffer_t xml_file_buffer;
        xml_file_buffer.data        = buffer_data;
        xml_file_buffer.size        = buffer_size; 
        xml_file_buffer.length      = 0;
        xml_file_buffer.cursor      = 0;
        xml_file_buffer.transferred = 0;

        // write the buffer and reset the arena
        bool did_save = true;
        did_save &= sld::xml_doc_buffer_write (config->xml_doc, xml_file_buffer);
        did_save &= eng_file_mngr_write       (config->file,    xml_file_buffer);
        assert(did_save);
    }

    IFB_ENG_FUNC eng_void
    eng_asset_config_read_file(
        eng_asset_config_t* const config) {

        eng_asset_config_validate(config);

        // get the file size
        const eng_u64 size = eng_file_mngr_get_size(config->file);
        if (size == 0) return;

        // allocate memory
        eng_bool  is_mem_ok  = sld::arena_roll_back  (config->arena);
        eng_byte* config_mem = sld::arena_push_bytes (config->arena, size);
        assert(is_mem_ok && config_mem != NULL);

        // initialize the file buffer
        eng_file_buffer_t file_buffer;
        file_buffer.data        = config_mem;
        file_buffer.size        = size;
        file_buffer.length      = 0;
        file_buffer.cursor      = 0;
        file_buffer.transferred = 0;

        // reset the xml
        eng_bool did_read = true; 
        sld::xml_stack_reset(config->xml_stack);
        config->xml_doc = sld::xml_stack_push_doc(config->xml_stack);
        assert(config->xml_doc);

        // read and parse the xml
        did_read &= eng_file_mngr_read       (config->file,    file_buffer);
        did_read &= sld::xml_doc_buffer_read (config->xml_doc, file_buffer);
        assert(did_read);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_read_text(
        eng_asset_config_t* const  config,
        eng_asset_config_node_t& node) {

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
        eng_asset_config_node_t&  node) {

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
        eng_asset_config_node_t&  node) {

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
        eng_asset_config_node_t&  node) {

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
        eng_asset_config_node_t&  node) {

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
        eng_asset_config_node_t&  node) {

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
        eng_asset_config_node_t&  node) {

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
        eng_asset_config_node_t&  node) {

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
        eng_asset_config_node_t& node,
        eng_xml_h32_node_t         xml_type) {

        bool is_mem_ok = sld::arena_roll_back(config->arena);
        assert(is_mem_ok);

        bool did_read = (xml_type.val != SLD_XML_INVALID_HANDLE); 
        if (did_read) {

            // allocate memory
            node.count      =  sld::xml_node_get_child_count(xml_type, _xml_cstr_node_asset);
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
                eng_xml_h32_node_t asset_node =  sld::xml_node_get_child(xml_type, _xml_cstr_node_asset);
                asset_node.val                != SLD_XML_INVALID_HANDLE;
                asset_node                    =  sld::xml_node_get_next_sibling(asset_node, _xml_cstr_node_asset)) {

                did_read &= sld::xml_attrib_get_val_utf8(asset_node, _xml_cstr_attrib_name, attrib_asset_name); 
                did_read &= sld::xml_attrib_get_val_utf8(asset_node, _xml_cstr_attrib_path, attrib_asset_path);

                assert(index < node.count);
                name_str.chars = node.array.name[index].chars;
                path_str.chars = node.array.path[index].chars;
                sld::cstr_copy(name_str, attrib_asset_name.as_utf8, name_str.size);
                sld::cstr_copy(path_str, attrib_asset_path.as_utf8, path_str.size);
            
                ++index;
            }
        }

        sld::xml_doc_reset(config->xml.doc);
        return(did_read);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_write_assets(
        eng_asset_config_t* const  config,
        eng_asset_config_node_t& node,
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

                const eng_xml_h32_node_t asset_node = sld::xml_node_add_child(xml_type, _xml_cstr_node_asset);
                did_write &= sld::xml_attrib_set_val_utf8(asset_node, _xml_cstr_attrib_name, attrib_name);
                did_write &= sld::xml_attrib_set_val_utf8(asset_node, _xml_cstr_attrib_path, attrib_path);
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