
::renderer
cl.exe /DLL /w /I dependencies /I src\\ /LD /Zi src\\renderer\\itfliesby-renderer.cpp /Fd: bin\\ItFliesBy.Renderer.pdb /Fo: bin\\ItFliesBy.Renderer.obj /Fe: bin\\ItFliesBy.Renderer.dll /link opengl32.lib glu32.lib bin\\ItFliesBy.Memory.lib
