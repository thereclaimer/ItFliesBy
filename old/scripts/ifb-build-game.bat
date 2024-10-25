::game
cl.exe /DLL /w /I dependencies /I src\\ /LD /Zi src\\game\\itfliesby-game.cpp /Fd: bin\\ItFliesBy.Game.pdb /Fo: bin\\ItFliesBy.Game.obj /Fe: bin\\ItFliesBy.Game.dll /link bin\\ItFliesBy.Engine.lib bin\\ItFliesBy.Memory.lib
