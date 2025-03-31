#pragma once

#include "ifb-data-structures.hpp"

using namespace ifb;

namespace ifb {

    struct data_structure_t {
        addr data_start;
        u32  data_size;
    };

    struct array_t : data_structure_t {
        u32 element_size;
        u32 element_count_total;
        u32 element_count_current;
    };

    struct array_list_t : data_structure_t {
        u32 element_size;
        u32 element_count_total;
        u32 element_count_current;
    };

    struct stack_t : data_structure_t {
        u64 position;
    };

    struct queue_t : data_structure_t {
        u32 position;
    };

    struct hash_table_t : data_structure_t {
        u32 element_array_start;
        u32 element_size;
        u32 element_count_max;
        u32 key_length_max;
    };
};

//sizes
#define STRUCT_SIZE_ARRAY       ifb_macro_align_size_struct(array_t)
#define STRUCT_SIZE_ARRAY_LIST  ifb_macro_align_size_struct(array_list_t)
#define STRUCT_SIZE_STACK       ifb_macro_align_size_struct(stack_t)
#define STRUCT_SIZE_QUEUE       ifb_macro_align_size_struct(queue_t)
#define STRUCT_SIZE_HASH_TABLE  ifb_macro_align_size_struct(hash_table_t)

namespace ifb {

    struct globals_t {
        u32 struct_size_array;
        u32 struct_size_array_list;
        u32 struct_size_stack;
        u32 struct_size_queue;
        u32 struct_size_hash_table;
    };

    constexpr ifb_global globals_t _globals = {
        STRUCT_SIZE_ARRAY,
        STRUCT_SIZE_ARRAY_LIST,
        STRUCT_SIZE_STACK,
        STRUCT_SIZE_QUEUE,
        STRUCT_SIZE_HASH_TABLE
    }; 

    inline void
    array_assert_valid(
        const array_t* array) {

        //assert the properties are valid
        b8 result = true;
        result &= (array                        != NULL);
        result &= (array->data_size             != NULL);
        result &= (array->data_start            != NULL);
        result &= (array->element_size          != NULL);
        result &= (array->element_count_total   != NULL);
        result &= (array->element_count_current <= array->element_count_total);
        ifb_macro_assert(result);
    }

    inline void
    array_list_assert_valid(
        const array_list_t* array_list) {

        //assert the pointer isn't null
        ifb_macro_assert(array_list);

        b8 is_valid = true;
        is_valid &= (array_list->data_start                 != 0);
        is_valid &= (array_list->data_size                  != 0);
        is_valid &= (array_list->element_size          != 0);
        is_valid &= (array_list->element_count_total   != 0);
        is_valid &= (array_list->element_count_current <= array_list->element_count_total);
        ifb_macro_assert(is_valid);
    }

    //TODO: verify
    inline void 
    array_list_shift_down(
              array_list_t* array_list,
        const u32           index,
        const u32           count) {

        ifb_macro_assert(count != 0);
        ifb_macro_assert(index <= array_list->element_count_total);

        //calculate sizes
        const u32 size_element = array_list->element_size;
        const u32 size_shift   = size_element * count; 
        const u32 index_offset = size_element * index;

        //calculate the source
        const addr shift_source_start = array_list->data_start + index_offset;
        byte*      shift_source       = (byte*)shift_source_start; 

        //copy the values
        for (
            u32 byte_index_destination = 0;
                byte_index_destination < size_shift;
              ++byte_index_destination) {

            //calculate source index
            const u32 byte_index_source = byte_index_destination + 1; 

            //get the source and destination
            byte& ref_byte_destination = shift_source[byte_index_destination];
            byte& ref_byte_source      = shift_source[byte_index_source];

            //copy the value    
            ref_byte_destination = ref_byte_source;
        }   

    }

    //TODO: verify
    inline void 
    array_list_shift_up(
              array_list_t* array_list,
        const u32           index,
        const u32           count) {

        ifb_macro_assert(count != 0);
        ifb_macro_assert(index <= array_list->element_count_total);

        //calculate sizes
        const u32 size_element = array_list->element_size;
        const u32 size_shift   = size_element * count; 
        const u32 index_offset = size_element * index;

        //calculate the source
        const addr  shift_source_start = array_list->data_start + index_offset;
        byte*       shift_source       = (byte*)shift_source_start; 

        //copy the values
        for (
            u32 byte_index_destination  = size_shift;
                byte_index_destination  > 0;
              --byte_index_destination) {

            //calculate source index
            const u32 byte_index_source = byte_index_destination - 1; 

            //get the source and destination
            byte& ref_byte_destination = shift_source[byte_index_destination];
            byte& ref_byte_source      = shift_source[byte_index_source];

            //copy the value    
            ref_byte_destination = ref_byte_source;
        }
    }
};
