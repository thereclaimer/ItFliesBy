$commonLibFlags =
	"/c "    +
        "/MD "   +
        "/Z7 "   +
	"/EHsc " +
	"/std:c++17 "

$libraryIncludes = 
	"/Imemory\include "          +
	"/Iplatform\include "        +
	"/Idata-structures\include " +
	"/Igraphics\include "        +
	"/Irendering\include "       +
	"/Irendering\src\gl "        +
	"/Iio\include "              +
	"/Ithreads\include "         +
	"/Iengine\include "         +
	"/Iwin32\include "         +
	"/Icommon "                  +
	"/Iexternal "                +
	"/Ivcpkg_installed\x64-windows\include "

$librarySources = 
	"memory\src\ifb-memory.cpp "                   +
	"data-structures\src\ifb-data-structures.cpp " +
	"platform\src\ifb-platform.cpp "               +
	"graphics\src\ifb-graphics.cpp "               +
	"rendering\src\ifb-rendering.cpp "             +
	"io\src\ifb-io.cpp "                           +
	"threads\src\ifb-threads.cpp "

$libraryObjs = 
	"build\debug\obj\ifb-memory.obj "          +
	"build\debug\obj\ifb-data-structures.obj " +
	"build\debug\obj\ifb-platform.obj "        +
	"build\debug\obj\ifb-graphics.obj "        +
	"build\debug\obj\ifb-rendering.obj "       +
	"build\debug\obj\ifb-io.obj "              +
	"build\debug\obj\ifb-threads.obj "

function Create-Directories { 
	
	if (!(Test-Path -Path "build\debug\bin")) { New-Item -ItemType Directory -Path "build\debug\bin" }
	if (!(Test-Path -Path "build\debug\obj")) { New-Item -ItemType Directory -Path "build\debug\obj" }
	if (!(Test-Path -Path "build\debug\lib")) { New-Item -ItemType Directory -Path "build\debug\lib" }
}

function Build-LibraryString {
	param (
		[string]$Name,
		[string]$Objs
	)

	$outString = "/OUT:build\debug\lib\ItFliesBy." + $Name + ".lib "

	$libraryString = 
		"lib.exe " +
		$outString +
		$Objs

	return $libraryString
}

function Build-Library {
	param (
		[string]$Source,
		[string]$Objs,
		[string]$Name
	)

	# create the directories
	Create-Directories

	# compile command 
	$compileString  = 
		"cl.exe "               +
		"/Fo:build\debug\obj\ " +
		$Source + " "           +
		$commonLibFlags         +
		$libraryIncludes

	# library command 
	$libraryString = Build-LibraryString -Name $Name -Objs $Objs

	# build library
	Invoke-Expression $compileString
	Invoke-Expression $libraryString
}

function Invoke-BuildMemory {

	Build-Library -Source "memory\src\ifb-memory.cpp" -Objs "build\debug\obj\ifb-memory.obj" -Name "Memory"
}

function Invoke-BuildDataStructures {

	Build-Library -Source "data-structures\src\ifb-data-structures.cpp" -Objs "build\debug\obj\ifb-data-structures.obj" -Name "DataStructures"
}

function Invoke-BuildPlatform {

	Build-Library -Source "platform\src\ifb-platform.cpp" -Objs "build\debug\obj\ifb-platform.obj" -Name "Platform"
}

function Invoke-BuildGraphics{

	Build-Library -Source "graphics\src\ifb-graphics.cpp"  -Objs "build\debug\obj\ifb-graphics.obj" -Name "Graphics"
}

function Invoke-BuildRendering {

	Build-Library -Source "rendering\src\ifb-rendering.cpp"  -Objs "build\debug\obj\ifb-rendering.obj" -Name "Rendering"
}

function Invoke-BuildIO{

	Build-Library -Source "io\src\ifb-io.cpp" -Objs "build\debug\obj\ifb-io.obj"  -Name "IO"
}

function Invoke-BuildThreads {

	Build-Library -Source "threads\src\ifb-threads.cpp" -Objs "build\debug\obj\ifb-threads.obj"  -Name "Threads"
}

function Invoke-BuildLibraries {

	Build-Library -Source $librarySources -Objs $libraryObjs -Name "Libraries"
}

