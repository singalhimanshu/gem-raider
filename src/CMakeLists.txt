find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_library(
    gem-raider-lib
    tile.cpp
    board.cpp
    game.cpp
    player.cpp
    gem-raider/tile.hpp
    gem-raider/constants.hpp
    gem-raider/board.hpp
    gem-raider/game.hpp
    gem-raider/player.hpp
)

add_executable(gem-raider main.cpp)
target_link_libraries(
    gem-raider
    PRIVATE project_options
    gem-raider-lib
    ${SDL2_LIBRARIES}
)
