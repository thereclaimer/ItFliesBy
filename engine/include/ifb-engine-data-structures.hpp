#ifndef IFB_ENGINE_DATA_STRUCTURES_HPP
#define IFB_ENGINE_DATA_STRUCTURES_HPP

#include <ifb-common.hpp>
#include "ifb-engine-memory.hpp"
#include "ifb-engine-tables.hpp"

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

struct IFBEngineStack {
    ifb_table_index_stack stack_index;
};

namespace ifb_engine {

    ifb_api const ifb_memory stack_push       (IFBEngineStack& stack_ref, const ifb_u32 size);
    ifb_api const ifb_memory stack_pull       (IFBEngineStack& stack_ref, const ifb_u32 size);
    ifb_api const ifb_memory stack_pointer    (IFBEngineStack& stack_ref);
    ifb_api const ifb_b8     stack_reset      (IFBEngineStack& stack_ref);
    ifb_api const ifb_u32    stack_size_total (IFBEngineStack& stack_ref);
    ifb_api const ifb_u32    stack_size_used  (IFBEngineStack& stack_ref);
};

/**********************************************************************************/
/* QUEUE                                                                          */
/**********************************************************************************/

struct IFBEngineQueue {
    ifb_u32 queue_index;
};

namespace ifb_engine {

    ifb_api const ifb_memory queue_push       (IFBEngineQueue& queue_ref, const ifb_u32 size);
    ifb_api const ifb_memory queue_pop        (IFBEngineQueue& queue_ref, const ifb_u32 size);
    ifb_api const ifb_memory queue_pointer    (IFBEngineQueue& queue_ref);
    ifb_api const ifb_b8     queue_reset      (IFBEngineQueue& queue_ref);
    ifb_api const ifb_u32    queue_size_total (IFBEngineQueue& queue_ref);
    ifb_api const ifb_u32    queue_size_used  (IFBEngineQueue& queue_ref);
};

/**********************************************************************************/
/* ARRAY LIST                                                                      */
/**********************************************************************************/

struct IFBEngineArrayList {
    ifb_u32 index;
}

namespace ifb_engine {

    ifb_api const ifb_u32    array_list_size_total              (IFBEngineArrayList& array_list_ref);
    ifb_api const ifb_u32    array_list_size_used               (IFBEngineArrayList& array_list_ref);
    ifb_api const ifb_u32    array_list_element_size            (IFBEngineArrayList& array_list_ref);
    ifb_api const ifb_u32    array_list_element_count           (IFBEngineArrayList& array_list_ref);
    ifb_api const ifb_b8     array_list_reset                   (IFBEngineArrayList& array_list_ref);
    ifb_api const ifb_memory array_list_element_first           (IFBEngineArrayList& array_list_ref);
    ifb_api const ifb_memory array_list_element_last            (IFBEngineArrayList& array_list_ref);
    ifb_api const ifb_memory array_list_element_at_index        (IFBEngineArrayList& array_list_ref, const ifb_u32    index);
    ifb_api const ifb_b8     array_list_element_remove_at_index (IFBEngineArrayList& array_list_ref, const ifb_u32    index);
    ifb_api const ifb_u32    array_list_element_add             (IFBEngineArrayList& array_list_ref, const ifb_memory element_ptr);
    ifb_api const ifb_u32    array_list_element_add_at_index    (IFBEngineArrayList& array_list_ref, const ifb_memory element_ptr, const ifb_u32 index);
};

#endif //IFB_ENGINE_DATA_STRUCTURES_HPP