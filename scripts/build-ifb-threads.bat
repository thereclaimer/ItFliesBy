::----------------------------------------------------------------
:: START
::----------------------------------------------------------------

@echo off

pushd ..

::----------------------------------------------------------------
:: VARIABLES
::----------------------------------------------------------------

::build path
@set path_build=                  build\debug

::vcpkg install directories
@set path_vcpkg=                  vcpkg_installed
@set path_vcpkg_lib=              %path_vcpkg%\x64-windows\lib

::include paths 
@set path_include_threads=        threads\include
@set path_include_platform=       platform\include
@set path_include_datastructures= data-structures\include
@set path_include_memory=         memory\include
@set path_include_common=         common
@set path_include_external=       external
@set path_include_vcpkg=          %path_vcpkg%\x64-windows\include

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

@set cl_output=     /Fo:%path_build%\obj\ItFliesBy.Threads.obj

@set cl_includes=   /I %path_include_threads%         ^
                    /I %path_include_platform%        ^
                    /I %path_include_datastructures%  ^
                    /I %path_include_memory%          ^
                    /I %path_include_common%          ^
                    /I %path_include_external%        ^
                    /I %path_include_vcpkg% 

@set cl_source=     threads\src\ifb-threads.cpp

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

call lib.exe                                   ^
    /OUT:build\debug\lib\ItFliesBy.Threads.lib ^
    %path_build%\obj\ItFliesBy.Threads.obj

::----------------------------------------------------------------
:: END
::----------------------------------------------------------------

popd