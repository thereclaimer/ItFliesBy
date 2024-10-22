::----------------------------------------------------------------
:: START
::----------------------------------------------------------------

@echo off

pushd ..

::----------------------------------------------------------------
:: VARIABLES
::----------------------------------------------------------------

@set path_build=              build\debug

::rlibs
@set path_rlibs_lib=          modules\r-libs\build\debug\lib
@set path_rlibs_bin=          modules\r-libs\build\debug\bin
@set path_rlibs_include=      modules\r-libs\build\debug\include

::vcpkg install directories
@set path_vcpkg=              modules\r-libs\vcpkg_installed
@set path_vcpkg_include=      %path_vcpkg%\x64-windows\include
@set path_vcpkg_lib=          %path_vcpkg%\x64-windows\lib

::----------------------------------------------------------------
:: DEPENDENCIES
::----------------------------------------------------------------

if not exist %path_build%\bin mkdir %path_build%\bin
if not exist %path_build%\obj mkdir %path_build%\obj
if not exist %path_build%\lib mkdir %path_build%\lib

xcopy %path_rlibs_bin%\*.dll %path_build%\bin /E /I /H /Y 
xcopy %path_rlibs_bin%\*.pdb %path_build%\bin /E /I /H /Y 

::----------------------------------------------------------------
:: COMPILER ARGUMENTS
::----------------------------------------------------------------

@set cl_flags=        /Zi ^
                      /LD ^
                      /MD

@set cl_output=       /Fe:%path_build%\bin\ItFliesBy.Engine.dll ^
                      /Fo:%path_build%\obj\ItFliesBy.Engine.obj ^
                      /Fd:%path_build%\bin\ItFliesBy.Engine.pdb

@set cl_includes=     /I engine\include       ^
                      /I engine\internal      ^
                      /I engine\src           ^
                      /I engine\src\assets    ^
                      /I engine\src\core      ^
                      /I engine\src\tools     ^
                      /I %path_rlibs_include% ^
                      /I %path_vcpkg_include%

@set cl_source=       engine\src\ifb-engine.cpp

@set cl_link=         /link                                    ^
                      /LIBPATH:modules\r-libs\build\debug\lib  ^
                      /LIBPATH:modules\r-libs\vcpkg_installed\x64-windows\lib ^
                      /IMPLIB:build\debug\lib\ItFliesBy.Engine.lib

@set cl_libs=         RLibs.lib ^
                      imgui.lib

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