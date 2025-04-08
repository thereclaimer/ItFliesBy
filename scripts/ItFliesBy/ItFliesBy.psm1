$commonLibFlags =
	"/c "    +
        "/MD "   +
        "/Z7 "   +
	"/EHsc " +
	"/std:c++17 "

$includeString = 
	"/Imemory\include "          +
	"/Iplatform\include "        +
	"/Idata-structures\include " +
	"/Icommon "                  +
	"/Iexternal "                +
	"/Ivcpkg_installed\x64-windows\include "

function Create-Directories { 
	
	if (!(Test-Path -Path "build\debug\bin")) { New-Item -ItemType Directory -Path "build\debug\bin" }
	if (!(Test-Path -Path "build\debug\obj")) { New-Item -ItemType Directory -Path "build\debug\obj" }
	if (!(Test-Path -Path "build\debug\lib")) { New-Item -ItemType Directory -Path "build\debug\lib" }
}

function Build-LibraryString {
	param (
		[string]$Name
	)

	$libraryString = 
		"lib.exe "                        +
		"/OUT:build\debug\lib\ItFliesBy." +
		$Name                             +
		".lib "                           +
		"build\debug\obj\ItFliesBy."      +
		$Name                             +
		".obj"

	return $libraryString
}

function Build-ObjFlag {
	param (
		[string]$Name
	)

	$objFlag = "/Fo:build\debug\obj\ItFliesBy." + $Name + ".obj "
}

function Build-Library {
	param (
		[string]$Source,
		[string]$Name
	)

	# create the directories
	Create-Directories

	# compile command 
	$compileString  = "cl.exe "
	$compileString += $Source + " "
	$compileString += Build-ObjFlag -Name $Name
	$compileString += $commonLibFlags
	$compileString += $includeString 
	
	# library command 
	$libraryString = Build-LibraryString -Name $Name

	# build library
	Invoke-Expression $compileString
	Invoke-Expression $libraryString
}

function Invoke-BuildMemory {

	Build-Library -Source "memory\src\memory.cpp" -Name "Memory"
}

function Invoke-BuildDataStructures {

	Build-Library -Source "data-structures\src\data-structures.cpp" -Name "DataStructures"
}

function Invoke-BuildPlatform {

	Build-Library -Source "platform\src\platform.cpp" -Name "Platform"
}

Export-ModuleMember -Function Invoke-BuildMemory 
Export-ModuleMember -Function Invoke-BuildDataStructures 
Export-ModuleMember -Function Invoke-BuildPlatform
