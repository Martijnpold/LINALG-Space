file(GLOB_RECURSE LIB_SOURCES "*.cpp")
list(REMOVE_ITEM LIB_SOURCES "main.cpp")

add_library(library STATIC ${LIB_SOURCES})

target_include_directories(library
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(SDL2_DIR "${CMAKE_SOURCE_DIR}/vendor/SDL2-2.0.10")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(executable main.cpp)

target_link_libraries(executable
        PUBLIC library)
