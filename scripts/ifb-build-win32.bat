::platform
cl.exe /I dependencies /I src\\ /Zi /Fe: bin\\ItFliesBy.exe src\\platform\\win32\\itfliesby-platform-win32.cpp /Fd: bin\\ItFliesBy.pdb /Fo: bin\\ItFliesBy.obj /link user32.lib gdi32.lib opengl32.lib glu32.lib Xinput.lib bin\\ItFliesBy.Game.lib
