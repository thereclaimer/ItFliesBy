#ifndef IFB_ENGINE_INTERNAL_PLATFORM_HPP
#define IFB_ENGINE_INTERNAL_PLATFORM_HPP

#include <r-libs.hpp>

#include "ifb-engine.hpp"

namespace ifb_engine {

    ifb_global funcptr_ifb_engine_platform_file_open_read_only  platform_file_open_read_only;
    ifb_global funcptr_ifb_engine_platform_file_open_read_write platform_file_open_read_write;
    ifb_global funcptr_ifb_engine_platform_file_close           platform_file_close;
    ifb_global funcptr_ifb_engine_platform_file_size            platform_file_size;
    ifb_global funcptr_ifb_engine_platform_file_read            platform_file_read;
    ifb_global funcptr_ifb_engine_platform_file_write           platform_file_write;

    inline const ifb_b8 
    platform_api_validate(
        IFBEnginePlatformApi& platform_api_ref) {

        ifb_b8 result = true;

        //file
        ifb_engine::platform_file_open_read_only  = platform_api_ref.file.open_read_only;
        ifb_engine::platform_file_open_read_write = platform_api_ref.file.open_read_write;
        ifb_engine::platform_file_close           = platform_api_ref.file.close;
        ifb_engine::platform_file_size            = platform_api_ref.file.size;
        ifb_engine::platform_file_read            = platform_api_ref.file.read;
        ifb_engine::platform_file_write           = platform_api_ref.file.write;

        result &= (
            ifb_engine::platform_file_open_read_only  &&
            ifb_engine::platform_file_open_read_write &&
            ifb_engine::platform_file_close           &&
            ifb_engine::platform_file_size            &&
            ifb_engine::platform_file_read            &&
            ifb_engine::platform_file_write);

        return(result);
    }
};

#endif //IFB_ENGINE_INTERNAL_PLATFORM_HPP