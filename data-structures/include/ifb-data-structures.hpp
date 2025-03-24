#ifndef IFB_DATA_STRUCTURES_HPP
#define IFB_DATA_STRUCTURES_HPP

#include <ifb.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

typedef IFBAddr IFBDS64;

typedef IFBDS64 IFBDS64Array;
typedef IFBDS64 IFBDS64ArrayList;
typedef IFBDS64 IFBDS64Stack;
typedef IFBDS64 IFBDS64Queue;
typedef IFBDS64 IFBDS64HashTable;

/**********************************************************************************/
/* ARRAY                                                                          */
/**********************************************************************************/

namespace ifb_array {

    //memory
    const IFBU32       memory_size         (const IFBU32 element_size, const IFBU32 element_count);
    const IFBDS64Array memory_init         (const IFBU32 element_size, const IFBU32 element_count, const IFBPtr memory);

    //pointers
    const IFBPtr       get_pointer_indexed (const IFBDS64Array array, const IFBU32 index);
    const IFBPtr       get_pointer_start   (const IFBDS64Array array);
    
    //size / count
    const IFBU32       get_element_size    (const IFBDS64Array array);
    const IFBU32       get_element_count   (const IFBDS64Array array);
    const IFBU32       get_array_size      (const IFBDS64Array array);
};


/**********************************************************************************/
/* ARRAY LIST                                                                      */
/**********************************************************************************/


namespace ifb_array_list {

    //memory
    const IFBU32           memory_size          (const IFBU32 element_size, const IFBU32 element_count);
    const IFBDS64ArrayList memory_init          (const IFBU32 element_size, const IFBU32 element_count, const IFBPtr memory);

    //operations
    const IFBB8            reset                (const IFBDS64ArrayList array_list);
    const IFBB8            is_empty             (const IFBDS64ArrayList array_list);
    const IFBB8            remove               (const IFBDS64ArrayList array_list, const IFBU32 index);
    const IFBB8            add_to_front         (const IFBDS64ArrayList array_list, const IFBPtr element_ptr);
    const IFBB8            add_to_end           (const IFBDS64ArrayList array_list, const IFBPtr element_ptr);
    const IFBB8            insert               (const IFBDS64ArrayList array_list, const IFBPtr element_ptr, const IFBU32 index);

    //size
    const IFBU32           get_size_total       (const IFBDS64ArrayList array_list);
    const IFBU32           get_size_used        (const IFBDS64ArrayList array_list);
    
    //pointers
    const IFBPtr           get_element_first    (const IFBDS64ArrayList array_list);
    const IFBPtr           get_element_last     (const IFBDS64ArrayList array_list);
    const IFBPtr           get_element_at_index (const IFBDS64ArrayList array_list, const IFBU32 index);
};
/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

namespace ifb_stack {

    //memory
    const IFBU32       memory_size    (const IFBU32 data_size);
    const IFBDS64Stack memory_init    (const IFBU32 data_size, const IFBPtr memory);

    //operations
    const IFBU32       push_relative  (const IFBDS64Stack stack, const IFBU32 size);
    const IFBPtr       push_absolute  (const IFBDS64Stack stack, const IFBU32 size);
    const IFBB8        pull           (const IFBDS64Stack stack, const IFBU32 size);
    const IFBB8        reset          (const IFBDS64Stack stack);
    
    //pointers
    const IFBPtr       get_pointer    (const IFBDS64Stack stack, const IFBU32 position);
    
    //size
    const IFBU32       get_size_total (const IFBDS64Stack stack);
    const IFBU32       get_size_free  (const IFBDS64Stack stack);
    const IFBU32       get_size_used  (const IFBDS64Stack stack);
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

namespace ifb_hash_table {

    //memory
    const IFBU32   memory_size              (const IFBU32 element_count, const IFBU32 element_size, const IFBU32 key_length_max);
    const IFBU32   memory_init              (const IFBU32 element_count, const IFBU32 element_size, const IFBU32 key_length_max, const IFBPtr memory);

    //operations
    const IFBB8    insert                   (const IFBDS64HashTable hash_table, const IFBChar* key, const IFBPtr element);
    const IFBB8    remove                   (const IFBDS64HashTable hash_table, const IFBChar* key);
    const IFBByte* lookup                   (const IFBDS64HashTable hash_table, const IFBChar* key);

    //indexing
    const IFBU32   index_of                 (const IFBDS64HashTable hash_table, const IFBChar* key);
    const IFBByte* get_element_at_index     (const IFBDS64HashTable hash_table, const IFBU32   index);

    //count
    const IFBU32   get_element_count_total  (const IFBDS64HashTable hash_table);
    const IFBU32   get_element_count_free   (const IFBDS64HashTable hash_table);
    const IFBU32   get_element_count_used   (const IFBDS64HashTable hash_table);
};

#endif //IFB_DATA_STRUCTURES_HPP