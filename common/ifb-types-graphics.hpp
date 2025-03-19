#ifndef IFB_TYPES_GRAPHICS_HPP
#define IFB_TYPES_GRAPHICS_HPP

#include "ifb-types-primitives.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBColorNormalized;
struct IFBColorHex;
struct IFBColor32;
struct IFBDimensions;
struct IFBPosition;
struct IFBDimensionsAndPosition;
struct IFBGraphicsContexts;
struct IFBWindow;
struct IFBMonitor;

typedef IFBPtr IFBGLContext;
typedef IFBPtr IFBImGuiContext;

/**********************************************************************************/
/* COORDINATES                                                                    */
/**********************************************************************************/

struct IFBDimensions {
    IFBU32 width;
    IFBU32 height;
};

struct IFBPosition {
    IFBU32 x;
    IFBU32 y;
};

struct IFBDimensionsAndPosition {
    IFBDimensions dimensions;
    IFBPosition   position;    
};

/**********************************************************************************/
/* COLORS                                                                         */
/**********************************************************************************/

struct IFBColorNormalized {
    IFBF32 red;
    IFBF32 blue;
    IFBF32 green;
    IFBF32 alpha;
};

struct IFBColorHex {
    IFBU8 red;
    IFBU8 blue;
    IFBU8 green;
    IFBU8 alpha;
};

struct IFBColor32 {
    IFBU32 value;
};

enum IFBColorFormat : IFBU32 {
     IFBColorFormat_RGBA = 0,
     IFBColorFormat_ARGB = 1,
     IFBColorFormat_ABGR = 2,
     IFBColorFormat_BGRA = 3
};

#define IFB_WINDOW_TITLE_LENGTH_MAX 255

/**********************************************************************************/
/* GRAPHICS WINDOW/HARDWARE                                                       */
/**********************************************************************************/

struct IFBGraphicsContexts {
    IFBGLContext    opengl;
    IFBImGuiContext imgui;
};

struct IFBWindow {
    IFBPosition         position;
    IFBDimensions       dimensions;
    IFBGraphicsContexts graphics_contexts;
    IFBB32              visible;
    IFBB32              quit_received;
    IFBChar*            title;
};

struct IFBMonitor {
    IFBDimensions dimensions;
    IFBPosition   position;
    IFBU32        refresh_hz;
    IFBU32        index;
};

#endif //IFB_TYPES_GRAPHICS_HPP