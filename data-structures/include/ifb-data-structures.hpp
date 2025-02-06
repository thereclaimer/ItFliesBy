#ifndef IFB_DATA_STRUCTURES_HPP
#ifndef IFB_DATA_STRUCTURES_HPP

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
    const ifb_ptr get_pointer    (IFBStack* stack_ptr, const ifb_u32 position);
    
    //size
    const ifb_ptr get_size_total (IFBStack* stack_ptr);
    const ifb_ptr get_size_free  (IFBStack* stack_ptr);
    const ifb_ptr get_size_used  (IFBStack* stack_ptr);
};

#ifndef IFB_DATA_STRUCTURES_HPP