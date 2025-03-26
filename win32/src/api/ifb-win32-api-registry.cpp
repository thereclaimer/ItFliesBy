#pragma once

#include "ifb-win32.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb_win32 {

    const IFBB8
    registry_open_key_readonly_base(
        const HKEY   key_root,
              LPCSTR key_path,
              HKEY&  key_ref);
};

/**********************************************************************************/
/* READ ONLY                                                                      */
/**********************************************************************************/

inline const IFBB8 
ifb_win32::registry_key_open_read_only_classes_root(
    const LPCSTR key_path,
    HKEY&  key_ref) {

    const HKEY key_root = HKEY_CLASSES_ROOT;

    const IFBB8 result = ifb_win32::registry_open_key_readonly_base(
        key_root,
        key_path,
        key_ref);

    return(result);
}

inline const IFBB8 
ifb_win32::registry_key_open_read_only_current_user(
    const LPCSTR key_path,
    HKEY&  key_ref) {

    const HKEY key_root = HKEY_CURRENT_USER;

    const IFBB8 result = ifb_win32::registry_open_key_readonly_base(
        key_root,
        key_path,
        key_ref);

    return(result);
}

inline const IFBB8 
ifb_win32::registry_key_open_read_only_local_machine(
    const LPCSTR key_path,
    HKEY&  key_ref) {

    const HKEY key_root = HKEY_LOCAL_MACHINE;

    const IFBB8 result = ifb_win32::registry_open_key_readonly_base(
        key_root,
        key_path,
        key_ref);

    return(result);
}

inline const IFBB8 
ifb_win32::registry_key_open_read_only_users(
    const LPCSTR key_path,
    HKEY&  key_ref) {

    const HKEY key_root = HKEY_USERS;

    const IFBB8 result = ifb_win32::registry_open_key_readonly_base(
        key_root,
        key_path,
        key_ref);

    return(result);
}

inline const IFBB8 
ifb_win32::registry_key_open_read_only_current_config(
    const LPCSTR key_path,
    HKEY&  key_ref) {

    const HKEY key_root = HKEY_CURRENT_CONFIG;

    const IFBB8 result = ifb_win32::registry_open_key_readonly_base(
        key_root,
        key_path,
        key_ref);

    return(result);
}

/**********************************************************************************/
/* CLOSE                                                                          */
/**********************************************************************************/

inline const IFBB8
ifb_win32::registry_key_close (
    const HKEY key) {

    const LRESULT result = RegCloseKey(key);

    return(result == ERROR_SUCCESS);
}

/**********************************************************************************/
/* VALUES                                                                         */
/**********************************************************************************/

inline const IFBB8
ifb_win32::registry_key_read_value_u32(
    const HKEY    key,
    const LPCSTR  value_name,
          IFBU32& value_ref) {

    DWORD data_size = sizeof(IFBU32);

    const LRESULT l_result = RegQueryValueEx(
        key,
        value_name,
        NULL,
        NULL,
        (LPBYTE)&value_ref,
        &data_size);

    const IFBB8 result = (l_result == ERROR_SUCCESS);

    return(result);
}

inline const IFBB8
ifb_win32::registry_key_read_value_cpu_speed_mhz(
    IFBWin32RegKeyU32& key_u32) {

    IFBU32 result = true;
    result &= ifb_win32_macro_registry_key_cpu_0               (key_u32.key);
    result &= ifb_win32_macro_registry_key_cpu_0_value_u32_mhz (key_u32.key,key_u32.value);
    return(result);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline const IFBB8
ifb_win32::registry_open_key_readonly_base(
    const HKEY    key_root,
          LPCSTR  key_path,
          HKEY&   key_ref) {

    //default parameters
    const DWORD  key_options = 0;
    const REGSAM key_access  = KEY_READ; 

    //open the key
    const LRESULT key_open_result = RegOpenKeyEx(
        key_root,
        key_path,
        key_options,
        key_access,
        &key_ref);

    //check result
    const IFBB8 result = (key_open_result == ERROR_SUCCESS);

    //we're done
    return(result);
}