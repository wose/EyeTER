cmake_minimum_required(VERSION 2.6)
project(EyeTER)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(wxWidgets_USE_DEBUG TRUE)
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")  

exec_program("git" ${CMAKE_CURRENT_SOURCE_DIR} ARGS "describe --tags" OUTPUT_VARIABLE VERSION )
set( GIT_VERSION ${VERSION} )
configure_file( ${CMAKE_SOURCE_DIR}/src/config.h.cmake ${CMAKE_SOURCE_DIR}/src/config.h )

find_package(OpenGL REQUIRED) 
find_package(OpenCV REQUIRED)

find_package(wxWidgets REQUIRED stc gl aui core base)
include(${wxWidgets_USE_FILE})

message("Building version: ${VERSION}")

add_subdirectory(src)
