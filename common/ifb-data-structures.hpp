#ifndef IFB_ENGINE_DATA_STRUCTURES_HPP
#define IFB_ENGINE_DATA_STRUCTURES_HPP

#include "ifb-types.hpp"
#include "ifb-memory.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBDataStructure {
    ifb_address start;
    ifb_u32     size;
};

struct IFBStack;
struct IFBQueue;
struct IFBArrayList;

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

struct IFBStack : IFBDataStructure {
    ifb_u32 position;
};

namespace ifb_data {

    const ifb_u32    stack_push    (IFBStack& stack_ref, const ifb_u32    size);
    const ifb_b8     stack_pull    (IFBStack& stack_ref, const ifb_u32    size);
    const ifb_memory stack_pointer (IFBStack& stack_ref, const ifb_memory base_memory);
};

inline const ifb_u32
ifb_data::stack_push(
          IFBStack& stack_ref, 
    const ifb_u32   size) {

    const ifb_u32 starting_position = stack_ref.position;
    const ifb_u32 new_position      = starting_position; 

    if (new_position > stack_ref.size) {
        return(0);
    }

    stack_ref.position = new_position;
    
    return(starting_position);
}

inline const ifb_b8
ifb_data::stack_pull(
          IFBStack& stack_ref, 
    const ifb_u32   size) {

    if (size > stack_ref.position) {
        return(false);
    }

    stack_ref.position -= size;

    return(true);
}

inline const ifb_memory
ifb_data::stack_pointer(
          IFBStack&  stack_ref, 
    const ifb_memory base_memory) {

    const ifb_memory stack_pointer = 
        base_memory     + 
        stack_ref.start + 
        stack_ref.position;

    return(stack_pointer);
}

/**********************************************************************************/
/* QUEUE                                                                          */
/**********************************************************************************/

struct IFBQueue : IFBDataStructure {
    ifb_u32 position;
    ifb_u32 element_size;
    ifb_u32 element_count;
};

namespace ifb_data {

    const ifb_ptr queue_pointer    (const IFBQueue& queue_ref);
    const ifb_b8  queue_reset      (const IFBQueue& queue_ref);
    const ifb_u32 queue_size_total (const IFBQueue& queue_ref);
    const ifb_u32 queue_size_used  (const IFBQueue& queue_ref);
    const ifb_u32 queue_peek       (const IFBQueue& queue_ref, const ifb_u32 index);
    
    const ifb_ptr queue_push       (IFBQueue& queue_ref);
    const ifb_ptr queue_pop        (IFBQueue& queue_ref);
};

/**********************************************************************************/
/* ARRAY LIST                                                                      */
/**********************************************************************************/

struct IFBArrayList : IFBDataStructure {
    ifb_u32 element_size;
    ifb_u32 element_count_total;
    ifb_u32 element_count_current;
};

namespace ifb_data {

    const ifb_u32 array_list_size_total              (const IFBArrayList& array_list_ref);
    const ifb_u32 array_list_size_used               (const IFBArrayList& array_list_ref);
    const ifb_u32 array_list_element_size            (const IFBArrayList& array_list_ref);
    const ifb_u32 array_list_element_count           (const IFBArrayList& array_list_ref);
    const ifb_ptr array_list_element_first           (const IFBArrayList& array_list_ref);
    const ifb_ptr array_list_element_last            (const IFBArrayList& array_list_ref);
    const ifb_ptr array_list_element_at_index        (const IFBArrayList& array_list_ref, const ifb_u32 index);

    const ifb_b8  array_list_reset                   (IFBArrayList& array_list_ref);
    const ifb_b8  array_list_element_remove_at_index (IFBArrayList& array_list_ref, const ifb_u32    index);
    const ifb_u32 array_list_element_add             (IFBArrayList& array_list_ref, const ifb_memory element_ptr);
    const ifb_u32 array_list_element_add_at_index    (IFBArrayList& array_list_ref, const ifb_memory element_ptr, const ifb_u32 index);
};

#endif //IFB_ENGINE_DATA_STRUCTURES_HPP