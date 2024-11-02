#include "ifb-engine-internal-core.hpp"
#include "ifb-engine-internal.hpp"

#include <string.h>

inline const ifb_b8 
ifb_engine::core_initialize(
    IFBEngineCore& core_ref) {

    ifb_b8 result = true;

    //reserve the memory
    result &= ifb_engine::core_memory_reserve(core_ref.memory);

    return(result);
}