function Invoke-BuildEngine {

	#---------------------------------
	# COMPILER ARGUMENTS
	#---------------------------------

	$compileIncludes =
		$libraryIncludes         +
		"/Iengine\src "          +
		"/Iengine\src\api "      +
		"/Iengine\src\context "  +
		"/Iengine\src\core "     +
		"/Iengine\src\graphics " +
		"/Iengine\src\renderer "

	$compileFlags = 
		"/c "         +
		"/Zi "        +
		"/LD "        +
		"/MD "        +
		"/std:c++17 " +
		"/EHsc "
	
	$compileOut = 
		"/Fd:build\debug\bin\ItFliesBy.Engine.pdb " +
		"/Fo:build\debug\obj\ "

	$compileSource = "engine\src\ifb-engine.cpp "

	$compileCommand = 
		"cl.exe "        +
		$compileSource   +
		$compileFlags    +
		$compileIncludes +
		$compileOut

	#---------------------------------
	# LINKER ARGUMENTS
	#---------------------------------

	$linkFlags = 
		"/DLL " +
		"/DEBUG "

	$linkPaths = 
		"/LIBPATH:vcpkg_installed\x64-windows\lib " +
                "/LIBPATH:build\debug\lib "                 +
                "/LIBPATH:build\debug\obj "

	$linkLibs = 
		"ItFliesBy.Libraries.lib " +
                "glew32.lib "              +
                "opengl32.lib "

	$linkObj = "build\debug\obj\ifb-engine.obj "

	$linkOutput = 
		"/IMPLIB:build\debug\lib\ItFliesBy.Engine.lib " +
		"/OUT:build\debug\bin\ItFliesBy.Engine.dll"

	$linkCommand = 
		"link.exe " +
		$linkFlags  +
		$linkPaths  +
		$linkLibs   +
		$linkObj    +
		$linkOutput

	#---------------------------------
	# BUILD
	#---------------------------------

	#build libraries
	Build-Library -Source $librarySources -Objs $libraryObjs -Name "Libraries"

	#compile and link engine
	Invoke-Expression $compileCommand
	Invoke-Expression $linkCommand
}

function Invoke-BuildAll {

	#---------------------------------
	# COMPILER ARGUMENTS
	#---------------------------------
	
	$compileIncludes = $libraryIncludes
	
	$compileFlags = 
		"/c "         +
		"/Zi "        +
		"/MD "        +
		"/std:c++17 " +
		"/EHsc "
	
	$compileOut = 
		"/Fd:build\debug\bin\ItFliesBy.pdb " +
		"/Fo:build\debug\obj\ "

	$compileSource = "win32\src\ifb-win32-itfliesby.cpp "

	$compileCommand = 
		"cl.exe "        +
		$compileSource   +
		$compileFlags    +
		$compileIncludes +
		$compileOut

	#---------------------------------
	# LINKER ARGUMENTS
	#---------------------------------
	
	$linkFlags = 
		"/DEBUG " +
		"/SUBSYSTEM:WINDOWS "

	$linkPaths = 
		"/LIBPATH:vcpkg_installed\x64-windows\lib " +
                "/LIBPATH:build\debug\lib "                 +
                "/LIBPATH:build\debug\obj "

	$linkLibs = 
		"ItFliesBy.Engine.lib " +
		"user32.lib "           +
		"imgui.lib "            +
		"glew32.lib "           +
                "opengl32.lib "         +
		"Advapi32.lib "

	$linkObj = "build\debug\obj\ifb-win32-itfliesby.obj "

	$linkOutput = "/OUT:build\debug\bin\ItFliesBy.exe"

	$linkCommand = 
		"link.exe " +
		$linkFlags  +
		$linkPaths  +
		$linkLibs   +
		$linkObj    +
		$linkOutput

	#---------------------------------
	# BUILD
	#---------------------------------

	#build the engine
	Invoke-BuildEngine

	#compile and link the exe
	Invoke-Expression $compileCommand
	Invoke-Expression $linkCommand
}

Export-ModuleMember -Function Invoke-BuildMemory 
Export-ModuleMember -Function Invoke-BuildDataStructures 
Export-ModuleMember -Function Invoke-BuildPlatform
Export-ModuleMember -Function Invoke-BuildGraphics
Export-ModuleMember -Function Invoke-BuildRendering
Export-ModuleMember -Function Invoke-BuildIO
Export-ModuleMember -Function Invoke-BuildThreads
Export-ModuleMember -Function Invoke-BuildLibraries
Export-ModuleMember -Function Invoke-BuildEngine
Export-ModuleMember -Function Invoke-BuildAll
