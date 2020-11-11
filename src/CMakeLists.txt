file(GLOB_RECURSE PROJ_SOURCES "*.cpp")
list(REMOVE_ITEM PROJ_SOURCES "main.cpp")

add_library(proj_lib STATIC ${PROJ_SOURCES})
target_include_directories(proj_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(game main.cpp)

target_link_libraries(game PUBLIC proj_lib)
target_include_directories(game PUBLIC "${PROJECT_BINARY_DIR}")
