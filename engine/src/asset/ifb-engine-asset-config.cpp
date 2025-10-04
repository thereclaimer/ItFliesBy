#pragma once

#include "ifb-engine-asset-internal.hpp"

namespace ifb {

    constexpr cchar _xml_cstr_node_ifb_assets [] = "ifb-assets";
    constexpr cchar _xml_cstr_node_text       [] = "text";
    constexpr cchar _xml_cstr_node_image      [] = "image";
    constexpr cchar _xml_cstr_node_sound      [] = "sound";
    constexpr cchar _xml_cstr_node_font       [] = "font";
    constexpr cchar _xml_cstr_node_asset      [] = "asset";

    constexpr cchar _xml_cstr_attrib_name     [] = "name"; 
    constexpr cchar _xml_cstr_attrib_path     [] = "path"; 

    constexpr cchar _xml_cstr_default_config  [] = 
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

    static eng_asset_config_t* _config;

    IFB_ENG_FUNC void
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
        _eng_asset_mngr.config = eng_mem_arena_push_struct (arena, eng_asset_config_t);
        void* xml_stack_memory = eng_mem_arena_push_bytes  (arena, xml_stack_size);

        // check allocations and save position
        bool is_mem_ok = true;        
        is_mem_ok &= sld::arena_save_position(arena); 
        is_mem_ok &= (_eng_asset_mngr.config != NULL);
        is_mem_ok &= (xml_stack_memory       != NULL);
        assert(is_mem_ok);

        // initialize the config
        _eng_asset_mngr.config->arena           = arena;
        _eng_asset_mngr.config->file            = eng_file_mngr_open_rw      (IFB_ENG_ASSET_CONFIG_PATH); 
        _eng_asset_mngr.config->xml.stack       = sld::xml_stack_init        (xml_stack_memory, xml_stack_size); 
        _eng_asset_mngr.config->xml.doc         = sld::xml_stack_push_doc    (_eng_asset_mngr.config->xml.stack);
        _eng_asset_mngr.config->xml.node.text   = sld::xml_stack_push_node   (_eng_asset_mngr.config->xml.stack);
        _eng_asset_mngr.config->xml.node.image  = sld::xml_stack_push_node   (_eng_asset_mngr.config->xml.stack);
        _eng_asset_mngr.config->xml.node.sound  = sld::xml_stack_push_node   (_eng_asset_mngr.config->xml.stack);
        _eng_asset_mngr.config->xml.node.font   = sld::xml_stack_push_node   (_eng_asset_mngr.config->xml.stack);
        _eng_asset_mngr.config->xml.node.asset  = sld::xml_stack_push_node   (_eng_asset_mngr.config->xml.stack);
        _eng_asset_mngr.config->xml.attrib.name = sld::xml_stack_push_attrib (_eng_asset_mngr.config->xml.stack);
        _eng_asset_mngr.config->xml.attrib.path = sld::xml_stack_push_attrib (_eng_asset_mngr.config->xml.stack);

