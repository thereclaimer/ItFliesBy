#include "ifb-engine-core-internal.hpp"

namespace ifb {

    IFB_ENG_FUNC eng_bool
    eng_core_monitor_table_validate(
        void) {

        bool is_valid = true;
        is_valid &= (_eng_core_monitor_table.array.position_x != NULL);
        is_valid &= (_eng_core_monitor_table.array.position_y != NULL);
        is_valid &= (_eng_core_monitor_table.array.width      != NULL);
        is_valid &= (_eng_core_monitor_table.array.height     != NULL);
        is_valid &= (_eng_core_monitor_table.array.name       != NULL);
        is_valid &= (_eng_core_monitor_table.array.handle     != NULL);
        return(is_valid);
    }

    IFB_ENG_FUNC void
    eng_core_monitor_table_init(
        void) {

        static eng_bool is_init = false;
        assert(!is_init);

        // initialize the table
        _eng_core_monitor_table.array.position_x = eng_core_platform_arena_push_struct_array (ENG_CORE_MONITOR_COUNT_MAX,        eng_u32);
        _eng_core_monitor_table.array.position_y = eng_core_platform_arena_push_struct_array (ENG_CORE_MONITOR_COUNT_MAX,        eng_u32);
        _eng_core_monitor_table.array.width      = eng_core_platform_arena_push_struct_array (ENG_CORE_MONITOR_COUNT_MAX,        eng_u32);
        _eng_core_monitor_table.array.height     = eng_core_platform_arena_push_struct_array (ENG_CORE_MONITOR_COUNT_MAX,        eng_u32);
        _eng_core_monitor_table.array.name       = eng_core_platform_arena_push_struct_array (ENG_CORE_MONITOR_NAME_BUFFER_SIZE, eng_cchar);
        _eng_core_monitor_table.array.handle     = eng_core_platform_arena_push_struct_array (ENG_CORE_MONITOR_COUNT_MAX,        eng_core_monitor_handle_t);

        // check the table
        is_init = true;
        is_init &= (_eng_core_monitor_table.array.position_x != NULL);
        is_init &= (_eng_core_monitor_table.array.position_y != NULL);
        is_init &= (_eng_core_monitor_table.array.width      != NULL);
        is_init &= (_eng_core_monitor_table.array.height     != NULL);
        is_init &= (_eng_core_monitor_table.array.name       != NULL);
        is_init &= (_eng_core_monitor_table.array.handle     != NULL);        
        assert(is_init);

        // do the first refresh
        eng_core_monitor_table_refresh();     
    }

    IFB_ENG_FUNC void
    eng_core_monitor_table_refresh(
        void) {

        // get the monitor info and working area
        sld::os_monitor_working_area_t working_area;
        sld::os_monitor_info_t         info_array[ENG_CORE_MONITOR_COUNT_MAX];
        sld::os_monitor_working_area   (working_area);
        sld::os_monitor_info           (info_array);

        // update the table
        _eng_core_monitor_table.primary             = sld::os_monitor_primary ();
        _eng_core_monitor_table.count               = sld::os_monitor_count   ();
        _eng_core_monitor_table.virtual_size.width  = working_area.virtual_pixel_height;
        _eng_core_monitor_table.virtual_size.height = working_area.virtual_pixel_width;

        // check the properties
        bool is_valid = true;
        is_valid &= eng_core_monitor_table_validate();
        is_valid &= (_eng_core_monitor_table.count               != 0);
        is_valid &= (_eng_core_monitor_table.virtual_size.width  != 0);
        is_valid &= (_eng_core_monitor_table.virtual_size.height != 0);
        assert(is_valid);        
        
        // add the monitors to the table
        cstr_t monitor_name_cstr_src = { NULL, sld::OS_MONITOR_NAME_WIDTH};
        cstr_t monitor_name_cstr_dst = { NULL, sld::OS_MONITOR_NAME_WIDTH};
        for (
            eng_u32 monitor = 0;
            monitor < _eng_core_monitor_table.count;
            ++monitor) {

            // get the next info
            sld::os_monitor_info_t& info = info_array[monitor];

            // check the monitor is valid
            bool is_monitor_valid = true;
            is_monitor_valid = (info.handle.val   != NULL);
            is_monitor_valid = (info.index        < _eng_core_monitor_table.count);
            is_monitor_valid = (info.pixel_width  > 0);
            is_monitor_valid = (info.pixel_height > 0);
            is_monitor_valid = (info.pixel_width  <= working_area.virtual_pixel_width);
            is_monitor_valid = (info.pixel_height <= working_area.virtual_pixel_height);
            is_monitor_valid = (info.position_x   <= working_area.virtual_pixel_width);
            is_monitor_valid = (info.position_y   <= working_area.virtual_pixel_height);
            assert(is_monitor_valid);

            // copy the name
            const eng_u32 name_str_offset = (monitor * sld::OS_MONITOR_NAME_WIDTH); 
            monitor_name_cstr_src.chars   = &info.name_cstr                              [name_str_offset];
            monitor_name_cstr_dst.chars   = &_eng_core_monitor_table.array.name [name_str_offset];
            (void)sld::cstr_copy(monitor_name_cstr_dst, monitor_name_cstr_src);          

            // set remaining properties
            _eng_core_monitor_table.array.position_x [monitor] = info.position_x;    
            _eng_core_monitor_table.array.position_y [monitor] = info.position_y;    
            _eng_core_monitor_table.array.width      [monitor] = info.pixel_width;         
            _eng_core_monitor_table.array.height     [monitor] = info.pixel_height;        
            _eng_core_monitor_table.array.handle     [monitor] = info.handle;
        }
    }

