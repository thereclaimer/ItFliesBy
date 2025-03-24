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

struct IFBDataStructureSize {
    IFBU64 total;
    IFBU32 structure;
    IFBU32 data;
};  

/**********************************************************************************/
/* ARRAY                                                                          */
/**********************************************************************************/


namespace ifb_array {

    //memory
    IFBVoid memory_size (IFBDataStructureSize& memory_size_ref);
    
    //create/initialize
    const IFBDS64Array
    create(
        const IFBPtr memory,
        const IFBU32 element_size,
        const IFBU32 element_count);

    //pointers
    const IFBPtr get_pointer_indexed (const IFBDS64Array array, const IFBU32 index);
    const IFBPtr get_pointer_start   (const IFBDS64Array array);
    
    //size / count
    const IFBU32 get_element_size    (const IFBDS64Array array);
    const IFBU32 get_element_count   (const IFBDS64Array array);
    const IFBU32 get_array_size      (const IFBDS64Array array);
};


/**********************************************************************************/
/* ARRAY LIST                                                                      */
/**********************************************************************************/


namespace ifb_array_list {

    //memory
    const IFBU32   memory_allocation_size  (const IFBU32 element_size, const IFBU32 element_count);
    IFBArrayList*  memory_initialize       (const IFBU32 element_size, const IFBU32 element_count, const IFBPtr memory);   

    //operations
    const IFBB8 reset                 (const IFBDS64ArrayList array_list);
    const IFBB8 remove                (const IFBDS64ArrayList array_list, const IFBU32 index);
    const IFBB8 add_to_front          (const IFBDS64ArrayList array_list, const IFBPtr element_ptr);
    const IFBB8 add_to_end            (const IFBDS64ArrayList array_list, const IFBPtr element_ptr);
    const IFBB8 insert                (const IFBDS64ArrayList array_list, const IFBPtr element_ptr, const IFBU32 index);
    const IFBB8 is_empty              (const IFBDS64ArrayList array_list);

    //size
    const IFBU32 get_size_total       (const IFBDS64ArrayList array_list);
    const IFBU32 get_size_used        (const IFBDS64ArrayList array_list);
    
    //pointers
    const IFBPtr get_element_first    (const IFBDS64ArrayList array_list);
    const IFBPtr get_element_last     (const IFBDS64ArrayList array_list);
    const IFBPtr get_element_at_index (const IFBDS64ArrayList array_list, const IFBU32 index);
};
/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

struct IFBStack : IFBMemoryBlock {
    IFBU64 position;
};

namespace ifb_stack {

    IFBStack*    arena_load_pointer    (IFBMemoryArena* ptr_arena, const IFBU32 arena_offset);
    IFBStack*    arena_commit_absolute (IFBMemoryArena* ptr_arena, const IFBU32 stack_size);
    const IFBU32 arena_commit_relative (IFBMemoryArena* ptr_arena, const IFBU32 stack_size);

    //operations
    const IFBU32 push_relative         (IFBStack* stack, const IFBU32 size);
    const IFBPtr push_absolute         (IFBStack* stack, const IFBU32 size);
    const IFBB8  pull                  (IFBStack* stack, const IFBU32 size);
    const IFBB8  reset                 (IFBStack* stack);
    
    //pointers
    const IFBPtr get_pointer           (const IFBStack* stack, const IFBU32 position);
    
    //size
    const IFBU32 get_size_total        (const IFBStack* stack);
    const IFBU32 get_size_free         (const IFBStack* stack);
    const IFBU32 get_size_used         (const IFBStack* stack);
};

/**********************************************************************************/
/* QUEUE                                                                          */
/**********************************************************************************/

struct IFBQueue : IFBMemoryBlock {
    IFBU32 position;
};

namespace ifb_queue {

    const IFBB8  reset          (const IFBQueue* queue_ptr);
    
    const IFBU32 peek           (const IFBQueue* queue_ptr, const IFBU32 size);
    const IFBPtr enqueue        (IFBQueue*       queue_ptr, const IFBU32 size);
    const IFBPtr dequeue        (IFBQueue*       queue_ptr, const IFBU32 size);
    
    const IFBU32 get_size_total (const IFBQueue* queue_ptr);
    const IFBU32 get_size_free  (const IFBQueue* queue_ptr);
    const IFBU32 get_size_used  (const IFBQueue* queue_ptr);
};

/**********************************************************************************/
/* LINKED LIST                                                                    */
/**********************************************************************************/

namespace ifb_linked_list {


};

/**********************************************************************************/
/* HASH TABLE                                                                     */
/**********************************************************************************/

struct IFBHashTable : IFBMemoryBlock {
    IFBU32 element_array_start;
    IFBU32 element_size;
    IFBU32 element_count_max;
    IFBU32 key_length_max;
};

namespace ifb_hash_table {

    //memory
    const IFBU32   memory_size              (const IFBU32 element_count,const IFBU32 element_size);
    const IFBU32   commit_to_arena_relative (IFBMemoryArena* ptr_arena, const IFBU32 element_count, const IFBU32 element_size, const IFBU32 key_length_max);
    IFBHashTable*  commit_to_arena_absolute (IFBMemoryArena* ptr_arena, const IFBU32 element_count, const IFBU32 element_size, const IFBU32 key_length_max);
    IFBHashTable*  load_from_arena          (IFBMemoryArena* ptr_arena, const IFBU32 offset);

    //operations
    const IFBB8    insert                   (IFBHashTable*       ptr_hash_table, const IFBChar* key, const IFBByte* element, IFBU32* ptr_element_index = NULL);
    const IFBB8    remove                   (const IFBHashTable* ptr_hash_table, const IFBChar* key);
    const IFBByte* lookup                   (const IFBHashTable* ptr_hash_table, const IFBChar* key);

    //indexing
    const IFBU32   index_of                 (const IFBHashTable* ptr_hash_table, const IFBChar* key);
    const IFBByte* get_element_at_index     (const IFBHashTable* ptr_hash_table, const IFBU32   index);

    //count
    const IFBU32   get_element_count_total  (const IFBHashTable* ptr_hash_table);
    const IFBU32   get_element_count_free   (const IFBHashTable* ptr_hash_table);
    const IFBU32   get_element_count_used   (const IFBHashTable* ptr_hash_table);
};

#endif //IFB_DATA_STRUCTURES_HPP