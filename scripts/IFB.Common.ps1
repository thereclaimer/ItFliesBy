

$Script:DebugBuildScripts = [PSCustomObject]@{
    Platform = 'scripts\build-debug-platform.bat'
    Engine   = 'scripts\build-debug-engine.bat'
    Game     = 'scripts\build-debug-game.bat'
}

$Script:ReleaseBuildScripts = [PSCustomObject]@{
    Platform = 'scripts\build-release-platform.bat'
    Engine   = 'scripts\build-release-engine.bat'
    Game     = 'scripts\build-release-game.bat'
}

$Script:BuildTools = [PSCustomObject]@{
    Compiler  = 'cl.exe'
    Libray    = 'lib.exe'
    Linker    = 'link.exe'  
}

$Script:OutDirsDebug = [PSCustomObject]@{
    Bin = 'build\debug\bin'
    Obj = 'build\debug\obj'
    Lib = 'build\debug\lib'
}

$Script:OutDirsRelease = [PSCustomObject]@{
    Bin = 'build\release\bin'
    Obj = 'build\release\obj'
    Lib = 'build\release\lib'
}

$Script:CompilerFlagsDebug = @(
    '/nologo',            # startup banner disabled
    '/c',                 # compile without linking
    '/MD',                # link against multithreaded runtime library (MSVCRT.dll)
    '/Z7',                # generate debug info
    '/EHs-',              # disable exception handling
    '/std:c++17',         # c++17 standard mode
    '/Od',                # disable optimizations
    '/D_HAS_EXCEPTIONS=0' # disable exceptions for STL and CRT
) -join ' '

$Script:CompilerFlagsDebugDLL = @(
    '/nologo',            # startup banner disabled
    '/c',                 # compile without linking
    '/MD',                # link against multithreaded runtime library (MSVCRT.dll)
    '/LD',                # build .dll 
    '/Z7',                # generate debug info
    '/EHs-',              # disable exception handling
    '/std:c++17',         # c++17 standard mode
    '/Od',                # disable optimizations
    '/D_HAS_EXCEPTIONS=0' # disable exceptions for STL and CRT
) -join ' '

$Script:SLDLib = [PSCustomObject]@{
    Include      = 'sld\include'
    Lib          = 'sld\build\debug\lib'
    VcpkgBin     = 'sld\vcpkg_installed\x64-windows\bin'  
    VcpkgInclude = 'sld\vcpkg_installed\x64-windows\include'  
    VcpkgLib     = 'sld\vcpkg_installed\x64-windows\lib'  
} 

function Export-IFBOutDirsDebug {

	if (!(Test-Path -Path $Script:OutDirsDebug.Bin)) { New-Item -ItemType Directory -Path $Script:OutDirsDebug.Bin }
	if (!(Test-Path -Path $Script:OutDirsDebug.Obj)) { New-Item -ItemType Directory -Path $Script:OutDirsDebug.Obj }
	if (!(Test-Path -Path $Script:OutDirsDebug.Lib)) { New-Item -ItemType Directory -Path $Script:OutDirsDebug.Lib }
}

function Export-IFBOutDirsRelease {

	if (!(Test-Path -Path $Script:OutDirsRelease.Bin)) { New-Item -ItemType Directory -Path $Script:OutDirsRelease.Bin }
	if (!(Test-Path -Path $Script:OutDirsRelease.Obj)) { New-Item -ItemType Directory -Path $Script:OutDirsRelease.Obj }
	if (!(Test-Path -Path $Script:OutDirsRelease.Lib)) { New-Item -ItemType Directory -Path $Script:OutDirsRelease.Lib }
}

function Invoke-IFBCleanBuild {

    Export-IFBOutDirsDebug
    Export-IFBOutDirsRelease

    Remove-Item ($Script:OutDirsDebug.Bin   + "\*") -Recurse -Force
    Remove-Item ($Script:OutDirsDebug.Obj   + "\*") -Recurse -Force
    Remove-Item ($Script:OutDirsDebug.Lib   + "\*") -Recurse -Force
    Remove-Item ($Script:OutDirsRelease.Bin + "\*") -Recurse -Force
    Remove-Item ($Script:OutDirsRelease.Obj + "\*") -Recurse -Force
    Remove-Item ($Script:OutDirsRelease.Lib + "\*") -Recurse -Force
}