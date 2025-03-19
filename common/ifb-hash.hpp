#ifndef IFB_HASH_HPP
#define IFB_HASH_HPP

#include <string.h>

#include "ifb-types-primitives.hpp"
#include "ifb-scopes.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBHash;

namespace ifb_hash {

    const IFBHash 
    get_hash(
        const IFBChar* c_str,
        const IFBU32   c_str_length_max);

    const IFBB8
    collision_check(
        const IFBHash* hash_value_array_ptr,
        const IFBU32   hash_value_array_count,
        const IFBHash  hash_value);
    
    const IFBB8
    find_next_clear_value(
        const IFBHash*  in_hash_value_array_ptr,
        const IFBU32    in_hash_value_array_count,
              IFBU32&  out_hash_index_ref);

    const IFBB8
    search(
        const IFBHash* in_hash_value_array_ptr,
        const IFBU32   in_hash_value_array_count,
        const IFBHash  in_hash_value,
              IFBU32& out_hash_index_ref);
    
    const IFBB8
    search(
        const IFBHash* hash_value_array_ptr,
        const IFBU32   hash_value_array_count,
        const IFBHash  hash_value);

    const IFBB8
    hash_is_clear(
        const IFBHash& hash_value);
};

/**********************************************************************************/
/* HASH                                                                           */
/**********************************************************************************/

struct IFBHash {
    union {
        struct {
            IFBU32 h1;
            IFBU32 h2;
            IFBU32 h3;
            IFBU32 h4;
        };
        IFBU32 h[4];
    };
};

inline const IFBHash 
ifb_hash::get_hash(
    const IFBChar* c_str,
    const IFBU32   c_str_length_max) {
    
    IFBHash hash_value;
    hash_value = {0};

    //sanity check
    if (!c_str) return(hash_value);

    //get the safe length of the string
    const IFBU32 c_str_length = strnlen_s(c_str,c_str_length_max - 1) + 1;

    //do the hash
    meow_u128 meow_hash_value = MeowHash(MeowDefaultSeed,c_str_length,(void*)c_str);

    //load the value
    _mm_storeu_epi32(hash_value.h,meow_hash_value);

    //we're done
    return(hash_value);
}

inline const IFBB8
ifb_hash::collision_check(
    const IFBHash* hash_value_array_ptr,
    const IFBU32  hash_value_array_count,
    const IFBHash  hash_value) {

    if (
        hash_value_array_ptr   == NULL ||  
        hash_value_array_count == 0) {
        
        return(false);
    }

    //load the hash value
    __m128i xmm_reg_0 = _mm_loadu_epi32(hash_value.h);

    for (
        IFBU32 hash_index = 0;
               hash_index < hash_value_array_count;
             ++hash_index) {

        //load the current value to compare            
        __m128i xmm_reg_1 = _mm_loadu_epi32(hash_value_array_ptr[hash_index].h); 

        //compare the values
        if (MeowHashesAreEqual(xmm_reg_0,xmm_reg_1)) {
            //if they are equal, we're done
            return(true);
        }
    }

    //no collisions, we're done
    return(false); 
}

inline const IFBB8
ifb_hash::find_next_clear_value(
    const IFBHash*  in_hash_value_array_ptr,
    const IFBU32   in_hash_value_array_count,
          IFBU32& out_hash_index_ref) {

    __m128i xmm_reg;

    for (
          out_hash_index_ref = 0;
          out_hash_index_ref < in_hash_value_array_count;
        ++out_hash_index_ref) {

        xmm_reg = _mm_loadu_epi32(in_hash_value_array_ptr[out_hash_index_ref].h);

        if (_mm_testz_si128(xmm_reg,xmm_reg) != 0) {
            return(true);
        }
    }

    return(false);
}

inline const IFBB8
ifb_hash::search(
    const IFBHash* in_hash_value_array_ptr,
    const IFBU32   in_hash_value_array_count,
    const IFBHash  in_hash_value,
          IFBU32& out_hash_index_ref) {

    if (
        in_hash_value_array_ptr   == NULL ||  
        in_hash_value_array_count == 0) {
        
        return(false);
    }

    //load the hash value
    __m128i xmm_reg_0 = _mm_loadu_epi32(in_hash_value.h);

    for (
            out_hash_index_ref = 0;
            out_hash_index_ref < in_hash_value_array_count;
        ++out_hash_index_ref) {

        //load the current value to compare            
        __m128i xmm_reg_1 = _mm_loadu_epi32(in_hash_value_array_ptr[out_hash_index_ref].h); 

        //compare the values
        if (MeowHashesAreEqual(xmm_reg_0,xmm_reg_1)) {
            //if they are equal, we're done
            return(true);
        }
    }

    //no collisions, we're done
    return(false); 
}

inline const IFBB8
ifb_hash::search(
    const IFBHash* hash_value_array_ptr,
    const IFBU32   hash_value_array_count,
    const IFBHash  hash_value) {

    if (
        hash_value_array_ptr   == NULL ||  
        hash_value_array_count == 0) {
        
        return(false);
    }

    //load the hash value
    __m128i xmm_reg_0 = _mm_loadu_epi32(hash_value.h);

    for (
        IFBU32 hash_index = 0;
                hash_index < hash_value_array_count;
                ++hash_index) {

        //load the current value to compare            
        __m128i xmm_reg_1 = _mm_loadu_epi32(hash_value_array_ptr[hash_index].h); 

        //compare the values
        if (MeowHashesAreEqual(xmm_reg_0,xmm_reg_1)) {
            //if they are equal, we're done
            return(true);
        }
    }

    //no collisions, we're done
    return(false); 
}


inline const IFBB8
ifb_hash::hash_is_clear(
    const IFBHash& hash_value) {

    IFBB8 is_clear = true;

    is_clear &= (hash_value.h1 == 0);
    is_clear &= (hash_value.h2 == 0);
    is_clear &= (hash_value.h3 == 0);
    is_clear &= (hash_value.h4 == 0);

    return(is_clear);
}

#endif //IFB_HASH_HPP