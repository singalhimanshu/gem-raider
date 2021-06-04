find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2 SDL2_ttf)
include_directories(${SDL2_INCLUDE_DIRS})

add_library(
  gem-raider-lib
  tile.cpp
  board.cpp
  game.cpp
  button.cpp
  sdl_util.cpp
  gem-raider/tile.hpp
  gem-raider/constants.hpp
  gem-raider/board.hpp
  gem-raider/game.hpp
  gem-raider/button.hpp
  gem-raider/sdl_util.hpp
)

add_executable(gem-raider main.cpp)
target_link_libraries(
  gem-raider
  PRIVATE project_options
  gem-raider-lib
  PRIVATE ${SDL2_LIBRARIES}
)
