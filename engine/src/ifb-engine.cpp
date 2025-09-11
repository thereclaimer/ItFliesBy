#pragma once

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

        return(is_init);
    }

};