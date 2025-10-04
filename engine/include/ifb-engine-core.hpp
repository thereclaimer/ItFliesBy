#pragma once

#include "ifb-engine.hpp"

namespace ifb {

    IFB_ENG_API bool eng_core_startup     (void);
    IFB_ENG_API bool eng_core_shutdown    (void);
    IFB_ENG_API bool eng_core_update      (void);
    IFB_ENG_API bool eng_core_render      (void);
    IFB_ENG_API bool eng_core_should_quit (void);
};