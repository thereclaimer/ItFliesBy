#ifndef IFB_DATA_STRUCTURES_HPP
#define IFB_DATA_STRUCTURES_HPP

#include <ifb.hpp>

using namespace ifb;

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb::ds {
    
    //---------------------------------
    // types
    //---------------------------------

    // array
    struct array_t;
    struct array_args_t;
    struct array_info_t;

    // array list
    struct array_list_t;
    struct array_list_args_t;
    struct array_list_info_t;

    // stack
    struct stack_t;
    struct stack_args_t;
    struct stack_info_t;

    // queue
    struct queue_t;
    struct queue_args_t;
    struct queue_info_t;

    // hash table
    struct hash_table_t;
    struct hash_table_args_t;
    struct hash_table_info_t;

    // handles
    typedef stack_t*      stack_h;
    typedef hash_table_t* hash_table_h;
    typedef array_list_t* array_list_h;
    typedef queue_t*      queue_h;
    typedef array_t*      array_h;

    //---------------------------------
    // array
    //---------------------------------

    const u32    array_memory_size       (const u32 element_size, const u32 element_count);
    array_h      array_memory_init       (const u32 element_size, const u32 element_count, const memory_t& memory);
    void         array_info              (array_h array, array_info_t& info);
    void         array_clear             (array_h array);
    const b8     array_add               (array_h array, const u32   count, const ptr element);
    const ptr    array_index             (array_h array, const u32   index);
    const b8     array_iterate           (array_h array, iterator_t& iterator);

    //---------------------------------
    // array list
    //---------------------------------

    const u32    array_list_memory_size  (const u32 element_size, const u32 element_count);
    array_list_h array_list_memory_init  (const u32 element_size, const u32 element_count, const memory_t& memory);
    void         array_list_info         (array_list_h array_list, array_list_info_t& info);
    void         array_list_reset        (array_list_h array_list);
    const b8     array_list_is_empty     (array_list_h array_list);
    const ptr    array_list_first        (array_list_h array_list);
    const ptr    array_list_last         (array_list_h array_list);
    const b8     array_list_add_to_front (array_list_h array_list, const ptr element_ptr);
    const b8     array_list_add_to_end   (array_list_h array_list, const ptr element_ptr);
    const b8     array_list_remove       (array_list_h array_list, const u32 index);
    const ptr    array_list_index        (array_list_h array_list, const u32 index);
    const b8     array_list_insert       (array_list_h array_list, const u32 index, const ptr element_ptr);

    //---------------------------------
    // stack
    //---------------------------------

    void         stack_memory_size       (const u32 stack_size);
    stack_h      stack_memory_init       (const u32 stack_size, const memory_t& memory);
    void         stack_info              (stack_h stack, stack_info_t& info);
    const u32    stack_push_relative     (stack_h stack, const u32 size);
    const ptr    stack_push_absolute     (stack_h stack, const u32 size);
    const b8     stack_pull              (stack_h stack, const u32 size);
    const ptr    stack_pointer           (stack_h stack, const u32 offset);
    void         stack_reset             (stack_h stack);

    //---------------------------------
    // queue
    //---------------------------------

    queue_h      queue_memory_init       (const u32 queue_size);
    const u32    queue_memory_size       (const u32 queue_size, const memory_t& memory);
    const b8     queue_reset             (queue_h queue);
    const u32    queue_peek              (queue_h queue, const u32 size);
    const ptr    queue_enqueue           (queue_h queue, const u32 size);
    const ptr    queue_dequeue           (queue_h queue, const u32 size);

    //---------------------------------
    // hash table
    //---------------------------------
    const u32    hash_table_memory_size  (const u32 element_size, const u32 element_count);
    hash_table_h hash_table_memory_init  (const u32 element_size, const u32 element_count, const u32 tag_size_max, const memory_t& memory);
    void         hash_table_info         (hash_table_h hash_table, hash_table_info_t& info);
    const b8     hash_table_insert       (hash_table_h hash_table, const utf8* key, const ptr element);
    const b8     hash_table_remove       (hash_table_h hash_table, const utf8* key);
    const ptr    hash_table_lookup       (hash_table_h hash_table, const utf8* key);
    const u32    hash_table_index_of     (hash_table_h hash_table, const utf8* key);
    const ptr    hash_table_index        (hash_table_h hash_table, const u32   index);
};

/**********************************************************************************/
/* DEFINITIONS                                                                    */
/**********************************************************************************/

namespace ifb::ds {

    struct array_info_t {
        u32 element_size;
        u32 element_count_total;
        u32 element_count_current;
    };

    struct array_list_info_t {
        u32 element_size;
        u32 element_count_total;
        u32 element_count_current;
    };

    struct stack_info_t {
        u32 size_total;
        u32 size_used;
    };

    struct queue_info_t {
        u32 size_total;
        u32 size_used;
    };
    struct hash_table_info_t {
        u32 element_size;
        u32 element_count_total;
        u32 element_count_used;
        u32 key_length_max;    
    };
};

#endif //IFB_DATA_STRUCTURES_HPP