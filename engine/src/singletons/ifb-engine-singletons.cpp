#include "ifb-engine-internal-singletons.hpp"
#include "ifb-engine-internal-graphics.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb_engine {

    const ifb_byte* 
    singletons_buffer_get_pointer(
        const IFBEngineSingletonBuffer& singleton_buffer,
        const ifb_u16                   singleton_handle);
};

/**********************************************************************************/
/* COMMIT                                                                         */
/**********************************************************************************/

inline ifb_void
ifb_engine::singletons_commit_all(
    IFBEngineSingletons* ptr_singletons) {

    //sanity check
    ifb_macro_assert(ptr_singletons);
    
    //calculate all the singleton sizes
    const ifb_u32 size_array[] = {
        ifb_macro_align_size_struct(IFBEngineConfig),
        ifb_macro_align_size_struct(IFBInput),
        ifb_macro_align_size_struct(IFBEngineDevTools),
        ifb_macro_align_size_struct(IFBEngineGraphicsManager)
    };
    
    //calculate the singleton count
    const ifb_u32 singletons_count = ifb_macro_array_count(ifb_u32,size_array); 

    //cast the singleton handles to an array
    ifb_u16* singlegon_handles_array = (ifb_u16*)&ptr_singletons->handles;
    ifb_u16  buffer_position_u16 = 0;

    //calculate all the handles
    for (
        ifb_u32 singleton_index = 0;
        singleton_index < singletons_count;
        ++singleton_index) {

        //get the current singleton size
        const ifb_u32 singleton_size_u32 = size_array[singleton_index];

        //calculate the new buffer position
        const ifb_u32 new_buffer_position_u32 = 
            singleton_size_u32 + buffer_position_u16;
    
        //sanity check
        ifb_macro_assert(singleton_size_u32      < IFB_ENGINE_SINGLETON_STACK_SIZE);
        ifb_macro_assert(new_buffer_position_u32 < IFB_ENGINE_SINGLETON_STACK_SIZE);

        //set the handle of the current singleton to the buffer position
        singlegon_handles_array[singleton_index] = buffer_position_u16;
        buffer_position_u16                      = (ifb_u16)new_buffer_position_u32;
    }
}

/**********************************************************************************/
/* LOAD                                                                           */
/**********************************************************************************/

inline IFBEngineConfig*
ifb_engine::singletons_load_config(
    const IFBEngineSingletons* ptr_singletons) {

    //sanity check
    ifb_macro_assert(ptr_singletons);
    
    //get the pointer
    IFBEngineConfig* ptr_config = (IFBEngineConfig*)ifb_engine::singletons_buffer_get_pointer(
            ptr_singletons->buffer,
            ptr_singletons->handles.config);

    //we're done
    return(ptr_config);
}

inline IFBInput*
ifb_engine::singletons_load_input(
    const IFBEngineSingletons* ptr_singletons) {

    //sanity check
    ifb_macro_assert(ptr_singletons);
    
    //get the pointer
    IFBInput* ptr_input = (IFBInput*)ifb_engine::singletons_buffer_get_pointer(
            ptr_singletons->buffer,
            ptr_singletons->handles.input);

    //we're done
    return(ptr_input);
}

inline IFBEngineDevTools*
ifb_engine::singletons_load_devtools(
    const IFBEngineSingletons* ptr_singletons) {

    //sanity check
    ifb_macro_assert(ptr_singletons);
    
    //get the pointer
    IFBEngineDevTools* ptr_devtools = (IFBEngineDevTools*)ifb_engine::singletons_buffer_get_pointer(
            ptr_singletons->buffer,
            ptr_singletons->handles.dev_tools);

    //we're done
    return(ptr_devtools);
}

inline IFBEngineGraphicsManager*
ifb_engine::singletons_load_graphics_manager(
    const IFBEngineSingletons* ptr_singletons) {

    //sanity check
    ifb_macro_assert(ptr_singletons);
    
    //get the pointer
    IFBEngineGraphicsManager* ptr_graphics_manager = (IFBEngineGraphicsManager*)ifb_engine::singletons_buffer_get_pointer(
            ptr_singletons->buffer,
            ptr_singletons->handles.graphics_manager);

    //we're done
    return(ptr_graphics_manager);
}


/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

inline const ifb_byte* 
ifb_engine::singletons_buffer_get_pointer(
    const IFBEngineSingletonBuffer& singleton_buffer,
    const ifb_u16                   singleton_handle) {

    const ifb_byte* pointer = &singleton_buffer.memory[singleton_handle];
    return(pointer);
}