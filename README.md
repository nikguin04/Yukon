# Yukon


## VSCODE 
### Compile with cmake:
#### Settings: (CMake: Environment)
|item|value|
|---|---|
|CC|C:\ProgramData\mingw64\bin\gcc.exe|
|CXX|C:\ProgramData\mingw64\bin\g++.exe|

### Language server
Install "clangd" from extensions to get proper language server and syntax correction for C23<br>

## SDL2 WINDOWS
### Download and extract
Download "SDL2-devel-2.30.2-mingw.zip" from https://github.com/libsdl-org/SDL/releases/tag/release-2.30.2<br>
Extract the "x86_64-w64-mingw32" folder inside the zip file to any path on computer, and rename it to something like "SDL2_x86"<br>

Download "SDL2_image-devel-2.8.2-mingw.zip" from https://github.com/libsdl-org/SDL_image/releases/tag/release-2.8.2<br>
Extract the "x86_64-w64-mingw32" folder inside the zip file to same folder as in previous step (ex: "SDL2_x86)<br>

Download "SDL2_ttf-devel-2.22.0-mingw.zip" from https://github.com/libsdl-org/SDL_ttf/releases/tag/release-2.22.0<br>
Extract the "x86_64-w64-mingw32" folder inside the zip file to same folder as in previous step (ex: "SDL2_x86)<br>

### Configure CMake

Open CMake GUI to the path of this project and press "Configure"<br>
Set "SDL2_DIR" to the absolute path of a subfolder from the folder you created previously located at "\lib\cmake\SDL2"<br>
Set "SDL2_image_DIR" to the absolute path of a subfolder from the folder you created previously located at "\lib\cmake\SDL2_image"<br>
Set "SDL2_ttf_DIR" to the absolute path of a subfolder from the folder you created previously located at "\lib\cmake\SDL2_ttf"<br>
Then press "Configure" and "Generate"<br>

### Add DLL to path

From windows search, open "View advanced system settings"<br>
Click "Environment variables"<br>
Under "System variables" or "User variables" (not recommended), double click the "Path" variable.<br>
Press "New" and enter the name of the folder you created earlier plus the subfolder "\bin"<br>
