#ifndef IFB_DATA_STRUCTURES_HPP
#define IFB_DATA_STRUCTURES_HPP

#include <ifb.hpp>

using namespace ifb;

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb::ds {

    //data structures
    struct array_t;
    struct array_list_t;
    struct stack_t;
    struct queue_t;
    struct hash_table_t;

    //handles

    //args
    struct args_array_t;
    struct args_array_list_t;
    struct args_stack_t;
    struct args_hash_table_t;

    //info
    struct info_array_t;
    struct info_array_list_t;
    struct info_stack_t;
    struct info_queue_t;
    struct info_hash_table_t;

    //iterator
    struct iterator_t {
        ptr pointer;
        u64 index;
    };
};

/**********************************************************************************/
/* ARRAY                                                                          */
/**********************************************************************************/
namespace ifb::array {

    struct array_t;
    struct array_args_t;
    struct array_info_t;

    typedef ptr array_handle_t;

    //memory
    void           size    (array_args_t& args);
    array_handle_t create  (array_args_t& args);
    
    //info
    void           info    (array_handle_t array_handle, array_info_t& info);

    //operations
    void           clear   (array_handle_t array_handle);
    const b8       add     (array_handle_t array_handle, const u32   count, const ptr element);
    const ptr      index   (array_handle_t array_handle, const u32   index);
    const b8       iterate (array_handle_t array_handle, iterator_t& iterator);
};

/**********************************************************************************/
/* ARRAY LIST                                                                      */
/**********************************************************************************/


namespace ifb::array_list {

    struct array_list_t;
    struct array_list_args_t;
    struct array_list_info_t;

    typedef ptr array_list_handle_t;

    //memory
    const u32           size         (const u32 element_size, const u32 element_count);
    array_list_handle_t create       (array_list_args_t& args);

    //info
    void                info         (array_list_handle_t array_list, array_list_info_t& info);

    //operations
    void                reset        (array_list_handle_t array_list);
    const b8            is_empty     (array_list_handle_t array_list);
    const ptr           first        (array_list_handle_t array_list);
    const ptr           last         (array_list_handle_t array_list);
    const b8            add_to_front (array_list_handle_t array_list, const ptr element_ptr);
    const b8            add_to_end   (array_list_handle_t array_list, const ptr element_ptr);
    const b8            remove       (array_list_handle_t array_list, const u32 index);
    const ptr           index        (array_list_handle_t array_list, const u32 index);
    const b8            insert       (array_list_handle_t array_list, const u32 index, const ptr element_ptr);
};

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

namespace ifb_stack {

    struct stack_t;
    struct stack_args_t;
    struct stack_info_t;

    typedef ptr stack_handle_t;

    //memory
    void           size           (stack_args_t& args);
    stack_handle_t init           (stack_args_t& args);

    //info
    void           info           (stack_handle_t stack, IFBStackInfo& info);

    //operations
    const u32      push_relative  (stack_handle_t stack, const u32 size);
    const ptr      push_absolute  (stack_handle_t stack, const u32 size);
    const b8       pull           (stack_handle_t stack, const u32 size);
    const ptr      pointer        (stack_handle_t stack, const u32 offset);
    void           reset          (stack_handle_t stack);
};

/**********************************************************************************/
/* QUEUE                                                                          */
/**********************************************************************************/

struct IFBQueueArgs {
    ptr memory_ptr;
    u32 memory_size;
    u32 stack_size;
};

struct IFBQueueInfo {

};

namespace ifb_queue {

    const u32       size           (IFBQueueArgs& args);
    const IFBDS64Queue init           (IFBQueueArgs& args);

    const b8        reset          (const IFBDS64Queue queue);
    
    const u32       peek           (const IFBDS64Queue queue, const u32 size);
    const ptr       enqueue        (const IFBDS64Queue queue, const u32 size);
    const ptr       dequeue        (const IFBDS64Queue queue, const u32 size);
    
    const u32       get_size_total (const IFBDS64Queue queue);
    const u32       get_size_free  (const IFBDS64Queue queue);
    const u32       get_size_used  (const IFBDS64Queue queue);
};

/**********************************************************************************/
/* HASH TABLE                                                                     */
/**********************************************************************************/

struct IFBHashTableArgs {
    ptr memory_ptr;
    u32 memory_size;
    u32 element_count;
    u32 element_size;
    u32 key_length_max;
};

struct IFBHashTableInfo {
    u32 element_size;
    u32 element_count_total;
    u32 element_count_used;
    u32 key_length_max;    
};

namespace ifb_hash_table {

    //memory
    const u32   size   (IFBHashTableArgs& args);
    const u32   init   (IFBHashTableArgs& args);

    void        info   (const IFBDS64HashTable hash_table, IFBHashTableInfo& info);

    //operations
    const b8  insert   (const IFBDS64HashTable hash_table, const utf8* key, const ptr element);
    const b8  remove   (const IFBDS64HashTable hash_table, const utf8* key);
    const ptr lookup   (const IFBDS64HashTable hash_table, const utf8* key);
    const u32 index_of (const IFBDS64HashTable hash_table, const utf8* key);
    const ptr index    (const IFBDS64HashTable hash_table, const u32   index);
};

/**********************************************************************************/
/* DEFINITIONS                                                                    */
/**********************************************************************************/

struct array_args_t {
    ptr memory_ptr;
    u64 memory_size;
    u32 element_size;
    u32 element_count;
};
struct array_info_t {
    u32 element_size;
    u32 element_count_total;
    u32 element_count_current;
};

struct array_list_args_t {
    ptr memory_ptr;
    u64 memory_size;
    u32 element_size;
    u32 element_count;    
};

struct array_list_info_t{
    u32 element_size;
    u32 element_count_total;
    u32 element_count_current;
};

struct stack_args_t {
    ptr memory_ptr;
    u32 memory_size;
    u32 stack_size;
};

struct stack_info_t {
    u32 size_total;
    u32 size_used;
};

#endif //IFB_DATA_STRUCTURES_HPP