        // check config and return
        bool is_init = true;
        is_init &= (_eng_asset_mngr.config->file.val        != IFB_ENG_FILE_H32_INVALID);
        is_init &= (_eng_asset_mngr.config->xml.stack       != NULL);
        is_init &= (_eng_asset_mngr.config->xml.doc         != NULL);
        is_init &= (_eng_asset_mngr.config->xml.node.text   != NULL);
        is_init &= (_eng_asset_mngr.config->xml.node.image  != NULL);
        is_init &= (_eng_asset_mngr.config->xml.node.sound  != NULL);
        is_init &= (_eng_asset_mngr.config->xml.node.font   != NULL);
        is_init &= (_eng_asset_mngr.config->xml.attrib.name != NULL);
        is_init &= (_eng_asset_mngr.config->xml.attrib.path != NULL);
        assert(is_init);
    }

    IFB_ENG_FUNC void
    eng_asset_config_destroy(
        void) {

        eng_asset_config_validate ();
        eng_file_mngr_close       (_eng_asset_mngr.config->file);
        eng_mem_arena_decommit    (_eng_asset_mngr.config->arena);
    }

    IFB_ENG_FUNC void
    eng_asset_config_validate(
        void) {

        bool is_valid = (_eng_asset_mngr.config != NULL);
        if (is_valid) {
            is_valid &= (_eng_asset_mngr.config->arena           != NULL);
            is_valid &= (_eng_asset_mngr.config->file.val        != IFB_ENG_FILE_H32_INVALID);
            is_valid &= (_eng_asset_mngr.config->xml.stack       != NULL);
            is_valid &= (_eng_asset_mngr.config->xml.doc         != NULL);
            is_valid &= (_eng_asset_mngr.config->xml.node.text   != NULL);
            is_valid &= (_eng_asset_mngr.config->xml.node.image  != NULL);
            is_valid &= (_eng_asset_mngr.config->xml.node.sound  != NULL);
            is_valid &= (_eng_asset_mngr.config->xml.node.font   != NULL);
            is_valid &= (_eng_asset_mngr.config->xml.node.asset  != NULL);
            is_valid &= (_eng_asset_mngr.config->xml.attrib.name != NULL);
            is_valid &= (_eng_asset_mngr.config->xml.attrib.path != NULL);
        }
        assert(is_valid);
    }

    IFB_ENG_FUNC void
    eng_asset_config_load_default(
        void) {

        eng_asset_config_validate();

        static const u32 size           = sizeof(_xml_cstr_default_config);
        static buffer_t  default_buffer = {
            (byte*)_xml_cstr_default_config, // data
            size,                            // size
            size                             // length
        };

        // reset the xml document
        sld::xml_doc_reset(_eng_asset_mngr.config->xml.doc);

        // read the default buffer
        const bool did_read = sld::xml_doc_buffer_read(_eng_asset_mngr.config->xml.doc, default_buffer);
        assert(did_read);
    }

    IFB_ENG_FUNC void
    eng_asset_config_save_file(
        void) {
        
        eng_asset_config_validate();

        // allocate memory
        const u64  buffer_size = sld::xml_doc_buffer_length (_eng_asset_mngr.config->xml.doc);  
        const bool is_mem_ok   = sld::arena_roll_back       (_eng_asset_mngr.config->arena);
        byte*      buffer_data = sld::arena_push_bytes      (_eng_asset_mngr.config->arena, buffer_size); 
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
        did_save &= sld::xml_doc_buffer_write (_eng_asset_mngr.config->xml.doc, xml_file_buffer);
        did_save &= eng_file_mngr_write       (_eng_asset_mngr.config->file,    xml_file_buffer);
        assert(did_save);
    }

    IFB_ENG_FUNC void
    eng_asset_config_read_file(
        eng_asset_config_t* const config) {

        eng_asset_config_validate();

        // get the file size
        const u64 size = eng_file_mngr_get_size(_eng_asset_mngr.config->file);
        if (size == 0) return;

        // allocate memory
        bool  is_mem_ok  = sld::arena_roll_back  (_eng_asset_mngr.config->arena);
        byte* config_mem = sld::arena_push_bytes (_eng_asset_mngr.config->arena, size);
        assert(is_mem_ok && config_mem != NULL);

        // initialize the file buffer
        eng_file_buffer_t file_buffer;
        file_buffer.data        = config_mem;
        file_buffer.size        = size;
        file_buffer.length      = 0;
        file_buffer.cursor      = 0;
        file_buffer.transferred = 0;

        // reset the xml
        bool did_read = true; 
        sld::xml_doc_reset(_eng_asset_mngr.config->xml.doc);

        // read and parse the xml
        did_read &= eng_file_mngr_read       (_eng_asset_mngr.config->file,    file_buffer);
        did_read &= sld::xml_doc_buffer_read (_eng_asset_mngr.config->xml.doc, file_buffer);
        assert(did_read);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_read_text(
        eng_asset_config_node_t& node) {

        eng_asset_config_validate();

        bool is_valid = true;
        is_valid &= (_eng_asset_mngr.config->xml.node.root != NULL); 
        is_valid &= (_eng_asset_mngr.config->xml.node.text != NULL); 
        assert(is_valid);

        const bool did_read = eng_asset_config_node_read_assets(
            node, _eng_asset_mngr.config->xml.node.text
        );
    
        return(did_read);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_read_image(
        eng_asset_config_node_t&  node) {

        eng_asset_config_validate();

        bool is_valid = true;
        is_valid &= (_eng_asset_mngr.config->xml.node.root  != NULL); 
        is_valid &= (_eng_asset_mngr.config->xml.node.image != NULL); 
        assert(is_valid);

        const bool did_read = eng_asset_config_node_read_assets(
            node, _eng_asset_mngr.config->xml.node.image
        );
    
        return(did_read);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_read_sound(
        eng_asset_config_node_t&  node) {

        eng_asset_config_validate();

        bool is_valid = true;
        is_valid &= (_eng_asset_mngr.config->xml.node.root  != NULL); 
        is_valid &= (_eng_asset_mngr.config->xml.node.sound != NULL); 
        assert(is_valid);

        const bool did_read = eng_asset_config_node_read_assets(
            node, _eng_asset_mngr.config->xml.node.sound
        );
    
        return(did_read);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_read_font(
        eng_asset_config_node_t&  node) {

        eng_asset_config_validate();

        bool is_valid = true;
        is_valid &= (_eng_asset_mngr.config->xml.node.root  != NULL); 
        is_valid &= (_eng_asset_mngr.config->xml.node.font != NULL); 
        assert(is_valid);

        const bool did_read = eng_asset_config_node_read_assets(
            node, _eng_asset_mngr.config->xml.node.font
        );
    
        return(did_read);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_write_text(
        eng_asset_config_node_t&  node) {

        eng_asset_config_validate();

        bool is_valid = true;
        is_valid &= (_eng_asset_mngr.config->xml.node.root  != NULL); 
        is_valid &= (_eng_asset_mngr.config->xml.node.text != NULL); 
        assert(is_valid);

        const bool did_write = eng_asset_config_node_write_assets(
            node, _eng_asset_mngr.config->xml.node.text
        );

        return(did_write);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_write_image(
        eng_asset_config_node_t&  node) {

        eng_asset_config_validate();    

        bool is_valid = true;
        is_valid &= (_eng_asset_mngr.config->xml.node.root  != NULL); 
        is_valid &= (_eng_asset_mngr.config->xml.node.image != NULL); 
        assert(is_valid);

        const bool did_write = eng_asset_config_node_write_assets(
            node, _eng_asset_mngr.config->xml.node.image
        );

        return(did_write);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_write_sound(
        eng_asset_config_node_t&  node) {

        eng_asset_config_validate();

        bool is_valid = true;
        is_valid &= (_eng_asset_mngr.config->xml.node.root  != NULL); 
        is_valid &= (_eng_asset_mngr.config->xml.node.sound != NULL); 
        assert(is_valid);

        const bool did_write = eng_asset_config_node_write_assets(
            node, _eng_asset_mngr.config->xml.node.sound
        );
        
        return(did_write);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_write_font(
        eng_asset_config_node_t&  node) {

        eng_asset_config_validate();

        bool is_valid = true;
        is_valid &= (_eng_asset_mngr.config->xml.node.root != NULL); 
        is_valid &= (_eng_asset_mngr.config->xml.node.font != NULL); 
        assert(is_valid);

        const bool did_write = eng_asset_config_node_write_assets(
            node, _eng_asset_mngr.config->xml.node.font
        );

        return(did_write);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_read_assets(
        eng_asset_config_node_t& node,
        xml_node_t*          xml_type) {

        // get the first asset node if there is any
        bool did_read = sld::xml_node_get_child(xml_type, _xml_cstr_node_asset, _eng_asset_mngr.config->xml.node.asset);
        if (did_read) {

            // allocate memory
            node.count      =  sld::xml_node_get_child_count(xml_type, _xml_cstr_node_asset);
            node.array.name =  eng_mem_arena_push_struct_array(_eng_asset_mngr.config->arena, node.count, eng_asset_cstr_t);
            node.array.path =  eng_mem_arena_push_struct_array(_eng_asset_mngr.config->arena, node.count, eng_asset_cstr_t);
            bool is_mem_ok  = true;
            is_mem_ok       &= (node.array.name != NULL);            
            is_mem_ok       &= (node.array.path != NULL);            
            assert(is_mem_ok);

            constexpr u32 asset_cstr_size = sizeof(eng_asset_cstr_t); 
            cstr_t        dst_cstr_name   = { NULL, asset_cstr_size};
            cstr_t        dst_cstr_path   = { NULL, asset_cstr_size};
            cstr_t        src_cstr_name   = { NULL, asset_cstr_size};
            cstr_t        src_cstr_path   = { NULL, asset_cstr_size};

            for (
                u32 index = 0;
                index < node.count;
                ++index) {

                // read the next asset node and attributes
                did_read &= sld::xml_node_get_next_sibling (_eng_asset_mngr.config->xml.node.asset, _xml_cstr_node_asset,  _eng_asset_mngr.config->xml.node.asset);
                did_read &= sld::xml_node_get_attrib       (_eng_asset_mngr.config->xml.node.asset, _xml_cstr_attrib_name, _eng_asset_mngr.config->xml.attrib.name);
                did_read &= sld::xml_node_get_attrib       (_eng_asset_mngr.config->xml.node.asset, _xml_cstr_attrib_path, _eng_asset_mngr.config->xml.attrib.path);
                did_read &= sld::xml_attrib_get_val_utf8   (_eng_asset_mngr.config->xml.attrib.name, src_cstr_name.chars); 
                did_read &= sld::xml_attrib_get_val_utf8   (_eng_asset_mngr.config->xml.attrib.path, src_cstr_path.chars);

                // copy the name and path 
                dst_cstr_name.chars              =  node.array.name[index].chars;
                dst_cstr_path.chars              =  node.array.path[index].chars;
                const u32 length_copied_name =  sld::cstr_copy(dst_cstr_name, src_cstr_name);
                const u32 length_copied_path =  sld::cstr_copy(dst_cstr_path, src_cstr_path);
                did_read                         &= (length_copied_name > 0);           
                did_read                         &= (length_copied_path > 0);           
            }
        }

        sld::xml_doc_reset(_eng_asset_mngr.config->xml.doc);
        assert(sld::arena_roll_back(_eng_asset_mngr.config->arena));
        return(did_read);
    }

    IFB_ENG_FUNC bool
    eng_asset_config_node_write_assets(
        eng_asset_config_node_t&  node,
        xml_node_t*           xml_type) {

        bool did_write = (xml_type != NULL); 
        if (did_write) {

            for (
                u32 index = 0;
                index < node.count;
                ++index) {

                sld::xml_utf8_t* name_chars = node.array.name[index].chars;
                sld::xml_utf8_t* path_chars = node.array.path[index].chars;

                did_write &= sld::xml_node_add_child      (xml_type, _xml_cstr_node_asset, _eng_asset_mngr.config->xml.node.asset);
                did_write &= sld::xml_node_add_attrib     (_eng_asset_mngr.config->xml.node.asset,  _xml_cstr_attrib_name, _eng_asset_mngr.config->xml.attrib.name);
                did_write &= sld::xml_node_add_attrib     (_eng_asset_mngr.config->xml.node.asset,  _xml_cstr_attrib_path, _eng_asset_mngr.config->xml.attrib.path);
                did_write &= sld::xml_attrib_set_val_utf8 (_eng_asset_mngr.config->xml.attrib.name, name_chars);
                did_write &= sld::xml_attrib_set_val_utf8 (_eng_asset_mngr.config->xml.attrib.path, path_chars);
            }
        }

        sld::xml_doc_reset(_eng_asset_mngr.config->xml.doc);
        return(did_write);
    }

    IFB_ENG_FUNC u64
    eng_asset_config_get_xml_buffer_size() {

        eng_asset_config_validate();

        const u64 size = sld::xml_doc_buffer_length(_eng_asset_mngr.config->xml.doc);
        return(size);
    }

    IFB_ENG_FUNC void
    eng_asset_config_get_xml_buffer(
        buffer_t& buffer) {

        const bool did_write = sld::xml_doc_buffer_write(
            _eng_asset_mngr.config->xml.doc,
            buffer
        );

        assert(did_write);
    }
};