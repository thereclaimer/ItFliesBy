::----------------------------------------------------------------
:: START
::----------------------------------------------------------------

@echo off

pushd ..

::----------------------------------------------------------------
:: VARIABLES
::----------------------------------------------------------------

::build files
@set build_file_prefix=ItFliesBy.Engine
@set build_file_dll=%build_file_prefix%.dll
@set build_file_pdb=%build_file_prefix%.pdb
@set build_file_obj=%build_file_prefix%.obj
@set build_file_lib=%build_file_prefix%.lib

::build directories
@set dir_build=build\debug
@set dir_build_bin=%dir_build%\bin
@set dir_build_obj=%dir_build%\obj
@set dir_build_lib=%dir_build%\lib

::build file paths
@set file_path_dll=build\debug\bin\ItFliesBy.Engine.dll
@set file_path_pdb=build\debug\bin\ItFliesBy.Engine.pdb
@set file_path_obj=build\debug\obj\ItFliesBy.Engine.obj
@set file_path_lib=build\debug\lib\ItFliesBy.Engine.lib

::vcpkg install directories
@set dir_vcpkg=vcpkg_installed
@set dir_vcpkg_include=%dir_vcpkg%\x64-windows\include
@set dir_vcpkg_lib=%dir_vcpkg%\x64-windows\lib

::----------------------------------------------------------------
:: DEPENDENCIES
::----------------------------------------------------------------

::build directories
if not exist %dir_build_bin% mkdir %dir_build_bin%
if not exist %dir_build_obj% mkdir %dir_build_obj%
if not exist %dir_build_lib% mkdir %dir_build_lib%
  
::vcpkg
if not exist %dir_vcpkg% call vcpkg install

::----------------------------------------------------------------
:: COMPILER ARGUMENTS
::----------------------------------------------------------------

@set cl_flags=      /c                         ^
                    /Zi                        ^
                    /LD                        ^
                    /MD                        ^
                    /EHsc

@set cl_out=        /Fe:%file_path_dll%        ^
                    /Fd:%file_path_pdb%        ^
                    /Fo:%file_path_obj%

@set cl_includes=   /I engine\include          ^
                    /I engine\src              ^
                    /I engine\src\api          ^
                    /I engine\src\context      ^
                    /I engine\src\core         ^
                    /I engine\src\graphics     ^
                    /I memory\include          ^
                    /I data-structures\include ^
                    /I graphics\include        ^
                    /I rendering\include       ^
                    /I common                  ^
                    /I external                ^
                    /I math                    ^
                    /I %dir_vcpkg_include%

@set cl_source=     engine\src\ifb-engine.cpp

::----------------------------------------------------------------
:: LINKER ARGUMENTS
::----------------------------------------------------------------

@set link_flags=    /DLL   ^
                    /DEBUG

@set link_paths=    /LIBPATH:vcpkg_installed\x64-windows\lib ^
                    /LIBPATH:build\debug\lib                 ^
                    /LIBPATH:build\debug\obj

@set link_libs=     ItFliesBy.Memory.lib         ^
                    ItFliesBy.Graphics.lib       ^
                    ItFliesBy.DataStructures.lib ^
                    ItFliesBy.Rendering.lib

@set link_objs=     %build_file_obj%

@set link_out=      /IMPLIB:build\debug\lib\ItFliesBy.Engine.lib ^
                    /OUT:%file_path_dll%
::----------------------------------------------------------------
:: BUILD
::----------------------------------------------------------------

::compile
call cl.exe       ^
    %cl_flags%    ^
    %cl_out%      ^
    %cl_includes% ^
    %cl_source%

::link
call link.exe    ^
    %link_flags% ^
    %link_paths% ^
    %link_out%   ^
    %link_libs%  ^
    %link_objs%

::----------------------------------------------------------------
:: END
::----------------------------------------------------------------

popd