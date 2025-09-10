############################
# INCLUDE
############################

. $PSScriptRoot\IFB.Common.ps1
. $PSScriptRoot\IFB.Engine.ps1

############################
# OUTPUT
############################

$Script:PlatformOut = [PSCustomObject]@{
    Obj = 'ItFliesBy.obj'
    Pdb = 'ItFliesBy.pdb'
    Exe = 'ItFliesBy.dll'
}

############################
# COMPILE
############################

$Script:PlatformDebugCompileArgs = [PSCustomObject]@{
    In      = 'platform\src\ifb-win32-main.cpp' 
    Out     = '/Fo:' + $Script:OutDirsDebug.Obj + '\' + $Script:PlatformOut.Obj
    Include = @(
        '/I' + 'platform\include'
        '/I' + 'platform\src'
        '/I' + 'engine\include'
        '/I' + 'sld\include'
        '/I' + 'sld\vcpkg_installed\x64-windows\include'
    ) -join ' '
    Flags = $Script:CompilerFlagsDebug    
}

$Script:PlatformDebugCompileExpression = @(
    $Script:BuildTools.Compiler
    $Script:PlatformDebugCompileArgs.In
    $Script:PlatformDebugCompileArgs.Out
    $Script:PlatformDebugCompileArgs.Include
    $Script:PlatformDebugCompileArgs.Flags
) -join ' '

############################
# LINK
############################

$Script:PlatformDebugLinkArgs = [PSCustomObject]@{
    Flags = @(
        "/nologo",
        "/SUBSYSTEM:WINDOWS",
        "/DEBUG"
    ) -join ' '
    Include = @(
        "/LIBPATH:" + $Script:OutDirsDebug.Obj,
        "/LIBPATH:" + $Script:OutDirsDebug.Lib
    ) -join ' '
    In = @(
        $Script:PlatformOut.Obj
        $Script:EngineOut.Lib
        "user32.lib"
        "kernel32.lib"
    ) -join ' '
    Out = '/OUT:' + $Script:OutDirsDebug.Bin + '\' + $Script:PlatformOut.Exe
}

$Script:PlatformDebugLinkExpression = @(
    $Script:BuildTools.Linker
    $Script:EngineDebugLinkArgs.Flags
    $Script:EngineDebugLinkArgs.Include
    $Script:EngineDebugLinkArgs.In
    $Script:EngineDebugLinkArgs.Out
) -join ' '


############################
# BUILD SCRIPT
############################

$Script:PlatformDebugBuildScript = @"
@echo off

pushd ..

@set dir_bin=    $($Script:OutDirsDebug.Bin)
@set dir_lib=    $($Script:OutDirsDebug.Lib)
@set dir_obj=    $($Script:OutDirsDebug.Obj)

@set cl_in=      $($Script:PlatformDebugCompileArgs.In)
@set cl_out=     $($Script:PlatformDebugCompileArgs.Out)
@set cl_include= $($Script:PlatformDebugCompileArgs.Include)
@set cl_flags=   $($Script:PlatformDebugCompileArgs.Flags)

@set link_in=    $($Script:PlatformDebugLinkArgs.In)
@set link_out=   $($Script:PlatformDebugLinkArgs.Out)
@set link_path=  $($Script:PlatformDebugLinkArgs.Include)
@set link_flags= $($Script:PlatformDebugLinkArgs.Flags)

@set cmd_cl=     $($Script:BuildTools.Compiler)   %cl_in%      %cl_out%    %cl_include% %cl_flags%
@set cmd_link=   $($Script:BuildTools.Linker) %link_flags% %link_path% %link_in%    %link_out%

IF NOT EXIST %dir_bin% mkdir %dir_bin%
IF NOT EXIST %dir_lib% mkdir %dir_lib%
IF NOT EXIST %dir_obj% mkdir %dir_obj%

call %cmd_cl%
call %cmd_link%

popd
"@

############################
# FUNCTIONS
############################

function Invoke-IFBPlatformBuildDebug {

    Push-Location (Join-Path $PSScriptRoot '..')

    Export-IFBOutDirsDebug

    Invoke-Expression $Script:PlatformDebugCompileExpression
    Invoke-Expression $Script:PlatformDebugLinkExpression

    Pop-Location
}

function Export-IFBPlatformBuildDebug {

    Push-Location (Join-Path $PSScriptRoot '..')

    New-Item    -Path $Script:DebugBuildScripts.Platform -ItemType File -Force
    Set-Content -Path $Script:DebugBuildScripts.Platform -Value    $Script:PlatformDebugBuildScript

    Pop-Location
}