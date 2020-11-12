file(GLOB_RECURSE GAME_SOURCES "*.cpp")
list(REMOVE_ITEM GAME_SOURCES "main.cpp")
add_library(game_lib STATIC ${GAME_SOURCES})

target_link_libraries(game_lib ${SDL2_LIBRARIES})

target_include_directories(game_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(game main.cpp)

target_link_libraries(game
        PUBLIC game_lib)

target_include_directories(game
        PUBLIC "${PROJECT_BINARY_DIR}")
