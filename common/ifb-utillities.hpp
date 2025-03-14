#ifndef IFB_UTILITIES_HPP
#define IFB_UTILITIES_HPP

#include "ifb-types.hpp"

namespace ifb_utilities {

    IFBPtr pointer_advance (const IFBPtr pointer, IFBU32& offset_ref, const IFBU32 size);
};

inline IFBPtr
ifb_utilities::pointer_advance(
    const IFBPtr  pointer,
          IFBU32& offset_ref,
    const IFBU32  size) {

    //get the next pointer
    IFBPtr next_pointer = pointer + offset_ref;

    //update the offset
    offset_ref += size;

    //we're done
    return(next_pointer);
}

#endif //IFB_UTILITIES_HPP