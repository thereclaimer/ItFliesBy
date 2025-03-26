#ifndef IFB_DATA_STRUCTURES_HPP
#define IFB_DATA_STRUCTURES_HPP

#include <ifb.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

//handles
typedef IFBAddr IFBDS64Handle;

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
    IFBPtr pointer;
    IFBU64 index;
};

/**********************************************************************************/
/* ARRAY                                                                          */
/**********************************************************************************/

struct IFBArrayArgs {
    IFBPtr memory_ptr;
    IFBU64 memory_size;
    IFBU32 element_size;
    IFBU32 element_count;
};
struct IFBArrayInfo {
    IFBU32 element_size;
    IFBU32 element_count_total;
    IFBU32 element_count_current;
};

namespace ifb_array {

    //memory
    IFBVoid            size    (IFBArrayArgs& args);
    const IFBDS64Array create  (IFBArrayArgs& args);
    
    //info
    IFBVoid            info    (const IFBDS64Array array_handle, IFBArrayInfo& info);

    //operations
    IFBVoid            clear   (const IFBDS64Array array_handle);
    const IFBB8        add     (const IFBDS64Array array_handle, const IFBU32 count, const IFBPtr element);
    const IFBPtr       index   (const IFBDS64Array array_handle, const IFBU32 index);
    const IFBB8        iterate (const IFBDS64Array array_handle, IFBIterator& iterator);
};

/**********************************************************************************/
/* ARRAY LIST                                                                      */
/**********************************************************************************/

struct IFBArrayListArgs {
    IFBPtr memory_ptr;
    IFBU64 memory_size;
    IFBU32 element_size;
    IFBU32 element_count;    
};

struct IFBArrayListInfo {
    IFBU32 element_size;
    IFBU32 element_count_total;
    IFBU32 element_count_current;
};

namespace ifb_array_list {

    //memory
    const IFBU32           size         (const IFBU32 element_size, const IFBU32 element_count);
    const IFBDS64ArrayList create       (IFBArrayListArgs& args);

    //info
    IFBVoid                info         (const IFBDS64ArrayList array_list, IFBArrayListInfo& info);

    //operations
    IFBVoid                reset        (const IFBDS64ArrayList array_list);
    const IFBB8            is_empty     (const IFBDS64ArrayList array_list);
    const IFBPtr           first        (const IFBDS64ArrayList array_list);
    const IFBPtr           last         (const IFBDS64ArrayList array_list);
    const IFBB8            add_to_front (const IFBDS64ArrayList array_list, const IFBPtr element_ptr);
    const IFBB8            add_to_end   (const IFBDS64ArrayList array_list, const IFBPtr element_ptr);
    const IFBB8            remove       (const IFBDS64ArrayList array_list, const IFBU32 index);
    const IFBPtr           index        (const IFBDS64ArrayList array_list, const IFBU32 index);
    const IFBB8            insert       (const IFBDS64ArrayList array_list, const IFBU32 index, const IFBPtr element_ptr);
};

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

struct IFBStackArgs {
    IFBPtr memory_ptr;
    IFBU32 memory_size;
    IFBU32 stack_size;
};

struct IFBStackInfo {
    IFBU32 size_total;
    IFBU32 size_used;
};

namespace ifb_stack {

    //memory
    IFBVoid            size           (IFBStackArgs& args);
    const IFBDS64Stack init           (IFBStackArgs& args);

    //info
    IFBVoid            info           (const IFBDS64Stack stack, IFBStackInfo& info);

    //operations
    const IFBU32       push_relative  (const IFBDS64Stack stack, const IFBU32 size);
    const IFBPtr       push_absolute  (const IFBDS64Stack stack, const IFBU32 size);
    const IFBB8        pull           (const IFBDS64Stack stack, const IFBU32 size);
    const IFBPtr       pointer        (const IFBDS64Stack stack, const IFBU32 offset);
    IFBVoid            reset          (const IFBDS64Stack stack);
};

/**********************************************************************************/
/* QUEUE                                                                          */
/**********************************************************************************/

struct IFBQueueArgs {
    IFBPtr memory_ptr;
    IFBU32 memory_size;
    IFBU32 stack_size;
};

struct IFBQueueInfo {

};

namespace ifb_queue {

    const IFBU32       size           (IFBQueueArgs& args);
    const IFBDS64Queue init           (IFBQueueArgs& args);

    const IFBB8        reset          (const IFBDS64Queue queue);
    
    const IFBU32       peek           (const IFBDS64Queue queue, const IFBU32 size);
    const IFBPtr       enqueue        (const IFBDS64Queue queue, const IFBU32 size);
    const IFBPtr       dequeue        (const IFBDS64Queue queue, const IFBU32 size);
    
    const IFBU32       get_size_total (const IFBDS64Queue queue);
    const IFBU32       get_size_free  (const IFBDS64Queue queue);
    const IFBU32       get_size_used  (const IFBDS64Queue queue);
};

/**********************************************************************************/
/* HASH TABLE                                                                     */
/**********************************************************************************/

struct IFBHashTableArgs {
    IFBPtr memory_ptr;
    IFBU32 memory_size;
    IFBU32 element_count;
    IFBU32 element_size;
    IFBU32 key_length_max;
};

struct IFBHashTableInfo {
    IFBU32 element_size;
    IFBU32 element_count_total;
    IFBU32 element_count_used;
    IFBU32 key_length_max;    
};

namespace ifb_hash_table {

    //memory
    const IFBU32   size   (IFBHashTableArgs& args);
    const IFBU32   init   (IFBHashTableArgs& args);

    IFBVoid        info   (const IFBDS64HashTable hash_table, IFBHashTableInfo& info);

    //operations
    const IFBB8  insert   (const IFBDS64HashTable hash_table, const IFBChar* key, const IFBPtr element);
    const IFBB8  remove   (const IFBDS64HashTable hash_table, const IFBChar* key);
    const IFBPtr lookup   (const IFBDS64HashTable hash_table, const IFBChar* key);
    const IFBU32 index_of (const IFBDS64HashTable hash_table, const IFBChar* key);
    const IFBPtr index    (const IFBDS64HashTable hash_table, const IFBU32   index);
};

#endif //IFB_DATA_STRUCTURES_HPP