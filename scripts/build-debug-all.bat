@echo off

pushd ..

@set dir_bin=    build\debug\bin
@set dir_lib=    build\debug\lib
@set dir_obj=    build\debug\obj

@set cl_sld_in=      sld\src\sld.cpp
@set cl_sld_out=     /Fo:build\debug\obj\SLD.Win32.obj
@set cl_sld_include= /Isld\external /Isld\include /Isld\src /Isld\src\allocators /Isld\src\core /Isld\src\math /Isld\src\memory /Isld\src\os /Isld\src\string /Isld\src\win32 /Isld\vcpkg_installed\x64-windows\include
@set cl_sld_flags=   /nologo /c /MD /Z7 /EHs- /std:c++17 /Od /D_HAS_EXCEPTIONS=0

@set lib_sld_in=     build\debug\obj\SLD.Win32.obj
@set lib_sld_out=    /OUT:build\debug\lib\SLD.Win32.lib
@set lib_sld_flags=  /nologo

@set cl_eng_in=      engine\src\ifb-engine.cpp
@set cl_eng_out=     /Fo:build\debug\obj\ItFliesBy.Engine.obj
@set cl_eng_include= /Iengine\include /Iengine\internal /Iengine\src /Iengine\src\core /Iengine\src\file /Iengine\src\memory /Iengine\src\asset /Isld\include /Isld\external /Isld\vcpkg_installed\x64-windows\include
@set cl_eng_flags=   /nologo /c /MD /LD /Z7 /EHs- /std:c++17 /Od /D_HAS_EXCEPTIONS=0

@set link_eng_in=    ItFliesBy.Engine.obj user32.lib kernel32.lib SLD.Win32.lib Gdi32.lib imgui.lib opengl32.lib pugixml.lib
@set link_eng_out=   /OUT:build\debug\bin\ItFliesBy.Engine.dll /IMPLIB:build\debug\lib\ItFliesBy.Engine.lib
@set link_eng_path=  /LIBPATH:build\debug\obj /LIBPATH:build\debug\lib /LIBPATH:sld\build\debug\lib /LIBPATH:sld\vcpkg_installed\x64-windows\lib
@set link_eng_flags= /nologo /SUBSYSTEM:WINDOWS /DEBUG /DLL

@set cl_pfm_in=      platform\src\ifb-win32-main.cpp
@set cl_pfm_out=     /Fo:build\debug\obj\ItFliesBy.obj
@set cl_pfm_include= /Iplatform\include /Iplatform\src /Iengine\include /Isld\include /Isld\external /Isld\vcpkg_installed\x64-windows\include
@set cl_pfm_flags=   /nologo /c /MD /Z7 /EHs- /std:c++17 /Od /D_HAS_EXCEPTIONS=0

@set link_pfm_in=    ItFliesBy.obj ItFliesBy.Engine.lib user32.lib kernel32.lib
@set link_pfm_out=   /OUT:build\debug\bin\ItFliesBy.exe
@set link_pfm_path=  /LIBPATH:build\debug\obj /LIBPATH:build\debug\lib
@set link_pfm_flags= /nologo /SUBSYSTEM:WINDOWS /DEBUG

@set cmd_sld_cl=     cl.exe %cl_sld_in% %cl_sld_out% %cl_sld_include% %cl_sld_flags%
@set cmd_eng_cl=     cl.exe %cl_eng_in% %cl_eng_out% %cl_eng_include% %cl_eng_flags%
@set cmd_pfm_cl=     cl.exe %cl_pfm_in% %cl_pfm_out% %cl_pfm_include% %cl_pfm_flags%

@set cmd_sld_lib=    lib.exe %lib_sld_flags% %lib_sld_in% %lib_sld_out%

@set cmd_pfm_link=   link.exe %link_pfm_in% %link_pfm_out% %link_pfm_path% %link_pfm_flags%
@set cmd_eng_link=   link.exe %link_eng_in% %link_eng_out% %link_eng_path% %link_eng_flags%     

IF NOT EXIST %dir_bin% mkdir %dir_bin%
IF NOT EXIST %dir_lib% mkdir %dir_lib%
IF NOT EXIST %dir_obj% mkdir %dir_obj%

call %cmd_sld_cl%
call %cmd_eng_cl%
call %cmd_pfm_cl%
call %cmd_sld_lib%
call %cmd_eng_link%
call %cmd_pfm_link%

popd