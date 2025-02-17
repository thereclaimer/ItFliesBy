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

    //allocate
    const ifb_u32 allocation_size_structure (ifb_void);
    const ifb_u32 allocation_size_data      (const ifb_u32 element_size,const ifb_u32 element_count);
    const ifb_u32 allocation_size_total     (const ifb_u32 element_size,const ifb_u32 element_count);

    //create/initialize

    IFBArray*
    create(
        const ifb_ptr memory,
        const ifb_u32 element_size,
        const ifb_u32 element_count);

    const ifb_b8
    initialize(
              IFBArray* array_ptr,
        const ifb_ptr   data,
        const ifb_u32   element_size,
        const ifb_u32   element_count);

    //pointers
    const ifb_ptr get_pointer_indexed (const IFBArray* array_ptr, const ifb_u32 index);
    const ifb_ptr get_pointer_start   (const IFBArray* array_ptr);
    
    //size / count
    const ifb_u32 get_element_size    (const IFBArray* array_ptr);
    const ifb_u32 get_element_count   (const IFBArray* array_ptr);
    const ifb_u32 get_array_size      (const IFBArray* array_ptr);
};


/**********************************************************************************/
/* ARRAY LIST                                                                      */
/**********************************************************************************/

namespace ifb_array_list {

    //create/reset
    const ifb_b8  reset                (IFBArrayList* array_list_ptr);

    //add/remove
    const ifb_b8  remove               (IFBArrayList* array_list_ptr, const ifb_u32   index);
    const ifb_u32 add                  (IFBArrayList* array_list_ptr, const ifb_byte* element_ptr);
    const ifb_u32 insert               (IFBArrayList* array_list_ptr, const ifb_byte* element_ptr, const ifb_u32 index);

    //size/count    
    const ifb_u32 get_size_total       (const IFBArrayList* array_list_ptr);
    const ifb_u32 get_size_used        (const IFBArrayList* array_list_ptr);
    const ifb_u32 get_element_size     (const IFBArrayList* array_list_ptr);
    const ifb_u32 get_element_count    (const IFBArrayList* array_list_ptr);
    
    //pointers
    const ifb_ptr get_element_first    (const IFBArrayList* array_list_ptr);
    const ifb_ptr get_element_last     (const IFBArrayList* array_list_ptr);
    const ifb_ptr get_element_at_index (const IFBArrayList* array_list_ptr, const ifb_u32 index);
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

namespace ifb_queue {

    const ifb_b8  reset          (const IFBQueue* queue_ptr);
    
    const ifb_u32 peek           (const IFBQueue* queue_ptr, const ifb_u32 size);
    const ifb_ptr enqueue        (IFBQueue*       queue_ptr, const ifb_u32 size);
    const ifb_ptr dequeue        (IFBQueue*       queue_ptr, const ifb_u32 size);
    
    const ifb_u32 get_size_total (const IFBQueue* queue_ptr);
    const ifb_u32 get_size_free  (const IFBQueue* queue_ptr);
    const ifb_u32 get_size_used  (const IFBQueue* queue_ptr);
};

#endif //IFB_DATA_STRUCTURES_HPP