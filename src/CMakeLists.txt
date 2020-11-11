file(GLOB_RECURSE SRC_SOURCES "*.cpp")
list(REMOVE_ITEM GAME_SOURCES "main.cpp")

add_library(src_lib STATIC ${SRC_SOURCES})

target_link_libraries(src_lib ${SDL2_LIBRARIES})
target_include_directories(src_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(executable main.cpp)
target_link_libraries(executable PUBLIC src_lib)