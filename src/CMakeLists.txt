file(GLOB_RECURSE SPACE_SOURCES "*.cpp")
list(REMOVE_ITEM SPACE_SOURCES "main.cpp")
add_library(space_lib STATIC ${SPACE_SOURCES} world/entity/SpaceShip.cpp world/entity/SpaceShip.hpp world/entity/Bullet.cpp world/entity/Bullet.hpp world/entity/Target.cpp world/entity/Target.hpp)

target_link_libraries(space_lib ${SDL2_LIBRARIES})

target_include_directories(space_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(executable main.cpp)

target_link_libraries(executable
        PUBLIC space_lib)

target_include_directories(executable
        PUBLIC "${PROJECT_BINARY_DIR}")
