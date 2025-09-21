#ifndef IFB_ENG_HASH_HPP
#define IFB_ENG_HASH_HPP

#include <sld-hash.hpp>

#include "ifb-engine.hpp"

namespace ifb {

    //-------------------------------------------------------------------
    // DATA STRUCTURES
    //-------------------------------------------------------------------

    typedef sld::hash128_t       eng_hash_u128_t;
    typedef sld::hash128_state_t eng_hash_u128_state_t;
    typedef sld::hash128_seed_t  eng_hash_u128_seed_t;

    //-------------------------------------------------------------------
    // DECLARATIONS
    //-------------------------------------------------------------------

    const eng_hash_u128_t eng_hash_data          (const eng_byte*        data,   const eng_u32         length);
    bool                  eng_hash_data_batch    (const eng_u32          count,  const eng_byte*       data,   const eng_u32           stride, eng_hash_u128_t* hashes);
    bool                  eng_hash_is_equal      (const eng_byte*        data_a, const eng_byte*       data_b, const eng_u32           length);
    bool                  eng_hash_is_equal      (const eng_hash_u128_t& hash,   const eng_byte*       data,   const eng_u32           length);
    bool                  eng_hash_search        (const eng_u32          count,  const eng_hash_u128_t search, const eng_hash_u128_t*  array,  eng_u32& index);

    void                  eng_hash_block_begin   (eng_hash_u128_state_t& state);
    void                  eng_hash_block_consume (eng_hash_u128_state_t& state, const eng_u64 block_size, const eng_byte* block_data);
    const eng_hash_u128_t eng_hash_block_end     (eng_hash_u128_state_t& state);

    //-------------------------------------------------------------------
    // GLOBALS
    //-------------------------------------------------------------------

    constexpr eng_hash_u128_seed_t _eng_hash_seed = {
        "maytheroadriseto" 
        "meetyouthewindbe"
        "alwaysatyourback"
        "thesunshinewarmu"
        "ponyourfacethera"
        "insfallsoftupony"
        "ougodholdyouinth"
        "epalmofhishand"
    };

    //-------------------------------------------------------------------
    // INLINE METHODS
    //-------------------------------------------------------------------

    IFB_ENG_INLINE const eng_hash_u128_t
    eng_hash_data(
        const eng_byte* data,
        const eng_u32   length) {

        const eng_hash_u128_t hash = sld::hash128_data(
            _eng_hash_seed,
            data,
            length            
        );

        return(hash);
    }

    IFB_ENG_INLINE eng_bool
    eng_hash_data_batch(
        const eng_u32    count,
        const eng_byte*  data,
        const eng_u32    stride,
        eng_hash_u128_t* hashes) {

        const eng_bool is_hashed = sld::hash128_data_batch(
            _eng_hash_seed,
            count,
            data,
            stride,
            hashes            
        );

        return(is_hashed);
    }

    IFB_ENG_INLINE eng_bool
    eng_hash_is_equal(
        const eng_byte* data_a,
        const eng_byte* data_b,
        const eng_u32   length) {

        const eng_bool is_equal = sld::hash128_is_equal(
            _eng_hash_seed,
            data_a,
            data_b,
            length
        );

        return(is_equal);
    }

    IFB_ENG_INLINE bool
    eng_hash_is_equal(
        const eng_hash_u128_t& hash,
        const eng_byte*        data,
        const eng_u32          length) {

        const eng_bool is_equal = sld::hash128_is_equal(
            _eng_hash_seed,
            hash,
            data,
            length
        );

        return(is_equal);
    }

    IFB_ENG_INLINE bool
    eng_hash_search(
        const eng_u32          count, 
        const eng_hash_u128_t  search,
        const eng_hash_u128_t* array,
        eng_u32&               index) {

        const eng_bool is_found = sld::hash128_search(
            count,
            search,
            array,
            index            
        );

        return(is_found);
    }

    IFB_ENG_INLINE void
    eng_hash_block_begin(
        eng_hash_u128_state_t& state) {

        sld::hash128_block_begin(state,_eng_hash_seed);
    }

    IFB_ENG_INLINE void
    eng_hash_block_consume(
        eng_hash_u128_state_t& state,
        const eng_u64          block_size,
        const eng_byte*        block_data) {

        sld::hash128_block_consume(state, block_size, block_data);
    }

    IFB_ENG_INLINE const eng_hash_u128_t
    eng_hash_block_end(
        eng_hash_u128_state_t& state) {

        const eng_hash_u128_t hash = sld::hash128_block_end(state);
        return(hash);
    }
};

#endif //IFB_ENG_HASH_HPP