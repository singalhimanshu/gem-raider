cmake_minimum_required(VERSION 3.15)

add_executable(
  gem-raider-test
  board_test.cpp
)

target_link_libraries(
  gem-raider-test
  gem-raider-lib
  ${SDL2_LIBRARIES}
  gtest_main
)

add_test(
  NAME gem-raider-test
  COMMAND gem-raider-test
)
