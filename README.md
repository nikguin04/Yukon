# Yukon


## VSCODE 
### Compile with cmake:
#### Settings: (CMake: Environment)
|item|value|
|---|---|
|CC|C:\ProgramData\mingw64\bin\gcc.exe|
|CXX|C:\ProgramData\mingw64\bin\g++.exe|

### Language server
Install "clangd" from extensions to get proper language server and syntax correction for C23

## SDL2 WINDOWS
### Download
Download "SDL2-devel-2.30.2-mingw.zip" from https://github.com/libsdl-org/SDL/releases/tag/release-2.30.2
Extract folder inside zip file to any path on computer
Create new file inside this new folder called "sdl-config.cmake"
Put all of this inside the new file:
```CMAKE
set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include")

# Support both 32 and 64 bit builds
if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
  set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/lib/x64/SDL2.lib;${CMAKE_CURRENT_LIST_DIR}/lib/x64/SDL2main.lib")
else ()
  set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/lib/x86/SDL2.lib;${CMAKE_CURRENT_LIST_DIR}/lib/x86/SDL2main.lib")
endif ()

string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
```

Open CMake GUI to the path of this project and press configure. Then set "SDL2_DIR" to the path of the folder you extracted the SDL2 development zip into

Credit to https://stackoverflow.com/a/44347594/8505114