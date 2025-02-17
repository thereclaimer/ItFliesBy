#ifndef IFB_ENGINE_HPP
#define IFB_ENGINE_HPP

#include <ifb.hpp>

#include "ifb-engine-types.hpp"
#include "ifb-engine-context.hpp"

ifb_global IFBPlatformApi* _ptr_platform_api;

namespace ifb_engine {

    inline const IFBPlatformApi* platform_api(ifb_void) { 
        ifb_macro_assert(_ptr_platform_api);
        return(_ptr_platform_api); 
    }
};

#endif //IFB_ENGINE_HPP