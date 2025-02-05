#ifndef IFB_SPRITE_HPP
#define IFB_SPRITE_HPP

#include "ifb-types.hpp"
#include "ifb-graphics.hpp"
#include "ifb-rendering.hpp"
#include "ifb-memory.hpp"
#include "ifb-tag.hpp"

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
    IFBIDTag           tag_id;
    IFBIDTransform     transform_id;
    IFBColorTableIndex color_table_index;
};

#endif //IFB_SPRITE_HPP