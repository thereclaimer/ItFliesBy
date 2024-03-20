del /q bin\\*.*


::memory
cl.exe /DLL /w /I dependencies /I src\\ /LD /Zi src\\memory\\itfliesby-memory.cpp /Fd: bin\\ItFliesBy.Memory.pdb /Fo: bin\\ItFliesBy.Memory.obj /Fe: bin\\ItFliesBy.Memory.dll 

::renderer
cl.exe /DLL /w /I dependencies /I src\\ /LD /Zi src\\renderer\\itfliesby-renderer.cpp /Fd: bin\\ItFliesBy.Renderer.pdb /Fo: bin\\ItFliesBy.Renderer.obj /Fe: bin\\ItFliesBy.Renderer.dll 

::engine
cl.exe /DLL /w /I dependencies /I src\\ /LD /Zi src\\engine\\itfliesby-engine.cpp /Fd: bin\\ItFliesBy.Engine.pdb /Fo: bin\\ItFliesBy.Engine.obj /Fe: bin\\ItFliesBy.Engine.dll /link bin\\ItFliesBy.Renderer.lib bin\\ItFliesBy.Memory.lib

::game
cl.exe /DLL /w /I dependencies /I src\\ /LD /Zi src\\game\\itfliesby-game.cpp /Fd: bin\\ItFliesBy.Game.pdb /Fo: bin\\ItFliesBy.Game.obj /Fe: bin\\ItFliesBy.Game.dll /link bin\\ItFliesBy.Engine.lib bin\\ItFliesBy.Memory.lib

::platform
cl.exe /I dependencies /I src\\ /Zi /Fe: bin\\ItFliesBy.exe src\\platform\\win32\\itfliesby-platform-win32.cpp /Fd: bin\\ItFliesBy.pdb /Fo: bin\\ItFliesBy.obj /link user32.lib gdi32.lib opengl32.lib glu32.lib Xinput.lib bin\\ItFliesBy.Game.lib
