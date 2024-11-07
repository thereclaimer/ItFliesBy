#ifndef IFB_ENGINE_INTERNAL_PLATFORM_HPP
#define IFB_ENGINE_INTERNAL_PLATFORM_HPP

#include <r-libs.hpp>

#include "ifb-engine.hpp"

namespace ifb_engine {

    //system
    ifb_global funcptr_ifb_engine_platform_system_page_size              platform_system_page_size;
    ifb_global funcptr_ifb_engine_platform_system_allocation_granularity platform_system_allocation_granularity;

    //memory
    ifb_global funcptr_ifb_engine_platform_memory_pages_reserve  platform_memory_pages_reserve;
    ifb_global funcptr_ifb_engine_platform_memory_pages_release  platform_memory_pages_release;
    ifb_global funcptr_ifb_engine_platform_memory_pages_commit   platform_memory_pages_commit;
    ifb_global funcptr_ifb_engine_platform_memory_pages_decommit platform_memory_pages_decommit;

    //file
    ifb_global funcptr_ifb_engine_platform_file_open_read_only  platform_file_open_read_only;
    ifb_global funcptr_ifb_engine_platform_file_open_read_write platform_file_open_read_write;
    ifb_global funcptr_ifb_engine_platform_file_close           platform_file_close;
    ifb_global funcptr_ifb_engine_platform_file_size            platform_file_size;
    ifb_global funcptr_ifb_engine_platform_file_read            platform_file_read;
    ifb_global funcptr_ifb_engine_platform_file_write           platform_file_write;

    //file dialog
    ifb_global funcptr_ifb_engine_platform_file_dialog_select_file platform_file_dialog_select_file;


    inline const ifb_b8 
    platform_api_validate(
        IFBEnginePlatformApi& platform_api_ref) {

        ifb_b8 result = true;

        //-----------------
        // system
        //-----------------

        ifb_engine::platform_system_page_size              = platform_api_ref.system.page_size; 
        ifb_engine::platform_system_allocation_granularity = platform_api_ref.system.allocation_granularity; 

        //-----------------
        // memory
        //-----------------

        ifb_engine::platform_memory_pages_reserve  = platform_api_ref.memory.pages_reserve; 
        ifb_engine::platform_memory_pages_release  = platform_api_ref.memory.pages_release; 
        ifb_engine::platform_memory_pages_commit   = platform_api_ref.memory.pages_commit; 
        ifb_engine::platform_memory_pages_decommit = platform_api_ref.memory.pages_decommit;         

        result &= (
            ifb_engine::platform_memory_pages_reserve  != NULL && 
            ifb_engine::platform_memory_pages_release  != NULL && 
            ifb_engine::platform_memory_pages_commit   != NULL && 
            ifb_engine::platform_memory_pages_decommit != NULL);

        //-----------------
        // file
        //-----------------

        ifb_engine::platform_file_open_read_only  = platform_api_ref.file.open_read_only;
        ifb_engine::platform_file_open_read_write = platform_api_ref.file.open_read_write;
        ifb_engine::platform_file_close           = platform_api_ref.file.close;
        ifb_engine::platform_file_size            = platform_api_ref.file.size;
        ifb_engine::platform_file_read            = platform_api_ref.file.read;
        ifb_engine::platform_file_write           = platform_api_ref.file.write;

        result &= (
            ifb_engine::platform_file_open_read_only  != NULL &&
            ifb_engine::platform_file_open_read_write != NULL &&
            ifb_engine::platform_file_close           != NULL &&
            ifb_engine::platform_file_size            != NULL &&
            ifb_engine::platform_file_read            != NULL &&
            ifb_engine::platform_file_write           != NULL);

        //-----------------
        // file dialog
        //-----------------

        ifb_engine::platform_file_dialog_select_file = platform_api_ref.file_dialog.select_file;        

        result &= (
            ifb_engine::platform_file_dialog_select_file != NULL);

        //we're done
        return(result);
    }
};

#endif //IFB_ENGINE_INTERNAL_PLATFORM_HPP