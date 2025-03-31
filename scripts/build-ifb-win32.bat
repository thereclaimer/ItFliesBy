::----------------------------------------------------------------
:: START
::----------------------------------------------------------------

@echo off

pushd ..

::----------------------------------------------------------------
:: VARIABLES
::----------------------------------------------------------------

@set path_build=                  build\debug

::vcpkg install directories
@set path_vcpkg=                  vcpkg_installed
@set path_vcpkg_lib=              %path_vcpkg%\x64-windows\lib

::includes
@set path_include_win32=          win32\include
@set path_include_engine=         engine\include
@set path_include_platform=       platform\include
@set path_include_common=         common
@set path_include_external=       external
@set path_include_memory=         memory\include
@set path_include_datastructures= data-structures\include
@set path_include_graphics=       graphics\include
@set path_include_rendering=      rendering\include
@set path_include_vcpkg=          %path_vcpkg%\x64-windows\include

::----------------------------------------------------------------
:: DEPENDENCIES
::----------------------------------------------------------------

if not exist %path_build%\bin mkdir %path_build%\bin
if not exist %path_build%\obj mkdir %path_build%\obj

::----------------------------------------------------------------
:: COMPILER ARGUMENTS
::----------------------------------------------------------------

@set cl_flags=      /Zi        ^
                    /MD        ^
                    /std:c++17 ^
                    /EHsc

@set cl_output=     /Fo:%path_build%\obj\ItFliesBy.obj ^
                    /Fd:%path_build%\bin\ItFliesBy.pdb ^
                    /Fe:%path_build%\bin\ItFliesBy.exe

@set cl_includes=   /I %path_include_win32%          ^
                    /I %path_include_engine%         ^
                    /I %path_include_platform%       ^
                    /I %path_include_common%         ^
                    /I %path_include_external%       ^
                    /I %path_include_memory%         ^
                    /I %path_include_datastructures% ^
                    /I %path_include_graphics%       ^
                    /I %path_include_rendering%      ^
                    /I %path_include_vcpkg%

@set cl_source=     win32\src\ifb-win32-itfliesby.cpp

@set cl_link=       /link                                    ^
                    /LIBPATH:vcpkg_installed\x64-windows\lib ^
                    /LIBPATH:build\debug\lib                 ^
                    /SUBSYSTEM:WINDOWS

@set cl_libs=       ItFliesBy.Engine.lib ^
                    ItFliesBy.Memory.lib ^
                    user32.lib           ^
                    imgui.lib            ^
                    opengl32.lib         ^
                    Advapi32.lib


::----------------------------------------------------------------
:: COMPILE AND LINK
::----------------------------------------------------------------

call cl.exe       ^
    %cl_flags%    ^
    %cl_output%   ^
    %cl_includes% ^
    %cl_source%   ^
    %cl_link%     ^
    %cl_libs%

::----------------------------------------------------------------
:: LINKER ARGUMENTS
::----------------------------------------------------------------



::----------------------------------------------------------------
:: END
::----------------------------------------------------------------

popd