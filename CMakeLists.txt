cmake_minimum_required(VERSION 3.27)
project(Yukon C)

set(CMAKE_C_STANDARD 23)

set(Yukon_COMMON_DIRS "src" "src/model" "src/controller")
set(Yukon_GUI_DIRS "src/sdlview" "src/sdlview/nuklear")
set(Yukon_CLI_DIRS "src/cliview")

foreach (_target COMMON GUI CLI)
	foreach (_dir ${Yukon_${_target}_DIRS})
		file(GLOB _files LIST_DIRECTORIES false CONFIGURE_DEPENDS "${_dir}/*.c")
		list(APPEND Yukon_${_target}_SOURCES ${_files})
	endforeach ()
endforeach ()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(YukonGUI ${Yukon_COMMON_SOURCES} ${Yukon_GUI_SOURCES})
add_executable(YukonCLI ${Yukon_COMMON_SOURCES} ${Yukon_CLI_SOURCES})
target_include_directories(YukonGUI PRIVATE ${Yukon_COMMON_DIRS} ${Yukon_GUI_DIRS})
target_include_directories(YukonCLI PRIVATE ${Yukon_COMMON_DIRS} ${Yukon_CLI_DIRS})
target_compile_definitions(YukonCLI PRIVATE USE_CLI)
target_link_options(YukonGUI PRIVATE $<$<CONFIG:Debug>:-mconsole>)

set(SDL2_IMAGE_LIBRARIES SDL2_image::SDL2_image)
set(SDL2_TTF_LIBRARIES SDL2_ttf::SDL2_ttf)
target_include_directories(YukonGUI PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(YukonGUI ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})

# Copy resources
file(COPY src/resource/ DESTINATION "${CMAKE_BINARY_DIR}/resource/")
