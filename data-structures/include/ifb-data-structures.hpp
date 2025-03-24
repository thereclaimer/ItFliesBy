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

//data structure 
struct IFBDataStructureMemory;

//array
struct IFBArrayMemory;
struct IFBArrayIterator;
struct IFBArrayInfo;

//array list
struct IFBArrayListMemory;
struct IFBArrayListInfo;

//stack
struct IFBStackMemory;
struct IFBStackInfo;

//hash table
struct IFBHashTableMemory;
struct IFBHashTableInfo;

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

struct IFBDataStructureMemory {
    IFBPtr pointer;
    IFBU64 size_total;
    IFBU32 size_struct;
    IFBU32 size_data;
};

/**********************************************************************************/
/* ARRAY                                                                          */
/**********************************************************************************/

struct IFBArrayMemory : IFBDataStructureMemory {
    struct {
        IFBU32 element_size;
        IFBU32 element_count;
    } args;
};

struct IFBArrayIterator {
    IFBU32 index;
    IFBPtr pointer;
};

struct IFBArrayInfo {
    IFBU32 element_size;
    IFBU32 element_count_total;
    IFBU32 element_count_current;
};

namespace ifb_array {

    //memory
    IFBVoid            memory_size (IFBArrayMemory& array_memory);
    const IFBDS64Array memory_init (IFBArrayMemory& array_memory);

    //operations
    IFBVoid            clear       (const IFBDS64Array array_handle);
    const IFBB8        add         (const IFBDS64Array array_handle, const IFBU32 count, const IFBPtr element);
    const IFBPtr       index       (const IFBDS64Array array_handle, const IFBU32 index);
    const IFBB8        iterate     (const IFBDS64Array array_handle, IFBArrayIterator& iterator);

    //info
    IFBVoid            info        (const IFBDS64Array array_handle, IFBArrayInfo& info);
};


/**********************************************************************************/
/* ARRAY LIST                                                                      */
/**********************************************************************************/

struct IFBArrayListMemory : IFBDataStructureMemory {
    IFBU32 element_size;
    IFBU32 element_count_total;    
};

struct IFBArrayListInfo {
    IFBU32 element_size;
    IFBU32 element_count_total;
    IFBU32 element_count_current;
};

namespace ifb_array_list {

    //memory
    IFBVoid                memory_size  (IFBArrayListMemory& memory);
    const IFBDS64ArrayList memory_init  (IFBArrayListMemory& memory);

    //info
    IFBVoid                info         (const IFBDS64ArrayList array_list, IFBArrayListInfo& info);

    //operations
    IFBVoid                reset        (const IFBDS64ArrayList array_list);
    const IFBB8            is_empty     (const IFBDS64ArrayList array_list);
    const IFBB8            remove       (const IFBDS64ArrayList array_list, const IFBU32 index);
    const IFBB8            add_to_front (const IFBDS64ArrayList array_list, const IFBPtr element_ptr);
    const IFBB8            add_to_end   (const IFBDS64ArrayList array_list, const IFBPtr element_ptr);
    const IFBB8            insert       (const IFBDS64ArrayList array_list, const IFBPtr element_ptr, const IFBU32 index);
    const IFBPtr           first        (const IFBDS64ArrayList array_list);
    const IFBPtr           last         (const IFBDS64ArrayList array_list);
    const IFBPtr           index        (const IFBDS64ArrayList array_list, const IFBU32 index);


};

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

struct IFBStackMemory : IFBDataStructureMemory { };

struct IFBStackInfo {
    IFBU32 size_total;
    IFBU32 size_used;
};

namespace ifb_stack {

    //memory
    IFBVoid            memory_size    (IFBStackMemory& stack_memory);
    const IFBDS64Stack memory_init    (IFBStackMemory& stack_memory);

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

namespace ifb_queue {

    const IFBU32       memory_size    (const IFBU32 data_size);
    const IFBDS64Queue memory_init    (const IFBU32 data_size, const IFBPtr memory);

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

struct IFBHashTableMemory : IFBDataStructureMemory {
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
    const IFBU32   memory_size (IFBHashTableMemory& memory);
    const IFBU32   memory_init (IFBHashTableMemory& memory);

    IFBVoid        info        (const IFBDS64HashTable hash_table, IFBHashTableInfo& info);

    //operations
    const IFBB8    insert      (const IFBDS64HashTable hash_table, const IFBChar* key, const IFBPtr element);
    const IFBB8    remove      (const IFBDS64HashTable hash_table, const IFBChar* key);
    const IFBByte* lookup      (const IFBDS64HashTable hash_table, const IFBChar* key);
    const IFBU32   index_of    (const IFBDS64HashTable hash_table, const IFBChar* key);
    const IFBByte* index       (const IFBDS64HashTable hash_table, const IFBU32   index);

};

#endif //IFB_DATA_STRUCTURES_HPP