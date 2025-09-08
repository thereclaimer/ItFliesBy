#ifndef IFB_ENGINE_MEMORY_INTERNAL_HPP
#ifndef IFB_ENGINE_MEMORY_INTERNAL_HPP

#include <sld-memory.hpp>
#include "ifb-engine-memory.hpp"

namespace ifb {

    typedef sld::reservation_t eng_mem_res_t;

    struct eng_mem_res_platform_t : eng_mem_res_t { };
    struct eng_mem_res_core_t     : eng_mem_res_t { };
    struct eng_mem_res_file_t     : eng_mem_res_t { };

    struct eng_mem_mngr_t {
        eng_mem_res_platform_t* res_platform;
        eng_mem_res_core_t*     res_core;
        eng_mem_res_file_t*     res_file;
    };

    eng_mem_mngr_t& eng_mem_mngr_instance (void);
    bool            eng_mem_mngr_init     (const eng_u64_t size_core, const eng_u64_t size_file_mngr);


};

#endif // IFB_ENGINE_MEMORY_INTERNAL_HPP
