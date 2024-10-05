::----------------------------------------------------------------
:: START
::----------------------------------------------------------------

@echo off

pushd ..

::----------------------------------------------------------------
:: VARIABLES
::----------------------------------------------------------------

@set path_build=              win32\build\debug

@set path_rlibs_lib=          modules\r-libs\build\debug\lib
@set path_rlibs_bin=          modules\r-libs\build\debug\bin
@set path_rlibs_include=      modules\r-libs\build\debug\include

@set path_script_build_rlibs= modules\r-libs\scripts\build-r-libs-debug.bat

::----------------------------------------------------------------
:: DEPENDENCIES
::----------------------------------------------------------------

if exist %path_build% rmdir /s /q %path_build%
mkdir %path_build%\bin
mkdir %path_build%\obj

xcopy %path_rlibs_bin%\*.dll %path_build%\bin /E /I /H /Y 
xcopy %path_rlibs_bin%\*.pdb %path_build%\bin /E /I /H /Y 

::----------------------------------------------------------------
:: COMPILER ARGUMENTS
::----------------------------------------------------------------

@set cl_flags=        /Zi ^
                      /MD

@set cl_output=       /Fe:%path_build%\bin\ItFliesBy.exe ^
                      /Fo:%path_build%\obj\ItFliesBy.obj ^
                      /Fd:%path_build%\bin\ItFliesBy.pdb

@set cl_includes=     /I win32\include ^
                      /I %path_rlibs_include%

@set cl_source=       win32\src\ifb-win32.cpp

@set cl_link=         /link ^
                      /LIBPATH:modules\r-libs\build\debug\lib

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