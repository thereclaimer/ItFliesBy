#ifndef IFB_SPRITE_HPP
#define IFB_SPRITE_HPP

#include "ifb-types.hpp"
#include "ifb-graphics.hpp"
#include "ifb-rendering.hpp"
#include "ifb-memory.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

//ids
struct IFBIDSprite      : IFBID { };
struct IFBIDSpriteAtlas : IFBID { };

//structs
struct IFBSpriteAtlas;
struct IFBSprite;

/**********************************************************************************/
/* SPRITE ATLAS                                                                   */
/**********************************************************************************/

struct IFBSpriteAtlas : IFBIDSpriteAtlas {
    IFBDimensions unit_sprite_dimensions;
    ifb_u32       count_rows;
    ifb_u32       count_columns;
};

/**********************************************************************************/
/* SPRITE                                                                         */
/**********************************************************************************/

struct IFBSprite : IFBIDSprite {
    IFBIDTransform     transform_id;
    IFBIDSpriteAtlas   sprite_atlas_id;
    IFBColorTableIndex color_table_index;
    ifb_u32            sprite_atlas_index;
};

#endif //IFB_SPRITE_HPP