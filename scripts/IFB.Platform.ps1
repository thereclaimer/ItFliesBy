. $PSScriptRoot\IFB.Common.ps1

$Script:PlatformObj            = 'ItFliesBy.obj'
$Script:PlatformPdb            = 'ItFliesBy.pdb'
$Script:PlatformExe            = 'ItFliesBy.exe'
$Script:PlatformCompileIn      = 'platform\src\ifb-win32-main.cpp' 
$Script:PlatformCompileOut     = @(
    '/Fo:' + $Script:DebugOutDirs.Obj + '\' + $Script:PlatformObj,
    '/Fe:' + $Script:DebugOutDirs.Bin + '\' + $Script:PlatformExe
) -join ' '
$Script:PlatformCompileInclude = @(
    ('/I' + 'platform\include'),
    ('/I' + 'platform\src')
) -join ' '
$Script:PlatformCompileCommandDebug = @(
    $Script:BuildTools.Compiler,
    $Script:PlatformCompileIn,
    $Script:PlatformCompileOut,
    $Script:PlatformCompileInclude,
    $Script:CompilerDebugFlags
) -join ' '
$Script:PlatformLinkFlags = @(
    "/nologo",
    "/SUBSYSTEM:WINDOWS",
    "/DEBUG"
) -join ' '
$Script:PlatformLinkLibPath = @(
    "/LIBPATH:" + $Script:DebugOutDirs.Obj,
    "/LIBPATH:" + $Script:DebugOutDirs.Lib
) -join ' '
$Script:PlatformLinkIn = @(
    $Script:PlatformObj,
    "user32.lib",
    "kernel32.lib"
) -join ' '
$Script:PlatformLinkOut     = '/OUT:' + $Script:DebugOutDirs.Bin + '\' + $Script:PlatformExe
$Script:PlatformLinkCommandDebug = @(
    $Script:BuildTools.Linker,
    $Script:PlatformLinkFlags,
    $Script:PlatformLinkLibPath,
    $Script:PlatformLinkIn,
    $Script:PlatformLinkOut
) -join ' '

function Invoke-IFBBuildDebugPlatform {

    Push-Location (Join-Path $PSScriptRoot '..')

    Export-IFBDebugOutDirs

    Invoke-Expression $Script:PlatformCompileCommandDebug
    Invoke-Expression $Script:PlatformLinkCommandDebug

    Pop-Location
}

function Export-IFBBuildDebugPlatform {

    $BuildScript = @(
        "@echo off"                                      
        ""                                      
        "pushd .."                                      
        ""                                      
        "@set dir_bin=    " + $Script:DebugOutDirs.Bin                                      
        "@set dir_lib=    " + $Script:DebugOutDirs.Lib                                      
        "@set dir_obj=    " + $Script:DebugOutDirs.Obj                                      
        ""                                      
        "@set cl_in=      " + $Script:PlatformCompileIn
        "@set cl_out=     " + $Script:PlatformCompileOut
        "@set cl_include= " + $Script:PlatformCompileInclude
        "@set cl_flags=   " + $Script:CompilerDebugFlags
        ""
        "@set link_in=    " + $Script:PlatformLinkIn
        "@set link_out=   " + $Script:PlatformLinkOut
        "@set link_path=  " + $Script:PlatformLinkLibPath
        "@set link_flags= " + $Script:PlatformLinkFlags
        ""
        "@set cmd_cl=     " + $Script:BuildTools.Compiler + " %cl_in% %cl_out% %cl_include% %cl_flags%"
        "@set cmd_link=   " + $Script:BuildTools.Linker + " %link_flags% %link_path% %link_in% %link_out%"
        ""
        "IF NOT EXIST %dir_bin% mkdir %dir_bin%"
        "IF NOT EXIST %dir_lib% mkdir %dir_lib%"
        "IF NOT EXIST %dir_obj% mkdir %dir_obj%"
        ""
        "call %cmd_cl%"
        "call %cmd_link%"
        ""
        "popd"
    ) -join "`n"


    Push-Location (Join-Path $PSScriptRoot '..')

    New-Item -Path $Script:DebugBuildScripts.Platform -ItemType File -Force
    $BuildScript | Out-File -Encoding ASCII -Append -FilePath $Script:DebugBuildScripts.Platform

    Pop-Location
}