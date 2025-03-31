#ifndef IFB_ENGINE_SYSTEMS_HPP
#define IFB_ENGINE_SYSTEMS_HPP

#include "ifb-engine.hpp"

namespace ifb {
/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

//engine core
struct engine_core_t;
struct engine_core_arenas_t;
struct engine_core_graphics_t;
struct engine_core_files_t;
struct engine_core_threads_t;

/**********************************************************************************/
/* ENGINE CORE                                                                    */
/**********************************************************************************/

struct engine_core_t {
    engine_memory_t*        memory;
    engine_core_graphics_t* graphics;
    engine_core_files_t*    files;
    engine_core_threads_t*  threads;
};

namespace engine {

    const b8 core_initialize   (engine_core_t* core);
    const b8 core_startup      (engine_core_t* core);
    const b8 core_frame_start  (engine_core_t* core);
    const b8 core_frame_render (engine_core_t* core);
    const b8 core_should_quit  (engine_core_t* core);
};

#define IFB_ENGINE_CORE_STRUCT_SIZE ifb_macro_align_size_struct(engine_core_t)

/**********************************************************************************/
/* GRAPHICS                                                                       */
/**********************************************************************************/

#define IFB_ENGINE_GRAPHICS_WINDOW_TITLE        "It Flies By (DEBUG)"
#define IFB_ENGINE_GRAPHICS_WINDOW_TITLE_LENGTH 255
#define IFB_ENGINE_GRAPHICS_WINDOW_INIT_WIDTH   1024
#define IFB_ENGINE_GRAPHICS_WINDOW_INIT_HEIGHT  768

struct engine_core_graphics_t {
    graphics_window_h window_handle;
};

namespace engine {

    const b8 core_graphics_initialize             (engine_core_graphics_t* graphics, engine_memory_t* engine_memory);
    const b8 core_graphics_create_and_show_window (engine_core_graphics_t* graphics);
    const b8 core_graphics_frame_start            (engine_core_graphics_t* graphics);
    const b8 core_graphics_frame_render           (engine_core_graphics_t* graphics);
    const b8 core_graphics_window_quit_received   (engine_core_graphics_t* graphics);
};

/**********************************************************************************/
/* FILES                                                                          */
/**********************************************************************************/

struct engine_files_t {
    u32 x;
};

/**********************************************************************************/
/* THREADS                                                                        */
/**********************************************************************************/

struct engine_threads_t {
    u32 x;
};

/**********************************************************************************/
/* GLOBALS                                                                        */
/**********************************************************************************/

struct engine_core_globals_t {
    u32   core_struct_size;
    u32   window_init_width;
    u32   window_init_height;
    u32   window_title_length;
    utf8* window_title;
};

namespace engine {

    ifb_global engine_core_globals_t _globals_core = {
        IFB_ENGINE_CORE_STRUCT_SIZE,
        IFB_ENGINE_GRAPHICS_WINDOW_INIT_WIDTH,
        IFB_ENGINE_GRAPHICS_WINDOW_INIT_HEIGHT,
        IFB_ENGINE_GRAPHICS_WINDOW_TITLE_LENGTH,
        IFB_ENGINE_GRAPHICS_WINDOW_TITLE
    };

};//namespace ifb::engine
};//namespace ifb

#endif //IFB_ENGINE_SYSTEMS_HPP