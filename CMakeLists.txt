cmake_minimum_required(VERSION 3.27)
project(Yukon C)

set(CMAKE_C_STANDARD 23)

file (GLOB_RECURSE Yukon_SOURCES CONFIGURE_DEPENDS "src/*.c")
file (GLOB_RECURSE Yukon_HEADERS CONFIGURE_DEPENDS "src/*.h")

set (Yukon_INCLUDE_DIRS "")
foreach (_headerFile ${Yukon_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND Yukon_INCLUDE_DIRS ${_dir})
endforeach()
list (REMOVE_DUPLICATES Yukon_INCLUDE_DIRS)

add_executable(Yukon ${Yukon_SOURCES})
target_include_directories(Yukon PRIVATE ${Yukon_INCLUDE_DIRS})
