::engine
cl.exe /DLL /w /I dependencies /I src\\ /LD /Zi src\\engine\\itfliesby-engine.cpp /Fd: bin\\ItFliesBy.Engine.pdb /Fo: bin\\ItFliesBy.Engine.obj /Fe: bin\\ItFliesBy.Engine.dll /link bin\\ItFliesBy.Renderer.lib bin\\ItFliesBy.Memory.lib
