#pragma once

#include <string.h>

#include "ifb-engine-algorithms.hpp"
#include "ifb-engine-external.hpp"

ifb_api const ifb_u32 
ifb_engine::hash_cstr(
    const ifb_cstr             in_cstr,
    const ifb_u32              in_cstr_length_max,
          IFBEngineHashValue& out_cstr_hash_value_ref) {

    //sanity check
    if (!in_cstr) {
        return(0);
    }

    //get the safe length of the string
    const ifb_u32 in_cstr_length = strnlen_s(in_cstr,in_cstr_length_max - 1) + 1;

    //do the hash
    meow_u128 meow_hash_value = MeowHash(MeowDefaultSeed,in_cstr_length,in_cstr);

    //load the value
    _mm_storeu_epi32(out_cstr_hash_value_ref.h,meow_hash_value);

    //we're done
    return(in_cstr_length);
}

ifb_api const ifb_b8
ifb_engine::hash_collision_check(
          IFBEngineHashValue& hash_value_ref,
    const IFBEngineHashValue* hash_value_array_ptr,
    const ifb_u32             hash_value_array_count) {

    if (
        hash_value_array_ptr   == NULL ||  
        hash_value_array_count == 0) {
        
        return(false);
    }

    //load the hash value
    __m128i xmm_reg_0 = _mm_loadu_epi32(hash_value_ref.h);

    for (
        ifb_u32 hash_index = 0;
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

ifb_api const ifb_b8
ifb_engine::hash_next_clear_value(
    const IFBEngineHashValue* in_hash_value_array_ptr,
    const ifb_u32             in_hash_value_array_count,
          ifb_u32&           out_hash_index_ref) {

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


ifb_api const ifb_b8
ifb_engine::hash_search(
          IFBEngineHashValue& in_hash_value_ref,
    const IFBEngineHashValue* in_hash_value_array_ptr,
    const ifb_u32             in_hash_value_array_count,
          ifb_u32&           out_hash_index_ref) {

    if (
        in_hash_value_array_ptr   == NULL ||  
        in_hash_value_array_count == 0) {
        
        return(false);
    }

    //load the hash value
    __m128i xmm_reg_0 = _mm_loadu_epi32(in_hash_value_ref.h);

    for (
        ifb_u32 out_hash_index_ref = 0;
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