::----------------------------------------------------------------
:: START
::----------------------------------------------------------------

@echo off

pushd ..

::----------------------------------------------------------------
:: VARIABLES
::----------------------------------------------------------------

@set path_build=              build\debug

@set path_rlibs_lib=          modules\r-libs\build\debug\lib
@set path_rlibs_bin=          modules\r-libs\build\debug\bin
@set path_rlibs_include=      modules\r-libs\build\debug\include


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

@set cl_includes=     /I engine\include  ^
                      /I engine\internal ^
                      /I engine\src      ^
                      /I %path_rlibs_include%

@set cl_source=       engine\src\ifb-engine.cpp

@set cl_link=         /link                                   ^
                      /LIBPATH:modules\r-libs\build\debug\lib ^
                      /IMPLIB:build\debug\lib\ItFliesBy.Engine.lib

@set cl_libs=         RLibs.lib

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