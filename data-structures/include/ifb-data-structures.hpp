#ifndef IFB_DATA_STRUCTURES_HPP
#define IFB_DATA_STRUCTURES_HPP

#include <ifb.hpp>

using namespace ifb;

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb {
    
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
};

/**********************************************************************************/
/* ARRAY                                                                          */
/**********************************************************************************/

namespace ifb::array {

    const u32 memory_size       (const u32 element_size, const u32 element_count);
    array_h   memory_init       (const u32 element_size, const u32 element_count, const memory_t& memory);
    void      info              (array_h array, array_info_t& info);
    void      clear             (array_h array);
    const b8  add               (array_h array, const u32   count, const ptr element);
    const ptr index             (array_h array, const u32   index);
    const b8  iterate           (array_h array, iterator_t& iterator);
};

/**********************************************************************************/
/* ARRAY LIST                                                                     */
/**********************************************************************************/

namespace ifb::array_list {

    const u32    memory_size  (const u32 element_size, const u32 element_count);
    array_list_h memory_init  (const u32 element_size, const u32 element_count, const memory_t& memory);
    void         info         (array_list_h array_list, array_list_info_t& info);
    void         reset        (array_list_h array_list);
    const b8     is_empty     (array_list_h array_list);
    const ptr    first        (array_list_h array_list);
    const ptr    last         (array_list_h array_list);
    const b8     add_to_front (array_list_h array_list, const ptr element_ptr);
    const b8     add_to_end   (array_list_h array_list, const ptr element_ptr);
    const b8     remove       (array_list_h array_list, const u32 index);
    const ptr    index        (array_list_h array_list, const u32 index);
    const b8     insert       (array_list_h array_list, const u32 index, const ptr element_ptr);
};

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

namespace ifb::stack {

    void      memory_size       (const u32 stack_size);
    stack_h   memory_init       (const u32 stack_size, const memory_t& memory);
    void      info              (stack_h stack, stack_info_t& info);
    const u32 push_relative     (stack_h stack, const u32 size);
    const ptr push_absolute     (stack_h stack, const u32 size);
    const b8  pull              (stack_h stack, const u32 size);
    const ptr pointer           (stack_h stack, const u32 offset);
    void      reset             (stack_h stack);
};

/**********************************************************************************/
/* QUEUE                                                                          */
/**********************************************************************************/

namespace ifb::queue {

    queue_h   memory_init       (const u32 queue_size);
    const u32 memory_size       (const u32 queue_size, const memory_t& memory);
    const b8  reset             (queue_h queue);
    const u32 peek              (queue_h queue, const u32 size);
    const ptr enqueue           (queue_h queue, const u32 size);
    const ptr dequeue           (queue_h queue, const u32 size);
};

/**********************************************************************************/
/* HASH TABLE                                                                     */
/**********************************************************************************/

namespace ifb::hash_table {

    const u32    memory_size  (const u32 element_size, const u32 element_count);
    hash_table_h memory_init  (const u32 element_size, const u32 element_count, const u32 tag_size_max, const memory_t& memory);
    void         info         (hash_table_h hash_table, hash_table_info_t& info);
    const b8     insert       (hash_table_h hash_table, const utf8* key, const ptr element);
    const b8     remove       (hash_table_h hash_table, const utf8* key);
    const ptr    lookup       (hash_table_h hash_table, const utf8* key);
    const u32    index_of     (hash_table_h hash_table, const utf8* key);
    const ptr    index        (hash_table_h hash_table, const u32   index);
};

/**********************************************************************************/
/* DEFINITIONS                                                                    */
/**********************************************************************************/

namespace ifb {

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