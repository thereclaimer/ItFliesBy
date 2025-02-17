#pragma once

#include "ifb-data-structures.hpp"

/**********************************************************************************/
/* ARRAY LIST                                                                     */
/**********************************************************************************/

struct IFBArrayList : IFBDataStructure {
    ifb_u32 element_size;
    ifb_u32 element_count_total;
    ifb_u32 element_count_current;
};

/**********************************************************************************/
/* CREATE/RESET                                                                   */
/**********************************************************************************/

const ifb_b8
ifb_array_list::reset(
    IFBArrayList* array_list_ptr) {

    ifb_macro_panic();
    return(false);
}

/**********************************************************************************/
/* ADD/REMOVE                                                                     */
/**********************************************************************************/

const ifb_b8
ifb_array_list::remove(
          IFBArrayList* array_list_ptr,
    const ifb_u32       index) {

    ifb_macro_panic();
    return(false);
}

const ifb_u32
ifb_array_list::add(
          IFBArrayList* array_list_ptr,
    const ifb_byte*     element_ptr) {

    ifb_macro_panic();
    return(0);
}

const ifb_u32
ifb_array_list::insert(
          IFBArrayList* array_list_ptr,
    const ifb_byte*     element_ptr,
    const ifb_u32       index) {

    ifb_macro_panic();
    return(0);
}

/**********************************************************************************/
/* SIZE/COUNT                                                                     */
/**********************************************************************************/

const ifb_u32
ifb_array_list::get_size_total(
    const IFBArrayList* array_list_ptr) {

    ifb_macro_panic();
    return(0);
}

const ifb_u32
ifb_array_list::get_size_used(
    const IFBArrayList* array_list_ptr) {

    ifb_macro_panic();
    return(0);
}

const ifb_u32
ifb_array_list::get_element_size(
    const IFBArrayList* array_list_ptr) {

    ifb_macro_panic();
    return(0);
}

const ifb_u32
ifb_array_list::get_element_count(
    const IFBArrayList* array_list_ptr) {

    ifb_macro_panic();
    return(0);
}

/**********************************************************************************/
/* POINTERS                                                                       */
/**********************************************************************************/

const ifb_ptr
ifb_array_list::get_element_first(
    const IFBArrayList* array_list_ptr) {

    ifb_macro_panic();
    return(NULL);
}

const ifb_ptr
ifb_array_list::get_element_last(
    const IFBArrayList* array_list_ptr) {

    ifb_macro_panic();
    return(NULL);
}

const ifb_ptr
ifb_array_list::get_element_at_index(
    const IFBArrayList* array_list_ptr,
    const ifb_u32       index) {

    ifb_macro_panic();
    return(NULL);
}