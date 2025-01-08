#ifndef IFB_TAG_HPP
#define IFB_TAG_HPP

#include "ifb-types.hpp"
#include "ifb-hash.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBIDTag : IFBID { };

struct IFBTag;

/**********************************************************************************/
/* TAG                                                                            */
/**********************************************************************************/

#define IFB_TAG_LENGTH 32

struct IFBTag : IFBIDTag {
    ifb_char value[IFB_TAG_LENGTH];
    IFBHash  hash;
};

namespace ifb_tag {

    const IFBHash tag_hash                     (const ifb_char* tag_value);
    const ifb_u32 tag_value_offset             (const IFBIDTag& tag_id_ref);

    const ifb_b8  tag_copy_value               (const ifb_char* tag_value_source, ifb_char*       tag_value_destination);
    
    const ifb_b8  tag_copy_from_indexed_buffer (IFBTag& tag_ref, const ifb_char* tag_value_buffer);
    const ifb_b8  tag_copy_to_indexed_buffer   (const IFBTag& tag_ref, ifb_char* tag_value_buffer);

    const ifb_b8  tag_update_value(
              IFBTag&   tag_ref,
        const ifb_char* tag_value_new);

    const ifb_b8  tag_update_value(
              ifb_char* tag_value,
              IFBHash&  tag_hash_ref,
        const ifb_char* tag_value_new);
};

inline const ifb_u32
ifb_tag::tag_value_offset(
    const IFBIDTag& tag_id_ref) {
    
    const ifb_u32 offset = IFB_TAG_LENGTH * tag_id_ref.index;

    return(offset);
}

inline const IFBHash
ifb_tag::tag_hash(
    const ifb_char* tag_value) {

    const IFBHash tag_hash = tag_value != NULL 
        ? ifb_hash::get_hash((ifb_cstr)tag_value,IFB_TAG_LENGTH)
        : IFBHash{0};

    return(tag_hash);
}

inline const ifb_b8
ifb_tag::tag_copy_value(
    const ifb_char* tag_value_source,
          ifb_char* tag_value_destination) {

    //sanity check
    const ifb_b8 result = tag_value_source && tag_value_destination;

    //copy the tag value, if we can
    for (
        ifb_u32 char_index = 0;
        result && char_index < IFB_TAG_LENGTH;
        ++char_index) {

        tag_value_destination[char_index] = tag_value_source[char_index];
    }

    //we're done
    return(result);
}

inline const ifb_b8 
ifb_tag::tag_copy_from_indexed_buffer(
          IFBTag&   tag_ref,
    const ifb_char* tag_value_buffer) {

    //sanity check
    if (tag_value_buffer == NULL) return(false);

    //get the value offset
    ifb_u32 offset = ifb_tag::tag_value_offset(tag_ref);

    //get the start of the tag value
    const ifb_char* tag_value_buffer_start = tag_value_buffer + offset;

    //copy the tag
    const ifb_b8 result = ifb_tag::tag_copy_value(
        tag_value_buffer_start,
        tag_ref.value);

    //hash the value
    tag_ref.hash = ifb_tag::tag_hash(tag_ref.value);

    //we're done
    return(result);
}

inline const ifb_b8
ifb_tag::tag_copy_to_indexed_buffer(
    const IFBTag&   tag_ref,
          ifb_char* tag_value_buffer) {

    //sanity check
    if (tag_value_buffer == NULL) return(false);

    //get the value offset
    ifb_u32 offset = ifb_tag::tag_value_offset(tag_ref);

    //get the start of the tag value
    ifb_char* tag_value_buffer_start = tag_value_buffer + offset;

    //copy the tag
    const ifb_b8 result = ifb_tag::tag_copy_value(
        tag_ref.value,
        tag_value_buffer_start);

    //we're done
    return(result);
}

inline const ifb_b8 
ifb_tag::tag_update_value(
          IFBTag&   tag_ref,
    const ifb_char* tag_value_new) {

    //sanity check
    if (!tag_value_new) return(false);

    //get the hash
    tag_ref.hash = ifb_tag::tag_hash(tag_value_new);

    //copy the value
    const ifb_b8 result = ifb_tag::tag_copy_value(
        tag_value_new,
        tag_ref.value);

    //we're done
    return(result);
}

inline const ifb_b8
ifb_tag::tag_update_value(
          ifb_char* tag_value,
          IFBHash&  tag_hash_ref,
    const ifb_char* tag_value_new) {

    //sanity check
    if (!tag_value || !tag_value_new) {
        return(false);
    }

    //hash the value
    tag_hash_ref = ifb_tag::tag_hash(tag_value_new);

    //copy the value
    const ifb_b8 result = ifb_tag::tag_copy_value(
        tag_value_new,
        tag_value);

    //we're done
    return(result);
}

#endif //IFB_TAG_HPP