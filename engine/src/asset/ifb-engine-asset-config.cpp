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
        eng_asset_config_t* config           = eng_mem_arena_push_struct (arena, eng_asset_config_t);
        void*               xml_stack_memory = eng_mem_arena_push_bytes  (arena, xml_stack_size);

        // check allocations and save position
        eng_bool is_mem_ok = true;        
        is_mem_ok &= sld::arena_save_position(arena); 
        is_mem_ok &= (config           != NULL);
        is_mem_ok &= (xml_stack_memory != NULL);
        assert(is_mem_ok);

        // initialize the config
        config->arena           = arena;
        config->file            = eng_file_mngr_open_rw      (IFB_ENG_ASSET_CONFIG_PATH); 
        config->xml.stack       = sld::xml_stack_init        (xml_stack_memory, xml_stack_size); 
        config->xml.doc         = sld::xml_stack_push_doc    (config->xml.stack);
        config->xml.node.text   = sld::xml_stack_push_node   (config->xml.stack);
        config->xml.node.image  = sld::xml_stack_push_node   (config->xml.stack);
        config->xml.node.sound  = sld::xml_stack_push_node   (config->xml.stack);
        config->xml.node.font   = sld::xml_stack_push_node   (config->xml.stack);
        config->xml.node.asset  = sld::xml_stack_push_node   (config->xml.stack);
        config->xml.attrib.name = sld::xml_stack_push_attrib (config->xml.stack);
        config->xml.attrib.path = sld::xml_stack_push_attrib (config->xml.stack);

        // check config and return
        bool is_init = true;
        is_init &= (config->file.val        != IFB_ENG_FILE_H32_INVALID);
        is_init &= (config->xml.stack       != NULL);
        is_init &= (config->xml.doc         != NULL);
        is_init &= (config->xml.node.text   != NULL);
        is_init &= (config->xml.node.image  != NULL);
        is_init &= (config->xml.node.sound  != NULL);
        is_init &= (config->xml.node.font   != NULL);
        is_init &= (config->xml.attrib.name != NULL);
        is_init &= (config->xml.attrib.path != NULL);
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
            is_valid &= (config->arena           != NULL);
            is_valid &= (config->file.val        != IFB_ENG_FILE_H32_INVALID);
            is_valid &= (config->xml.stack       != NULL);
            is_valid &= (config->xml.doc         != NULL);
            is_valid &= (config->xml.node.text   != NULL);
            is_valid &= (config->xml.node.image  != NULL);
            is_valid &= (config->xml.node.sound  != NULL);
            is_valid &= (config->xml.node.font   != NULL);
            is_valid &= (config->xml.node.asset  != NULL);
            is_valid &= (config->xml.attrib.name != NULL);
            is_valid &= (config->xml.attrib.path != NULL);
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
        sld::xml_doc_reset(config->xml.doc);

        // read the default buffer
        bool did_read = sld::xml_doc_buffer_read(config->xml.doc, default_buffer);
        assert(did_read);
    }

    IFB_ENG_FUNC eng_void
    eng_asset_config_save_file(
        eng_asset_config_t* const config) {
        
        eng_asset_config_validate(config);

        // allocate memory
        const eng_u64  buffer_size = sld::xml_doc_buffer_length (config->xml.doc);  
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
        did_save &= sld::xml_doc_buffer_write (config->xml.doc, xml_file_buffer);
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
        sld::xml_doc_reset(config->xml.doc);

        // read and parse the xml
        did_read &= eng_file_mngr_read       (config->file,    file_buffer);
        did_read &= sld::xml_doc_buffer_read (config->xml.doc, file_buffer);
        assert(did_read);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_read_text(
        eng_asset_config_t* const  config,
        eng_asset_config_node_t& node) {

        eng_asset_config_validate(config);

        bool is_valid = true;
        is_valid &= (config->xml.node.root != NULL); 
        is_valid &= (config->xml.node.text != NULL); 
        assert(is_valid);

        const bool did_read = eng_asset_config_node_read_assets(
            config, node, config->xml.node.text
        );
    
        return(did_read);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_read_image(
        eng_asset_config_t* const config,
        eng_asset_config_node_t&  node) {

        eng_asset_config_validate(config);

        bool is_valid = true;
        is_valid &= (config->xml.node.root  != NULL); 
        is_valid &= (config->xml.node.image != NULL); 
        assert(is_valid);

        const bool did_read = eng_asset_config_node_read_assets(
            config, node, config->xml.node.image
        );
    
        return(did_read);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_read_sound(
        eng_asset_config_t* const config,
        eng_asset_config_node_t&  node) {

        eng_asset_config_validate(config);

        bool is_valid = true;
        is_valid &= (config->xml.node.root  != NULL); 
        is_valid &= (config->xml.node.sound != NULL); 
        assert(is_valid);

        const bool did_read = eng_asset_config_node_read_assets(
            config, node, config->xml.node.sound
        );
    
        return(did_read);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_read_font(
        eng_asset_config_t* const config,
        eng_asset_config_node_t&  node) {

        eng_asset_config_validate(config);

        bool is_valid = true;
        is_valid &= (config->xml.node.root  != NULL); 
        is_valid &= (config->xml.node.font != NULL); 
        assert(is_valid);

        const bool did_read = eng_asset_config_node_read_assets(
            config, node, config->xml.node.font
        );
    
        return(did_read);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_write_text(
        eng_asset_config_t* const config,
        eng_asset_config_node_t&  node) {

        eng_asset_config_validate(config);

        bool is_valid = true;
        is_valid &= (config->xml.node.root  != NULL); 
        is_valid &= (config->xml.node.text != NULL); 
        assert(is_valid);

        const bool did_write = eng_asset_config_node_write_assets(
            config, node, config->xml.node.text
        );

        return(did_write);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_write_image(
        eng_asset_config_t* const config,
        eng_asset_config_node_t&  node) {

        eng_asset_config_validate(config);    

        bool is_valid = true;
        is_valid &= (config->xml.node.root  != NULL); 
        is_valid &= (config->xml.node.image != NULL); 
        assert(is_valid);

        const bool did_write = eng_asset_config_node_write_assets(
            config, node, config->xml.node.image
        );

        return(did_write);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_write_sound(
        eng_asset_config_t* const config,
        eng_asset_config_node_t&  node) {

        eng_asset_config_validate(config);

        bool is_valid = true;
        is_valid &= (config->xml.node.root  != NULL); 
        is_valid &= (config->xml.node.sound != NULL); 
        assert(is_valid);

        const bool did_write = eng_asset_config_node_write_assets(
            config, node, config->xml.node.sound
        );
        
        return(did_write);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_write_font(
        eng_asset_config_t* const config,
        eng_asset_config_node_t&  node) {

        eng_asset_config_validate(config);

        bool is_valid = true;
        is_valid &= (config->xml.node.root != NULL); 
        is_valid &= (config->xml.node.font != NULL); 
        assert(is_valid);

        const bool did_write = eng_asset_config_node_write_assets(
            config, node, config->xml.node.font
        );

        return(did_write);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_read_assets(
        eng_asset_config_t* const  config,
        eng_asset_config_node_t&   node,
        eng_xml_node_t*            xml_type) {

        // get the first asset node if there is any
        bool did_read = sld::xml_node_get_child(xml_type, _xml_cstr_node_asset, config->xml.node.asset);
        if (did_read) {

            // allocate memory
            node.count      =  sld::xml_node_get_child_count(xml_type, _xml_cstr_node_asset);
            node.array.name =  eng_mem_arena_push_struct_array(config->arena, node.count, eng_asset_cstr_t);
            node.array.path =  eng_mem_arena_push_struct_array(config->arena, node.count, eng_asset_cstr_t);
            bool is_mem_ok  = true;
            is_mem_ok       &= (node.array.name != NULL);            
            is_mem_ok       &= (node.array.path != NULL);            
            assert(is_mem_ok);

            constexpr eng_u32 asset_cstr_size = sizeof(eng_asset_cstr_t); 
            eng_cstr_t        dst_cstr_name   = { NULL, asset_cstr_size};
            eng_cstr_t        dst_cstr_path   = { NULL, asset_cstr_size};
            eng_cstr_t        src_cstr_name   = { NULL, asset_cstr_size};
            eng_cstr_t        src_cstr_path   = { NULL, asset_cstr_size};

            for (
                eng_u32 index = 0;
                index < node.count;
                ++index) {

                // read the next asset node and attributes
                did_read &= sld::xml_node_get_next_sibling (config->xml.node.asset, _xml_cstr_node_asset,  config->xml.node.asset);
                did_read &= sld::xml_node_get_attrib       (config->xml.node.asset, _xml_cstr_attrib_name, config->xml.attrib.name);
                did_read &= sld::xml_node_get_attrib       (config->xml.node.asset, _xml_cstr_attrib_path, config->xml.attrib.path);
                did_read &= sld::xml_attrib_get_val_utf8   (config->xml.attrib.name, src_cstr_name.chars); 
                did_read &= sld::xml_attrib_get_val_utf8   (config->xml.attrib.path, src_cstr_path.chars);

                // copy the name and path 
                dst_cstr_name.chars              =  node.array.name[index].chars;
                dst_cstr_path.chars              =  node.array.path[index].chars;
                const eng_u32 length_copied_name =  sld::cstr_copy(dst_cstr_name, src_cstr_name);
                const eng_u32 length_copied_path =  sld::cstr_copy(dst_cstr_path, src_cstr_path);
                did_read                         &= (length_copied_name > 0);           
                did_read                         &= (length_copied_path > 0);           
            }
        }

        sld::xml_doc_reset(config->xml.doc);
        assert(sld::arena_roll_back(config->arena));
        return(did_read);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_write_assets(
        eng_asset_config_t* const config,
        eng_asset_config_node_t&  node,
        eng_xml_node_t*           xml_type) {

        bool did_write = (xml_type != NULL); 
        if (did_write) {

            for (
                eng_u32 index = 0;
                index < node.count;
                ++index) {

                sld::xml_utf8_t* name_chars = node.array.name[index].chars;
                sld::xml_utf8_t* path_chars = node.array.path[index].chars;

                did_write &= sld::xml_node_add_child      (xml_type, _xml_cstr_node_asset, config->xml.node.asset);
                did_write &= sld::xml_node_add_attrib     (config->xml.node.asset,  _xml_cstr_attrib_name,config->xml.attrib.name);
                did_write &= sld::xml_node_add_attrib     (config->xml.node.asset,  _xml_cstr_attrib_path,config->xml.attrib.path);
                did_write &= sld::xml_attrib_set_val_utf8 (config->xml.attrib.name, name_chars);
                did_write &= sld::xml_attrib_set_val_utf8 (config->xml.attrib.path, path_chars);
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