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
  progress_bar.cpp
  game_timer.cpp
  gem-raider/tile.hpp
  gem-raider/constants.hpp
  gem-raider/board.hpp
  gem-raider/game.hpp
  gem-raider/button.hpp
  gem-raider/sdl_util.hpp
  gem-raider/progress_bar.hpp
  gem-raider/timer.hpp
  gem-raider/game_timer.hpp
)

target_include_directories(gem-raider-lib PUBLIC .)

add_executable(gem-raider main.cpp)
target_link_libraries(gem-raider-lib ${SDL2_LIBRARIES})
target_link_libraries(
  gem-raider
  gem-raider-lib
)
