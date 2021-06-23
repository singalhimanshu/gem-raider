cmake_minimum_required(VERSION 3.15)

add_executable(
  gem-raider-test
  board_test.cpp
  button_test.cpp
  game_test.cpp
  sdl_util_test.cpp
  spy_timer.cpp
  gem-raider/spy_timer.hpp
)

target_include_directories(gem-raider-test PRIVATE .)
target_link_libraries(
  gem-raider-test
  gem-raider-lib
  gtest_main
)

add_test(
  NAME gem-raider-test
  COMMAND gem-raider-test
)
