#ifndef IFB_ENGINE_DATA_STRUCTURES_HPP
#define IFB_ENGINE_DATA_STRUCTURES_HPP

#include "ifb-types.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBDataStructure {
    ifb_address start;
    ifb_u32     size;
};

struct IFBStack;
struct IFBQueue;
struct IFBArray;
struct IFBArrayList;

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

#define IFB_STACK_INVALID_POSITION 0xFFFFFFFF

struct IFBStack : IFBDataStructure {
    ifb_u32 position;
};

namespace ifb_data {

    const ifb_u32 stack_allocation_size(const ifb_u32 stack_size);

    IFBStack*
    stack_create(
        const ifb_ptr memory,
        const ifb_u32 size);

    const ifb_b8  stack_reset         (IFBStack* stack_ptr);
    const ifb_u32 stack_push_relative (IFBStack* stack_ptr, const ifb_u32 size);
    const ifb_ptr stack_push_absolute (IFBStack* stack_ptr, const ifb_u32 size);
    const ifb_b8  stack_pull          (IFBStack* stack_ptr, const ifb_u32 size);
    const ifb_ptr stack_get_pointer   (IFBStack* stack_ptr, const ifb_u32 position);
};

inline const ifb_u32
ifb_data::stack_allocation_size(
    const ifb_u32 stack_size) {

    const ifb_u32 size_struct     = ifb_macro_align_size_struct(IFBStack);
    const ifb_u32 size_allocation = size_struct + size_allocation;

    return(size_allocation);
}

inline IFBStack*
ifb_data::stack_create(
    const ifb_ptr base_pointer,
    const ifb_u32 size) {

    //calculate the struct size
    const ifb_u32 struct_size = ifb_macro_align_size_struct(IFBStack);
    
    //sanity check
    if (!base_pointer || size == 0 || struct_size <= size) return(NULL);

    //cast the stack
    IFBStack* stack_ptr = (IFBStack*)base_pointer;

    //calculate the start and size of the stack memory
    const ifb_address stack_memory_start = (ifb_address)base_pointer + struct_size;
    const ifb_u32     stack_memory_size  = size - struct_size; 

    //initialize the stack
    stack_ptr->start    = stack_memory_start;
    stack_ptr->size     = stack_memory_size;
    stack_ptr->position = 0;

    //we're done
    return(stack_ptr);
}

inline const ifb_u32
ifb_data::stack_push_relative(
          IFBStack* stack_ptr, 
    const ifb_u32   size) {
    
    //sanity check
    if (!stack_ptr || size == 0) return(IFB_STACK_INVALID_POSITION);

    //calculate the new position
    const ifb_u32 starting_position = stack_ptr->position;
    const ifb_u32 new_position      = starting_position + size; 

    //sanity check
    if (new_position > stack_ptr->size) return(IFB_STACK_INVALID_POSITION);

    //update the position
    stack_ptr->position = new_position;
    
    //return the position at the start of the push
    return(starting_position);
}

inline const ifb_ptr
ifb_data::stack_push_absolute(
          IFBStack* stack_ptr, 
    const ifb_u32   size) {

    //do the relative push
    const ifb_u32 position = ifb_data::stack_push_relative(
        stack_ptr,
        size);

    //calculate the address, if the position is valid
    const ifb_address push_address = (position != IFB_STACK_INVALID_POSITION)  
        ? stack_ptr->start + position
        : 0;

    //cast the pointer
    const ifb_ptr push_pointer = (ifb_ptr)push_address;

    //we're done
    return(push_pointer);
}

inline const ifb_b8
ifb_data::stack_pull(
          IFBStack* stack_ptr, 
    const ifb_u32   size) {

    if (size > stack_ptr->position) {
        return(false);
    }

    stack_ptr->position -= size;

    return(true);
}

inline const ifb_ptr
ifb_data::stack_get_pointer(
          IFBStack* stack_ptr, 
    const ifb_u32   position) {

    //sanity check
    if (!stack_ptr || position > stack_ptr->position) return(NULL);

    //calculate the pointer
    const ifb_address address = stack_ptr->start + position;
    const ifb_ptr     pointer = (ifb_ptr)address;

    //we're done
    return(pointer);
}

inline const ifb_b8 
ifb_data::stack_reset(
    IFBStack* stack_ptr) {

    //sanity check
    if (!stack_ptr) return(false);

    //reset the position
    stack_ptr->position = 0;

    //we're done
    return(true);
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
    const ifb_b8  array_list_element_remove_at_index (IFBArrayList& array_list_ref, const ifb_u32   index);
    const ifb_u32 array_list_element_add             (IFBArrayList& array_list_ref, const ifb_byte* element_ptr);
    const ifb_u32 array_list_element_add_at_index    (IFBArrayList& array_list_ref, const ifb_byte* element_ptr, const ifb_u32 index);
};

#endif //IFB_ENGINE_DATA_STRUCTURES_HPP