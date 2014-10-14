cmake_minimum_required(VERSION 2.8.11)
project(EyeTER)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(COPY ${CMAKE_SOURCE_DIR}/res
  DESTINATION ${CMAKE_BINARY_DIR}
)

find_package(Qt5Widgets)
find_package(OpenGL REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(
    include
)

add_subdirectory(src/libeyeter)
add_subdirectory(src)
