::----------------------------------------------------------------
:: START
::----------------------------------------------------------------

@echo off

pushd ..

::----------------------------------------------------------------
:: VARIABLES
::----------------------------------------------------------------

@set path_build=              build\debug

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

@set cl_flags=        /Zi ^
                      /LD ^
                      /MD

@set cl_output=       /Fe:%path_build%\bin\ItFliesBy.Engine.dll ^
                      /Fo:%path_build%\obj\ItFliesBy.Engine.obj ^
                      /Fd:%path_build%\bin\ItFliesBy.Engine.pdb

@set cl_includes=     /I engine\include          ^
                      /I engine\internal         ^
                      /I engine\src              ^
                      /I engine\src\context      ^
                      /I engine\src\memory       ^
                      /I memory\include          ^
                      /I memory\internal         ^
                      /I memory\src         ^
                      /I data-structures\include ^
                      /I common                  ^
                      /I external                ^
                      /I math                    ^
                      /I %path_vcpkg_include%

@set cl_source=       engine\src\ifb-engine.cpp build\debug\lib\ItFliesBy.Memory.lib

@set cl_link=         /link                                    ^
                      /LIBPATH:vcpkg_installed\x64-windows\lib ^
                      /LIBPATH:build\debug\lib                 ^
                      /IMPLIB:build\debug\lib\ItFliesBy.Engine.lib

@set cl_libs=         imgui.lib                    ^
                      opengl32.lib                 ^
                      glew32.lib

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