#ifndef IFB_DATA_STRUCTURES_HPP
#define IFB_DATA_STRUCTURES_HPP

#include <ifb.hpp>
#include <ifb-memory.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBDataStructure {
    IFBAddr start;
    IFBU32     size;
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
    const IFBU32 allocation_size_structure (IFBVoid);
    const IFBU32 allocation_size_data      (const IFBU32 element_size,const IFBU32 element_count);
    const IFBU32 allocation_size_total     (const IFBU32 element_size,const IFBU32 element_count);
    
    //arena reserve
    IFBArray* reserve_from_arena (const IFBHNDLinearAllocator linear_arena_handle, const IFBU32 element_size, const IFBU32 element_count);
    IFBArray* reserve_from_arena (const IFBHNDArenaBlock  block_arena_handle,  const IFBU32 element_size, const IFBU32 element_count);
    
    //create/initialize
    IFBArray*
    create(
        const IFBPtr memory,
        const IFBU32 element_size,
        const IFBU32 element_count);

    const IFBB8
    initialize(
              IFBArray* array_ptr,
        const IFBPtr   data,
        const IFBU32   element_size,
        const IFBU32   element_count);

    //pointers
    const IFBPtr get_pointer_indexed (const IFBArray* array_ptr, const IFBU32 index);
    const IFBPtr get_pointer_start   (const IFBArray* array_ptr);
    
    //size / count
    const IFBU32 get_element_size    (const IFBArray* array_ptr);
    const IFBU32 get_element_count   (const IFBArray* array_ptr);
    const IFBU32 get_array_size      (const IFBArray* array_ptr);
};


/**********************************************************************************/
/* ARRAY LIST                                                                      */
/**********************************************************************************/

namespace ifb_array_list {

    //create/reset
    const IFBB8  reset                (IFBArrayList* array_list_ptr);

    //add/remove
    const IFBB8  remove               (IFBArrayList* array_list_ptr, const IFBU32   index);
    const IFBU32 add                  (IFBArrayList* array_list_ptr, const IFBByte* element_ptr);
    const IFBU32 insert               (IFBArrayList* array_list_ptr, const IFBByte* element_ptr, const IFBU32 index);

    //size/count    
    const IFBU32 get_size_total       (const IFBArrayList* array_list_ptr);
    const IFBU32 get_size_used        (const IFBArrayList* array_list_ptr);
    const IFBU32 get_element_size     (const IFBArrayList* array_list_ptr);
    const IFBU32 get_element_count    (const IFBArrayList* array_list_ptr);
    
    //pointers
    const IFBPtr get_element_first    (const IFBArrayList* array_list_ptr);
    const IFBPtr get_element_last     (const IFBArrayList* array_list_ptr);
    const IFBPtr get_element_at_index (const IFBArrayList* array_list_ptr, const IFBU32 index);
};

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

namespace ifb_stack {

    //create / allocate

    const IFBU32 allocation_size(const IFBU32 stack_size);

    IFBStack*
    create(
        const IFBPtr memory,
        const IFBU32 size);

    //reset
    const IFBB8  reset          (IFBStack* stack_ptr);

    //push / pull
    const IFBU32 push_relative  (IFBStack* stack_ptr, const IFBU32 size);
    const IFBPtr push_absolute  (IFBStack* stack_ptr, const IFBU32 size);
    const IFBB8  pull           (IFBStack* stack_ptr, const IFBU32 size);
    
    //pointers
    const IFBPtr get_pointer    (const IFBStack* stack_ptr, const IFBU32 position);
    
    //size
    const IFBU32 get_size_total (const IFBStack* stack_ptr);
    const IFBU32 get_size_free  (const IFBStack* stack_ptr);
    const IFBU32 get_size_used  (const IFBStack* stack_ptr);
};

/**********************************************************************************/
/* QUEUE                                                                          */
/**********************************************************************************/

namespace ifb_queue {

    const IFBB8  reset          (const IFBQueue* queue_ptr);
    
    const IFBU32 peek           (const IFBQueue* queue_ptr, const IFBU32 size);
    const IFBPtr enqueue        (IFBQueue*       queue_ptr, const IFBU32 size);
    const IFBPtr dequeue        (IFBQueue*       queue_ptr, const IFBU32 size);
    
    const IFBU32 get_size_total (const IFBQueue* queue_ptr);
    const IFBU32 get_size_free  (const IFBQueue* queue_ptr);
    const IFBU32 get_size_used  (const IFBQueue* queue_ptr);
};

#endif //IFB_DATA_STRUCTURES_HPP