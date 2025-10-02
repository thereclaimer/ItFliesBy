############################
# INCLUDE
############################

. $PSScriptRoot\IFB.Common.ps1

############################
# FUNCTIONS
############################

function ConvertTo-Base85Header {
    param(
        [string] $Source,
        [string] $Destination,
        [string] $DefineMacro,
        [string] $BufferName
    )

    #remove the destination file if it already exists
    if (Test-Path $Destination) {
        Remove-Item $Destination -Force
    }

    #create the file
    New-Item $Destination

    $file_info = Get-Item $Source

    $converter_args = @(
        ($PSScriptRoot + "\..\build\debug\bin\binary-to-compressed-c.exe"),
        "-base85",
        $Source,
        $BufferName
    )

    $converter_command = $converter_args -join " "

    ("#ifndef " + $DefineMacro)                              | Out-File -FilePath $Destination -Encoding UTF8 -Append
    ("#define " + $DefineMacro)                              | Out-File -FilePath $Destination -Encoding UTF8 -Append
    ("")                                                     | Out-File -FilePath $Destination -Encoding UTF8 -Append
    ("//--------------------------------------------------") | Out-File -FilePath $Destination -Encoding UTF8 -Append
    ("// Source: " + $file_info.Name)                        | Out-File -FilePath $Destination -Encoding UTF8 -Append
    ("// Created using binary-to-compressed-c.exe")          | Out-File -FilePath $Destination -Encoding UTF8 -Append
    ("// do not directly edit this file")                    | Out-File -FilePath $Destination -Encoding UTF8 -Append
    ("//--------------------------------------------------") | Out-File -FilePath $Destination -Encoding UTF8 -Append
    ("")                                                     | Out-File -FilePath $Destination -Encoding UTF8 -Append
    (Invoke-Expression $converter_command)                   | Out-File -FilePath $Destination -Encoding UTF8 -Append
    ("")                                                     | Out-File -FilePath $Destination -Encoding UTF8 -Append
    ("#endif //" + $DefineMacro)                             | Out-File -FilePath $Destination -Encoding UTF8 -Append
}