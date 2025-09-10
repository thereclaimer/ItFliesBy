############################
# INCLUDE
############################

. $PSScriptRoot\IFB.Common.ps1

############################
# SLDLib
############################

$Script:SLDLib = [PSCustomObject]@{
    Include      = 'sld\include'
    Lib          = 'sld\build\debug\lib'
    VcpkgBin     = 'sld\vcpkg_installed\x64-windows\bin'  
    VcpkgInclude = 'sld\vcpkg_installed\x64-windows\include'  
    VcpkgLib     = 'sld\vcpkg_installed\x64-windows\lib'  
} 

############################
# OUTPUT
############################

$Script:EngineOut = [PSCustomObject]@{
    Obj = 'ItFliesBy.Engine.obj'
    Pdb = 'ItFliesBy.Engine.pdb'
    Dll = 'ItFliesBy.Engine.dll'
    Lib = 'ItFliesBy.Engine.lib'
}

############################
# COMPILE
############################

$Script:EngineDebugCompileArgs = [PSCustomObject]@{
    In      = 'engine\src\ifb-engine.cpp'
    Out     = '/Fo:' + $Script:OutDirsDebug.Obj + '\' + $Script:EngineOut.Obj
    Include = @(
    '/I' + 'engine\include'
    '/I' + 'engine\internal'
    '/I' + 'engine\src'
    '/I' + 'engine\src\file'
    '/I' + 'engine\src\memory'
    '/I' + 'engine\src\asset'
    '/I' + 'sld\include'
    '/I' + 'sld\vcpkg_installed\x64-windows\include'
    ) -join ' '
    Flags = $Script:CompilerFlagsDebugDLL    
}

$Script:EngineDebugCompileExpression = @(
    $Script:BuildTools.Compiler
    $Script:EngineDebugCompileArgs.In
    $Script:EngineDebugCompileArgs.Out
    $Script:EngineDebugCompileArgs.Include
    $Script:EngineDebugCompileArgs.Flags
) -join ' '

############################
# LINK
############################

$Script:EngineDebugLinkArgs = [PSCustomObject]@{
    Flags = @(
        "/nologo"
        "/SUBSYSTEM:WINDOWS"
        "/DEBUG"
        "/DLL"
    ) -join ' '
    LibPath = @(
        "/LIBPATH:" + $Script:OutDirsDebug.Obj
        "/LIBPATH:" + $Script:OutDirsDebug.Lib
        "/LIBPATH:" + $Script:SLDLib.Lib
        "/LIBPATH:" + $Script:SLDLib.VcpkgLib
    ) -join ' '
    LinkIn = @(
        "ItFliesBy.Engine.obj"
        "user32.lib",
        "kernel32.lib",
        "SLD.Win32.lib"
    ) -join ' '
    LinkOut = @(
        '/OUT:'    + $Script:OutDirsDebug.Bin + '\' + $Script:EngineOut.Dll
        '/IMPLIB:' + $Script:OutDirsDebug.Lib + '\' + $Script:EngineOut.Lib
    )
}

$Script:EngineDebugLinkExpression = @(
    $Script:BuildTools.Linker
    $Script:EngineDebugLinkArgs.Flags
    $Script:EngineDebugLinkArgs.LibPath
    $Script:EngineDebugLinkArgs.LinkIn
    $Script:EngineDebugLinkArgs.LinkOut
) -join ' '

############################
# BUILD SCRIPT
############################

$Script:EngineDebugBuildScript = @"
@echo off

pushd ..

@set dir_bin=    $($Script:OutDirsDebug.Bin)
@set dir_lib=    $($Script:OutDirsDebug.Lib)
@set dir_obj=    $($Script:OutDirsDebug.Obj)

@set cl_in=      $($Script:EngineDebugCompileArgs.In)
@set cl_out=     $($Script:EngineDebugCompileArgs.Out)
@set cl_include= $($Script:EngineDebugCompileArgs.Include)
@set cl_flags=   $($Script:EngineDebugCompileArgs.Flags)

@set link_in=    $($Script:EngineDebugLinkArgs.LinkIn)
@set link_out=   $($Script:EngineDebugLinkArgs.LinkOut)
@set link_path=  $($Script:EngineDebugLinkArgs.LibPath)
@set link_flags= $($Script:EngineDebugLinkArgs.Flags)

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

function Invoke-IFBEngineBuildDebug {

    Push-Location (Join-Path $PSScriptRoot '..')

    Export-IFBOutDirsDebug

    Invoke-Expression $Script:EngineDebugCompileExpression
    Invoke-Expression $Script:EngineDebugLinkExpression

    Pop-Location
}

function Export-IFBEngineBuildDebug {

    Push-Location (Join-Path $PSScriptRoot '..')

    New-Item    -Path $Script:DebugBuildScripts.Engine -ItemType File -Force
    Set-Content -Path $Script:DebugBuildScripts.Engine -Value    $Script:EngineDebugBuildScript

    Pop-Location
}