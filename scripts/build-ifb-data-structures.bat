::----------------------------------------------------------------
:: START
::----------------------------------------------------------------

@echo off

pushd ..

::----------------------------------------------------------------
:: VARIABLES
::----------------------------------------------------------------

::build path
@set path_build=          build\debug

::include paths 
@set path_data_structures_include=  data-structures\include
@set path_common=                   common
@set path_external=                 external

::vcpkg install directories
@set path_vcpkg=              vcpkg_installed
@set path_vcpkg_include=      %path_vcpkg%\x64-windows\include
@set path_vcpkg_lib=          %path_vcpkg%\x64-windows\lib

::----------------------------------------------------------------
:: DEPENDENCIES
::----------------------------------------------------------------

if not exist %path_build%\bin mkdir %path_build%\bin
if not exist %path_build%\obj mkdir %path_build%\obj
if not exist %path_build%\lib mkdir %path_build%\lib

::----------------------------------------------------------------
:: COMPILER ARGUMENTS
::----------------------------------------------------------------

@set cl_flags=      /Zi ^
                    /MD ^
                    /c

@set cl_output=     /Fo:%path_build%\obj\ItFliesBy.DataStructures.obj ^
                    /Fd:%path_build%\bin\ItFliesBy.DataStructures.pdb

@set cl_includes=   /I %path_data_structures_include%  ^
                    /I %path_common%                   ^
                    /I %path_external%                 ^
                    /I %path_vcpkg_include%

@set cl_source=     data-structures\src\ifb-data-structures.cpp

::----------------------------------------------------------------
:: BUILD
::----------------------------------------------------------------

call cl.exe       ^
    %cl_flags%    ^
    %cl_output%   ^
    %cl_includes% ^
    %cl_source%

::----------------------------------------------------------------
:: LIB
::----------------------------------------------------------------

call lib.exe                                          ^
    /OUT:build\debug\lib\ItFliesBy.DataStructures.lib ^
    %path_build%\obj\ItFliesBy.DataStructures.obj

::----------------------------------------------------------------
:: END
::----------------------------------------------------------------

popd