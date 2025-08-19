

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

$Script:DebugOutDirs = [PSCustomObject]@{
    Bin = 'build\debug\bin'
    Obj = 'build\debug\obj'
    Lib = 'build\debug\lib'
}

$Script:ReleaseOutDirs = [PSCustomObject]@{
    Bin = 'build\release\bin'
    Obj = 'build\release\obj'
    Lib = 'build\release\lib'
}

$Script:CompilerDebugFlags = @(
    '/nologo',            # startup banner disabled
    '/c',                 # compile without linking
    '/MD',                # link against multithreaded runtime library (MSVCRT.dll)
    '/Z7',                # generate debug info
    '/EHs-',              # disable exception handling
    '/std:c++17',         # c++17 standard mode
    '/Od',                # disable optimizations
    '/D_HAS_EXCEPTIONS=0' # disable exceptions for STL and CRT
) -join ' '

function Export-IFBDebugOutDirs {

	if (!(Test-Path -Path $Script:DebugOutDirs.Bin)) { New-Item -ItemType Directory -Path $Script:DebugOutDirs.Bin }
	if (!(Test-Path -Path $Script:DebugOutDirs.Obj)) { New-Item -ItemType Directory -Path $Script:DebugOutDirs.Obj }
	if (!(Test-Path -Path $Script:DebugOutDirs.Lib)) { New-Item -ItemType Directory -Path $Script:DebugOutDirs.Lib }
}

function Export-IFBReleaseOutDirs {

	if (!(Test-Path -Path $Script:ReleaseOutDirs.Bin)) { New-Item -ItemType Directory -Path $Script:ReleaseOutDirs.Bin }
	if (!(Test-Path -Path $Script:ReleaseOutDirs.Obj)) { New-Item -ItemType Directory -Path $Script:ReleaseOutDirs.Obj }
	if (!(Test-Path -Path $Script:ReleaseOutDirs.Lib)) { New-Item -ItemType Directory -Path $Script:ReleaseOutDirs.Lib }
}