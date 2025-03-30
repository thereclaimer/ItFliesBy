#ifndef IFB_DATA_STRUCTURES_HPP
#define IFB_DATA_STRUCTURES_HPP

#include <ifb.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

//handles
typedef ifb::addr IFBDS64Handle;

struct IFBDS64Array     { IFBDS64Handle h64; };
struct IFBDS64ArrayList { IFBDS64Handle h64; };
struct IFBDS64Stack     { IFBDS64Handle h64; };
struct IFBDS64Queue     { IFBDS64Handle h64; };
struct IFBDS64HashTable { IFBDS64Handle h64; };

#define IFB_DATA_STRUCTURES_INVALID_HANDLE_64 0

//args
struct IFBArrayArgs;
struct IFBArrayListArgs;
struct IFBStackArgs;
struct IFBHashTableArgs;

//info
struct IFBArrayInfo;
struct IFBArrayListInfo;
struct IFBStackInfo;
struct IFBHashTableInfo;

struct IFBIterator {
    ifb::ptr pointer;
    ifb::u64 index;
};

/**********************************************************************************/
/* ARRAY                                                                          */
/**********************************************************************************/

struct IFBArrayArgs {
    ifb::ptr memory_ptr;
    ifb::u64 memory_size;
    ifb::u32 element_size;
    ifb::u32 element_count;
};
struct IFBArrayInfo {
    ifb::u32 element_size;
    ifb::u32 element_count_total;
    ifb::u32 element_count_current;
};

namespace ifb_array {

    //memory
    void            size    (IFBArrayArgs& args);
    const IFBDS64Array create  (IFBArrayArgs& args);
    
    //info
    void            info    (const IFBDS64Array array_handle, IFBArrayInfo& info);

    //operations
    void            clear   (const IFBDS64Array array_handle);
    const ifb::b8        add     (const IFBDS64Array array_handle, const ifb::u32 count, const ifb::ptr element);
    const ifb::ptr       index   (const IFBDS64Array array_handle, const ifb::u32 index);
    const ifb::b8        iterate (const IFBDS64Array array_handle, IFBIterator& iterator);
};

/**********************************************************************************/
/* ARRAY LIST                                                                      */
/**********************************************************************************/

struct IFBArrayListArgs {
    ifb::ptr memory_ptr;
    ifb::u64 memory_size;
    ifb::u32 element_size;
    ifb::u32 element_count;    
};

struct IFBArrayListInfo {
    ifb::u32 element_size;
    ifb::u32 element_count_total;
    ifb::u32 element_count_current;
};

namespace ifb_array_list {

    //memory
    const ifb::u32           size         (const ifb::u32 element_size, const ifb::u32 element_count);
    const IFBDS64ArrayList create       (IFBArrayListArgs& args);

    //info
    void                info         (const IFBDS64ArrayList array_list, IFBArrayListInfo& info);

    //operations
    void                reset        (const IFBDS64ArrayList array_list);
    const ifb::b8            is_empty     (const IFBDS64ArrayList array_list);
    const ifb::ptr           first        (const IFBDS64ArrayList array_list);
    const ifb::ptr           last         (const IFBDS64ArrayList array_list);
    const ifb::b8            add_to_front (const IFBDS64ArrayList array_list, const ifb::ptr element_ptr);
    const ifb::b8            add_to_end   (const IFBDS64ArrayList array_list, const ifb::ptr element_ptr);
    const ifb::b8            remove       (const IFBDS64ArrayList array_list, const ifb::u32 index);
    const ifb::ptr           index        (const IFBDS64ArrayList array_list, const ifb::u32 index);
    const ifb::b8            insert       (const IFBDS64ArrayList array_list, const ifb::u32 index, const ifb::ptr element_ptr);
};

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

struct IFBStackArgs {
    ifb::ptr memory_ptr;
    ifb::u32 memory_size;
    ifb::u32 stack_size;
};

struct IFBStackInfo {
    ifb::u32 size_total;
    ifb::u32 size_used;
};

namespace ifb_stack {

    //memory
    void            size           (IFBStackArgs& args);
    const IFBDS64Stack init           (IFBStackArgs& args);

    //info
    void            info           (const IFBDS64Stack stack, IFBStackInfo& info);

    //operations
    const ifb::u32       push_relative  (const IFBDS64Stack stack, const ifb::u32 size);
    const ifb::ptr       push_absolute  (const IFBDS64Stack stack, const ifb::u32 size);
    const ifb::b8        pull           (const IFBDS64Stack stack, const ifb::u32 size);
    const ifb::ptr       pointer        (const IFBDS64Stack stack, const ifb::u32 offset);
    void            reset          (const IFBDS64Stack stack);
};

/**********************************************************************************/
/* QUEUE                                                                          */
/**********************************************************************************/

struct IFBQueueArgs {
    ifb::ptr memory_ptr;
    ifb::u32 memory_size;
    ifb::u32 stack_size;
};

struct IFBQueueInfo {

};

namespace ifb_queue {

    const ifb::u32       size           (IFBQueueArgs& args);
    const IFBDS64Queue init           (IFBQueueArgs& args);

    const ifb::b8        reset          (const IFBDS64Queue queue);
    
    const ifb::u32       peek           (const IFBDS64Queue queue, const ifb::u32 size);
    const ifb::ptr       enqueue        (const IFBDS64Queue queue, const ifb::u32 size);
    const ifb::ptr       dequeue        (const IFBDS64Queue queue, const ifb::u32 size);
    
    const ifb::u32       get_size_total (const IFBDS64Queue queue);
    const ifb::u32       get_size_free  (const IFBDS64Queue queue);
    const ifb::u32       get_size_used  (const IFBDS64Queue queue);
};

/**********************************************************************************/
/* HASH TABLE                                                                     */
/**********************************************************************************/

struct IFBHashTableArgs {
    ifb::ptr memory_ptr;
    ifb::u32 memory_size;
    ifb::u32 element_count;
    ifb::u32 element_size;
    ifb::u32 key_length_max;
};

struct IFBHashTableInfo {
    ifb::u32 element_size;
    ifb::u32 element_count_total;
    ifb::u32 element_count_used;
    ifb::u32 key_length_max;    
};

namespace ifb_hash_table {

    //memory
    const ifb::u32   size   (IFBHashTableArgs& args);
    const ifb::u32   init   (IFBHashTableArgs& args);

    void        info   (const IFBDS64HashTable hash_table, IFBHashTableInfo& info);

    //operations
    const ifb::b8  insert   (const IFBDS64HashTable hash_table, const ifb::utf8* key, const ifb::ptr element);
    const ifb::b8  remove   (const IFBDS64HashTable hash_table, const ifb::utf8* key);
    const ifb::ptr lookup   (const IFBDS64HashTable hash_table, const ifb::utf8* key);
    const ifb::u32 index_of (const IFBDS64HashTable hash_table, const ifb::utf8* key);
    const ifb::ptr index    (const IFBDS64HashTable hash_table, const ifb::u32   index);
};

#endif //IFB_DATA_STRUCTURES_HPP