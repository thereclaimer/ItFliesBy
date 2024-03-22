::tools
cl.exe /I dependencies /I src\\ /Zi /Fe: bin\\ItFliesBy.AssetFileBuilder.exe src\\tools\\asset-file-builder\\itfliesby-asset-file-builder.cpp /Fd: bin\\ItFliesBy.AssetFileBuilder.pdb /Fo: bin\\ItFliesBy.AssetFileBuilder.obj /link user32.lib Shell32.lib
