#pragma once

#include <sld-xml.hpp>

#include "ifb-engine.hpp"
#include "ifb-engine-memory-internal.hpp"
#include "ifb-engine-file-internal.hpp"

#include "ifb-engine-file-manager.cpp"
#include "ifb-engine-asset.cpp"
#include "ifb-engine-core-id.cpp"
#include "ifb-engine-core-image.cpp"
#include "ifb-engine-memory-manager.cpp"

namespace ifb {

    IFB_ENG_API bool
    eng_init(void) {

        bool is_init = true;

        eng_mem_mngr_init  ();
        eng_file_mngr_init ();

        const sld::u64 xml_mem_size        = sld::size_megabytes(1);
        const sld::u64 xml_mem_granularity = sld::size_kilobytes(1);
        void*          xml_mem_start       = malloc(xml_mem_size); 

        sld::xml_memory_init(
            xml_mem_start,
            xml_mem_size,
            xml_mem_granularity
        );

        sld::xml_doc_t*    doc    = sld::xml_memory_alloc_doc    ();
        sld::xml_node_t*   node   = sld::xml_memory_alloc_node   ();
        sld::xml_attrib_t* attrib = sld::xml_memory_alloc_attrib ();

        const bool    is_valid = sld::xml_doc_add_child_node (doc, "test", node);
        const eng_u64 size     = sld::xml_doc_buffer_size    (doc);

        byte data[128];
        eng_buffer_t xml_file_buffer;
        xml_file_buffer.data   = data;
        xml_file_buffer.size   = sizeof(data);
        xml_file_buffer.length = 0;

        sld::xml_doc_buffer_write(doc, xml_file_buffer);

        sld::xml_memory_free_doc    (doc);
        sld::xml_memory_free_node   (node);
        sld::xml_memory_free_attrib (attrib);

        free(xml_mem_start);

        return(is_init);
    }

};