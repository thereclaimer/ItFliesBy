#ifndef IFB_DATA_STRUCTURES_HPP
#define IFB_DATA_STRUCTURES_HPP

#include <ifb.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBDataStructure {
    ifb_address start;
    ifb_u32     size;
};

struct IFBArray;
struct IFBStack;
struct IFBQueue;     //TODO
struct IFBArrayList; //TODO

/**********************************************************************************/
/* ARRAY                                                                          */
/**********************************************************************************/

#define IFB_STACK_INVALID_POSITION 0xFFFFFFFF

namespace ifb_array {

    //create / allocate
    const ifb_u32
    allocation_size(
        const ifb_u32 element_size,
        const ifb_u32 element_count);

    IFBArray*
    create(
        const ifb_ptr memory,
        const ifb_u32 element_size,
        const ifb_u32 element_count);

    //pointers
    const ifb_ptr get_pointer_indexed (const IFBArray* array_ptr, const ifb_u32 index);
    const ifb_ptr get_pointer_start   (const IFBArray* array_ptr);
    
    //size / count
    const ifb_u32 get_element_size    (const IFBArray* array_ptr);
    const ifb_u32 get_element_count   (const IFBArray* array_ptr);
    const ifb_u32 get_array_size      (const IFBArray* array_ptr);
};

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

namespace ifb_stack {

    //create / allocate

    const ifb_u32 allocation_size(const ifb_u32 stack_size);

    IFBStack*
    create(
        const ifb_ptr memory,
        const ifb_u32 size);

    //reset
    const ifb_b8  reset          (IFBStack* stack_ptr);

    //push / pull
    const ifb_u32 push_relative  (IFBStack* stack_ptr, const ifb_u32 size);
    const ifb_ptr push_absolute  (IFBStack* stack_ptr, const ifb_u32 size);
    const ifb_b8  pull           (IFBStack* stack_ptr, const ifb_u32 size);
    
    //pointers
    const ifb_ptr get_pointer    (const IFBStack* stack_ptr, const ifb_u32 position);
    
    //size
    const ifb_u32 get_size_total (const IFBStack* stack_ptr);
    const ifb_u32 get_size_free  (const IFBStack* stack_ptr);
    const ifb_u32 get_size_used  (const IFBStack* stack_ptr);
};


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

#endif //IFB_DATA_STRUCTURES_HPP