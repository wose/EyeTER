cmake_minimum_required(VERSION 2.6)
project(EyeTER)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(wxWidgets_USE_DEBUG TRUE)
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")  

find_package(OpenGL REQUIRED) 
find_package(OpenCV REQUIRED)

find_package(wxWidgets REQUIRED stc gl aui core base)
include(${wxWidgets_USE_FILE})

add_subdirectory(src)
