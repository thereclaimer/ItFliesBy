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
    IFBChar value[IFB_TAG_LENGTH];
    IFBHash  hash;
};

namespace ifb_tag {

    const IFBHash tag_hash                     (const IFBChar* tag_value);
    const IFBU32 tag_value_offset             (const IFBIDTag& tag_id_ref);

    const IFBB8  tag_copy_value               (const IFBChar* tag_value_source, IFBChar*       tag_value_destination);
    
    const IFBB8  tag_copy_from_indexed_buffer (IFBTag& tag_ref, const IFBChar* tag_value_buffer);
    const IFBB8  tag_copy_to_indexed_buffer   (const IFBTag& tag_ref, IFBChar* tag_value_buffer);

    const IFBB8  tag_update_value(
              IFBTag&   tag_ref,
        const IFBChar* tag_value_new);

    const IFBB8  tag_update_value(
              IFBChar* tag_value,
              IFBHash&  tag_hash_ref,
        const IFBChar* tag_value_new);
};

inline const IFBU32
ifb_tag::tag_value_offset(
    const IFBIDTag& tag_id_ref) {
    
    const IFBU32 offset = IFB_TAG_LENGTH * tag_id_ref.index;

    return(offset);
}

inline const IFBHash
ifb_tag::tag_hash(
    const IFBChar* tag_value) {

    const IFBHash tag_hash = tag_value != NULL 
        ? ifb_hash::get_hash((IFBChar*)tag_value,IFB_TAG_LENGTH)
        : IFBHash{0};

    return(tag_hash);
}

inline const IFBB8
ifb_tag::tag_copy_value(
    const IFBChar* tag_value_source,
          IFBChar* tag_value_destination) {

    //sanity check
    const IFBB8 result = tag_value_source && tag_value_destination;

    //copy the tag value, if we can
    for (
        IFBU32 char_index = 0;
        result && char_index < IFB_TAG_LENGTH;
        ++char_index) {

        tag_value_destination[char_index] = tag_value_source[char_index];
    }

    //we're done
    return(result);
}

inline const IFBB8 
ifb_tag::tag_copy_from_indexed_buffer(
          IFBTag&   tag_ref,
    const IFBChar* tag_value_buffer) {

    //sanity check
    if (tag_value_buffer == NULL) return(false);

    //get the value offset
    IFBU32 offset = ifb_tag::tag_value_offset(tag_ref);

    //get the start of the tag value
    const IFBChar* tag_value_buffer_start = tag_value_buffer + offset;

    //copy the tag
    const IFBB8 result = ifb_tag::tag_copy_value(
        tag_value_buffer_start,
        tag_ref.value);

    //hash the value
    tag_ref.hash = ifb_tag::tag_hash(tag_ref.value);

    //we're done
    return(result);
}

inline const IFBB8
ifb_tag::tag_copy_to_indexed_buffer(
    const IFBTag&   tag_ref,
          IFBChar* tag_value_buffer) {

    //sanity check
    if (tag_value_buffer == NULL) return(false);

    //get the value offset
    IFBU32 offset = ifb_tag::tag_value_offset(tag_ref);

    //get the start of the tag value
    IFBChar* tag_value_buffer_start = tag_value_buffer + offset;

    //copy the tag
    const IFBB8 result = ifb_tag::tag_copy_value(
        tag_ref.value,
        tag_value_buffer_start);

    //we're done
    return(result);
}

inline const IFBB8 
ifb_tag::tag_update_value(
          IFBTag&   tag_ref,
    const IFBChar* tag_value_new) {

    //sanity check
    if (!tag_value_new) return(false);

    //get the hash
    tag_ref.hash = ifb_tag::tag_hash(tag_value_new);

    //copy the value
    const IFBB8 result = ifb_tag::tag_copy_value(
        tag_value_new,
        tag_ref.value);

    //we're done
    return(result);
}

inline const IFBB8
ifb_tag::tag_update_value(
          IFBChar* tag_value,
          IFBHash&  tag_hash_ref,
    const IFBChar* tag_value_new) {

    //sanity check
    if (!tag_value || !tag_value_new) {
        return(false);
    }

    //hash the value
    tag_hash_ref = ifb_tag::tag_hash(tag_value_new);

    //copy the value
    const IFBB8 result = ifb_tag::tag_copy_value(
        tag_value_new,
        tag_value);

    //we're done
    return(result);
}

#endif //IFB_TAG_HPP