    IFB_ENG_FUNC eng_u32
    eng_core_monitor_table_search(
        const eng_core_monitor_handle_t monitor) {

        bool is_valid = true; 
        is_valid &= eng_core_monitor_table_validate();
        is_valid &= (monitor.val != NULL);
        assert(is_valid);

        eng_u32  index    = 0;
        eng_bool is_found = false;
        for (
            index;
            index < _eng_core_monitor_table.count;
            ++index) {

            is_found |= (_eng_core_monitor_table.array.handle[index].val == monitor.val);
            if (is_found) break;
        }

        assert(is_found && index < _eng_core_monitor_table.count);
        return(index);
    }

    IFB_ENG_FUNC void
    eng_core_monitor_get_size(
        const eng_core_monitor_handle_t monitor,
        eng_dims_size_t&                   size) {

        bool is_valid = true; 
        is_valid &= eng_core_monitor_table_validate();
        is_valid &= (monitor.val != NULL);
        assert(is_valid);

        const eng_u32 index = eng_core_monitor_table_search(monitor);

        size.width  = _eng_core_monitor_table.array.width  [index];
        size.height = _eng_core_monitor_table.array.height [index];
    }

    IFB_ENG_FUNC void
    eng_core_monitor_get_position(
        const eng_core_monitor_handle_t monitor,
        eng_dims_pos_t&                    pos) {

        bool is_valid = true; 
        is_valid &= eng_core_monitor_table_validate();
        is_valid &= (monitor.val != NULL);
        assert(is_valid);

        const eng_u32 index = eng_core_monitor_table_search(monitor);

        pos.x = _eng_core_monitor_table.array.position_x [index];
        pos.y = _eng_core_monitor_table.array.position_y [index];
    }

    IFB_ENG_FUNC void
    eng_core_monitor_get_name(
        const eng_core_monitor_handle_t monitor,
        eng_core_monitor_name_t&           name) {

        bool is_valid = true; 
        is_valid &= eng_core_monitor_table_validate();
        is_valid &= (monitor.val != NULL);
        assert(is_valid);

        const eng_u32 index = eng_core_monitor_table_search(monitor);

        eng_cstr_t dst;
        dst.chars = name.cstr;
        dst.size  = sld::OS_MONITOR_NAME_WIDTH;

        eng_cstr_t src;
        src.chars = &_eng_core_monitor_table.array.name[index * sld::OS_MONITOR_NAME_WIDTH];  
        src.size  = sld::OS_MONITOR_NAME_WIDTH;

        (void)sld::cstr_copy(dst, src);
    }

    IFB_ENG_FUNC void
    eng_core_monitor_get_info(
        const eng_core_monitor_handle_t monitor,
        eng_core_monitor_info_t&           info) {

        bool is_valid = true; 
        is_valid &= eng_core_monitor_table_validate();
        is_valid &= (monitor.val != NULL);
        assert(is_valid);

        const eng_u32 index = eng_core_monitor_table_search(monitor);

        info.size.width  = _eng_core_monitor_table.array.width      [index];
        info.size.height = _eng_core_monitor_table.array.height     [index];
        info.pos.x       = _eng_core_monitor_table.array.position_x [index];
        info.pos.y       = _eng_core_monitor_table.array.position_y [index];

        eng_cstr_t dst, src;
        dst.chars = info.name.cstr;
        src.chars = &_eng_core_monitor_table.array.name[index * sld::OS_MONITOR_NAME_WIDTH];  
        dst.size  = sld::OS_MONITOR_NAME_WIDTH;
        src.size  = sld::OS_MONITOR_NAME_WIDTH;
        (void)sld::cstr_copy(dst, src);
    }
};