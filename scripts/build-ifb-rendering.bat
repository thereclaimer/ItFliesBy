::----------------------------------------------------------------
:: START
::----------------------------------------------------------------

@echo off

pushd ..

::----------------------------------------------------------------
:: VARIABLES
::----------------------------------------------------------------

::build path
@set path_build=             build\debug

::include paths 
@set path_rendering_include=      rendering\include
@set path_graphics_include=       graphics\include
@set path_datastructures_include= data-structures\include
@set path_memory_include=         memory\include
@set path_common=                 common
@set path_external=               external

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

@set cl_flags=      /c    ^
                    /MD   ^
                    /Z7   ^
                    /EHsc

@set cl_output=     /Fo:%path_build%\obj\ItFliesBy.Rendering.obj

@set cl_includes=   /I %path_external%               ^
                    /I %path_common%                 ^
                    /I %path_vcpkg_include%          ^
                    /I %path_rendering_include%      ^
                    /I %path_datastructures_include% ^
                    /I %path_memory_include%         ^
                    /I %path_graphics_include%       ^
                    /I rendering\src\gl

@set cl_source=     rendering\src\ifb-rendering.cpp

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

call lib.exe                                  ^
    /OUT:build\debug\lib\ItFliesBy.Rendering.lib ^
    %path_build%\obj\ItFliesBy.Rendering.obj

::----------------------------------------------------------------
:: END
::----------------------------------------------------------------

popd