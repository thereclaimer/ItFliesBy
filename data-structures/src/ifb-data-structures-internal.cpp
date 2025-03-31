#pragma once

#include "ifb-data-structures.hpp"

using namespace ifb;

namespace array      = ifb::array;
namespace array_list = ifb::array_list;

namespace ifb {

    struct array_t : memory_t {
        u32 element_size;
        u32 element_count_total;
        u32 element_count_current;
    };

    struct array_list_t : memory_t {
        u32 element_size;
        u32 element_count_total;
        u32 element_count_current;
    };

    struct stack_t : memory_t {
        u64 position;
    };

    struct queue_t : memory_t {
        u32 position;
    };

    struct hash_table_t : memory_t {
        u32 element_array_start;
        u32 element_size;
        u32 element_count_max;
        u32 key_length_max;
    };
};

#define STRUCT_SIZE_ARRAY                    ifb_macro_align_size_struct(array_t)
#define STRUCT_SIZE_ARRAY_LIST               ifb_macro_align_size_struct(array_list_t)

#define array_macro_size_data(stride,count)  (stride * count)
#define array_macro_size_total(stride,count) STRUCT_SIZE_ARRAY + array_macro_size_data(stride,count) 

namespace ifb::array {

    inline void
    assert_valid(
        const array_t* array) {

        //assert the properties are valid
        b8 result = true;
        result &= (array                        != NULL);
        result &= (array->size                  != NULL);
        result &= (array->start                 != NULL);
        result &= (array->element_size          != NULL);
        result &= (array->element_count_total   != NULL);
        result &= (array->element_count_current <= array->element_count_total);
        ifb_macro_assert(result);
    }
};

namespace ifb::array_list {

    //TODO: verify
    inline void
    assert_valid(
        const array_list_t* array_list) {

        //assert the pointer isn't null
        ifb_macro_assert(array_list);

        b8 is_valid = true;
        is_valid &= (array_list->start                 != 0);
        is_valid &= (array_list->size                  != 0);
        is_valid &= (array_list->element_size          != 0);
        is_valid &= (array_list->element_count_total   != 0);
        is_valid &= (array_list->element_count_current <= array_list->element_count_total);
        ifb_macro_assert(is_valid);
    }

    //TODO: verify
    inline void 
    shift_down(
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
        const addr shift_source_start = array_list->start + index_offset;
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

    inline void 
    shift_up(
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
        const addr  shift_source_start = array_list->start + index_offset;
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