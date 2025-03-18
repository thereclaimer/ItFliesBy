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
@set path_io_include=        io\include
@set path_common=            common
@set path_external=          external
@set path_datastructures=    data-structures\include
@set path_memory=            memory\include

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

@set cl_output=     /Fo:%path_build%\obj\ItFliesBy.IO.obj

@set cl_includes=   /I %path_io_include% ^
                    /I %path_datastructures%   ^
                    /I %path_memory%           ^
                    /I %path_common%           ^
                    /I %path_external%         ^
                    /I %path_vcpkg_include%

@set cl_source=     io\src\ifb-io.cpp

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

call lib.exe                              ^
    /OUT:build\debug\lib\ItFliesBy.IO.lib ^
    %path_build%\obj\ItFliesBy.IO.obj

::----------------------------------------------------------------
:: END
::----------------------------------------------------------------

popd