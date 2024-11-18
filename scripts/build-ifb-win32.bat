::----------------------------------------------------------------
:: START
::----------------------------------------------------------------

@echo off

pushd ..

::----------------------------------------------------------------
:: VARIABLES
::----------------------------------------------------------------

@set path_build=              build\debug

@set path_engine_include=     engine\include

::vcpkg install directories
@set path_vcpkg=              vcpkg_installed
@set path_vcpkg_include=      %path_vcpkg%\x64-windows\include
@set path_vcpkg_lib=          %path_vcpkg%\x64-windows\lib

::----------------------------------------------------------------
:: DEPENDENCIES
::----------------------------------------------------------------

if not exist %path_build%\bin mkdir %path_build%\bin
if not exist %path_build%\obj mkdir %path_build%\obj

::----------------------------------------------------------------
:: COMPILER ARGUMENTS
::----------------------------------------------------------------

@set cl_flags=        /Zi ^
                      /MD

@set cl_output=       /Fe:%path_build%\bin\ItFliesBy.exe ^
                      /Fo:%path_build%\obj\ItFliesBy.obj ^
                      /Fd:%path_build%\bin\ItFliesBy.pdb

@set cl_includes=     /I win32\include         ^
                      /I %path_engine_include% ^
                      /I %path_vcpkg_include%


@set cl_source=       win32\src\ifb-win32.cpp

@set cl_link=         /link                                    ^
                      /LIBPATH:vcpkg_installed\x64-windows\lib ^
                      /LIBPATH:build\debug\lib

@set cl_libs=         ItFliesBy.Engine.lib

::----------------------------------------------------------------
:: BUILD
::----------------------------------------------------------------

call cl.exe       ^
    %cl_flags%    ^
    %cl_output%   ^
    %cl_includes% ^
    %cl_source%   ^
    %cl_link%     ^
    %cl_libs%    

::----------------------------------------------------------------
:: END
::----------------------------------------------------------------

popd