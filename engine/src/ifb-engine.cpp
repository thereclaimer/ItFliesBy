#pragma once

#include <sld-xml.hpp>

#include "ifb-engine.hpp"
#include "ifb-engine-asset-internal.hpp"
#include "ifb-engine-core-internal.hpp"
#include "ifb-engine-file-internal.hpp"
#include "ifb-engine-memory-internal.hpp"

#include "ifb-engine-asset-config.cpp"
#include "ifb-engine-asset-database-builder.cpp"
#include "ifb-engine-asset-database-file.cpp"
#include "ifb-engine-asset-database.cpp"
#include "ifb-engine-asset-manager.cpp"
#include "ifb-engine-asset.cpp"

#include "ifb-engine-core-id.cpp"
#include "ifb-engine-core-image.cpp"
#include "ifb-engine-core.cpp"

#include "ifb-engine-file-manager.cpp"
#include "ifb-engine-memory-manager.cpp"


namespace ifb {

    IFB_ENG_API bool
    eng_init(void) {

        bool is_init = true;

        eng_mem_mngr_init  ();
        eng_file_mngr_init ();
        eng_core_init      ();

        byte data[128];
        eng_buffer_t xml_file_buffer;
        xml_file_buffer.data   = data;
        xml_file_buffer.size   = sizeof(data);
        xml_file_buffer.length = 0;

        const sld::xml_hnd_doc_t  doc  = sld::xml_doc_create(); 
        const sld::xml_hnd_node_t node = sld::xml_doc_add_child_node (doc, "test"); 
        const eng_u64             size = sld::xml_doc_buffer_size    (doc);

        sld::xml_doc_buffer_write (doc, xml_file_buffer);
        sld::xml_doc_destroy      (doc);


        return(is_init);
    }

};