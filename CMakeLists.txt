cmake_minimum_required(VERSION 3.17)
project(LINALG-Space)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(SDL2_DIR "${CMAKE_SOURCE_DIR}/vendor/SDL2-2.0.10")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_subdirectory(src)
